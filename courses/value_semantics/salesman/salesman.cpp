#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <random>
#include "salesman.hpp"

namespace
{
    constexpr double pi = 3.14159265358979323846;
}

namespace hpc
{

/********
 * CITY *
 ********/

city::city(const std::string& name, double longitude, double latitude)
    : m_name(name)
    , m_longitude(longitude)
    , m_latitude(latitude)
{
}

const std::string& city::get_name() const
{
    return m_name;
}

double city::distance(const city& other) const
{
    double x_dist = (m_longitude - other.m_longitude) * 40000. * std::cos(m_latitude - other.m_latitude) * pi / 360. / 360.;
    double y_dist = (m_latitude - other.m_latitude) * 40000. / 360.;
    double dist = std::sqrt(x_dist * x_dist + y_dist * y_dist);
    return dist;
}

double distance(const city& lhs, const city& rhs)
{
    return lhs.distance(rhs);
}

/***********
 * CIRCUIT *
 ***********/

circuit::circuit(size_t size)
    : m_city_list(size, city("uninitialized", 0., 0.))
    , m_fitness(0.)
{
}

size_t circuit::size() const
{
    return m_city_list.size();
}

const city& circuit::get_city(size_t index) const
{
    return m_city_list[index];
}

bool circuit::has_city(const city& c) const
{
    auto iter = std::find_if(m_city_list.begin(), m_city_list.end(),
                             [&c](const city& ct) { return ct.get_name() == c.get_name(); });
    return iter != m_city_list.end();
}

void circuit::set_city(size_t index, const city& c)
{
    m_fitness = 0.;
    m_city_list[index] = c;
}

void circuit::generate(const city_list& cm)
{
    m_city_list = cm;
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(m_city_list.begin(), m_city_list.end(), g);
}

double circuit::get_fitness() const
{
    if (m_fitness == 0.)
    {
        double dist = 0.;
        for (size_t i = 0; i < size() - 1; ++i)
        {
            dist += distance(m_city_list[i], m_city_list[i+1]);
        }
        dist += distance(m_city_list.front(), m_city_list.back());
        m_fitness = 1./dist;
    }
    return m_fitness;
}

double circuit::get_distance() const
{
    return 1./get_fitness();
}

/**************
 * POPULATION *
 **************/

population::population(size_t population_size, size_t circuit_size)
    : m_circuit_list(population_size, circuit(circuit_size))
{
}

population::population(size_t size, const city_list& cl)
    : m_circuit_list(size, circuit(cl.size()))
{
    std::for_each(m_circuit_list.begin(), m_circuit_list.end(),
                  [&cl](auto& c) { c.generate(cl); });
}

size_t population::size() const
{
    return m_circuit_list.size();
}

const circuit& population::get_circuit(size_t index) const
{
    return m_circuit_list[index];
}

void population::save_circuit(size_t index, const circuit& c)
{
    m_circuit_list[index] = c;
}

const circuit& population::get_fittest() const
{
    return *std::max_element(m_circuit_list.begin(), m_circuit_list.end(),
                             [](const circuit& lhs, const circuit& rhs) { return lhs.get_fitness() < rhs.get_fitness(); });
}

/*************
 * ALGORITHM *
 *************/

namespace
{
    size_t random_int(size_t lower, size_t upper)
    {
        static std::random_device rd; // obtain a random number from hardware
        static std::mt19937 gen(rd()); // seed the generator
        std::uniform_int_distribution<size_t> distr(lower, upper); // define the range
        return distr(gen);
    }

    double random_double(double lower, double upper)
    {

        static std::random_device rd; // obtain a random number from hardware
        static std::mt19937 gen(rd()); // seed the generator
        std::uniform_real_distribution<> distr(lower, upper); // define the range
        return distr(gen);
    }
}

genetic_algorithm::genetic_algorithm(size_t tournament_size, double mutation_rate)
    : m_tournament_size(tournament_size)
    , m_mutation_rate(mutation_rate)
{
}

population genetic_algorithm::evolve(const population& pop) const
{
    population res(pop.size(), pop.get_circuit(0).size());
    res.save_circuit(0, pop.get_fittest());

    for (size_t i = 1; i < res.size(); ++i)
    {
        circuit parent1 = select(pop, m_tournament_size);
        circuit parent2 = select(pop, m_tournament_size);
        circuit child = crossover(parent1, parent2);
        mutate(child, m_mutation_rate);
        res.save_circuit(i, child);
    }

    return res;
}

circuit genetic_algorithm::select(const population& pop, size_t tournament_size) const
{
    population tournament(tournament_size, pop.get_circuit(0).size());
    for (size_t i = 0; i < tournament_size; ++i)
    {
        size_t random_idx = random_int(0, pop.size() - 1);
        tournament.save_circuit(i, pop.get_circuit(random_idx));
    }
    return tournament.get_fittest();
}

void genetic_algorithm::mutate(circuit& c, double mutation_rate) const
{
    for (size_t pos1 = 0; pos1 < c.size(); ++pos1)
    {
        double d = random_double(0., 1.);
        if (d < mutation_rate)
        {
            size_t pos2 = random_int(0, c.size() - 1);
            city c1 = c.get_city(pos1);
            city c2 = c.get_city(pos2);
            c.set_city(pos1, c2);
            c.set_city(pos2, c1);
        }
    }
}

circuit genetic_algorithm::crossover(const circuit& parent1, const circuit& parent2) const
{
    circuit child(parent1.size());
    size_t pos1 = random_int(0, child.size() - 1);
    size_t pos2 = random_int(0, child.size() - 1);

    size_t lower = std::min(pos1, pos2);
    size_t upper = std::max(pos1, pos2);

    for (size_t i = lower; i <= upper; ++i)
    {
        child.set_city(i, parent1.get_city(i));
    }

    size_t idx2 = 0u;
    for (size_t i = 0u; i < child.size(); ++i)
    {
        if (i >= lower && i <= upper)
        {
            continue;
        }

        while (child.has_city(parent2.get_city(idx2)))
        {
            ++idx2;
        }
        
        child.set_city(i, parent2.get_city(idx2));
        ++idx2;
    }

    return child;
}

}

