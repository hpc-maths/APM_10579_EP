#include "graph.hpp"
#include <limits>
#include <queue>

namespace hpc
{

node::node(size_t id)
    : m_id(id)
{
}

size_t node::get_id() const
{
    return m_id;
}

void node::add_neighboor(size_t id, double distance)
{
    m_neighboor_list.push_back(std::make_pair(id, distance));
}

//const node::neighboor_list& node::get_neighboors() const
auto node::get_neighboors() const -> const neighboor_list&
{
    return m_neighboor_list;
}


void graph::add_node(const node& n)
{
    m_node_list.push_back(n);
}

auto graph::get_nodes() const -> const node_list& 
{
    return m_node_list;
}

namespace
{
    struct comp
    {
        using neighboor = node::neighboor;
        bool operator()(const neighboor& lhs, const neighboor& rhs) const
        {
            return lhs.second > rhs.second;
        }
    };
}

void dijkstra(const graph& g, size_t start, size_t end, std::list<size_t>& path)
{
    using neighboor = node::neighboor;
    using neighboor_list = node::neighboor_list;
    using queue_type = std::priority_queue<neighboor, neighboor_list, comp>;

    size_t node_nb = g.get_nodes().size();
    std::vector<size_t> previous(node_nb);
    std::vector<double> dist(node_nb, std::numeric_limits<double>::infinity());
    dist[start] = 0.;

    queue_type q;
    q.push(neighboor(start, 0));

    while (!q.empty())
    {
        size_t n = q.top().first;
        double d = q.top().second;
        q.pop();

        if (n == end)
        {
            break;
        }

        if (dist[n] < d)
        {
            continue;
        }

        const auto& neighboors = g.get_nodes()[n].get_neighboors();
        for (size_t i = 0; i < neighboors.size(); ++i)
        {
            size_t u = neighboors[i].first;
            double ud = neighboors[i].second;
            if (dist[u] > dist[n] + ud)
            {
                dist[u] = dist[n] + ud;
                q.push(neighboor(u, dist[u]));
                previous[u] = n;
            }
        }
    }

    size_t n = end;
    while(n != start)
    {
        path.push_front(n);
        n = previous[n];
    }
}

}




void function()
{
    uvector<double>* p = new uvector(50);

    <=> void* d = malloc(sizeof(uvector<double>));
    uvector<double>* p = uvector::uvector(d, 50);
    /// ..;
    //
    delete p;
    <=> p.~uvector();
    free(p);
}

#include <cstddef>



int main()
{
    hpc::uvector v2(50);
    hpc::uvector v1 = v2;
    return 0;
}
