#include "poly2.h"
#include <cmath>
#include <iostream>

Poly2::Poly2(float a, float b, float c)
{
    this->a = a;
    this->b = b;
    this->c = c;
}

float Poly2::eval(float x)
{
    return a * x * x + b * x + c;
}

void Poly2::findRoots()
{
    auto const d = b * b - 4.0f * a * c;
    if (d < 0.0f) {
        std::cout << "Imaginary roots\n";
    } else if (d == 0.0f) {
        auto const x = (-b + std::sqrt(d)) / (2.0f * a);
        std::cout << x << "\n";
    } else {
        auto const sq = std::sqrt(d);
        auto const x1 = (-b + sq) / (2.0f * a);
        auto const x2 = (-b - sq) / (2.0f * a);
        std::cout << x1 << ", " << x2 << "\n";
    }
}

