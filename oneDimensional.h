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
    oneDimensional(std::string);
    void    goldenSection(double, double);         // Параметрами являются точки-края интервала поиска минимума
    void    dichotomy(double, double);             // Параметрами являются точки-края интервала поиска минимума
    void    fibonacci(double, double);

    void    getResult(std::string, double);        // Вывод результата метода
    double  getGoldenMinimum();
    double  getDichotomyMinimum();
    double  getFibonacciMinimum();
private:
    size_t iterationsNumber;                    // Количество итераций последнего отработавшего метода

    std::string entered_function;               // Введёная функция
    double myFunction(double);                  // Обработка введённой функции

    double goldenMinimum;                       // Результат золотого сечения
    size_t goldenIterationsNumber;

    double dichotomyMinimum;                    // Результат дихотомии
    size_t dichotomyIterationsNumber;

    double fibonacciMinimum;                    // Результат метода Фибоначчи
    size_t fibonacciIterationsNumber;
    std::vector<double> getFibonacciNumber(size_t);               // Вычисление количества итераций для метода Фибоначчи
};

#endif // oneDimensional_H
