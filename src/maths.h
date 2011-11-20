#ifndef MATHS_H_
#define MATHS_H_

// For C++ compilers:
#ifdef __cplusplus
extern "C" {
#endif

/** Compute \sqrt(a^2 + b^2) without under/overflow. */
double hypot(double a, double b);

#ifdef __cplusplus
}
#endif

#endif
