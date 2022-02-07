#include <exception>
#include <iostream>
#include "resource.hpp"

int main()
{
    resource r;
    resource_guard g(r);
    r.print_message();
}