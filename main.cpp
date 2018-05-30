#include <iostream>
#include "oneDimensional.h"
#include "twodimensional.h"

int main()
{
    oneDimensional first;
    first.goldenSection(-100, 100);
    first.getResult("golden section", first.getGoldenMinimum());
    first.dichotomy(-100, 100);
    first.getResult("dichotomy", first.getDichotomyMinimum());
    first.fibonacci(-100, 100);
    first.getResult("fibonacci method", first.getFibonacciMinimum());

    twoDimensional second;
    second.gradientDescent(0.01, -100, 100);
    second.fastestDescent(-100, 100);

    return 0;
}
