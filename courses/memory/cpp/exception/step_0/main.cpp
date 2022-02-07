#include "resource.hpp"

int main()
{
    resource r;
    r.acquire();
    r.print_message();
    r.release();
}