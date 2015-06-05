#include "../intf/ILocker.h"
#include "CLockerFactory.h"
#include <string>

//-------------------------------------------------
ILocker::Ptr CLockerFactoryLinux::CreateLMutex()
{
   CLockerFactoryLinux aFactory;
   return aFactory.CreateLSemaphore();
}

ILocker::Ptr CLockerFactoryLinux::CreateLMutex(std::string aName)
{
   CLockerFactoryLinux aFactory;
   return aFactory.CreateLSemaphore(aName);
}
