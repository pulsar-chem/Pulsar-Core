/*! \file
 *
 * \brief Handling of python errors (header)
 * \author Benjamin Pritchard (ben@bennyp.org)
 */


#ifndef _GUARD_ERRORS_HPP_
#define _GUARD_ERRORS_HPP_

#include <string>

namespace bpmodule {
namespace python {
namespace detail {


/*! \brief Get the current python exception and convert to a GeneralException
 *
 * Can handle some bpmodule-derived exception classes
 */
std::string GetPyException(void);



} // close namespace detail
} // close namespace python
} // close namespace bpmodule

#endif
