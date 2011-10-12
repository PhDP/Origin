#ifndef MATHS_H_
#define MATHS_H_

// For C++ compilers:
#ifdef __cplusplus
extern "C" {
#endif

/**
 * \brief Compute the hypotenuse \sqrt(a^2 + b^2) without under/overflow.
 *
 * \param a  First length.
 * \param b  Second length.
 * \return   \sqrt(a^2 + b^2).
 */
double hypot(double a, double b);

#ifdef __cplusplus
}
#endif

#endif
