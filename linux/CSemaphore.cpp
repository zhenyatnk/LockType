#include "semaphore.h"
#include "fcntl.h"
#include "../intf/ILocker.h"
#include "CLockerFactory.h"
#include <string>

//-------------------------------------------------
class CSemaphore:public ILocker
{
public:
   CSemaphore();
   CSemaphore(int);
   virtual ~CSemaphore();

   virtual bool Lock() override;
   virtual bool Lock(int aTimeWat) override;
   virtual void UnLock() override;

private:
   sem_t mSemaphoreHandle;
};
//-------------------------------------------------
CSemaphore::CSemaphore()
{
   sem_init(&mSemaphoreHandle, 0 ,1);
}
CSemaphore::CSemaphore(int aMaxLock)
{
   sem_init(&mSemaphoreHandle, 0 ,aMaxLock);
}
CSemaphore::~CSemaphore()
{
   sem_close(&mSemaphoreHandle);
}

bool CSemaphore::Lock()
{
   return sem_wait(&mSemaphoreHandle) >=0;
}

bool CSemaphore::Lock(int aTimeWait)
{
   timespec lTimeStruct;
   lTimeStruct.tv_nsec = aTimeWait;
   return sem_timedwait(&mSemaphoreHandle, &lTimeStruct) >=0;
}

void CSemaphore::UnLock()
{
   sem_post(&mSemaphoreHandle);
}
//-------------------------------------------------
class CSemaphoreNamed:public ILocker
{
public:
   CSemaphoreNamed(std::string);
   CSemaphoreNamed(std::string, int);
   virtual ~CSemaphoreNamed();

   virtual bool Lock() override;
   virtual bool Lock(int aTimeWat) override;
   virtual void UnLock() override;

private:
   sem_t* mSemaphoreHandle;
};
//-------------------------------------------------
CSemaphoreNamed::CSemaphoreNamed(std::string aName)
{
   mSemaphoreHandle = sem_open(aName.c_str(), O_RDWR|O_CREAT, 0, 1);
}
CSemaphoreNamed::CSemaphoreNamed(std::string aName, int aMaxLock)
{
   mSemaphoreHandle = sem_open(aName.c_str(), O_RDWR|O_CREAT, 0, aMaxLock);
}
CSemaphoreNamed::~CSemaphoreNamed()
{
   sem_close(mSemaphoreHandle);
}

bool CSemaphoreNamed::Lock()
{
   return sem_wait(mSemaphoreHandle) >=0;
}

bool CSemaphoreNamed::Lock(int aTimeWait)
{
   timespec lTimeStruct;
   lTimeStruct.tv_nsec = aTimeWait;
   return sem_timedwait(mSemaphoreHandle, &lTimeStruct) >=0;
}

void CSemaphoreNamed::UnLock()
{
   sem_post(mSemaphoreHandle);
}
//-------------------------------------------------
ILocker::Ptr CLockerFactoryLinux::CreateLSemaphore()
{
   return ILocker::Ptr(new CSemaphore());
}

ILocker::Ptr CLockerFactoryLinux::CreateLSemaphore(int aMaxLock)
{
   return ILocker::Ptr(new CSemaphore(aMaxLock));
}

ILocker::Ptr CLockerFactoryLinux::CreateLSemaphore(std::string aName)
{
   return ILocker::Ptr(new CSemaphoreNamed(aName));
}
ILocker::Ptr CLockerFactoryLinux::CreateLSemaphore(std::string aName, int aMaxLock)
{
   return ILocker::Ptr(new CSemaphoreNamed(aName, aMaxLock));
}