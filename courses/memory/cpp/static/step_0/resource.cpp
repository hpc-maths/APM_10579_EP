#include <iostream>
#include "resource.hpp"

resource::resource()
{
    std::cout << "resource constructor" <<  std::endl;
}

void resource::acquire()
{
    std::cout << "resource acquire: " << m_count++ << std::endl;
}

resource::~resource()
{
    std::cout << "resource destructor" << std::endl;
}

resource r;