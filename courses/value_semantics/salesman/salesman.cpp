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

}

