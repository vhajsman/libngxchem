#ifndef __LIBNGXDEV_VECTOR3_HPP
#define __LIBNGXDEV_VECTOR3_HPP

#include <cmath>
namespace ngxchem {
    struct Vector3 {
        double x, y, z;

        constexpr Vector3(): x(0), y(0), z(0) {}
        constexpr Vector3(double x, double y, double z): x(x), y(y), z(z) {}

        constexpr double length() const {
            return std::sqrt(x*x + y*y + z*z);
        }
    };
};

#endif
