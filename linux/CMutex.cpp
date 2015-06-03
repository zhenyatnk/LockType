#include "../intf/ILocker.h"
#include "CLockerFactory.h"
#include <string>

//-------------------------------------------------
ILocker::Ptr CLockerFactory::CreateLMutex()
{
   CLockerFactory aFactory;
   return aFactory.CreateLSemaphore();
}

ILocker::Ptr CLockerFactory::CreateLMutex(std::string aName)
{
   CLockerFactory aFactory;
   return aFactory.CreateLSemaphore(aName);
}
