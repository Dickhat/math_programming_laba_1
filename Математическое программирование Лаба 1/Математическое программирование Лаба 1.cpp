﻿#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

//Исходная функция Вариант 1
double function(double x1, double x2, double x3);

double dx1(double x1, double x2, double x3);
double dx2(double x1, double x2, double x3);
double dx3(double x1, double x2, double x3);

//Градиент
struct grad
{
    double dx1;
    double dx2;
    double dx3;
};

//Одномерная минимизация для поиска шага с помощью метода половинного деления
double step_compute(double x1, double x2, double x3, grad gradient, double step);

int main()
{
    setlocale(LC_ALL, "RUSSIAN");

    //Вектор направлений
    double p1;
    double p2;
    double p3;

    //Предыдущий вектор направлений
    double pred_p1 = 0;
    double pred_p2 = 0;
    double pred_p3 = 0;

    //Точность вычислений
    double eps = 0.001;

    //Итерация
    int iteration = 0;

    //Шаг
    double step = 0.1;

    //Стационарная точка
    double x1 = -0.27;
    double x2 = -1.618;
    double x3 = 0.404;

    //Предыдущее значение функции
    double predFun = function(x1, x2, x3);

    grad gradient = {0, 0, 0};
    double pred_gradient;

    //Вычисление частных производных для градиента
    gradient.dx1 = dx1(x1, x2, x3);
    gradient.dx2 = dx2(x1, x2, x3);
    gradient.dx3 = dx3(x1, x2, x3);

    cout << setw(11) << left << " Итерация" << setw(12) << left << "x1 " << setw(12) << left << "x2 " << setw(12) << left << "x3 " 
         << setw(16) << left << "gradF(x^k) " << setw(12) << left << " F(x^k)" << setw(12) << left << " Шаг \n" << endl;

    //Нормированный градиент
    double norm_grad = sqrt(pow(gradient.dx1, 2) + pow(gradient.dx2, 2) + pow(gradient.dx3, 2));

    pred_gradient = norm_grad;
    p1 = -gradient.dx1 / norm_grad;
    p2 = -gradient.dx2 / norm_grad;
    p3 = -gradient.dx3 / norm_grad;

    //while Проверка, что необходимая точность не получена
    while (norm_grad > eps)
    {
        //Вектор направлений
        p1 = -gradient.dx1 + pow(norm_grad, 2) / pow(pred_gradient, 2) * pred_p1;
        p2 = -gradient.dx2 + pow(norm_grad, 2) / pow(pred_gradient, 2) * pred_p2;
        p3 = -gradient.dx3 + pow(norm_grad, 2) / pow(pred_gradient, 2) * pred_p3;

        //Предыдущий вектор направлений
        pred_p1 = p1;
        pred_p2 = p2;
        pred_p3 = p3;

        pred_gradient = norm_grad;

        if (predFun < function(x1, x2, x3))
            step = step_compute(x1, x2, x3, gradient, step);

        x1 = x1 + step * p1;
        x2 = x2 + step * p2;
        x3 = x3 + step * p3;

        gradient.dx1 = dx1(x1, x2, x3);
        gradient.dx2 = dx1(x1, x2, x3);
        gradient.dx3 = dx1(x1, x2, x3);

        norm_grad = sqrt(pow(gradient.dx1, 2) + pow(gradient.dx2, 2) + pow(gradient.dx3, 2));

        cout << " " << setw(10) << left << iteration << setw(12) << left << x1 << setw(12) << left << x2 << setw(12) << left << x3
             << setw(16) << left<< norm_grad << setw(12) << left << function(x1, x2, x3) << setw(12) << left << step << endl;

        iteration++;
    }

    cout << "\n Точка экстремума: (" << x1 << ", " << x2 << ", " << x3 << ")\n";
}

//Возвращает исходную функцию
double function(double x1, double x2, double x3)
{
    return (3 * x1 * x1) + (2 * x2 * x2) + (x3 * x3) - (x1 * x2 + x2 * x3 / 2) + (6 * x2);
}

//Производная f/x1
double dx1(double x1, double x2, double x3)
{
    return 6 * x1 - x2;
}

//Производная f/x2
double dx2(double x1, double x2, double x3)
{
    return 4 * x2 - x1 + x3 / 2 + 6;
}

//Производная f/x3
double dx3(double x1, double x2, double x3)
{
    return 2*x3+x2/2;
}

//Одномерная минимизация для поиска шага с помощью метода половинного деления
double step_compute(double x1, double x2, double x3, grad gradient, double step)
{
    //Иксы для левой стороны
    double left_X1; 
    double left_X2;
    double left_X3;

    //Иксы для правой стороны
    double right_X1;
    double right_X2;
    double right_X3;

    //Границы отрезка для шага [0.1, 0.5]
    double a = 0.0001, b = step;
    double eps = 0.01;
    double left_side;
    double right_side;

    //Нормированный градиент
    double norm_grad = sqrt(pow(gradient.dx1, 2) + pow(gradient.dx2, 2) + pow(gradient.dx3, 2));

    //while Точность вычислений
    while ((b - a) > 0.05)
    {
        //Левая и правая стороны отрезка
        left_side = (a + b) / 2 - eps;
        right_side = (a + b) / 2 + eps;

        //Значения иксов для левой стороны отрезка
        left_X1 = x1 + left_side * (-gradient.dx1) / norm_grad;
        left_X2 = x2 + left_side * (-gradient.dx2) / norm_grad;
        left_X3 = x3 + left_side * (-gradient.dx3) / norm_grad;

        //Значения иксов для правой стороны отрезка
        right_X1 = x1 + right_side * (-gradient.dx1) / norm_grad;
        right_X2 = x2 + right_side * (-gradient.dx2) / norm_grad;
        right_X3 = x3 + right_side * (-gradient.dx3) / norm_grad;

        //if Проверка на выбор сокращения интервала
        if (function(left_X1, left_X2, left_X3) > function(right_X1, right_X2, right_X3))
        {
            a = left_side;
        }
        else if (function(left_X1, left_X2, left_X3) < function(right_X1, right_X2, right_X3))
        {
            b = right_side;
        }
        else
        {
            a = left_side;
            b = right_side;
        }
    }

    //Возврат шага
    return (a + b)/ 2;
}