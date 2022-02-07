#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <list>
#include <vector>
#include <utility>

namespace hpc
{
    class node
    {
    public:

        using neighboor = std::pair<size_t, double>;
        using neighboor_list = std::vector<neighboor>;

        explicit node(size_t id);

        size_t get_id() const;
        void add_neighboor(size_t id, double distance);
        const neighboor_list& get_neighboors() const;

    private:

        size_t m_id;
        neighboor_list m_neighboor_list;
    };

    class graph
    {
    public:

        using node_list = std::vector<node>;

        void add_node(const node& n);
        const node_list& get_nodes() const;

    private:

        node_list m_node_list;
    };

    void dijkstra(const graph& g, size_t start, size_t end, std::list<size_t>& path);
}

#endif
