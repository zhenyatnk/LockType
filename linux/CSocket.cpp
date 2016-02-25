#include "../intf/ISocket.h"

#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>

//---------------------------------------------
class CSocketInitializer
   :public ISocketInitializer
{
public:
   CSocketInitializer();
   ~CSocketInitializer();

public:
};

CSocketInitializer::CSocketInitializer()
{
}

CSocketInitializer::~CSocketInitializer()
{
}

ISocketInitializer::Ptr ISocketInitializer::Create()
{
   return ISocketInitializer::Ptr(new CSocketInitializer());
}

//---------------------------------------------
sockaddr_in Convert(const TConectionParms &aConParms)
{
   sockaddr_in mAddr;
   memset(&mAddr, 0, sizeof(mAddr));
   mAddr.sin_addr.s_addr = htonl(INADDR_ANY);
   if (aConParms.mHostName.empty())
      mAddr.sin_addr.s_addr = inet_addr(aConParms.mIP.c_str());
   else
   {
      hostent *lHost = gethostbyname(aConParms.mHostName.c_str());
      if (!lHost)
         throw("Нельзя распознать адрес");
      mAddr.sin_addr.s_addr = *(u_long *)(lHost->h_addr_list[0]);
   }
   mAddr.sin_port = htons(aConParms.mPort);
   mAddr.sin_family = aConParms.mFamily;
   return mAddr;
}
//---------------------------------------------
class CSocket
   :public ISocket
{
public:
   explicit CSocket(const int &aSocket);
   explicit CSocket(const TConectionParms &aConParms);
   virtual ~CSocket();
   
   virtual void Connect();
   virtual void Send(std::string aMessage);
   virtual bool Receive(char* aBuff, int aSize);

   virtual void Bind();
   virtual void Listen(int aMaxConnection);
   virtual ISocket::Ptr Accept();

private:
    int mSocket;
    sockaddr_in mConParms;
};

CSocket::CSocket(const int &aSocket)
  :mSocket(aSocket)
{
}

CSocket::CSocket(const TConectionParms &aConParms)
   :mConParms(Convert(aConParms))
{
   mSocket = socket(AF_INET, SOCK_STREAM, 0);
}

CSocket::~CSocket()
{
   close(mSocket);
}

void CSocket::Connect()
{
   connect(mSocket, (sockaddr *)&mConParms, sizeof(mConParms));
}

void CSocket::Send(std::string aMessage)
{
   send(mSocket, aMessage.c_str(), strlen(aMessage.c_str()), 0);
}

bool CSocket::Receive(char* aBuff, int aSize)
{
   int size_recieved;
   if ((size_recieved = recv(mSocket, aBuff, aSize, 0)))
      aBuff[size_recieved] = 0;
   return !!size_recieved;
}

void CSocket::Bind()
{
   bind(mSocket, (sockaddr *)&mConParms, sizeof(mConParms));
}

void CSocket::Listen(int aMaxConnection)
{
   listen(mSocket, aMaxConnection);
}

ISocket::Ptr CSocket::Accept()
{
   int lRetSocket = accept(mSocket, 0, 0);
   if (0 == lRetSocket)
      return ISocket::Ptr(NULL);
   else
      return ISocket::Ptr(new CSocket(lRetSocket));
}

ISocket::Ptr ISocket::Create(const TConectionParms &aConParms)
{
   return ISocket::Ptr(new CSocket(aConParms));
}