#ifndef _ADAPTERS_OBJECT_LOCK_H_
#define _ADAPTERS_OBJECT_LOCK_H_

#include "ILocker.h"
#include "ILockerFactory.h"
#include <string>

//-------------------------------------------------
template <class Type>
class CLockedObject 
   :public ILocker
{
public:   
    template <class lType>
    CLockedObject(lType aObject, ILocker::Ptr SyncObj)
      :mObject(aObject), mSyncObj(SyncObj)
   {
   }
   explicit CLockedObject(Type aObject)
      :mObject(aObject)
   {
      mSyncObj = ILockerFactory::Create()->CreateLSemaphore();
   }   
   
   Type GetObject()
   {
      return mObject;
   }

   void SetObject(Type aObject)
   {
      mObject = aObject;
   }

public:   //Interface ILocker
   virtual bool Lock() override
   {
      return mSyncObj->Lock();
   }
   virtual bool Lock(int aTimeWat) override
   {
      return mSyncObj->Lock(aTimeWat);
   }
   virtual void UnLock() override
   {
      mSyncObj->UnLock();
   }
   
private:
   Type mObject;
   ILocker::Ptr mSyncObj;
};

//-------------------------------------------------
template <class Type>
class CLockedObjectAdapter
   :public ILocker, public Type
{
public:
   explicit CLockedObjectAdapter(ILocker::Ptr SyncObj)
      :mSyncObj(SyncObj)
   {
   }
   CLockedObjectAdapter()
   {
      mSyncObj = ILockerFactory::Create()->CreateLSemaphore();
   }  
   
public:   //Interface ILocker
   virtual bool Lock()
   {
      return mSyncObj->Lock();
   }
   virtual bool Lock(int aTimeWat)
   {
      return mSyncObj->Lock(aTimeWat);
   }
   virtual void UnLock()
   {
      mSyncObj->UnLock();
   }
   
private:
   ILocker::Ptr mSyncObj;   
};

#endif