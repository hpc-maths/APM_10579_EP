#ifndef RESOURCE_HPP
#define RESOURCE_HPP

struct resource
{
    void acquire();
    void release();
    void print_message();
};

class resource_guard
{
public:
    resource_guard(resource &r);
    ~resource_guard();

private:
    resource &m_r;
};
#endif