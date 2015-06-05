#include "../intf/ILocker.h"
#include "CLockerFactory.h"

//-------------------------------------------------
class CEmptySync:public ILocker
{
public:
   virtual bool Lock() override;
   virtual bool Lock(int aTimeWat) override;
   virtual void UnLock() override;

   virtual ILocker* Clone() override;
};
//-------------------------------------------------
bool CEmptySync::Lock()
{
   return false;
}

bool CEmptySync::Lock(int aTimeWait)
{
   return false;
}

void CEmptySync::UnLock()
{
}

ILocker* CEmptySync::Clone()
{
   return new CEmptySync();
}
//------------------------------------------------
ILocker::Ptr CLockerFactoryEmpty::CreateLMutex()
{
   return ILocker::Ptr(new CEmptySync());
}

ILocker::Ptr CLockerFactoryEmpty::CreateLMutex(std::string)
{
   return ILocker::Ptr(new CEmptySync());
}

ILocker::Ptr CLockerFactoryEmpty::CreateLSemaphore()
{
   return ILocker::Ptr(new CEmptySync());
}

ILocker::Ptr CLockerFactoryEmpty::CreateLSemaphore(int)
{
   return ILocker::Ptr(new CEmptySync());
}

ILocker::Ptr CLockerFactoryEmpty::CreateLSemaphore(std::string)
{
   return ILocker::Ptr(new CEmptySync());
}

ILocker::Ptr CLockerFactoryEmpty::CreateLSemaphore(std::string, int)
{
   return ILocker::Ptr(new CEmptySync());
}

ILocker::Ptr CLockerFactoryEmpty::CreateLCriticalSection()
{
   return ILocker::Ptr(new CEmptySync());
}

ILocker::Ptr CLockerFactoryEmpty::CreateLEvent()
{
   return ILocker::Ptr(new CEmptySync());
}

ILocker::Ptr CLockerFactoryEmpty::CreateLEvent(std::string)
{
   return ILocker::Ptr(new CEmptySync());
}