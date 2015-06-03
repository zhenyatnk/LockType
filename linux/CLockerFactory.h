#ifndef _LOCKER_FACTORY_LINUX_H_
#define _LOCKER_FACTORY_LINUX_H_


#include "../intf/ILocker.h"
#include "../intf/ILockerFactory.h"

class CLockerFactory: public ILockerFactory
{
public: //Interface ILockerFactory
	virtual ILocker::Ptr CreateLMutex() override;
   virtual ILocker::Ptr CreateLMutex(std::string) override;
   virtual ILocker::Ptr CreateLSemaphore() override;
   virtual ILocker::Ptr CreateLSemaphore(int) override;
   virtual ILocker::Ptr CreateLSemaphore(std::string) override;
   virtual ILocker::Ptr CreateLSemaphore(std::string, int) override;
   virtual ILocker::Ptr CreateLCriticalSection() override;
   virtual ILocker::Ptr CreateLEvent() override;
   virtual ILocker::Ptr CreateLEvent(std::string) override;
};

#endif