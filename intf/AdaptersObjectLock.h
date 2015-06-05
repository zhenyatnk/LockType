#ifndef _ADAPTERS_OBJECT_LOCK_H_
#define _ADAPTERS_OBJECT_LOCK_H_

#include "ILocker.h"
#include "ILockerFactory.h"
#include <string>

//-------------------------------------------------
template <class Type>
class CLockedObjectAdapter;

template <class Type>
class CLockedObject 
{
   template <class> friend class CLockedObjectAdapter;

public:   
    template <class lType>
    CLockedObject(lType aObject, ILocker::Ptr SyncObj)
      :mObject(aObject), mSyncObj(SyncObj)
   {   }

   explicit CLockedObject(Type aObject)
      :mObject(aObject), mSyncObj(ILockerFactory::Create()->CreateLSemaphore())
   {   } 
   
   CLockedObject(const CLockedObjectAdapter<Type> &aLockObj)
      :mObject((Type)aLockObj), mSyncObj(aLockObj.mSyncObj->Clone())
   {   }   

   CLockedObject(const CLockedObject &aObj)
      : mObject(aObj.GetObject), mSyncObj(aObj.mSyncObj->Clone())
   {   }


   const Type& GetObject() const
   {
      return mObject;
   }

   void SetObject(Type aObject)
   {
      mObject = aObject;
   }

public:   //Interface locking
   bool Lock()
   {
      return mSyncObj->Lock();
   }
   bool Lock(int aTimeWat)
   {
      return mSyncObj->Lock(aTimeWat);
   }
   void UnLock()
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
   :public Type
{
   template <class> friend class CLockedObject;

public:
   CLockedObjectAdapter()
      :mSyncObj(ILockerFactory::Create()->CreateLSemaphore())
   {   }

   explicit CLockedObjectAdapter(ILocker::Ptr SyncObj)
      :mSyncObj(SyncObj)
   {   }

   CLockedObjectAdapter(const CLockedObject<Type> &aLockObj)
      :Type(aLockObj.GetObject()), mSyncObj(aLockObj.mSyncObj->Clone())
   {   }

   CLockedObjectAdapter(const CLockedObjectAdapter<Type> &aLockObj)
      :Type((Type)aLockObj), mSyncObj(aLockObj.mSyncObj->Clone())
   {   }

public:   //Interface locking
   bool Lock()
   {
      return mSyncObj->Lock();
   }
   bool Lock(int aTimeWat)
   {
      return mSyncObj->Lock(aTimeWat);
   }
   void UnLock()
   {
      mSyncObj->UnLock();
   }
   
private:
   ILocker::Ptr mSyncObj;   
};

#endif