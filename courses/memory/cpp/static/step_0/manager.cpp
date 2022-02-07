#include <iostream>
#include "manager.hpp"
#include "resource.hpp"

manager::manager()
{
    std::cout << "construct manager" << std::endl;
    r.acquire();
}

manager::~manager()
{
    std::cout << "destroy manager" << std::endl;
}
