#include <iostream>
#include <vector>
#include "salesman.hpp"

namespace hpc
{
    city_list make_city_list()
    {
        city_list res = {
            {"Clermont-Ferrand", 3.002556, 45.846117},
            {"Bordeaux", -0.644905, 44.896839},
            {"Bayonne", -1.380989, 43.470961},
            {"Toulouse", 1.376579, 43.662010},
            {"Marseille", 5.337151, 43.327276},
            {"Nice", 7.265252, 43.745404},
            {"Nantes", -1.650154, 47.385427},
            {"Rennes", -1.430427, 48.197310},
            {"Paris", 2.414787, 48.953260},
            {"Lille", 3.090447, 50.612962},
            {"Dijon", 5.013054, 47.370547},
            {"Valence", 4.793327, 44.990153},
            {"Aurillac", 2.447746, 44.966838},
            {"Orleans", 1.750115, 47.980822},
            {"Reims", 4.134148, 49.323421},
            {"Strasbourg", 7.506950, 48.580332},
            {"Limoges", 1.233757, 45.865246},
            {"Troyes", 4.047255,48.370925},
            {"Le Havre", 0.103163,49.532415},
            {"Cherbourg", -1.495348, 49.667704},
            {"Brest", -4.494615, 48.447500},
            {"Niort", -0.457140, 46.373545}
        };

        return res;
    }

    void test_genetic()
    {
        size_t generation_number = 100u;
        size_t tournament_size = 5;
        double mutation_rate = 0.015;

        auto l = make_city_list();
        population p(50u, l);

        std::cout << "Initial distance: " << p.get_fittest().get_distance() << std::endl;

        genetic_algorithm ga(tournament_size, mutation_rate);
        for (size_t i = 0; i < generation_number; ++i)
        {
            p = ga.evolve(p);
        }

        std::cout << "Final distance: " << p.get_fittest().get_distance() << std::endl;
    }
}

int main()
{
    hpc::test_genetic();
    return 0;
}

