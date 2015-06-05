#include "../intf/ILocker.h"
#include "CLockerFactory.h"
#include <string>
//-------------------------------------------------
ILocker::Ptr CLockerFactoryLinux::CreateLEvent()
{
   CLockerFactoryLinux aFactory;
   return aFactory.CreateLSemaphore();
}

ILocker::Ptr CLockerFactoryLinux::CreateLEvent(std::string aName)
{
   CLockerFactoryLinux aFactory;
   return aFactory.CreateLSemaphore(aName);
}
