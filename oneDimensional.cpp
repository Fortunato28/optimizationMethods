#include "oneDimensional.h"

oneDimensional::oneDimensional()
{
    std::cout << "Enter your one-demensional function: " << std::endl;
    getline(std::cin, entered_function, '\n');
    if(oneDimensional::entered_function.empty())
        oneDimensional::entered_function = "9(x-6)^2+21";
}

double oneDimensional::myFunction(double x)
{
    typedef exprtk::symbol_table<double> symbol_table_t;
    typedef exprtk::expression<double> expression_t;
    typedef exprtk::parser<double> parser_t;

    symbol_table_t symbol_table;
    symbol_table.add_variable("x", x);
    symbol_table.add_constants();

    expression_t expression;
    expression.register_symbol_table(symbol_table);

    parser_t parser;
    parser.compile(oneDimensional::entered_function, expression);
    return expression.value();
}

void oneDimensional::goldenSection(double a, double b)
{
    const double alpha = 0.618;     // Константа золотого сечения
    const double epsilon = 0.001;   // Условие останова
    double delta = fabs(b - a);     // Интервал неопределённости
    double xAlpha = a + alpha * delta;
    double xBetta = b - alpha * delta;

    // Условие останова, вывод результата
    if(delta < epsilon)
    {
        goldenMinimum = (a + b) / 2;
        goldenMinimumResult();
        return;
    }

    myFunction(xAlpha) < myFunction(xBetta) ?
                oneDimensional::goldenSection(xBetta, b) :
                oneDimensional::goldenSection(a, xAlpha);
}

void oneDimensional::dichotomy(double a, double b)
{
    const double sigma = 0.0005;    // Шаг приращения
    const double epsilon = 0.001;   // Условие останова
    double delta = fabs(b - a);     // Интервал неопределённости
    double x1 = (a + b - sigma) / 2;
    double x2 = (a + b + sigma) / 2;

    // Условие останова, вывод результата
    if(delta < epsilon)
    {
        dichotomyMinimum = (a + b) / 2;
        dichotomyMinimumResult();
        return;
    }

    myFunction(x1) < myFunction(x2) ?
                oneDimensional::dichotomy(a, x2) :
                oneDimensional::dichotomy(x1, b);
}

void oneDimensional::fibonacci(double a, double b)
{
    double delta = fabs(b - a);     // Интервал неопределённости
    size_t n = 10;                  // Количество итераций
    std::vector<double> fibonacciNumber = {1, 1, 2, 3, 5, 8, 13,
                                           21, 34, 55, 89, 144};
    static size_t i = 0;            // Номер текущей итерации и её приращение
    ++i;
    double x1 = a + (fibonacciNumber.at(n - i - 1) / fibonacciNumber.at(n - i + 1)) * delta;
    double x2 = a + (fibonacciNumber.at(n - i) / fibonacciNumber.at(n - i + 1)) * delta;

    // Условие останова, вывод результата
    if(i == (n - 1))
    {
        fibonacciMinimum = (a + b) / 2;
        fibonacciMinimumResult();
        return;
    }

    myFunction(x1) < myFunction(x2) ?
                oneDimensional::fibonacci(a, x2) :
                oneDimensional::fibonacci(x1, b);
}

void oneDimensional::goldenMinimumResult()
{
    std::cout << "Result of the golden section method:" << std::endl;
    std::cout << "x = " << oneDimensional::goldenMinimum << std::endl;
    std::cout << "f(x) = "<<oneDimensional::myFunction(goldenMinimum) << std::endl;
}

void oneDimensional::dichotomyMinimumResult()
{
    std::cout << "Result of the dichotomy:" << std::endl;
    std::cout << "x = " << oneDimensional::dichotomyMinimum << std::endl;
    std::cout << "f(x) = "<<oneDimensional::myFunction(dichotomyMinimum) << std::endl;
}

void oneDimensional::fibonacciMinimumResult()
{
    std::cout << "Result of the Fibonacci method:" << std::endl;
    std::cout << "x = " << oneDimensional::fibonacciMinimum << std::endl;
    std::cout << "f(x) = "<<oneDimensional::myFunction(fibonacciMinimum) << std::endl;
}
