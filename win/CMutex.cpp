#include "windows.h"
#include "../intf/ILocker.h"
#include "CLockerFactory.h"
#include <string>

//-------------------------------------------------------------------------
class CMutex:public ILocker
{
public:
   CMutex();
   CMutex(std::string aName);
   virtual ~CMutex();

   virtual bool Lock() override;
   virtual bool Lock(int aTimeWat) override;
   virtual void UnLock() override;

private:
   HANDLE mMutexHandle;
};
//-------------------------------------------------------------------------
CMutex::CMutex(std::string aName)
{
   mMutexHandle = CreateMutex(NULL, FALSE, aName.c_str());
}
CMutex::CMutex()
{
   mMutexHandle = CreateMutex(NULL, FALSE, NULL);
}
CMutex::~CMutex()
{
   CloseHandle(mMutexHandle);
}

bool CMutex::Lock()
{
   return WaitForSingleObject(mMutexHandle, INFINITE) == WAIT_OBJECT_0;
}
bool CMutex::Lock(int aTimeWat)
{
   return WaitForSingleObject(mMutexHandle, aTimeWat) == WAIT_TIMEOUT;
}
void CMutex::UnLock()
{
   ReleaseMutex(mMutexHandle);
}

//-------------------------------------------------
ILocker::Ptr CLockerFactoryWin::CreateLMutex()
{
   return ILocker::Ptr(new CMutex());
}

ILocker::Ptr CLockerFactoryWin::CreateLMutex(std::string aName)
{
   return ILocker::Ptr(new CMutex(aName));
}
