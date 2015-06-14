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

   virtual ILocker* Clone() override;

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
   return 0 != TryEnterCriticalSection(&mCriticalSection);
}

void CCriticalSection::UnLock()
{
   LeaveCriticalSection(&mCriticalSection);
}

ILocker* CCriticalSection::Clone()
{
   return new CCriticalSection();
}

//-------------------------------------------------
ILocker::Ptr CLockerFactoryWin::CreateLCriticalSection()
{
   return ILocker::Ptr(new CCriticalSection());
}

