#include "oneDimensional.h"

oneDimensional::oneDimensional()
{
    std::cout << "Enter your one-demensional function: " << std::endl;
    getline(std::cin, entered_function, '\n');
    if(entered_function.empty())
        entered_function = "9(x-6)^2+21";

    dichotomyIterationsNumber   = 0;
    goldenIterationsNumber      = 0;
    fibonacciIterationsNumber   = 0;
}

oneDimensional::oneDimensional(std::string input)
{
    dichotomyIterationsNumber   = 0;
    goldenIterationsNumber      = 0;
    fibonacciIterationsNumber   = 0;

    oneDimensional::entered_function = input;
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
    parser.compile(entered_function, expression);
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
        iterationsNumber = goldenIterationsNumber;
        return;
    }
    ++goldenIterationsNumber;        // Следующая итерация

    myFunction(xAlpha) < myFunction(xBetta) ?
                goldenSection(xBetta, b) :
                goldenSection(a, xAlpha);
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
        iterationsNumber = dichotomyIterationsNumber;
        return;
    }
    ++dichotomyIterationsNumber;    // Увеличение счётчика итераций

    myFunction(x1) < myFunction(x2) ?
                dichotomy(a, x2) :
                dichotomy(x1, b);
}

std::vector<double> oneDimensional::getFibonacciNumber(size_t N)
{
    std::vector<double> fibonacciNumber = {1, 1};
    for(size_t i = 1; fibonacciNumber.back() <= N; ++i)
    {
        fibonacciNumber.push_back(fibonacciNumber.at(i - 1) + fibonacciNumber.back());
    }

    return fibonacciNumber;
}

void oneDimensional::fibonacci(double a, double b)
{
    double delta = fabs(b - a);     // Интервал неопределённости
    const double epsilon = 0.001;
    static size_t N_fib = delta / epsilon;
    static std::vector<double> fibonacciNumber = getFibonacciNumber(N_fib);
    size_t N = fibonacciNumber.size() - 2;
    size_t n = fibonacciIterationsNumber;
    double x1 = a + (fibonacciNumber.at(N - n - 1) / fibonacciNumber.at(N - n + 1)) * delta;
    double x2 = a + (fibonacciNumber.at(N - n) / fibonacciNumber.at(N - n + 1)) * delta;

    // Условие останова, вывод результата
    if(n == (N - 1))
    {
        fibonacciMinimum = (a + b) / 2;
        iterationsNumber = fibonacciIterationsNumber;
        return;
    }
    ++fibonacciIterationsNumber;                            // Увеличение счётчика итераций

    myFunction(x1) < myFunction(x2) ?
                fibonacci(a, x2) :
                fibonacci(x1, b);
}

void oneDimensional::getResult(std::string method, double minimumPoint)
{
    std::cout << "Result of the " << method << ":" << std::endl;
    std::cout << "x = " << minimumPoint << std::endl;
    std::cout << "f(x) = "<< myFunction(minimumPoint) << std::endl;
    std::cout << "Number of iterations = " << iterationsNumber << std::endl;
}

double oneDimensional::getGoldenMinimum()
{
    return this->goldenMinimum;
}

double oneDimensional::getDichotomyMinimum()
{
    return this->dichotomyMinimum;
}

double oneDimensional::getFibonacciMinimum()
{
    return this->fibonacciMinimum;
}
