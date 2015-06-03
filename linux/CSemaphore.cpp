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
   CSemaphore(std::string);
   CSemaphore(std::string, int);
   virtual ~CSemaphore();

   virtual bool Lock() override;
   virtual bool Lock(int aTimeWat) override;
   virtual void UnLock() override;

private:
   sem_t* mSemaphoreHandle;
};
//-------------------------------------------------
CSemaphore::CSemaphore()
{
   mSemaphoreHandle = new sem_t();
   sem_init(mSemaphoreHandle, 0 ,1);
}
CSemaphore::CSemaphore(int aMaxLock)
{
   mSemaphoreHandle = new sem_t();
   sem_init(mSemaphoreHandle, 0 ,aMaxLock);
}
CSemaphore::CSemaphore(std::string aName)
{
   mSemaphoreHandle = sem_open(aName.c_str(), O_RDRW|O_CREATE, 0, 1);
}
CSemaphore::CSemaphore(std::string aName, int aMaxLock)
{
   mSemaphoreHandle = sem_open(aName.c_str(), O_RDRW|O_CREATE, 0, aMaxLock);
}
CSemaphore::~CSemaphore()
{
   sem_close(mSemaphoreHandle);
}

bool CSemaphore::Lock()
{
   return sem_wait(mSemaphoreHandle) >=0;
}

bool CSemaphore::Lock(int aTimeWat)
{
   return sem_wait(mSemaphoreHandle) >=0;
}

void CSemaphore::UnLock()
{
   sem_post(mSemaphoreHandle);
}

//-------------------------------------------------
ILocker::Ptr CLockerFactory::CreateLSemaphore()
{
   return ILocker::Ptr(new CSemaphore());
}

ILocker::Ptr CLockerFactory::CreateLSemaphore(int aMaxLock)
{
   return ILocker::Ptr(new CSemaphore(aMaxLock));
}

ILocker::Ptr CLockerFactory::CreateLSemaphore(std::string aName)
{
   return ILocker::Ptr(new CSemaphore(aName));
}
ILocker::Ptr CLockerFactory::CreateLSemaphore(std::string aName, int aMaxLock)
{
   return ILocker::Ptr(new CSemaphore(aName, aMaxLock));
}