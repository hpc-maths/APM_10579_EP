#ifndef SALESMAN_HPP
#define SALESMAP_HPP

#include <string>
#include <vector>

namespace hpc
{

    /********
     * CITY *
     ********/

    class city
    {
    public:

        city(const std::string& name,
             double longitude,
             double latitude);

        const std::string& get_name() const;
        double distance(const city& other) const;

    private:

        std::string m_name;
        double m_longitude;
        double m_latitude;

    };

    double distance(const city& lhs, const city& rhs);

    /***********
     * CIRCUIT *
     ***********/

    using city_list = std::vector<city>;

    class circuit
    {
    public:

        explicit circuit(size_t size);

        size_t size() const;
        const city& get_city(size_t index) const;
        bool has_city(const city& c) const;
        void set_city(size_t index, const city& c);

        void generate(const city_list& cm);
        double get_fitness() const;
        double get_distance() const;

    private:

        city_list m_city_list;
        mutable double m_fitness;
    };

    /**************
     * POPULATION *
     **************/

    class population
    {
    public:

        population(size_t population_size, size_t circuit_size);
        population(size_t size, const city_list& cl);

        size_t size() const;
        const circuit& get_circuit(size_t index) const;
        void save_circuit(size_t index, const circuit& c);

        const circuit& get_fittest() const;

    private:

        std::vector<circuit> m_circuit_list;
    };

    /*********************
     * GENETIC_ALGORITHM *
     *********************/

    class genetic_algorithm
    {
    public:

        genetic_algorithm(size_t tournament_size,
                          double mutation_rate);

        population evolve(const population& pop) const;

    private:

        circuit select(const population& pop, size_t tournament_size) const;
        void mutate(circuit& c, double mutation_rate) const;
        circuit crossover(const circuit& parent1, const circuit& parent2) const;

        size_t m_tournament_size;
        double m_mutation_rate;
    };
}

#endif
