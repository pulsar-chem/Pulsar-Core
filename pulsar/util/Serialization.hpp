/*! \file
 *
 * \brief Serialization helpers
 * \author Benjamin Pritchard (ben@bennyp.org)
 */

#ifndef PULSAR_GUARD_UTIL__SERIALIZATION_HPP_
#define PULSAR_GUARD_UTIL__SERIALIZATION_HPP_

// Included via SerializationArchives.hpp
//#include <cereal/cereal.hpp>
//#include <cereal/access.hpp>
#include <cereal/types/array.hpp>
#include <cereal/types/vector.hpp>
#include <cereal/types/memory.hpp>
#include <cereal/types/map.hpp>
#include <cereal/types/utility.hpp>
#include <cereal/types/set.hpp>
#include <cereal/types/tuple.hpp>
#include <cereal/types/string.hpp>
#include <cereal/types/complex.hpp>

#include "pulsar/util/Serialization_fwd.hpp" // for ByteArray
#include "pulsar/util/SerializationArchives.hpp"

#define DECLARE_SERIALIZATION_FRIENDS \
    friend class cereal::access; \
    template<typename T> friend class pulsar::util::detail::StdStreamArchive;



namespace pulsar{
namespace util {

/*! \brief Convert a c++ object to a byte array
 *
 * The C++ object must be serializable
 */
template<typename T>
ByteArray to_byte_array(const T & obj)
{
    MemoryArchive mar;
    mar.begin_serialization();
    mar.serialize(obj);
    mar.end_serialization();
    return mar.to_byte_array(); 
}


/*! \brief Create c++ object from a byte array
 *
 * The C++ object must be serializable
 */
template<typename T>
T from_byte_array(const ByteArray & arr)
{
    MemoryArchive mar;
    mar.from_byte_array(arr);
    mar.begin_unserialization();
    T obj;
    mar.unserialize(obj);
    mar.end_unserialization();
    return obj; 
}


/*! \brief Create c++ object from a byte array
 *
 * The C++ object must be serializable
 */
template<typename T>
std::unique_ptr<T> new_from_byte_array(const ByteArray & arr)
{
    MemoryArchive mar;
    mar.from_byte_array(arr);
    mar.begin_unserialization();
    std::unique_ptr<T> objptr(new T);
    mar.unserialize(*objptr);
    mar.end_unserialization();
    return std::move(objptr);
}




} // close namespace util
} // close namespace pulsar

#endif

