import pandas as pd
import requests

url = "https://pubchem.ncbi.nlm.nih.gov/rest/pug/periodictable/CSV"
csv_data = requests.get(url)
csv_data.raise_for_status()

with open("build/dataset/periodic_table.csv", "wb") as f:
    f.write(csv_data.content)

df = pd.read_csv("build/dataset/periodic_table.csv")
df.columns = [c.strip() for c in df.columns]

print("Columns detected:", df.columns.tolist())

def safe(row, key, default=""):
    if key not in row or pd.isna(row[key]):
        return default
    return row[key]

header = """#ifndef __LIBNGXCHEM_PERIODIC_TABLE_HPP
#define __LIBNGXCHEM_PERIODIC_TABLE_HPP

#include "Element.hpp"
#include "temp_t.hpp"

namespace ngxchem {
    const Element PERIODIC_TABLE[] = {
"""

lines = []

for _, row in df.iterrows():
    try:
        symbol = safe(row, "Symbol", "?")
        name = safe(row, "Element") or safe(row, "Name") or symbol
        atomic_no = int(safe(row, "AtomicNumber", 0))
        atomic_mass = safe(row, "AtomicMass", 0.0)
        period = int(safe(row, "Period", 0))
        group = int(safe(row, "Group", 0))
        ar = safe(row, "AtomicRadius", 0.0)
        cr = safe(row, "CovalentRadius", 0.0)
        vdw = safe(row, "VanDerWaalsRadius", 0.0)
        elneg = safe(row, "Electronegativity", 0.0)
        ion = safe(row, "IonizationEnergy", 0.0)
        ea = safe(row, "ElectronAffinity", 0.0)
        fusion = safe(row, "HeatOfFusion", 0.0)
        state = safe(row, "Phase", "solid").lower()
        state_enum = "ElementState::STATE_SOLID"
        if "gas" in state:
            state_enum = "ElementState::STATE_GAS"
        elif "liquid" in state or "fluid" in state:
            state_enum = "ElementState::STATE_FLUID"

        line = f"""        {{
            "{symbol}",
            "{name}",
            {atomic_no},
            {atomic_mass},
            {period},
            {group},
            {ar},
            {cr},
            {vdw},
            1.0,
            {"true" if str(safe(row, "Type", "")).lower().find("metal") != -1 else "false"},
            {"true" if str(safe(row, "Type", "")).lower().find("noble gas") != -1 else "false"},
            {"true" if str(safe(row, "Radioactive", "")).lower() == 'yes' else "false"},
            Temp(298.15),
            {state_enum},
            0.0,
            0.0,
            {elneg},
            {{}},
            {ion},
            {ea},
            Temp({fusion})
        }}"""
        lines.append(line)
    except Exception as e:
        print("Skipping row due to error:", e)

footer = """
    };
};
#endif
"""

with open("include/libngxchem/periodic_table.hpp", "w") as f:
    f.write(header + ",\n".join(lines) + footer)

print(f"Generated periodic_table.hpp with {len(lines)} elements.")