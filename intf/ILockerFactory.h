#ifndef _I_LOCKER_FACTORY_H_
#define _I_LOCKER_FACTORY_H_

#include "ILocker.h"
#include <string>

class ILockerFactory
{
public:
   typedef SmartPtr<ILockerFactory>::Ptr Ptr;

public:
   virtual ~ILockerFactory()
   {}

   virtual ILocker::Ptr CreateLMutex() = 0;
   virtual ILocker::Ptr CreateLMutex(std::string) = 0;
   virtual ILocker::Ptr CreateLSemaphore() = 0;
   virtual ILocker::Ptr CreateLSemaphore(int) = 0;
   virtual ILocker::Ptr CreateLSemaphore(std::string) = 0;
   virtual ILocker::Ptr CreateLSemaphore(std::string, int) = 0;
   virtual ILocker::Ptr CreateLCriticalSection() = 0;
   virtual ILocker::Ptr CreateLEvent() = 0;
   virtual ILocker::Ptr CreateLEvent(std::string) = 0;
   
   //FactoryMethod
   static ILockerFactory::Ptr Create();
};

#endif