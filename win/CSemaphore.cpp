#include "windows.h"
#include "../intf/ILocker.h"
#include "CLockerFactoryWin.h"
#include <string>

//-------------------------------------------------
class CSemaphore:public ILocker
{
public:
   CSemaphore();
   CSemaphore(int);
   CSemaphore(std::string);
   CSemaphore(std::string, int);
   virtual ~CSemaphore();

   virtual bool Lock() override;
   virtual bool Lock(int aTimeWat) override;
   virtual void UnLock() override;

private:
   HANDLE mSemaphoreHandle;
};
//-------------------------------------------------
CSemaphore::CSemaphore()
{
   mSemaphoreHandle = CreateSemaphore(NULL, 1, 1, NULL);
}
CSemaphore::CSemaphore(int aMaxLock)
{
   mSemaphoreHandle = CreateSemaphore(NULL, aMaxLock, aMaxLock, NULL);
}
CSemaphore::CSemaphore(std::string aName)
{
   mSemaphoreHandle = CreateSemaphore(NULL, 1, 1, aName.c_str());
}
CSemaphore::CSemaphore(std::string aName, int aMaxLock)
{
   mSemaphoreHandle = CreateSemaphore(NULL, aMaxLock, aMaxLock, aName.c_str());
}
CSemaphore::~CSemaphore()
{
   CloseHandle(mSemaphoreHandle);
}

bool CSemaphore::Lock()
{
   return WaitForSingleObject(mSemaphoreHandle, INFINITE) == WAIT_OBJECT_0;
}

bool CSemaphore::Lock(int aTimeWat)
{
   return WaitForSingleObject(mSemaphoreHandle, aTimeWat) == WAIT_OBJECT_0;
}

void CSemaphore::UnLock()
{
   ReleaseSemaphore(mSemaphoreHandle, 1, NULL);
}

//-------------------------------------------------
ILocker::Ptr CLockerFactoryWin::CreateLSemaphore()
{
   return ILocker::Ptr(new CSemaphore());
}

ILocker::Ptr CLockerFactoryWin::CreateLSemaphore(int aMaxLock)
{
   return ILocker::Ptr(new CSemaphore(aMaxLock));
}

ILocker::Ptr CLockerFactoryWin::CreateLSemaphore(std::string aName)
{
   return ILocker::Ptr(new CSemaphore(aName));
}
ILocker::Ptr CLockerFactoryWin::CreateLSemaphore(std::string aName, int aMaxLock)
{
   return ILocker::Ptr(new CSemaphore(aName, aMaxLock));
}