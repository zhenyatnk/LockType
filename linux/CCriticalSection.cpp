#include "../intf/ILocker.h"
#include "CLockerFactory.h"
#include <string>
//-------------------------------------------------
ILocker::Ptr CLockerFactory::CreateLCriticalSection()
{
   CLockerFactory aFactory;
   return aFactory.CreateLSemaphore();
}

