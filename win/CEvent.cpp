#include "windows.h"
#include "../intf/ILocker.h"
#include "CLockerFactory.h"
#include <string>

//-------------------------------------------------
class CEvent:public ILocker
{
public:
   CEvent();
   CEvent(std::string);
   virtual ~CEvent();

   virtual bool Lock() override;
   virtual bool Lock(int aTimeWat) override;
   virtual void UnLock() override;

private:
   HANDLE mEventHandle;
};
//-------------------------------------------------
CEvent::CEvent()
{
   mEventHandle = CreateEvent(NULL, TRUE, TRUE, NULL);
}
CEvent::CEvent(std::string aName)
{
   mEventHandle = CreateEvent(NULL, TRUE, TRUE, aName.c_str());
}
CEvent::~CEvent()
{
   CloseHandle(mEventHandle);
}

bool CEvent::Lock()
{
   bool lState = WaitForSingleObject(mEventHandle, INFINITE) == WAIT_OBJECT_0;
   if (lState)
      ResetEvent(mEventHandle);
   return lState;
}

bool CEvent::Lock(int aTimeWat)
{
   bool lState = WaitForSingleObject(mEventHandle, aTimeWat) == WAIT_OBJECT_0;
   if (lState)
      ResetEvent(mEventHandle);
   return lState;
}

void CEvent::UnLock()
{
   SetEvent(mEventHandle);
}
//-------------------------------------------------
ILocker::Ptr CLockerFactoryWin::CreateLEvent()
{
   return ILocker::Ptr(new CEvent());
}

ILocker::Ptr CLockerFactoryWin::CreateLEvent(std::string aName)
{
   return ILocker::Ptr(new CEvent(aName));
}
