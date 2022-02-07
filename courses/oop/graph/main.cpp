#include "graph.hpp"
#include <iostream>

hpc::graph build_example()
{
    hpc::graph g;

    hpc::node n0(0);
    n0.add_neighboor(1, 85.);
    n0.add_neighboor(2, 217.);
    n0.add_neighboor(4, 173.);
    g.add_node(n0);

    hpc::node n1(1);
    n1.add_neighboor(5, 80.);
    g.add_node(n1);

    hpc::node n2(2);
    n2.add_neighboor(6, 186.);
    n2.add_neighboor(7, 103.);
    g.add_node(n2);

    hpc::node n3(3);
    g.add_node(n3);

    hpc::node n4(4);
    n4.add_neighboor(9, 502.);
    g.add_node(n4);

    hpc::node n5(5);
    n5.add_neighboor(8, 250.);
    g.add_node(n5);

    hpc::node n6(6);
    g.add_node(n6);

    hpc::node n7(7);
    n7.add_neighboor(3, 183.);
    g.add_node(n7);

    hpc::node n8(8);
    n8.add_neighboor(9, 84.);
    g.add_node(n8);

    hpc::node n9(9);
    g.add_node(n9);

    return g;
}

int main()
{
    auto g = build_example();
    std::list<size_t> path;
    hpc::dijkstra(g, 0, 9, path);
    for(auto iter = path.cbegin(); iter != path.end(); ++iter)
    {
        std::cout << *iter << ", ";
    }
    std::cout << std::endl;

    return 0;
}

