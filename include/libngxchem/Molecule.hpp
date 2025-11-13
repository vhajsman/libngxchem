#ifndef __LIBNGXCHEM_MOLECULE_HPP
#define __LIBNGXCHEM_MOLECULE_HPP

#include "Atom.hpp"
#include "Vector3.hpp"

#include <stdexcept>
#include <vector>
#include <string>

namespace ngxchem {
    /**
     * @struct Molecule
     * @brief Represents a chemical molecule composed of atoms and their bonds.
     * 
     * The Molecule structure holds atom and bond data, providing 
     * basic physical computations such as total mass, center of mass, 
     * and interatomic distances.
     */
    struct Molecule {
        std::string name;                   // molecule name (e.g. "H2O", "C2H5OH")
        std::vector<ngxchem::Atom> atoms;   // list of atoms that form the molecule
        std::vector<ngxchem::Bond> bonds;   // list of bonds connecting the atoms

        /**
         * @brief Compute the total molecular mass.
         * 
         * @return Total mass in kilograms [kg].
         */
        double totalMass() const {
            double m = 0.00;
            for(const auto& atom_curr: this->atoms)
                m += atom_curr.calcMass();

            return m;
        }

        /**
         * @brief Compute the molecule's center of mass.
         * 
         * Uses mass-weighted averaging of atom positions.
         * 
         * @return Center of mass vector [m].
         */
        Vector3 massCenter() const {
            Vector3 sum = {0.00, 0.00, 0.00};
            double m = 0.00;
            for(const auto& atom_curr : this->atoms) {
                sum = sum + atom_curr.position * atom_curr.calcMass();
                m += atom_curr.calcMass();
            }

            return sum / m;
        }

        /**
         * @brief Compute the distance between two atoms in the molecule.
         * 
         * @param i Index of the first atom.
         * @param j Index of the second atom.
         * @throws std::out_of_range if atom indices are invalid.
         * @return Distance between atoms [m].
         */
        double distance(int i, int j) const {
            if(i < 0 || j < 0 || i >= this->atoms.size() || j >= this->atoms.size())
                throw std::out_of_range("atom index out of range in ngxchem::Molecule::distance()");

            return (this->atoms[i].position - this->atoms[j].position).length();
        }
    };
};

#endif
