#ifndef _DEF_SMART_PTR_H_
#define _DEF_SMART_PTR_H_

#if defined(WIN32)
   #include <memory>
#elif defined(LINUX)
   #include <boost/shared_ptr.hpp>
#endif

template <typename Type>
class SmartPtr
{
public:
#if defined(WIN32)
   typedef typename std::shared_ptr<Type> Ptr;
#elif defined(LINUX)
   typedef typename boost::shared_ptr<Type> Ptr;
#endif    
};

#endif