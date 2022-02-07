#include <iostream>
#include "manager.hpp"

manager::manager()
{
    std::cout << "construct manager" << std::endl;
    m_r.acquire();
}

void manager::print()
{
    std::cout << "hello manager" << std::endl;
    m_r.acquire();
}

manager::~manager()
{
    std::cout << "destroy manager" << std::endl;
}

resource manager::m_r{};