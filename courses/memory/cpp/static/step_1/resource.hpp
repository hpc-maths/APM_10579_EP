#pragma once

#include <string>

class resource
{
public:
    resource();
    void acquire();
    ~resource();

private:
    std::size_t m_count=0;
};

static resource r;
