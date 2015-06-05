#include "windows.h"
#include "../intf/ILocker.h"
#include "CLockerFactory.h"
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

   virtual ILocker* Clone() override;

private:
   HANDLE mSemaphoreHandle;
   std::string mName;
   int mMaxLock;
};
//-------------------------------------------------
CSemaphore::CSemaphore()
   :mMaxLock(1)
{
   mSemaphoreHandle = CreateSemaphore(NULL, mMaxLock, mMaxLock, NULL);
}
CSemaphore::CSemaphore(int aMaxLock)
   :mMaxLock(aMaxLock)
{
   mSemaphoreHandle = CreateSemaphore(NULL, mMaxLock, mMaxLock, NULL);
}
CSemaphore::CSemaphore(std::string aName)
   :mName(aName), mMaxLock(1)
{
   mSemaphoreHandle = CreateSemaphore(NULL, mMaxLock, mMaxLock, aName.c_str());
}
CSemaphore::CSemaphore(std::string aName, int aMaxLock)
   :mName(aName), mMaxLock(aMaxLock)
{
   mSemaphoreHandle = CreateSemaphore(NULL, mMaxLock, mMaxLock, aName.c_str());
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

ILocker* CSemaphore::Clone()
{
   if(mName.empty())
      return new CSemaphore(mMaxLock);
   else
      return new CSemaphore(mName, mMaxLock);
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