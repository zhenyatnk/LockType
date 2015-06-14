#include "./intf/AdaptersObjectLock.h"
#include "./intf/IThread.h"
#include "./utst/utst.h"
#include <iostream>
#include <vector>
#include "./intf/ILockerFactory.h"

ILockerFactory::Ptr gFactorySync;

int testThread()
{
   class TestThread
      :public IThread
   {
   public:
      TestThread(int &aResult)
         :mResult(aResult)
      {   }

      virtual void Run()
      {
         mResult = 12;
      }

   private:
      int &mResult;
   };

   int lResult = 0;
   TestThread *lThread = new TestThread(lResult);
   UASSERT(0 == lResult);
   lThread->start();
   lThread->wait();
   UASSERT(12 == lResult);
   
   delete lThread;
   return 1;
}

CLockedObjectAdapter<std::vector<int> > gVectorLocked;
int testMutextUnNamed()
{
   class TestThread
      :public IThread
   {
   public:
      TestThread(int &aResult)
         :mResult(aResult)
      {   }

      virtual void Run()
      {
         if (!gVectorLocked.Lock(500))
            mResult = -1;
         else
         {
            mResult = 1;
            gVectorLocked.UnLock();
         }
      }

   private:
      int &mResult;
   };

   int lResult = 0;
   TestThread *lThread = new TestThread(lResult);
   UASSERT(0 == lResult);
   gVectorLocked = CLockedObjectAdapter<std::vector<int> >(gFactorySync->CreateLMutex());
   UASSERT(gVectorLocked.Lock(500));
   lThread->start();
   lThread->wait();
   UASSERT(-1 == lResult);

   gVectorLocked.UnLock();
   lThread->start();
   lThread->wait();
   UASSERT(1 == lResult);

   return 1;
}

int testMutextNamed()
{
   class TestThread
      :public IThread
   {
   public:
      TestThread(int &aResult)
         :mResult(aResult)
      {   }

      virtual void Run()
      {
         if (!gVectorLocked.Lock(500))
            mResult = -1;
         else
         {
            mResult = 1;
            gVectorLocked.UnLock();
         }
      }

   private:
      int &mResult;
   };

   int lResult = 0;
   TestThread *lThread = new TestThread(lResult);
   UASSERT(0 == lResult);
   gVectorLocked = CLockedObjectAdapter<std::vector<int> >(gFactorySync->CreateLMutex("/GlobalMutex"));
   UASSERT(gVectorLocked.Lock(500));
   lThread->start();
   lThread->wait();
   UASSERT(-1 == lResult);

   gVectorLocked.UnLock();
   lThread->start();
   lThread->wait();
   UASSERT(1 == lResult);

   return 1;
}

int testCriticalSection()
{
   class TestThread
      :public IThread
   {
   public:
      TestThread(int &aResult)
         :mResult(aResult)
      {   }

      virtual void Run()
      {
         if (!gVectorLocked.Lock(500))
            mResult = -1;
         else
         {
            mResult = 1;
            gVectorLocked.UnLock();
         }
      }

   private:
      int &mResult;
   };

   int lResult = 0;
   TestThread *lThread = new TestThread(lResult);
   UASSERT(0 == lResult);
   gVectorLocked = CLockedObjectAdapter<std::vector<int> >(gFactorySync->CreateLCriticalSection());
   UASSERT(gVectorLocked.Lock(500));
   lThread->start();
   lThread->wait();
   UASSERT(-1 == lResult);

   gVectorLocked.UnLock();
   lThread->start();
   lThread->wait();
   UASSERT(1 == lResult);

   return 1;
}

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
   CLockedObject<std::vector<int> > lVectorLocked(std::vector<int>(), gFactorySync->CreateLSemaphore());
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
   CLockedObjectAdapter<std::vector<int> > lVectorLocked(gFactorySync->CreateLSemaphore());
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
   CLockedObjectAdapter<std::vector<int> > lVectorLocked(gFactorySync->CreateLSemaphore());
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

int testLockerAdapterCopyCtorValue()
{
   CLockedObjectAdapter<std::vector<int> > lVectorLocked(gFactorySync->CreateLSemaphore());
   lVectorLocked.push_back(1);
   lVectorLocked.push_back(2);
   CLockedObjectAdapter<std::vector<int> > lVectorLocked1 = lVectorLocked;

   UASSERT(lVectorLocked1.size() == 2);
   UASSERT(lVectorLocked[0] == lVectorLocked1[0]);
   UASSERT(lVectorLocked[1] == lVectorLocked1[1]);

   lVectorLocked.push_back(3);
   UASSERT(lVectorLocked1.size() == 2);
   UASSERT(lVectorLocked.size() == 3);

   return 1;
}
int testLockerAdapterCopyOprtValue()
{
   CLockedObjectAdapter<std::vector<int> > lVectorLocked(gFactorySync->CreateLSemaphore());
   lVectorLocked.push_back(1);
   lVectorLocked.push_back(2);
   CLockedObjectAdapter<std::vector<int> > lVectorLocked1;
   lVectorLocked1 = lVectorLocked;

   UASSERT(lVectorLocked1.size() == 2);
   UASSERT(lVectorLocked[0] == lVectorLocked1[0]);
   UASSERT(lVectorLocked[1] == lVectorLocked1[1]);

   lVectorLocked.push_back(3);
   UASSERT(lVectorLocked1.size() == 2);
   UASSERT(lVectorLocked.size() == 3);

   return 1;
}
int testLockerCopyCtorValue()
{
   CLockedObject<std::vector<int> > lVectorLocked(std::vector<int>(), gFactorySync->CreateLSemaphore());
   lVectorLocked.GetObject().push_back(1);
   lVectorLocked.GetObject().push_back(2);
   CLockedObject<std::vector<int> > lVectorLocked1 = lVectorLocked;

   UASSERT(lVectorLocked1.GetObject().size() == 2);
   UASSERT(lVectorLocked.GetObject()[0] == lVectorLocked1.GetObject()[0]);
   UASSERT(lVectorLocked.GetObject()[1] == lVectorLocked1.GetObject()[1]);

   lVectorLocked.GetObject().push_back(3);
   UASSERT(lVectorLocked1.GetObject().size() == 2);
   UASSERT(lVectorLocked.GetObject().size() == 3);

   return 1;
}

int testLockerCopyOprtValue()
{
   CLockedObject<std::vector<int> > lVectorLocked(std::vector<int>(), gFactorySync->CreateLSemaphore());
   lVectorLocked.GetObject().push_back(1);
   lVectorLocked.GetObject().push_back(2);
   CLockedObject<std::vector<int> > lVectorLocked1((std::vector<int>)std::vector<int>());
   lVectorLocked1 = lVectorLocked;

   UASSERT(lVectorLocked1.GetObject().size() == 2);
   UASSERT(lVectorLocked.GetObject()[0] == lVectorLocked1.GetObject()[0]);
   UASSERT(lVectorLocked.GetObject()[1] == lVectorLocked1.GetObject()[1]);

   lVectorLocked.GetObject().push_back(3);
   UASSERT(lVectorLocked1.GetObject().size() == 2);
   UASSERT(lVectorLocked.GetObject().size() == 3);

   return 1;
}

int main(int argc, char* argv[])
{
   gFactorySync = ILockerFactory::Create();
   START_UTST;
   
   RUN_UTST(testUASSERT);
   RUN_UTST(testThread);

   RUN_UTST(testMutextNamed);
   RUN_UTST(testMutextUnNamed);
   RUN_UTST(testCriticalSection);
   RUN_UTST(testSemaphoreUnNamed);
   RUN_UTST(testSemaphoreNamed);
   RUN_UTST(testSemaphoreCountLock);
   RUN_UTST(testEvent);

   RUN_UTST(testDefaultSync);
   RUN_UTST(testConvertLocker1);
   RUN_UTST(testConvertLocker2);
   RUN_UTST(testConvertLockerCopyValue);
   RUN_UTST(testLockerAdapterCopyCtorValue);
   RUN_UTST(testLockerAdapterCopyOprtValue);
   RUN_UTST(testLockerCopyCtorValue);
   RUN_UTST(testLockerCopyOprtValue);

   FINISH_UTST;
   return 0;
}

