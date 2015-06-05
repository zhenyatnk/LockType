#include "./intf/AdaptersObjectLock.h"
#include "./utst/utst.h"
#include <iostream>
#include <vector>
#include "./intf/ILockerFactory.h"

ILockerFactory::Ptr gFactorySync;

class Base
{
};
class A: public Base
{
};


int testSemaphoreUnNamed()
{
   CLockedObjectAdapter<std::vector<int> > lVectorLocked(gFactorySync->CreateLSemaphore());
   UASSERT(lVectorLocked.Lock(500));
   UASSERT(!lVectorLocked.Lock(500));

   lVectorLocked.UnLock();
   UASSERT(lVectorLocked.Lock(500));

   lVectorLocked.UnLock();

   return 1;
}
int testSemaphoreCountLock()
{
   CLockedObjectAdapter<std::vector<int> > lVectorLocked(gFactorySync->CreateLSemaphore(2));
   UASSERT(lVectorLocked.Lock(500));
   UASSERT(lVectorLocked.Lock(500));
   UASSERT(!lVectorLocked.Lock(500));

   lVectorLocked.UnLock();
   lVectorLocked.UnLock();
   UASSERT(lVectorLocked.Lock(500));

   lVectorLocked.UnLock();

   return 1;
}
int testSemaphoreNamed()
{
   CLockedObjectAdapter<std::vector<int> > lVectorNLocked(gFactorySync->CreateLSemaphore("/GlobalSemaphore"));

   UASSERT(lVectorNLocked.Lock(500));
   UASSERT(!lVectorNLocked.Lock(500));

   lVectorNLocked.UnLock();
   UASSERT(lVectorNLocked.Lock(500));

   lVectorNLocked.UnLock();

   return 1;
}

int testCriticalSection()
{
   CLockedObjectAdapter<std::vector<int> > lVectorLocked(gFactorySync->CreateLCriticalSection());
   UASSERT(lVectorLocked.Lock(500));
   UASSERT(!lVectorLocked.Lock(500));

   lVectorLocked.UnLock();
   UASSERT(lVectorLocked.Lock(500));

   lVectorLocked.UnLock();

   return 1;
}

int testEvent()
{
   CLockedObjectAdapter<std::vector<int> > lVectorLocked(gFactorySync->CreateLEvent());
   UASSERT(lVectorLocked.Lock(500));
   UASSERT(!lVectorLocked.Lock(500));

   lVectorLocked.UnLock();
   UASSERT(lVectorLocked.Lock(500));

   lVectorLocked.UnLock();

   return 1;
}

int testDefaultSync()
{
   CLockedObjectAdapter<std::vector<int> > lVectorLocked;
   UASSERT(lVectorLocked.Lock(500));
   UASSERT(!lVectorLocked.Lock(500));

   lVectorLocked.UnLock();
   UASSERT(lVectorLocked.Lock(500));

   lVectorLocked.UnLock();

   return 1;
}

int main(int argc, char* argv[])
{
   gFactorySync = ILockerFactory::Create();
   
   RUN_UTST(testSemaphoreUnNamed);
   RUN_UTST(testSemaphoreNamed);
   RUN_UTST(testSemaphoreCountLock);
   RUN_UTST(testEvent);
   RUN_UTST(testDefaultSync);
   return 0;
}

