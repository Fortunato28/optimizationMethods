#include <iostream>
#include "oneDimensional.h"
#include "twodimensional.h"

int main()
{
    oneDimensional first;
    first.goldenSection(-100, 100);
    first.dichotomy(-100, 100);
    first.fibonacci(-10, 10);

    twoDimensional second;
    second.gradientDescent(0.01, -10, 10);

    return 0;
}
