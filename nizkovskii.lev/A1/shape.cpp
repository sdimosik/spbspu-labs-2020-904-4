#include "shape.hpp"
#include <cstdlib>
#include <iostream>

std::ostream& operator<<(std::ostream& out, const Shape& shape)
{
    if (out.good())
    {
        shape.print(out);
    }
    else
    {
        std::cerr << "Out Incorrect\n";
    }
    return out;
}
