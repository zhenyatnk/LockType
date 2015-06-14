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

   virtual ILocker* Clone() override;

private:
   HANDLE mMutexHandle;
   std::string mName;
};
//-------------------------------------------------------------------------
CMutex::CMutex()
{
   mMutexHandle = CreateMutex(NULL, FALSE, NULL);
}

CMutex::CMutex(std::string aName)
   :mName(aName)
{
   mMutexHandle = CreateMutex(NULL, FALSE, mName.c_str());
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
   return WaitForSingleObject(mMutexHandle, aTimeWat) == WAIT_OBJECT_0;
}

void CMutex::UnLock()
{
   ReleaseMutex(mMutexHandle);
}

ILocker* CMutex::Clone()
{
   if(mName.empty())
      return new CMutex();
   else
      return new CMutex(mName);
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
