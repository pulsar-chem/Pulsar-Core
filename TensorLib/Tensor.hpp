#ifndef TENSOR_H_
#define TENSOR_H_

#include <array>
#include "TensorSettings.hpp"
//#include "Shape.hpp"

namespace TensorWrap {

/*! \brief The main tensor wrapper class
 *
 *  Terminology.  Tensor terms vary depending on whom you talk to.  I will
 *  refer to the number of indices as the "rank" of the tensor, i.e. a
 *  scalar is a rank 0 tensor, a vector is a rank 1, and a matrix is a rank
 *  2.  Each index has a maximum value, the set of these values will be
 *  called the shape of the tensor,
 *  i.e. a scalar has the empty set, \f$\lbrace\emptyset\rbrace\f$,
 *  as a shape, a vector of length \f$m\f$ has a shape:
 *  \f$\lbrace m\rbrace\f$, a matrix that is \f$m\f$ by \f$n\f$ has a shape:
 *  \f$\lbrace m,n\rbrace\f$.
 *
 *  Consider an \f$m\f$ by \f$n\f$ matrix, for which we want element
 *  \f$i,j\f$.  In C++ this is commonly done via an offset from the start
 *  of the array, e.g. :
 *  \code
 *  std::vector<double> Matrix(m*n);
 *  double E_IJ=Matrix[i*n+j];
 *  \endcode
 *  We refer to this as offset notation, that is we will say the above
 *  like: "give me the element at offset i*n+j".  The less computer
 *  programmy way of specifying an element, i.e. "give me element i,j"
 *  will be referred to as coordinate notation.  Note that for a
 *  scalar and a vector coordinate and offset notation are identical.  Also
 *  note that offset notation requires you to know how the data is laid
 *  out, specifically the above code is for so-called row major (the matrix
 *  is stored as rows, alternatively we say the column runs fast because
 *  looping over the data sequentially changes the column more than the
 *  row).  If the data was stored in column major form (that is the
 *  row runs fast) we instead have:
 *  \code
 *  std::vector<double> Matrix(m*n);
 *  //Pretending C++ is column major...(it's not)
 *  double E_IJ=Matrix[i+j*m]
 *  \endcode
 *  As you can see this means you need to know how the data is laid out in
 *  memory, which quite frankly, if you are using this class you don't know
 *  how it is laid out...
 *
 *  The reality is the only time you should be accessing
 *  a tensor element-wise is when you are filling it.  The offset notation
 *  is good for initializing a tensor with a single value, but we
 *  provide the "Fill" fxn for that purpose (tensors default
 *  to zero).  For more complicated fill patterns use coordinate notation,
 *  which is accessed via this class's iterator
 *
 *  The general philosophy of this class is that you should never have to
 *  get the raw-data pointer out, nor should you ever have to introduce logic
 *  into your codes like: "if tensor is non-zero".  This class is
 *  intelligent and is designed to recognize optimizations, such as
 *  multiplying by zero, all by itself.  Running with this example when you
 *  declare a tensor's shape initially, that tensor is a zero tensor.
 *  Internally, this is modeled with a null pointer to the data, hence
 *  multiplying the zero tensor by any other appropriately sized tensor,
 *  will return another zero tensor almost immediately, as it amounts to
 *  checking for a null pointer and then establishing the final zero
 *  tensor's shape (a few integer arithmetic operations).  We exploit
 *  this in designing our tensors.
 *
 *  \todo It's unclear to me at this moment whether this actually works
 *
 *  Before filling your tensor you should establish its shape.  There
 *  are a few ways to do this.  At construction you may pass
 *  an std::array<size_t,Rank> to the tensor, where element \f$i\f$ is
 *  the length of the \f$i\f$-th index.  Alternatively, you may pass each
 *  length to the constructor like:
 *  \code
 *  //Builds a 10 by 10 by 10 rank 3 tensor
 *  Tensor<double,3> A(10,10,10);
 *  \endcode
 *  The tensor may also be default constructed and then you may use
 *  either filling option at a later point by invoking the SetShape()
 *  member function.  SetShape() should not be invoked if the default
 *  constructor has not been used.  Also note that any attempts at
 *  setting a shape for a scalar will be ignored.
 *
 *  For some applications it is convenient to be able to construct a
 *  larger tensor from smaller tensors.  For example consider the
 *  computation of the interaction energy of a water dimer.  If we
 *  run each water monomer computation we end with the density of
 *  water 1, W1, and the density of water 2, W2.  A great starting
 *  guess for the density of the dimer is
 *  \f[
 *  \left(\begin{array}{cc}
 *     W1 &  0\\
 *      0 & W2
 *  \end{array}\right)
 *  \f]
 *  This is known as the direct sum of W1 and W2.
 *  This is performed by the +=()
 *  operator.  Note:
 *  \code
 *  Tensor<double,3> A(10,10,10);
 *  Tensor<double,3> B(10,10,10);
 *
 *  //Normal "element-wise" tensor addition
 *  A["i,j,k"]+=B["i,j,k"];
 *  //Direct sum
 *  A+=B;
 *  \endcode
 *  The + operator is also defined for direct summation, if one wishes to
 *  preserve the input tensors.
 *
 *  The direct sum combined with the fact that tensors default to zero
 *  tensors leads to a quick way to build a tensor, if you know the
 *  structure ahead of time.  We can build the above shape like:
 *  \code
 *  Tensor<double,2> W1(nbf,nbf),W2(nbf,nbf),W12;
 *  W12=W1+W2;  //All tensors are still 0, we just have a shape
 *  \endcode
 *  The resulting tensor, W12, can be thought of as
 *  rank four (you have two indices for specifying
 *  the monomer block and then two indices within each block
 *  for specifying the density element).  For convenience, we
 *  may want to refer to the first two indices based on which
 *  monomer they stem from, "W1" or "W2".  We can do this via:
 *  \code
 *  //Syntax is rank we are mapping to, then values, in the order
 *  //we want
 *  W12.MapIndices(0,{"W1","W2"});
 *  W12.MapIndices(1,{"W1","W2"});
 *  \endcode
 *
 *  The W1 tensor can then be retrieved from W12 as:
 *  \code
 *  //Note the placement of the quotes and the use of operator()
 *  //vs. operator[]
 *  W1copy=W12("W1","W1");
 *
 *  //This would sum W1 and W2:
 *  W1pW2=W12["W1,W1"];
 * 
 *  //This is W1 squared
 *  W1_2["i,k"]=W12("W1","W1")["i,j"]*W12("W1","W1")["j,k"];
 *  \endcode
 * 
 *  Note that in C++ the default copy constructor, as
 *  well as the default assignment operator, are shallow
 *  copies (the value of all pointers, i.e. the address of the actual
 *  object, is copied, not the object).  We follow this convention for
 *  our tensor class as well. This is to say W1copy above is a shallow copy
 *  of the W1 block of W12, but W1_2 is a shallow copy of a
 *  "temporary" (quotes because no temporary is actually made,
 *  thanks to lazy evaluation, the temporary is just built in W1_2)
 *  and will thus represent a memory chunk distinct from W12.
 *
 *  You may default construct a tensor, but it will
 *  not be usable until you set it's shape (unless it's a scalar, then
 *  the shape is automatically set).
 *
 *  \param T The type this tensor contains.  May
 *      be double, complex, or Tensor<T2>
 *
 *  \param Rank The rank of this tensor
 *
 *  The following is an implementation detail and should
 *  not concern you.  If you are familiar with template meta-programming,
 *  this is a property map (see Boost's graph class or the Boost property
 *  map library for more details).  The idea is it wraps implementation
 *  details in a generic manner so that I don't have to worry about
 *  what is the syntax CTF uses vs. that of TA.
 *
 *  \param Impl_t Class that wraps basic implementation details, default
 *         is set in TensorSettings.hpp file based on which tensor backend
 *         the user has selected.
 */
template <typename T, size_t Rank, typename Impl_t=TImpl<T, Rank> >
class Tensor {
   private:
      ///For my sanity and internal use only
      typedef typename Impl_t::TensorBase_t TBase_t;
      typedef typename Impl_t::IndexedTensor_t ITensor_t;
      typedef Tensor<T, Rank, Impl_t> My_t;
   public:

      ///The iterator types
      typedef typename Impl_t::iterator iterator;
      //typedef Impl_t::const_iterator const_iterator;

      ///Convenient typedef of the Shape object
      typedef std::array<size_t, Rank> Shape_t;

      ///Makes a tensor which requires a shape to work
      Tensor() :
            ActualTensor_(nullptr) {
      }

      ///Frees Impl_
      ~Tensor() {
         if (ActualTensor_!=nullptr) delete ActualTensor_;
      }

      ///Makes a tensor given a shape
      Tensor(const Shape_t& Shape) :
            Shape_(Shape), ActualTensor_(Impl_t::Make(Shape_)) {
      }

      template <typename ... Args>
      Tensor(Args ... args) :
            Shape_(Shape_t({args...})), ActualTensor_(Impl_t::Make(Shape_)) {
      }

      ///How you specify the contraction pattern.
      ///(Don't worry about the signature...)
      ITensor_t operator[](const char* string) {
         if (ActualTensor_==nullptr)      //Shape better be set now
            ActualTensor_=Impl_t::Make(Shape_);
         return Impl_t::DeRef(string, *ActualTensor_);
      }

      /*! \brief Retrieves an element by coordinate index
       *
       *
       */
      ///@{
      template <typename ... Args>
      Tensor<T, Rank-sizeof...(Args),Impl_t> operator()(Args... args) {
         return this->operator()(
               std::array<size_t,sizeof...(Args)>( {args...}));
      }

      template<size_t SRank>
      Tensor<T,Rank-SRank,Impl_t> operator()(
            const std::array<size_t,SRank>& Index) {
         Impl_t::Get(Index,*ActualTensor_);
      }
      ///@}

      ///Initial direct sum
      Tensor<My_t,Rank+2,TImpl<T,Rank+2> >& operator+(const My_t& Other) {

      }

      ///Repeated direct sum
      My_t& operator+=(const Tensor<T,Rank-2,TImpl<T,Rank-2> >& Other) {
         return *this;
      }

      ///Fills this tensor with a value (technically only the local block)
      void Fill(const T& value) {Impl_t::Fill(value,*ActualTensor_);}

      ///Sets the shape of the tensor
      ///@{
      void SetShape(const Shape_t& Shape) {Shape_.Fill(Shape);}

      template<typename... Args>
      void SetShape(Args... args) {Shape_.Fill(Shape_t( {args...}));}
      ///@}

      /*! \brief begin/end iterators for looping over the data
       *
       *  This iterator should really only be used to fill the tensor.
       *
       *  In general the data in the tensor will be stored in a pattern that
       *  is unbeknownst to you.  That is you won't know where it resides or
       *  even which elements are next to each other in RAM or on disk.  The
       *  point of this class is to serve as the liaison to you so that you
       *  can fill in the tensor.  When you are given an instance of this
       *  class you will use it like:
       *  \code
       *  //Make a 10 by 10 matrix
       *  Tensor<double,2> T(10,10);
       *
       *  //Get an iterator to it's elements
       *  T::iterator Itr=T.begin(),ItrEnd=T.end();
       *
       *  //Buffer to hold the current index
       *  std::array<size_t,2> Idx
       *
       *  //Loop over the blocks contained in the iterator
       *  while(Itr!=ItrEnd){
       *    Idx=Itr.Index();
       *Itr=value(Idx);//Fills in element i,j
       *    ++Itr;
       *  }
       *  \endcode
       *
       *  \todo Implement const_iterator
       */
      ///@{
      iterator begin() {return Impl_t::begin(*ActualTensor_);}
      //const_iterator begin()const{return Impl_t::begin(*ActualTensor_);}
      iterator end() {return Impl_t::end(*ActualTensor_);}
      //const_iterator end()const{return Impl_t::end(*ActualTensor_);}
      ///@}

      std::ostream& operator<<(std::ostream& os)const {
         return Impl_t::PrintOut(os,*ActualTensor_);
      }

      private:
      ///The shape of our current tensor
      Shape Shape_;

      ///The actual tensor
      TBase_t* ActualTensor_;

   };

///Specialization to a scalar
template <typename T, typename T2>
class Tensor<T, 0, T2> {
   private:
      ///For my sanity and internal use only
      typedef std::array<T, 1> TensorBase_t;
   public:

      ///The iterator types
      typedef typename TensorBase_t::iterator iterator;
      //typedef Impl_t::const_iterator const_iterator;

      typedef std::array<size_t, 0> Shape_t;

      ///Makes a tensor which requires a shape to work
      Tensor() {
      }

      ///No memory to free up
      ~Tensor() {
      }

      ///Shape is ignored
      Tensor(const Shape_t&) {
      }

      ///Shape is ignored
      template <typename ... Args>
      Tensor(Args...) {
      }

      ///How you specify the contraction pattern.
      ///(Don't worry about the signature...)
      T operator[](const char*) {
         return ActualTensor_[0];
      }

      ///How you retrieve an element, args are ignored
      template <typename ... Args>
      T operator()(Args...) const {
         return ActualTensor_[0];
      }

      ///Casts the current tensor to the type it is
      operator T() {
         return ActualTensor_[0];
      }

      ///Direct product (which is just scaling for a scalar)
      template <typename T2>
      T2 operator*(T2& Other) const {
         return (*this)(0)*Other;
      }

      ///Fills this tensor with a value (technically only the local block)
      void Fill(const T& value) {
         ActualTensor_[0]=value;
      }

      ///Sets the shape of the tensor
      ///@{
      void SetShape(const Shape_t&) {
      }

      template <typename ... Args>
      void SetShape(Args...) {
      }
      ///@}

      /*! \brief begin/end iterators for looping over the data
       *
       *  This iterator should really only be used to fill the tensor.
       *
       *  In general the data in the tensor will be stored in a pattern that
       *  is unbeknownst to you.  That is you won't know where it resides or
       *  even which elements are next to each other in RAM or on disk.  The
       *  point of this class is to serve as the liaison to you so that you
       *  can fill in the tensor.  When you are given an instance of this
       *  class you will use it like:
       *  \code
       *  //Make a 10 by 10 matrix
       *  Tensor<double,2> T(10,10);
       *
       *  //Get an iterator to it's elements
       *  T::iterator Itr=T.begin(),ItrEnd=T.end();
       *
       *  //Buffer to hold the current index
       *  std::array<size_t,2> Idx
       *
       *  //Loop over the blocks contained in the iterator
       *  while(Itr!=ItrEnd){
       *    Idx=Itr.Index();
       *Itr=value(Idx);//Fills in element i,j
       *    ++Itr;
       *  }
       *  \endcode
       *
       *  \todo Implement const_iterator
       */
      ///@{
      iterator begin() {
         return ActualTensor_.begin();
      }
      //const_iterator begin()const{return Impl_t::begin(*ActualTensor_);}
      iterator end() {
         return ActualTensor_.end();
      }
      //const_iterator end()const{return Impl_t::end(*ActualTensor_);}
      ///@}

      std::ostream& operator<<(std::ostream& os) const {
         return os<<ActualTensor_[0];
      }

   private:
      ///The actual tensor
      std::array<T, 1> ActualTensor_;
};

}       //End namespace TensorWrap

template <typename T, size_t Rank, typename Impl_t>
inline std::ostream& operator<<(std::ostream& os,
      const TensorWrap::Tensor<T, Rank, Impl_t>& Ten) {
   Ten<<os;
   return os;
}

#endif /* TENSOR_H_ */
