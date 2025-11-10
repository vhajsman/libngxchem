#ifndef __LIBNGXCHEM_TEMP_T_HPP
#define __LIBNGXCHEM_TEMP_T_HPP

namespace ngxchem {
    struct Temp {
        double K;   // kelvin
        
        constexpr Temp(): K(0.0) {}
        constexpr Temp(double kelvin): K(kelvin) {}

        Temp& operator=(const Temp& other) {
            K = other.K;
            return *this;
        }

        Temp& operator=(double kelvin) {
            K = kelvin;
            return *this;
        }

        constexpr Temp operator+(const Temp& other)     const { return Temp(K + other.K); }
        constexpr Temp operator-(const Temp& other)     const { return Temp(K - other.K); }
        constexpr Temp& operator+=(const Temp& other)         { K += other.K; return *this; }
        constexpr Temp& operator-=(const Temp& other)         { K -= other.K; return *this; }

        constexpr double toCelsius() const {
            return this->K - 273.15;
        }

        constexpr double toEnergyParticle() const {
            constexpr double kB = 1.380649e-23;
            return this->K * kB;
        }

        constexpr double toEnergyMol() const {
            constexpr double R = 8.314462618;
            return this->K * R;
        }
    };

    constexpr Temp TEMP_MIN(0.0);
};

#endif
