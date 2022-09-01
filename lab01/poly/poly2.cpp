#include "poly2.h"
#include <cmath>

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

void Poly2::findRoots(std::int32_t& root_count, float& root_a, float& root_b)
{
    auto const d = b * b - 4.0f * a * c;
    if (d < 0.0f) {
        root_count = 0;
        root_a = NAN;
        root_b = NAN;
    } else if (d == 0.0f) {
        root_count = 1;
        root_a = (-b + std::sqrt(d)) / (2.0f * a);
    } else {
        auto const sq = std::sqrt(d);
        root_count = 2;
        root_a = (-b - sq) / (2.0f * a);
        root_b = (-b + sq) / (2.0f * a);
    }
}

