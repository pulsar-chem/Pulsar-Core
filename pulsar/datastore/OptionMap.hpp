/*! \file
 *
 * \brief Storage of options for a module (header)
 * \author Benjamin Pritchard (ben@bennyp.org)
 */


#ifndef PULSAR_GUARD_DATASTORE__OPTIONMAP_HPP_
#define PULSAR_GUARD_DATASTORE__OPTIONMAP_HPP_

#include <map>

#include "pulsar/datastore/OptionTypes.hpp"
#include "pulsar/datastore/OptionHolder.hpp"
#include "pulsar/exception/Exceptions.hpp"
#include "pulsar/util/StringUtil.hpp"
#include "pulsar/util/bphash/Hasher_fwd.hpp"


namespace pulsar{
namespace datastore {


//! Significant Options to compare
typedef std::set<std::string> KeySet;


//! Holds top-level issues with an OptionMap
typedef std::vector<std::string> WholeOptionMapIssues;


//! Holds all issues related to an OptionMap
//! \todo python export
struct OptionMapIssues
{
    WholeOptionMapIssues toplevel;                  //!< Issues with the map itself
    std::map<std::string, OptionIssues> optissues;  //!< Issues with any individual options

    /*! \brief Check to see if there are issues
     *
     * Returns true if there are no issues stored in this structure
     */
    bool OK(void) const;


    /*! \brief Print issues (if there are any) */
    void Print(std::ostream & os) const;

    /*! \brief Obtain the issues as a string */
    std::string String(void) const;

};




/*! \brief A class for holding options to a module
 *
 * The options are stored as a key -> value map, with the
 * key being a string. The key is case insensitive.
 *
 * \par Hashing
 *     The hash value of an OptionMap is unique with respect to the values
 *     and defaults. This includes whether or not a value is set, even if
 *     it is set to the default. (ie, an option with a value manually
 *     set to the default and one without a value explicitly set will
 *     have different hashes). See HashValues for one that just hashes
 *     the values. Note that hashing does not include validators, but does
 *     include whether or not expert mode is enabled.
 */
class OptionMap
{
    public:
        OptionMap(void);

        ~OptionMap(void) = default;


        /*! \brief Copy construct
        *
        * Deep copies all the stored options
        */
        OptionMap(const OptionMap & rhs);


        /*! \brief Assignment
        *
        * Deep copies all the stored options
        */
        OptionMap & operator=(const OptionMap & rhs);



        OptionMap(OptionMap &&)                  = default;
        OptionMap & operator=(OptionMap &&)      = default;


        /*! \brief Determine if this object contains a value for a key
         *
         * Checks to see if the map has the key and then if
         * the option for that key has a value or a default
         *
         * \param [in] key The key to the data
         * \return True if the key exists and has a value, false otherwise
         */
        bool Has(const std::string & key) const;



        /*! \brief Determine if this object contains an option with the given key
         *
         * \param [in] key The key to the data
         * \return True if the key exists, false otherwise
         */
        bool HasKey(const std::string & key) const;



        /*! \brief Return the number of elements contained in this object
         *
         * \exnothrow
         *
         * \return Number of elements in this container
         */
        size_t Size(void) const noexcept;



        /*! \brief Check if the option is currently set to the default
         *
         * \throw pulsar::exception::OptionException if
         *        the key doesn't exist
         */
        bool IsDefault(const std::string & key) const;




        /*! \brief Check to see if an option is set
         * 
         * Ie, is the option set by the user. This is true even
         * if it is explicitly set to the default value.
         */
        bool IsSet(const std::string & key) const;



        /*! \brief Sets an option to its default
         *
         * \throw pulsar::exception::OptionException if
         *        the key doesn't exist
         *
         * \exstrong
         */
        void ResetToDefault(const std::string & key);



        /*! \brief Check all options to see if all required options are set
         *
         * \exnothrow
         */
        bool AllReqSet(void) const noexcept;


        /*! \brief Obtain the option keys for all missing required options
         */
        KeySet AllMissingReq(void) const;



        /*! \brief Validate this OptionMap
         *
         * Checks to see if all are set, and calls the validator
         * for all options. Also calls the overall map validator.
         *
         * \note This is not meant to be called from python
         *
         * \throw pulsar::exception::PythonCallException if there is a problem
         *        with calling a validation function
         */
        OptionMapIssues GetIssues(void) const;



        /*! \brief See if there are any issues with this OptionMap
         *
         * \throw pulsar::exception::PythonCallException if there is a problem
         *        with validation.
         */
        bool HasIssues(void) const;



        /*! \brief Turn on expert mode for all options
         *
         * In expert mode, some failures (mostly invalid options) will print warnings,
         * but an exception will not be thrown
         */
        void SetExpert(bool expert) noexcept;



        /*! \brief See if expert mode is enabled
         */
        bool IsExpert(void) const noexcept;



        /*! \brief Dumps the options to the output
        */
        void Print(std::ostream & os) const;



        /*! \brief Obtain the value for an option
         *
         * Will attempt some safe conversions between integer types
         * or between floating point types.
         *
         * \throw pulsar::exception::OptionException if the
         *        option does not have a value or if the
         *        key does not exist or if the value cannot be
         *        cast to the appropriate type
         */
        template<typename T>
        T Get(const std::string & key) const
        {
            static constexpr OptionType opt_type = OptionTypeMap<T>::opt_type;
            typedef typename OptionTypeInfo<opt_type>::stored_type stored_type;

            CheckType_<T>();

            stored_type val = GetOrThrow_Cast_<opt_type>(key)->Get();

            try {
                return OptionCast<T,stored_type>::Cast(val);
            }
            catch(const std::exception & ex)
            {
                throw exception::OptionException(ex, "optionkey", key);
            }
        }



        /*! \brief Change the stored value for a key
         *
         * The data is copied.
         *
         * \throw pulsar::exception::OptionException if
         *        the value is invalid (and not expert),
         *        if the key does not exist, or the
         *        data cannot be cast to the appropriate type
         *
         * \exstrong
         */
        template<typename T>
        void Change(const std::string & key, const T & value)
        {
            static constexpr OptionType opt_type = OptionTypeMap<T>::opt_type;
            typedef typename OptionTypeInfo<opt_type>::stored_type stored_type;

            CheckType_<T>();

            stored_type convval;

            try {
                 convval = OptionCast<stored_type, T>::Cast(value);
            }
            catch(const std::exception & ex)
            {
                // convert to an OptionException and add the key
                throw exception::OptionException(ex, "optionkey", key);
            }

            GetOrThrow_Cast_<opt_type>(key)->Change(convval);
        }



        /*! \brief Compare two OptionMap
         * 
         * Checks that all keys exist in both maps and that
         * all values match. It doesn't matter where the value
         * comes from (default or user-supplied), just that
         * the value obtained from Get() match
         */
        bool Compare(const OptionMap & rhs) const; 


        /*! \copydocs Compare(const OptionMap & rhs) const
         * 
         * \todo does this make sense?
         */
        bool operator==(const OptionMap & rhs) const;




        /*! \brief Add an option to this map
         *
         * \todo exceptions 
         */
        void AddOption(std::string key, OptionType opttype, bool required,
                       const pybind11::object & validator, std::string help,
                       const pybind11::object & def);



        /*! \brief Obtain a unique hash for this OptionMap
         * 
         * This includes values and defaults, and the expert flag.
         * It does not include validation functions.
         */
        util::Hash MyHash(void) const;


        /*! \brief Hash only the values of a set of options
         *
         * This hashes only the keys and values of options. It does
         * not take into account where that value comes from.
         *
         * \throw pulsar::exception::OptionException if
         *        the key does not exist
         */ 
        util::Hash HashValues(const std::set<std::string> & keys) const;


        /*! \brief Hash only the values of all options
         * 
         * This hashes only the keys and values of options. It does
         * not take into account where that value comes from.
         */ 
        util::Hash HashAllValues(void) const;


        /////////////////////////////
        // Python
        /////////////////////////////
        /*! \brief Change an option by passing a boost::python object
         *
         * \throw pulsar::exception::OptionException if there is
         *        a problem with the option (nonexistant key, validation, conversion, etc)
         *
         * \throw pulsar::exception::PythonCallException if there is a problem
         *        with the validation itself.
         *
         * \exstrong
         */
        void ChangePy(const std::string & key, const pybind11::object & obj);



        /*! \brief Return the option's value as a python object
         *
         * \throw pulsar::exception::OptionException if there is
         *        a problem with the option (nonexistant key, validation, conversion, etc)
         */
        pybind11::object GetPy(const std::string & key) const;



    private:
        //! Function that validates the whole option container
        typedef std::function<WholeOptionMapIssues (const OptionMap &)> WholeOptionValidator;

        //! If true, don't throw exceptions on validation errors
        bool expert_;

        //! Holds the options
        std::map<std::string, detail::OptionBasePtr, util::CaseInsensitiveLess> opmap_;

        //!< Validates the whole options container
        WholeOptionValidator wholevalid_;



        //////////////////////////////
        // Functions
        //////////////////////////////

        /*! \brief Get an OptionBase or throw if the key doesn't exist
         *
         * \note Key should already have been transformed to lowercase
         *
         * \throw pulsar::exception::OptionException
         *        if a key doesn't exist
         */
        const detail::OptionBase * GetOrThrow_(const std::string & key) const;


         /* \copydoc GetOrThrow_
         */
        detail::OptionBase * GetOrThrow_(const std::string & key);


        /*! \brief Get a pointer to OptionBase and cast it to an appropriate OptionBase
         *
         * \note Key should already have been transformed to lowercase
         *
         * \throw pulsar::exception::OptionException
         *        if a key doesn't exist or cannot
         *        be cast to the desired type
         */
        template<OptionType OPTTYPE>
        const detail::OptionHolder<OPTTYPE> * GetOrThrow_Cast_(const std::string & key) const
        {
            const detail::OptionBase * ptr = GetOrThrow_(key);
            const detail::OptionHolder<OPTTYPE> * oh = dynamic_cast<const detail::OptionHolder<OPTTYPE> *>(ptr);
            if(oh == nullptr)
                throw exception::OptionException("Bad option cast", "optionkey", key,
                                                 "fromtype", ptr->TypeString(),
                                                 "totype", OptionTypeToString(OPTTYPE)); 

            return oh;
        }


        /*! \copydoc GetOrThrow_Cast_
         */
        template<OptionType OPTTYPE>
        detail::OptionHolder<OPTTYPE> * GetOrThrow_Cast_(const std::string & key)
        {
            detail::OptionBase * ptr = GetOrThrow_(key);
            detail::OptionHolder<OPTTYPE> * oh = dynamic_cast<detail::OptionHolder<OPTTYPE> *>(ptr);
            if(oh == nullptr)
                throw exception::OptionException("Bad option cast", "optionkey", key,
                                                 "fromtype", ptr->TypeString(),
                                                 "totype", OptionTypeToString(OPTTYPE)); 

            return oh;
        }



        /*! \brief Checks if a given type is valid for an option
         *
         * If the type is not valid, the program will not compile
         */
        template<typename T>
        static void CheckType_(void) noexcept
        {
            /*! \todo - check types for better compilation error messages */
            //static_assert( OptionTypeMap<T>::valid,
            //               "Invalid type for an option given to OptionMap");
        }


        //! \name Serialization and Hashing
        ///@{

        DECLARE_SERIALIZATION_FRIENDS
        DECLARE_HASHING_FRIENDS


        template<class Archive>
        void save(Archive & ar) const
        {
            // We don't do validators - map should only be read-only
            // after unserializing
            ar(expert_);

            // We have to do the options a special way
            // static cast for size - just to be absolutely sure
            ar(static_cast<size_t>(opmap_.size()));
            for(const auto & it : opmap_)
                ar(it.first, it.second->Type(), it.second->ToByteArray());
        }

        template<class Archive>
        void load(Archive & ar)
        {
            size_t size;
            ar(expert_, size);

            // We have to do the options a special way
            for(size_t i = 0; i < size; i++)
            {
                std::string key;
                OptionType opttype;
                ByteArray ba;
                ar(key, opttype, ba);
                detail::OptionBasePtr opt = detail::OptionHolderFromByteArray(opttype, ba);
                opmap_.emplace(key, std::move(opt));
            }
        }


        void hash(util::Hasher & h) const;

        ///@}
};



} // close namespace datastore
} // close namespace pulsar



#endif
