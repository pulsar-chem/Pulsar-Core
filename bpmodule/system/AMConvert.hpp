#ifndef BPMODULE_GUARD_SYSTEM__AMCONVERT_HPP_
#define BPMODULE_GUARD_SYSTEM__AMCONVERT_HPP_

#include <string>

namespace bpmodule {
namespace system {


/*! \brief Converts a string ("s", "p", etc) to an integer angular momentum
 *
 * The string is not case sensitive
 *
 * \throw bpmodule::exception::BasisSetException if the string is not found
 */
int StringToAM(const std::string & s);



/*! \brief Converts an integer angular momentum (0, 1, 2) to a string string ("s", "p", "d")
 *
 * The string is always lowercase
 *
 * \throw bpmodule::exception::BasisSetException if the integer is not found
 */
std::string AMToString(int am);



} // close namespace system
} // close namespace bpmodule

#endif