//name: multiple function template
// write a function once, then it's compatible with different data types = that's function template. With auto keyword the function  return type is automatically detected or deduced by the compiler
#include <iostream>

template <typename T, typename U>

auto max(T x, U y)
{
    return (x > y) ? x : y;
}
int main()
{
    std::cout << "\n\t\t<< Project name: Multiple Function template(Overloaded function) + auto keyword >>\n";

    double x = 13.23;
    double y = 34.55;
    std::cout << "\t\t" << max(x,10) << "\n";

    std::cout << "\n\t\n";
    return 0;
}