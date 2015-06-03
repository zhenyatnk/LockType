#include "../intf/ILocker.h"
#include "CLockerFactory.h"
#include <string>
//-------------------------------------------------
ILocker::Ptr CLockerFactory::CreateLEvent()
{
   CLockerFactory aFactory;
   return aFactory.CreateLSemaphore();
}

ILocker::Ptr CLockerFactory::CreateLEvent(std::string aName)
{
   CLockerFactory aFactory;
   return aFactory.CreateLSemaphore(aName);
}
