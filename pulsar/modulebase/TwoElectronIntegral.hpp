/*! \file
 *
 * \brief Two-electron integral implementation (header)
 * \author Ben Pritchard (ben@bennyp.org)
 */


#ifndef PULSAR_GUARD_MODULEBASE__TWOELECTRONINTEGRAL_HPP_
#define PULSAR_GUARD_MODULEBASE__TWOELECTRONINTEGRAL_HPP_

#include "pulsar/modulebase/ModuleBase.hpp"


namespace pulsar{
namespace modulebase {

/*! \brief Two-electron integral implementation
 *
 */
class TwoElectronIntegral : public ModuleBase
{
    public:
        typedef TwoElectronIntegral BaseType;

        TwoElectronIntegral(ID_t id)
            : ModuleBase(id, "TwoElectronIntegral")
        { }


        /*! \brief Set the basis sets for the integrals
         *
         * \param [in] bs1 Basis set tag to use for the first center
         * \param [in] bs2 Basis set tag to use for the second center
         * \param [in] bs3 Basis set tag to use for the third center
         * \param [in] bs4 Basis set tag to use for the fourth center
         */
        void SetBases(const system::System & sys,
                      const std::string & bs1, const std::string & bs2,
                      const std::string & bs3, const std::string & bs4)
        {
            return ModuleBase::CallFunction(&TwoElectronIntegral::SetBases_, sys, bs1, bs2, bs3, bs4);
        }


        /*! \brief Calculate an integral
         *
         * \param [in] deriv Derivative to calculate
         * \param [in] shell1 Shell index on the first center
         * \param [in] shell2 Shell index on the second center
         * \param [in] shell3 Shell index on the third center
         * \param [in] shell4 Shell index on the fourth center
         * \param [in] outbuffer Where to place the completed integrals
         * \param [in] bufsize Size of \p outbuffer (as the number of doubles)
         * \return Number of integrals calculated
         */
        uint64_t Calculate(uint64_t deriv,
                           uint64_t shell1, uint64_t shell2,
                           uint64_t shell3, uint64_t shell4,
                           double * outbuffer, size_t bufsize)
        {
            return ModuleBase::FastCallFunction(&TwoElectronIntegral::Calculate_,
                                                deriv, shell1, shell2, shell3, shell4,
                                                outbuffer, bufsize);
        }

        /*! \brief Calculate an integral (for use from python)
         *
         * \param [in] deriv Derivative to calculate
         * \param [in] shell1 Shell index on the first center
         * \param [in] shell2 Shell index on the second center
         * \param [in] shell3 Shell index on the third center
         * \param [in] shell4 Shell index on the fourth center
         * \param [in] outbuffer Where to place the completed integrals
         * \return Number of integrals calculated
         */
        uint64_t CalculatePy(uint64_t deriv,
                             uint64_t shell1, uint64_t shell2,
                             uint64_t shell3, uint64_t shell4,
                             pybind11::buffer outbuffer)
        {
            auto ptrinfo = PythonBufferToPtr<double>(outbuffer, 1);

            return ModuleBase::FastCallFunction(&TwoElectronIntegral::Calculate_,
                                                deriv, shell1, shell2, shell3, shell4,
                                                ptrinfo.first, ptrinfo.second[0]);
        }


        /*! \brief Calculate multiple integrals
         *
         * \param [in] deriv Derivative to calculate
         * \param [in] shells1 Shell indicies on the first center
         * \param [in] shells2 Shell indicies on the second center
         * \param [in] shells3 Shell indicies on the third center
         * \param [in] shells4 Shell indicies on the fourth center
         * \param [in] outbuffer Where to place the completed integrals
         * \param [in] bufsize Size of \p outbuffer (as the number of doubles)
         * \return Number of integrals calculated
         */
        uint64_t CalculateMulti(uint64_t deriv,
                                const std::vector<uint64_t> & shells1,
                                const std::vector<uint64_t> & shells2,
                                const std::vector<uint64_t> & shells3,
                                const std::vector<uint64_t> & shells4,
                                double * outbuffer, size_t bufsize)
        {
            return ModuleBase::FastCallFunction(&TwoElectronIntegral::CalculateMulti_,
                                                deriv, shells1, shells2, shells3, shells4,
                                                outbuffer, bufsize);
        }


        /*! \brief Calculate multiple integrals (for use from python)
         *
         * \param [in] deriv Derivative to calculate
         * \param [in] shells1 Shell indicies on the first center
         * \param [in] shells2 Shell indicies on the second center
         * \param [in] shells3 Shell indicies on the third center
         * \param [in] shells4 Shell indicies on the fourth center
         * \param [in] outbuffer Where to place the completed integrals
         * \return Number of integrals calculated
         */
        uint64_t CalculateMultiPy(uint64_t deriv,
                                  const std::vector<uint64_t> & shells1,
                                  const std::vector<uint64_t> & shells2,
                                  const std::vector<uint64_t> & shells3,
                                  const std::vector<uint64_t> & shells4,
                                  pybind11::buffer outbuffer)
        {
            auto ptrinfo = PythonBufferToPtr<double>(outbuffer, 1);

            return ModuleBase::FastCallFunction(&TwoElectronIntegral::CalculateMulti_,
                                                deriv, shells1, shells2, shells3, shells4,
                                                ptrinfo.first, ptrinfo.second[0]);
        }


        /////////////////////////////////////////
        // To be implemented by derived classes
        /////////////////////////////////////////
        //! \copydoc SetBases
        virtual void SetBases_(const system::System & sys,
                               const std::string & bs1, const std::string & bs2,
                               const std::string & bs3, const std::string & bs4) = 0;


        //! \copydoc Calculate
        virtual uint64_t Calculate_(uint64_t deriv,
                                    uint64_t shell1, uint64_t shell2,
                                    uint64_t shell3, uint64_t shell4,
                                    double * outbuffer, size_t bufsize) = 0;

        //! \copydoc CalculateMulti
        virtual uint64_t CalculateMulti_(uint64_t deriv,
                                         const std::vector<uint64_t> & shells1,
                                         const std::vector<uint64_t> & shells2,
                                         const std::vector<uint64_t> & shells3,
                                         const std::vector<uint64_t> & shells4,
                                         double * outbuffer, size_t bufsize)
        {
            //////////////////////////////////////////////////////////
            // default implementation - just loop over and do them all
            //////////////////////////////////////////////////////////

            uint64_t ntotal = 0;

            for(uint64_t s1 : shells1)
            for(uint64_t s2 : shells2)
            for(uint64_t s3 : shells3)
            for(uint64_t s4 : shells4)
            {
                uint64_t nbatch = Calculate_(deriv, s1, s2, s3, s4, outbuffer, bufsize);
                ntotal += nbatch;
                outbuffer += nbatch;

                // be safe with unsigned types
                bufsize = ( (nbatch >= bufsize) ? 0 : (bufsize - nbatch) );
            }

            return ntotal;
        }
};


class TwoElectronIntegral_Py : public TwoElectronIntegral
{
    public:
        using TwoElectronIntegral::TwoElectronIntegral;

        MODULEBASE_FORWARD_PROTECTED_TO_PY

        virtual void SetBases_(const system::System & sys,
                               const std::string & bs1, const std::string & bs2,
                               const std::string & bs3, const std::string & bs4)

        {
            return CallPyOverride<void>("SetBases_", sys, bs1, bs2, bs3, bs4);
        }


        virtual uint64_t Calculate_(uint64_t deriv,
                                    uint64_t shell1, uint64_t shell2,
                                    uint64_t shell3, uint64_t shell4,
                                    double * outbuffer, size_t bufsize)
        {
            //! \todo untested

            pybind11::buffer_info buf(outbuffer,
                                      sizeof(double),
                                      pybind11::format_descriptor<double>::value(),
                                      1, { bufsize },
                                      { sizeof(double) });

            return CallPyOverride<uint64_t>("Calculate_", deriv, shell1, shell2, shell3, shell4,
                                            buf, bufsize);
        }


        virtual uint64_t CalculateMulti_(uint64_t deriv,
                                         const std::vector<uint64_t> & shells1,
                                         const std::vector<uint64_t> & shells2,
                                         const std::vector<uint64_t> & shells3,
                                         const std::vector<uint64_t> & shells4,
                                         double * outbuffer, size_t bufsize)
        {

            if(HasPyOverride("CalculateMulti_"))
            {
                //! \todo untested

                pybind11::buffer_info pybuf(outbuffer,
                                            sizeof(double),
                                            pybind11::format_descriptor<double>::value(),
                                            1, { bufsize },
                                            { sizeof(double) });

                return CallPyOverride<uint64_t>("CalculateMulti_",
                                                deriv, shells1, shells2, shells3, shells4, pybuf, bufsize);
            }
            else
                return TwoElectronIntegral::CalculateMulti_(deriv, shells1, shells2, shells3, shells4,
                                                                outbuffer, bufsize);
        }

};

} // close namespace modulebase
} // close namespace pulsar

#endif