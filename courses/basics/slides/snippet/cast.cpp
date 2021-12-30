#include <iostream>
#include <vector>
#include <string>

int main()
{
    int a = 1, b = 2;

    std::cout << a/b << " " << static_cast<float>(a)/b << std::endl;
    std::vector<int> c = static_cast<std::vector<int>>(b);
    // std::string *s = static_cast<std::string*>(&b);
    std::string *s = reinterpret_cast<std::string*>(&b);
    std::cout << *s << std::endl;
    return 0;
}