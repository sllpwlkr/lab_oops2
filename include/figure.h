#pragma once

#include <iostream>
#include <string>
#include <cmath>
#include <algorithm>
#include "point.h"

using namespace std;


template <typename T>
class Figure{
    public:
        //объявление  функции
        Figure() = default; 
        //объявление виртуальной функции. функция не должна изменять состояние объекта => нужно объявить её const.
        virtual T square() const = 0;
        virtual Point<T> center() const = 0;

        virtual operator T() const = 0;
        //деструктор
        ~Figure() = default; 
};