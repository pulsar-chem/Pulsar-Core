/*! \file
 *
 * \brief An iteration in an SCF procedure
 */ 


#ifndef PULSAR_GUARD_MODULEBASE__SCFITERATOR_HPP_
#define PULSAR_GUARD_MODULEBASE__SCFITERATOR_HPP_

#include "pulsar/modulebase/ModuleBase.hpp"
#include "pulsar/math/IrrepSpinMatrix.hpp"


namespace pulsar{
namespace modulebase {

class SCFIterator : public ModuleBase
{   
    public:
        typedef SCFIterator BaseType;
        
        SCFIterator(ID_t id): ModuleBase(id, "SCFIterator") { }
        
        /*! \brief Form a new wavefunction based on the given wfn and fock matrix
         */ 
        datastore::Wavefunction Next(const datastore::Wavefunction & wfn, const math::IrrepSpinMatrixD & fmat)
        {
            return ModuleBase::CallFunction(&SCFIterator::Next_, wfn, fmat);
        }


        virtual datastore::Wavefunction Next_(const datastore::Wavefunction & wfn, const math::IrrepSpinMatrixD & fmat) = 0;
        
};

class SCFIterator_Py : public SCFIterator{
    public:
        using SCFIterator::SCFIterator;
        MODULEBASE_FORWARD_PROTECTED_TO_PY
                
        virtual datastore::Wavefunction Next_(const datastore::Wavefunction & wfn, const math::IrrepSpinMatrixD & fmat)
        {
            return CallPyOverride<datastore::Wavefunction>("Next_", wfn, fmat);
        }    
};

} // close namespace modulebase
} // close namespace pulsar

#endif