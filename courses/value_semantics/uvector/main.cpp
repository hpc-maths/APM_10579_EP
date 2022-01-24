#include <iostream>
#include "uvector.hpp"

int main(int argc, char* argv[])
{
    hpc::uvector u(4);
    std::cout << u[2] << std::endl;
    return 0;
}
