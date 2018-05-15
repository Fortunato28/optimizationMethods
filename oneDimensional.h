#ifndef oneDimensional_H
#define oneDimensional_H

#include <vector>
#include <iostream>
#include <math.h>
#include "exprtk.hpp"

/*
 * В данном классе реализованы три метода нахождения минимума
 * одномерной функции. При запуске программы будет выведено
 * приглашение ввода функции.
*/
class oneDimensional
{
public:
    oneDimensional();
    void goldenSection(double, double);         // Параметрами являются точки-края интервала поиска минимума
    void dichotomy(double, double);             // Параметрами являются точки-края интервала поиска минимума
    void fibonacci(double, double);
private:
    std::string entered_function;               // Введёная функция
    double myFunction(double);                  // Обработка введённой функции

    double goldenMinimum;                       // Результат золотого сечения
    void goldenMinimumResult();                 // Отображение результата золотого сечения

    double dichotomyMinimum;                    // Результат дихотомии
    void dichotomyMinimumResult();              // Отображение результата дихотомии

    double fibonacciMinimum;                    // Результат метода Фибоначчи
    void fibonacciMinimumResult();              // Отображение результата метода Фибоначчи
};

#endif // oneDimensional_H
