// Mutex.cpp : Defines the entry point for the console application.
//
#include "windows.h"
#include "../intf/ILocker.h"
#include "CLockerFactory.h"
#include <string>

//-------------------------------------------------
class CCriticalSection:public ILocker
{
public:
   CCriticalSection();
   virtual ~CCriticalSection();

   virtual bool Lock() override;
   virtual bool Lock(int aTimeWat) override;
   virtual void UnLock() override;

private:
   CRITICAL_SECTION mCriticalSection;
};
//-------------------------------------------------
CCriticalSection::CCriticalSection()
{
   InitializeCriticalSection(&mCriticalSection);
}

CCriticalSection::~CCriticalSection()
{
}

bool CCriticalSection::Lock()
{
   EnterCriticalSection(&mCriticalSection);
   return true;
}

bool CCriticalSection::Lock(int aTimeWat)
{
   EnterCriticalSection(&mCriticalSection);
   return true;
}

void CCriticalSection::UnLock()
{
   LeaveCriticalSection(&mCriticalSection);
}
//-------------------------------------------------
ILocker::Ptr CLockerFactory::CreateLCriticalSection()
{
   return ILocker::Ptr(new CCriticalSection());
}

