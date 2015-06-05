#include "../intf/ILocker.h"
#include "CLockerFactory.h"
#include <string>
//-------------------------------------------------
ILocker::Ptr CLockerFactoryLinux::CreateLCriticalSection()
{
   CLockerFactoryLinux aFactory;
   return aFactory.CreateLSemaphore();
}

