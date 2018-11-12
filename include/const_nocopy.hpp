#ifndef CONST_NOCOPY_HPP_
#define CONST_NOCOPY_HPP_
	
template<class T>
struct const_reference
{
   using type = const std::remove_reference_t<T>&;
};
 
template <class T>
using const_reference_t =  typename const_reference<T>::type;
 
template <class T>
struct const_nocopy
{
   using type =  std::conditional_t<std::is_lvalue_reference_v<T>, const_reference_t<T>, const T>;
};
 
template <class T>
using const_nocopy_t =  typename const_nocopy<T>::type;

#endif // CONST_NOCOPY_HPP_
