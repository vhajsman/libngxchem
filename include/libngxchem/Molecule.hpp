#ifndef __LIBNGXCHEM_MOLECULE_HPP
#define __LIBNGXCHEM_MOLECULE_HPP

#include "Atom.hpp"
#include "Vector3.hpp"

#include <stdexcept>
#include <vector>
#include <string>

namespace ngxchem {
    struct Molecule {
        std::string name;
        std::vector<ngxchem::Atom> atoms;
        std::vector<ngxchem::Bond> bonds;

        double totalMass() const {
            double m = 0.00;
            for(const auto& atom_curr: this->atoms)
                m += atom_curr.calcMass();

            return m;
        }

        Vector3 massCenter() const {
            Vector3 sum = {0.00, 0.00, 0.00};
            double m = 0.00;
            for(const auto& atom_curr : this->atoms) {
                sum = sum + atom_curr.position * atom_curr.calcMass();
                m += atom_curr.calcMass();
            }

            return sum / m;
        }

        double distance(int i, int j) const {
            if(i < 0 || j < 0 || i >= this->atoms.size() || j >= this->atoms.size())
                throw std::out_of_range("atom index out of range in ngxchem::Molecule::distance()");

            return (this->atoms[i].position - this->atoms[j].position).length();
        }
    };
};

#endif
