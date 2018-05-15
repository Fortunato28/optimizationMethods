#include "twodimensional.h"

twoDimensional::twoDimensional()
{
    // Выделение памяти под точки и производную
    twoDimensional::gradientMinimumPoint.resize(twoDimensional::dimensionPoint);
    twoDimensional::fastestMinimumPoint.resize(twoDimensional::dimensionPoint);
    twoDimensional::derivativeF.resize(twoDimensional::dimensionPoint);

    // Считывание функции
    std::cout << "Enter your two-dimensional function:" << std::endl;
    getline(std::cin, twoDimensional::entered_function, '\n');
    if(twoDimensional::entered_function.empty())
        twoDimensional::entered_function = "9(x1-6)^2+80(x2-4)^2+21";

    // Считывание производной
    std::cout << "Enter derivative of your two-dimensional function:" << std::endl;
    for(size_t i = 0; i < twoDimensional::derivativeF.size(); ++i)
    {
        getline(std::cin, twoDimensional::derivativeF.at(i), '\n');
    }
    if(twoDimensional::derivativeF.at(0).empty())
        twoDimensional::derivativeF.at(0) = "18x1-108";
    if(twoDimensional::derivativeF.at(1).empty())
        twoDimensional::derivativeF.at(1) = "160x2-640";
}

double twoDimensional::getFunctionValue(std::string function, double x1, double x2)
{
    typedef exprtk::symbol_table<double> symbol_table_t;
    typedef exprtk::expression<double> expression_t;
    typedef exprtk::parser<double> parser_t;

    symbol_table_t symbol_table;
    symbol_table.add_variable("x1", x1);
    symbol_table.add_variable("x2", x2);
    symbol_table.add_constants();

    expression_t expression;
    expression.register_symbol_table(symbol_table);

    parser_t parser;
    parser.compile(function, expression);

    return expression.value();
}

double twoDimensional::vectorLength(std::vector<double>& currentPoint)
{
    double result = 0;

    for(size_t i = 0; i < currentPoint.size(); ++i)
    {
        double derivativeResult = getFunctionValue(twoDimensional::derivativeF.at(i), currentPoint.at(i), currentPoint.at(i));
        result += derivativeResult * derivativeResult;
    }
    return sqrt(result);
}

std::vector<double> twoDimensional::getNextX(std::vector<double>& previousPoint, const double t)
{
    std::vector<double> currentPoint(twoDimensional::dimensionPoint);

    for(size_t i = 0; i < twoDimensional::dimensionPoint; ++i)
    {
        currentPoint.at(i) = previousPoint.at(i) - t *
                twoDimensional::getFunctionValue(twoDimensional::derivativeF.at(i), previousPoint.at(i), previousPoint.at(i));
    }

    return currentPoint;
}

void twoDimensional::gradientDescent(double t, double x, double y)
{
    // Исходные данные
    const double epsilon = 0.001;       // Точность решения
    std::vector<double> x0;             // Начальная точка
    x0.push_back(x);
    x0.push_back(y);
    const size_t N = 50000;             // Общее количество итераций
    size_t n = 0;                       // Счётчик итераций

    std::vector<double> currentPoint(twoDimensional::dimensionPoint);
    currentPoint = x0;

    while((twoDimensional::vectorLength(currentPoint) > epsilon) && (n < N))
    {
        currentPoint = twoDimensional::getNextX(currentPoint, t);
        ++n;
    }
    twoDimensional::iterationsNumber = n;
    twoDimensional::gradientMinimumPoint = currentPoint;
    twoDimensional::gradientDescentResult();
}

void twoDimensional::fastestDescent(double, double)
{

}

void twoDimensional::gradientDescentResult()
{
    std::cout << "Result of the gradient descent method:" << std::endl;
    std::cout << "Point:" << std::endl;
    for(size_t i = 0; i < twoDimensional::dimensionPoint; ++i)
        std::cout << twoDimensional::gradientMinimumPoint.at(i) << " ";
    std::cout << std::endl;
    std::cout << "F(x1, x2) = " << twoDimensional::getFunctionValue(twoDimensional::entered_function,
                                                                    twoDimensional::gradientMinimumPoint.at(0),
                                                                    twoDimensional::gradientMinimumPoint.at(1)) << std::endl;
    std::cout << "Number of iterations = "<< twoDimensional::iterationsNumber << std::endl;
}

void twoDimensional::fastestDescentResult()
{

}
