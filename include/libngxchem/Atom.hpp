#ifndef __LIBNGXCHEM_ATOM_HPP
#define __LIBNGXCHEM_ATOM_HPP

#include "ElementClass.hpp"
#include "Vector3.hpp"
#include "temp_t.hpp"

namespace ngxchem {
    /**
     * @enum ElCharge
     * @brief Atomic charge type
     * 
     * CATION: +1, ANION: -1, NEUTRAL: 0
     */
    typedef enum {
        CATION = 1,
        ANION = -1,
        NEUTRAL = 0
    } ElCharge;

    struct Atom {
        const Element*  element;            // pointer to base chemical element
        Vector3         position;           // 3D position in meters [m]
        Vector3         velocity;           // 3D velocity in meters per second [m/s]
        ElCharge        charge;             // atomic charge
        double          qspin;              // quantum spin, arbitrary units
        double          energy_kinetic;     // kinetic energy [J]
        double          energy_potential;   // potential energy [J]

        int             valence_electrons;  // count of valence electrons
        int             valence_max;        // maximal chemical bound count
        int             bonds_count;        // current count of bounds

        Temp            sim_temp;

        /**
         * @brief default constructor
         * initializes atom with neutral charge, zero velocity and energy and a null element
         */
        constexpr Atom()
            : element(nullptr), position(), velocity(), charge(NEUTRAL), qspin(0.00), sim_temp(), energy_kinetic(0.00), energy_potential(0), valence_electrons(0), valence_max(0), bonds_count(0) {}
        
        /**
         * @brief construct an atom with specific element, position, velocity and charge
         * 
         * @param el pointer to element
         * @param pos initial position (defaults to zero vector)
         * @param vel initial velocity (defaults to zero vector)
         * @param q charge type (default NEUTRAL)
         */
        constexpr Atom(const Element* el, Vector3 pos = {}, Vector3 vel = {}, ElCharge q = NEUTRAL)
            : element(el), position(pos), velocity(vel), charge(q), qspin(0), sim_temp(0), energy_kinetic(0), energy_potential(0), valence_electrons(el ? el->group : 0), valence_max(el ? el->group : 0), bonds_count(0) {}

        /**
         * @brief calculate mass of the atom in kilograms
         * 
         * @return mass in kg
         */
        constexpr double calcMass() const {
            return this->element ? (this->element->atomicMass * 1.66053906660e-27) : 0.0; // g/mol -> Kg
        }

        /**
         * @brief total energy of the atom (kinetic + potential)
         * 
         * @return total energy in joules
         */
        constexpr double totEnergy() const {
            return this->energy_kinetic + this->energy_potential;
        }

        /**
         * @brief Apply a force to the atom over a time step
         * 
         * Updates the atom's velocity according to F = m * a
         * 
         * @param force Force vector in Newtons
         * @param dt Time step in seconds
         */
        inline void applyForce(Vector3 force, double dt) {
            if(!this->element)
                return;

            double mass = this->calcMass();
            this->velocity.x += (force.x / mass) * dt;
            this->velocity.y += (force.y / mass) * dt;
            this->velocity.z += (force.z / mass) * dt;
        }

        /**
         * @brief Update position based on its current velocity
         * 
         * @param dt time step (delta t) in seconds
         */
        inline void updatePosition(double dt) {
            this->position.x += this->velocity.x * dt;
            this->position.y += this->velocity.y * dt;
            this->position.z += this->velocity.z * dt;
        }

        /**
         * @brief Update the kinetic energy of the atom
         * 
         */
        inline void updateKineticEnergy() {
            double m =          this->calcMass();
            double v_square =   this->velocity.x * this->velocity.x + 
                                this->velocity.y * this->velocity.y + 
                                this->velocity.z * this->velocity.z;
            this->energy_kinetic = 0.5 * m * v_square;
        }

        /**
         * @brief Update the potential energy of the atom
         * 
         * @param potential_field potential in joules per coulomb [J/C]
         */
        inline void updatePotentialEnergy(double potential_field) {
            this->energy_potential = this->charge * potential_field;
        }

        inline void resetEnergy() {
            this->energy_kinetic = 0; 
            this->energy_potential = 0; 
        }

        inline bool canBond() const {
            return this->bonds_count < this->valence_max;
        }

        inline void addBond() {
            if(this->canBond()) {
                this->bonds_count++;
        }

        inline void removeBond() {
            if(this.bonds_count > 0)
                this.bonds_count--;
        }
    };
};

#endif
