#include <string>
#include <vector>

#include "temp_t.hpp"

namespace ngxchem {
    enum class ElementTableBlock { S, P, D, F };
    enum class ElementState { STATE_GAS, STATE_FLUID, STATE_SOLID };

    struct Element {
        // --- IDENTIFICATION ---
        std::string symbol;      // chemical symbol, e.g. "H" for Hydrogen
        std::string name;        // full element name, e.g. "Hydrogen"

        // --- BASIC PROPERTIES ---
        int atomicNumber;        // number of protons, e.g. 1 for H
        double atomicMass;       // atomic mass [g/mol]
        int period;              // period in periodic table
        int group;               // group in periodic table

        // --- ATOMIC RADII ---
        double atomicRadius;     // atomic radius [pm]
        double covalentRadius;   // covalent radius [pm]
        double vdwRadius;        // van der Waals radius [pm]
        double vdwScale;         // scaling factor for visualization

        // --- CHEMICAL PROPERTIES ---
        bool isMetal;            // true if element is a metal
        bool isNobleGas;         // true if element is a noble gas
        bool isRadioactive;      // true if element is radioactive
        Temp stdStateTemp;       // standard state temperature [K]
        ElementState stdState;   // standard state (gas, fluid, solid)
        double polarizability;   // polarizability [Å³], for pharm simulations
        double refractiveIndex;  // refractive index, for optical simulations

        // --- ELECTRONIC PROPERTIES ---
        double electronegativity;       // Pauling electronegativity
        std::vector<int> valence;       // possible oxidation states
        double firstIonizationEnergy;   // first ionization energy [eV]
        double electronAffinity;        // electron affinity [eV]

        // --- PHYSICAL PROPERTIES ---
        Temp meltingPoint;              // melting point [K]
        Temp boilingPoint;              // boiling point [K]
        double density;                 // density [g/cm³]
    };
};
