#ifndef _I_SOCKET_H_
#define _I_SOCKET_H_

#include <string>
#include "DSmartPtr.h"

//---------------------------------------------
class ISocketInitializer
{
public:
   typedef SmartPtr<ISocketInitializer>::Ptr Ptr;

public:
   virtual ~ISocketInitializer()
   {}

public:
   static ISocketInitializer::Ptr Create();
};

//---------------------------------------------
struct TConectionParms
{
public:
   TConectionParms()
      :mHostName(""), mIP(""), mPort(0), mFamily(0)
   {}
   std::string mHostName;
   std::string mIP;
   int mPort;
   unsigned int mFamily;
};
//---------------------------------------------
class ISocket
{
public:
   typedef SmartPtr<ISocket>::Ptr Ptr;

public:
   virtual ~ISocket()
   {}

   virtual void Connect() = 0;
   virtual void Send(std::string aMessage) = 0;
   virtual bool Receive(char* aBuff, int aSize) = 0;

   virtual void Bind() = 0;
   virtual void Listen(int aMaxConnection) = 0;
   virtual ISocket::Ptr Accept() = 0;

public:
   static ISocket::Ptr Create(const TConectionParms &aConParms);
};

#endif