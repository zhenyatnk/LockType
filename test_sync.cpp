#include "./intf/AdaptersObjectLock.h"
#include "./utst/utst.h"
#include <iostream>
#include <vector>
#include "./intf/ILockerFactory.h"

ILockerFactory::Ptr gFactorySync;

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

int testCopyUnNamedLocked()
{
   CLockedObjectAdapter<std::vector<int> > lVectorLocked(gFactorySync->CreateLSemaphore());
   CLockedObjectAdapter<std::vector<int> > lVectorLocked1 = lVectorLocked;
   UASSERT(lVectorLocked.Lock(500));
   UASSERT(lVectorLocked1.Lock(500));

   UASSERT(!lVectorLocked.Lock(500));
   UASSERT(!lVectorLocked1.Lock(500));


   lVectorLocked.UnLock();
   lVectorLocked1.UnLock();
   UASSERT(lVectorLocked.Lock(500));
   UASSERT(lVectorLocked1.Lock(500));

   lVectorLocked.UnLock();
   lVectorLocked1.UnLock();

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

int testUASSERT()
{
   UASSERT(1==1);
   UASSERT(1!=4);

   return 1;
}

int testConvertLocker1()
{
   CLockedObject<std::vector<int>> lVectorLocked(std::vector<int>(), gFactorySync->CreateLSemaphore());
   CLockedObjectAdapter<std::vector<int> > lVectorLocked1 = lVectorLocked;
   UASSERT(lVectorLocked.Lock(500));
   UASSERT(lVectorLocked1.Lock(500));

   UASSERT(!lVectorLocked.Lock(500));
   UASSERT(!lVectorLocked1.Lock(500));


   lVectorLocked.UnLock();
   lVectorLocked1.UnLock();
   UASSERT(lVectorLocked.Lock(500));
   UASSERT(lVectorLocked1.Lock(500));

   lVectorLocked.UnLock();
   lVectorLocked1.UnLock();

   return 1;
}

int testConvertLocker2()
{
   CLockedObjectAdapter<std::vector<int>> lVectorLocked(gFactorySync->CreateLSemaphore());
   CLockedObject<std::vector<int> > lVectorLocked1 = lVectorLocked;
   UASSERT(lVectorLocked.Lock(500));
   UASSERT(lVectorLocked1.Lock(500));

   UASSERT(!lVectorLocked.Lock(500));
   UASSERT(!lVectorLocked1.Lock(500));

   lVectorLocked.UnLock();
   lVectorLocked1.UnLock();
   UASSERT(lVectorLocked.Lock(500));
   UASSERT(lVectorLocked1.Lock(500));

   lVectorLocked.UnLock();
   lVectorLocked1.UnLock();

   return 1;
}
int testConvertLockerCopyValue()
{
   CLockedObjectAdapter<std::vector<int>> lVectorLocked(gFactorySync->CreateLSemaphore());
   lVectorLocked.push_back(1);
   lVectorLocked.push_back(2);
   CLockedObject<std::vector<int> > lVectorLocked1 = lVectorLocked;

   UASSERT(lVectorLocked1.GetObject().size() == 2);
   UASSERT(lVectorLocked[0] == lVectorLocked1.GetObject()[0]);
   UASSERT(lVectorLocked[1] == lVectorLocked1.GetObject()[1]);

   lVectorLocked.push_back(3);
   UASSERT(lVectorLocked1.GetObject().size() == 2);
   UASSERT(lVectorLocked.size() == 3);

   return 1;
}

int main(int argc, char* argv[])
{
   gFactorySync = ILockerFactory::Create();
   START_UTST;
   
   RUN_UTST(testUASSERT);
   RUN_UTST(testSemaphoreUnNamed);
   RUN_UTST(testSemaphoreNamed);
   RUN_UTST(testSemaphoreCountLock);
   RUN_UTST(testEvent);
   RUN_UTST(testDefaultSync);
   RUN_UTST(testConvertLocker1);
   RUN_UTST(testConvertLocker2);
   RUN_UTST(testConvertLockerCopyValue);

   FINISH_UTST;
   return 0;
}

