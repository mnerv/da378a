#ifndef LAB01_POLY2_H
#define LAB01_POLY2_H
#include <cstdint>

class Poly2
{
public:

    /*
     * Constructor
     */
    Poly2(float a, float b, float c);

    /*
     * Evaluate y(x)
     */
    float eval(float x);

    /*
     * Find roots, i.e. x when y(x) = 0
     */
    void findRoots(std::int32_t& root_count, float& root_a, float& root_b);

    /*
     * Destructor:
     * not needed since no dynamic memory has been allocated,
     */

private:
    float a, b, c;
};

#endif  // LAB01_POLY2_H

