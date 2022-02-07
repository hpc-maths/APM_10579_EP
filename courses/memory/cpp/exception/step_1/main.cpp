#include <exception>
#include <iostream>
#include "resource.hpp"

int main()
{
    resource r;
    try
    {
        r.acquire();
        r.print_message();
        r.release();
    }
    catch (const std::exception &e)
    {
        std::cout << "coucou " << e.what() << '\n';
        r.release();
    }
}