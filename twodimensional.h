#ifndef TWODIMENSIONAL_H
#define TWODIMENSIONAL_H

#include <vector>
#include <iostream>
#include <math.h>
#include "exprtk.hpp"
#include "oneDimensional.h"
#include <string>

using std::cout;
using std::endl;

/*
 * В данном классе реализованы два метода нахождения минимума
 * двумерной функции. При запуске программы будет выведено
 * приглашение ввода функции.
*/
class twoDimensional
{
public:
    twoDimensional();
    void gradientDescent(const double, double, double);     // Параметрами являются шаг метода и начальная точка
    void fastestDescent(double, double);                    // Параметрами являются точки-края интервала поиска минимума
private:
    static const size_t dimensionPoint = 2;                 // Количество координат у каждой точки
    std::string entered_function;                           // Введёная функция
    double getFunctionValue(std::string,
                            double, double);                // Обработка введённой функции
    std::vector<std::string> derivativeF;                   // Вектор частных производных

    size_t iterationsNumber;                                // Общее число итераций
    std::vector<double> gradientMinimumPoint;               // Результат градиентного спуска
    double vectorLength(std::vector<double>&);              // Вычисление длины вектора
    std::vector<double> getNextX(std::vector<double>&,
                                 const double);             // Получение следующей точки
    void gradientDescentResult();                           // Отображение результата градиентного спуска

    std::vector<double> fastestMinimumPoint;                // Результат наискорейшего спуска
    std::string getOneDimentionalFunc(std::vector<double>&); // Получение одномерной функции для нахождения шага
    void fastestDescentResult();                            // Отображение результата наискорейшего спуска
};

#endif // TWODIMENSIONAL_H
