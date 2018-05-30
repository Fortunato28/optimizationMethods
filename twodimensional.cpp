#include "twodimensional.h"

twoDimensional::twoDimensional()
{
    // Выделение памяти под точки и производную
    gradientMinimumPoint.resize(dimensionPoint);
    fastestMinimumPoint.resize(dimensionPoint);
    derivativeF.resize(dimensionPoint);

    // Считывание функции
    std::cout << "Enter your two-dimensional function:" << std::endl;
    getline(std::cin, entered_function, '\n');
    if(entered_function.empty())
        entered_function = "9(x1-6)^2+80(x2-4)^2+21";

    // Считывание производной
    std::cout << "Enter derivative of your two-dimensional function:" << std::endl;
    for(size_t i = 0; i < derivativeF.size(); ++i)
    {
        getline(std::cin, derivativeF.at(i), '\n');
    }
    if(derivativeF.at(0).empty())
        derivativeF.at(0) = "18x1-108";
    if(derivativeF.at(1).empty())
        derivativeF.at(1) = "160x2-640";
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
        double derivativeResult = getFunctionValue(derivativeF.at(i), currentPoint.at(i), currentPoint.at(i));
        result += derivativeResult * derivativeResult;
    }
    return sqrt(result);
}

std::vector<double> twoDimensional::getNextX(std::vector<double>& previousPoint, const double t)
{
    std::vector<double> currentPoint(dimensionPoint);

    for(size_t i = 0; i < dimensionPoint; ++i)
    {
        currentPoint.at(i) = previousPoint.at(i) - t *
                getFunctionValue(derivativeF.at(i), previousPoint.at(i), previousPoint.at(i));
    }

    return currentPoint;
}

void twoDimensional::gradientDescent(const double t, double x, double y)
{
    // Исходные данные
    const double epsilon = 0.001;       // Точность решения
    std::vector<double> x0;             // Начальная точка
    x0.push_back(x);
    x0.push_back(y);
    const size_t N = 50000;             // Общее количество итераций
    size_t n = 0;                       // Счётчик итераций

    std::vector<double> currentPoint(dimensionPoint);
    currentPoint = x0;

    while((vectorLength(currentPoint) > epsilon) && (n < N))
    {
        currentPoint = getNextX(currentPoint, t);
        ++n;
    }
    iterationsNumber = n;
    gradientMinimumPoint = currentPoint;
    gradientDescentResult();
}

void twoDimensional::fastestDescent(double x, double y)
{
    // Исходные данные
    const double epsilon = 0.001;       // Точность решения
    double t = 0;                       // Шаг метода
    const size_t N = 50000;             // Общее количество итераций
    size_t n = 0;                       // Счётчик итераций

    std::vector<double> currentPoint;
    currentPoint.push_back(x);
    currentPoint.push_back(y);

    while((vectorLength(currentPoint) > epsilon) && (n < N))
    {
        std::string func = getOneDimentionalFunc(currentPoint);
        oneDimensional newT(func);
        newT.dichotomy(-100, 100);
        t = newT.getDichotomyMinimum();

        currentPoint = getNextX(currentPoint, t);
        ++n;

    }
    iterationsNumber = n;
    fastestMinimumPoint = currentPoint;
    fastestDescentResult();
}

std::string twoDimensional::getOneDimentionalFunc(std::vector<double>& currentPoint)
{
    std::string result = entered_function;
    std::vector<std::string> x1x2;
    size_t index = 0;                       // Для поиска подстроки
    for(size_t i = 0; i < currentPoint.size(); ++i)
    {
        x1x2.push_back(std::to_string(currentPoint.at(i)) +
            "-x*(" +
            std::to_string(getFunctionValue(derivativeF.at(i), currentPoint.at(i), currentPoint.at(i))) +
            ")");
    }

    // Замена переменных в исходной строке на выражение с x
    index = result.find("x1", index);
    result.replace(index, x1x2.at(0).length(), x1x2.at(0));
    result += entered_function.substr(index + 2);
    index = 0;
    index = result.find("x2", index);
    result.replace(index, x1x2.at(1).length(), x1x2.at(1));
    index = 0;
    index = entered_function.find("x2", index);
    result += entered_function.substr(index + 2);
    return result;
}

void twoDimensional::gradientDescentResult()
{
    std::cout << "Result of the gradient descent method:" << std::endl;
    std::cout << "Point:" << std::endl;
    for(size_t i = 0; i < dimensionPoint; ++i)
        std::cout << gradientMinimumPoint.at(i) << " ";
    std::cout << std::endl;
    std::cout << "F(x1, x2) = " << getFunctionValue(entered_function,
                                                    gradientMinimumPoint.at(0),
                                                    gradientMinimumPoint.at(1)) << std::endl;
    std::cout << "Number of iterations = "<< iterationsNumber << std::endl;
}

void twoDimensional::fastestDescentResult()
{
    std::cout << "Result of the fastest descent method:" << std::endl;
    std::cout << "Point:" << std::endl;
    for(size_t i = 0; i < dimensionPoint; ++i)
        std::cout << fastestMinimumPoint.at(i) << " ";
    std::cout << std::endl;
    std::cout << "F(x1, x2) = " << getFunctionValue(entered_function,
                                                    fastestMinimumPoint.at(0),
                                                    fastestMinimumPoint.at(1)) << std::endl;
    std::cout << "Number of iterations = "<< iterationsNumber << std::endl;
}
