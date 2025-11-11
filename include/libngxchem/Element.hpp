#ifndef __LIBNGXCHEM_ELEMENT_HPP
#define __LIBNGXCHEM_ELEMENT_HPP

#include <string>

#include "periodic_table.hpp"
#include "ElementClass.hpp"

namespace ngxchem {
    const Element* findBySymbol(const std::string& symbol) {
        for(const auto& el: ngxchem::PERIODIC_TABLE)  {
            if(el.symbol == symbol)
                return &el;
        }

        return nullptr;
    }
};

#endif
