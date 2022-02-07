#include <iostream>
#include "manager.hpp"

manager::manager()
{
    std::cout << "construct manager" << std::endl;
    get_resource().acquire();
}

void manager::print()
{
    std::cout << "hello manager" << std::endl;
    get_resource().acquire();
}

resource& manager::get_resource()
{
    static resource r;
    return r;
}

manager::~manager()
{
    std::cout << "destroy manager" << std::endl;
}