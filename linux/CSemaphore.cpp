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

   ILocker* Clone() override;

private:
   sem_t mSemaphoreHandle;
   int mMaxLock;
};
//-------------------------------------------------
CSemaphore::CSemaphore()
  :mMaxLock(1)
{
   sem_init(&mSemaphoreHandle, 0 ,mMaxLock);
}
CSemaphore::CSemaphore(int aMaxLock)
   :mMaxLock(aMaxLock)
{
   sem_init(&mSemaphoreHandle, 0 ,mMaxLock);
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
   lTimeStruct.tv_sec = 0;
   lTimeStruct.tv_nsec = 1000000*aTimeWait;
   return sem_timedwait(&mSemaphoreHandle, &lTimeStruct) >=0;
}

void CSemaphore::UnLock()
{
   sem_post(&mSemaphoreHandle);
}

ILocker* CSemaphore::Clone()
{
   return new CSemaphore(mMaxLock);
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

   ILocker* Clone() override;

private:
   sem_t* mSemaphoreHandle;
   std::string mName;
   int mMaxLock;
};
//-------------------------------------------------
CSemaphoreNamed::CSemaphoreNamed(std::string aName)
  :mName(aName), mMaxLock(1)
{
   mSemaphoreHandle = sem_open(mName.c_str(), O_RDWR|O_CREAT, S_IRWXO | S_IRWXG | S_IRWXU, mMaxLock);
}
CSemaphoreNamed::CSemaphoreNamed(std::string aName, int aMaxLock)
  :mName(aName), mMaxLock(aMaxLock)
{
   mSemaphoreHandle = sem_open(mName.c_str(), O_RDWR|O_CREAT, S_IRWXO | S_IRWXG | S_IRWXU, mMaxLock);
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
   lTimeStruct.tv_sec = 0;
   lTimeStruct.tv_nsec = 1000000*aTimeWait;
   return sem_timedwait(mSemaphoreHandle, &lTimeStruct) >=0;
}

void CSemaphoreNamed::UnLock()
{
   sem_post(mSemaphoreHandle);
}

ILocker* CSemaphoreNamed::Clone()
{
   return new CSemaphoreNamed(mName, mMaxLock);
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