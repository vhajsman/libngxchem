#ifndef __LIBNGXCHEM_ELEMENT_HPP
#define __LIBNGXCHEM_ELEMENT_HPP

#include <string>

#include "periodic_table.hpp"
#include "ElementClass.hpp"

namespace ngxchem {
    inline const Element* findElementBySymbol(const std::string& symbol) {
        for(const auto& el: ngxchem::PERIODIC_TABLE)  {
            if(el.symbol == symbol)
                return &el;
        }

        return nullptr;
    }

    inline const Element* findElementByAtomicNumber(const int atomic_no) {
        for(const auto& el: ngxchem::PERIODIC_TABLE) {
            if(el.atomicNumber == atomic_no)
                return &el;
        }

        return nullptr;
    }
};

#endif
