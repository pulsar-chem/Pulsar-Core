#ifndef _GUARD_ATOMICINFO_H_
#define _GUARD_ATOMICINFO_H_

#include <vector>
#include <string>

namespace bpmodule {
namespace molecule {


struct IsotopeData
{
    int isonum;           //! Isotope number (Z + number of neutrons)
    double mass;          //! Mass of the isotope
    double mass_low;      //! Lower bound of the isotope mass
    double mass_high;     //! Upper bound of the isotope mass
                         
    double abund;         //! Natural abundance of the isotope (out of 1)
    double abund_low;     //! Lower bound on the isotope's abundance
    double abund_high;    //! Upper bound on the isotope's abundance 
};


struct AtomicData
{
    int Z;                //! Atomic Z-number (number of protons)
    std::string sym;      //! Element's atomic symbol
    std::string name;     //! Full name of the element 
    double mass;          //! Mass of the element (isotope masses weighted by abundance)
    double mass_low;      //! Lower bound on the mass of the element
    double mass_high;     //! Upper bound on the mass of the element


    // All isotope information for this atom
    std::vector<IsotopeData> isotopes;

    std::vector<IsotopeData> GetIsotopes(void) { return isotopes; }

};


//////////////////////////
// Free functions
//////////////////////////

/*! \brief Get atomic data by Z number
 *
 * \throw bpmodule::exception::MoleculeException if the
 *        data does not exist for this Z number
 */
const AtomicData & AtomicInfoFromZ(int Z);


/*! \brief Get atomic data by symbol
 *
 * Symbol is not case sensitive
 *
 * \throw bpmodule::exception::MoleculeException if the
 *        data does not exist for this symbol
 */
const AtomicData & AtomicInfoFromSym(const std::string & sym);



/*! \brief Get isotope data by Z number and isotope number
 *
 * \throw bpmodule::exception::MoleculeException if the
 *        data does not exist for this Z number and isotope number.
 */
const IsotopeData & IsotopeInfoFromZ(int Z, int isonum);



/*! \brief Get isotope data by symbol and isotope number
 *
 * Symbol is not case sensitive
 *
 * \throw bpmodule::exception::MoleculeException if the
 *        data does not exist for this symbol and isotope number.
 */
const IsotopeData & IsotopeInfoFromSym(const std::string & sym, int isonum);



/*! \brief Look up an atomic mass by Z number
 *
 * \throw bpmodule::exception::MoleculeException if the
 *        data does not exist for this Z number
 */
double AtomicMassFromZ(int Z);



/*! \brief Look up an atomic mass by symbol
 *
 * Symbol is not case sensitive
 *
 * \throw bpmodule::exception::MoleculeException if the
 *        data does not exist for this symbol
 */
double AtomicMassFromSym(const std::string & sym);



/*! \brief Look up an isotope mass by Z number and isotope number
 *
 * \throw bpmodule::exception::MoleculeException if the
 *        data does not exist for this Z number and isotope number.
 */
double IsotopeMassFromZ(int Z, int isonum);



/*! \brief Look up an isotope mass by symbol and isotope number
 *
 * Symbol is not case sensitive
 *
 * \throw bpmodule::exception::MoleculeException if the
 *        data does not exist for this symbol and isotope number
 */
double IsotopeMassFromSym(const std::string & sym, int isonum);



//! Look up a atomic symbol by Z number 
std::string AtomicSymFromZ(int Z);



/*! \brief Look up Z number by symbol
 *
 * Symbol is not case sensitive
 *
 * \throw bpmodule::exception::MoleculeException if the
 *        symbol is not defined for this Z number
 */
int AtomicZNumberFromSym(const std::string & sym);



/*! Look up an atomic name by Z number
 *
 * \throw bpmodule::exception::MoleculeException if the
 *        name is not defined for this Z number
 */
std::string AtomicNameFromZ(int Z);



/*! \brief Look up an atomic name by symbol
 *
 * Symbol is not case sensitive
 *
 * \throw bpmodule::exception::MoleculeException if the
 *        name is not defined for this symbol
 */
std::string AtomicNameFromSym(const std::string & sym);



} // closing namespace molecule
} // closing namespace bpmodule


#endif