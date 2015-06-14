#include <pthread.h>
#include "../intf/IThread.h"

//----------------------------------------------------------
class CPosixRunnerThread
: public IRunnerThread
{
public:
   virtual bool Start(IThread* aObj);
   virtual bool Wait();
private:
  pthread_t thread;
};
//----------------------------------------------------------

bool CPosixRunnerThread::Start(IThread* aObj)
{
   return 0 == pthread_create(&thread, NULL, IThread::thread_func, (void*)aObj);
}

bool CPosixRunnerThread::Wait()
{
   return 0 == pthread_join(thread, NULL);
}
//-------------------------------------------------------------------------
IRunnerThread::Ptr IRunnerThread::Create()
{
return new CPosixRunnerThread();
}