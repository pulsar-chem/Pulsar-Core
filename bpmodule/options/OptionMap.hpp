/*! \file
 *
 * \brief Storage of options for a module (header)
 * \author Benjamin Pritchard (ben@bennyp.org)
 */ 


#ifndef _GUARD_OPTIONMAP_HPP_
#define _GUARD_OPTIONMAP_HPP_

#include <map>

#include "bpmodule/options/OptionTypes.hpp"
#include "bpmodule/options/OptionHolder.hpp"
#include "bpmodule/exception/OptionException.hpp"


namespace bpmodule {
namespace options {



/*! \brief A class for holding options to a module
 *
 * \todo Split out functions into cpp file
 */
class OptionMap
{
    public:
        OptionMap(void) = default;

        ~OptionMap(void) = default;


        /*! \brief Copy construct
        * 
        * Deep copies (clones) all the stored options
        */
        OptionMap(const OptionMap & rhs);


        /*! \brief Assignment
        * 
        * Deep copies (clones) all the stored options
        */
        OptionMap & operator=(const OptionMap & rhs);



        OptionMap(OptionMap && rhs)                  = default;
        OptionMap & operator=(OptionMap && rhs)      = default;



        /*! \brief Obtain the value for an option
         * 
         * Will attempt some safe conversions
         *
         * \throw bpmodule::exception::OptionException if the
         *        option does not have a value or if the 
         *        key does not exist or if the value cannot be 
         *        cast to the appropriate type
         */
        template<typename T>
        T Get(const std::string & key) const
        {
            typedef typename detail::OptionConvert<T>::stored_type stored_type;

            CheckType_<T>();
            std::string lkey = LowerString_(key);

            stored_type val = GetOrThrow_Cast_<stored_type>(lkey)->Get();

            try {
                return detail::OptionConvert<T>::ConvertFromStored(val); 
            }
            catch(const exception::GeneralException & ex)
            {
                throw exception::OptionException(ex, key);
            }
        }



        /*! \brief Determine if this object contains a value for a key
         *
         * Checks to see if the map has the key and then if
         * the option for that key has a value or a default
         *
         * \param [in] key The key to the data
         * \return True if the key exists and has a value, false otherwise
         */
        bool Has(const std::string & key) const;



        /*! \brief Determine if this object contains a key
         *
         * Checks to see if the map has the key
         *
         * \param [in] key The key to the data
         * \return True if the key exists, false otherwise
         */
        bool HasKey(const std::string & key) const;



        /*! \brief Return the number of elements contained
         *
         * \exnothrow
         *
         * \return Number of elements in this container
         */
        size_t Size(void) const noexcept;



        /*! \brief Check if the option is currently set to the default
         */ 
        bool IsDefault(const std::string & key) const;



        /*! \brief Change the stored value for a key
         *
         * The data is copied.
         *
         * \throw bpmodule::exception::OptionException if
         *        the value is invalid (and not expert),
         *        if the key does not exist, or the
         *        data cannot be cast to the appropriate type
         *
         * \exstrong 
         */
        template<typename T>
        void Change(const std::string & key, const T & value)
        {
            typedef typename detail::OptionConvert<T>::stored_type stored_type;

            CheckType_<T>();
            std::string lkey = LowerString_(key);
            stored_type convval;

            try {
                 convval = detail::OptionConvert<T>::ConvertToStored(value); 
            }
            catch(const exception::GeneralException & ex)
            {
                throw exception::OptionException(ex, key);
            }

            GetOrThrow_Cast_<T>(lkey)->Change(convval);
        }




        /*! \brief Sets an option to its default
         *
         * \throw bpmodule::exception::OptionException if
         *        the option does not have a default or the
         *        key doesn't exist
         *
         * \exstrong 
         */ 
        void ResetToDefault(const std::string & key);



        /*! \brief Check all options to see if they are valid
         * 
         * \exnothrow
         */
        bool IsValid(void) const noexcept;



        /*! \brief Check if the map has a key with a given type
         *  
         *  Does not check for validity or if the stored value
         *  can be successfully converted (ie, overflow)
         */
        template<typename T>
        bool HasType(const std::string & key) const
        {
            typedef typename detail::OptionConvert<T>::stored_type stored_type;

            CheckType_<T>();

            if(!HasKey(key))
                return false;

            std::string lkey = LowerString_(key);
            return GetOrThrow_(lkey)->IsType<stored_type>();
        } 



        /*! \brief Dumps the options to the output
        */
        void Print(void) const;



        /////////////////////////////
        // Python-related functions
        /////////////////////////////
        /*! \brief Construct options from a python dictionary
         * 
         * \throw bpmodule::exception::OptionException if there is
         *        a problem with the option (validation, conversion, duplicate key, etc)
         */ 
        OptionMap(const boost::python::dict & opt);



        /*! \brief Change options via python dictionary
         *
         * Dictionary is simple string key -> value mapping.
         *
         * \throw bpmodule::exception::OptionException if there is
         *        a problem with the option (nonexistant key, validation, conversion, duplicate key, etc)
         *
         * \exstrong
         */
        void ChangePyDict(const boost::python::dict & opt);



        /*! \brief Change an option by passing a boost::python object
         *
         * \throw bpmodule::exception::OptionException if there is
         *        a problem with the option (nonexistant key, validation, conversion, etc)
         *
         * \exstrong
         */ 
        void ChangePy(const std::string & key, const boost::python::object & obj);



        /*! \brief Return the option's value as a python object
         *
         * \throw bpmodule::exception::OptionException if there is
         *        a problem with the option (nonexistant key, validation, conversion, etc)
         */  
        boost::python::object GetPy(const std::string & key) const;





        //////////////////////////////////////////
        // these aren't static constexpr
        // since the are to be called from python
        //////////////////////////////////////////
        /*! \brief Return the maximum value for an integer that can be stored in this OptionMap
         */ 
        detail::OptionInt MaxInt(void) const
        {
            return std::numeric_limits<detail::OptionInt>::max();
        }


        /*! \brief Return the minimum value for an integer that can be stored in this OptionMap
         */ 
        detail::OptionInt MinInt(void) const
        {
            return std::numeric_limits<detail::OptionInt>::lowest();
        }


        /*! \brief Return the maximum value for an floating point that can be stored in this OptionMap
         */ 
        detail::OptionFloat MaxFloat(void) const
        {
            return std::numeric_limits<detail::OptionFloat>::max();
        }


        /*! \brief Return the minimum value for a floating point that can be stored in this OptionMap
         */ 
        detail::OptionFloat MinFloat(void) const
        {
            return std::numeric_limits<detail::OptionFloat>::lowest();
        }


    private:
        std::map<std::string, detail::OptionBasePtr> opmap_;


        /*! \brief Get an OptionBasePtr or throw if the key doesn't exist
         * 
         * \note Key should already have been transformed to lowercase
         *
         * \throw bpmodule::exception::OptionException
         *        if a key doesn't exist
         */
        detail::OptionBasePtr & GetOrThrow_(const std::string & key);



        //! \copydoc GetOrThrow_
        const detail::OptionBasePtr & GetOrThrow_(const std::string & key) const;




        /*! \brief Get an OptionBasePtr and cast to an appropriate OptionHolder
         * 
         * \note Key should already have been transformed to lowercase
         *
         * \throw bpmodule::exception::OptionException
         *        if a key doesn't exist or cannot
         *        be cast to the desired type
         */
        template<typename T>
        const detail::OptionHolder<T> * GetOrThrow_Cast_(const std::string & key) const
        {
            CheckType_<T>();
            const detail::OptionBasePtr & ptr = GetOrThrow_(key);
            const detail::OptionHolder<T> * oh = dynamic_cast<const detail::OptionHolder<T> *>(ptr.get());
            if(oh == nullptr)
                throw exception::OptionException("Bad cast", key,
                                                 "fromtype", ptr->Type(),
                                                 "totype", typeid(T).name()); 

            return oh;
        }


        /*! \brief Converts a string to lower case
         */ 
        static std::string LowerString_(const std::string & str);


        /*! \brief Checks if a given type is valid for an option
         * 
         * If the type is not valid, the program will not compile
         */
        template<typename T>
        static void CheckType_(void) noexcept
        {
            static_assert( detail::IsValidType<T>::value,
                           "Invalid type for an option given to OptionMap"); 
        }

};



} // close namespace options
} // close namespace bpmodule



#endif

