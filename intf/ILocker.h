#ifndef _I_LOCKER_H_
#define _I_LOCKER_H_

#include "DSmartPtr.h"

class ILocker
{
public:
   typedef SmartPtr<ILocker>::Ptr Ptr;

public:
   virtual ~ILocker()
   {}

   virtual bool Lock() = 0;
   virtual bool Lock(int aTimeWat) = 0;
   virtual void UnLock() = 0;
};

#endif