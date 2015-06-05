#include "CLockerFactory.h"

ILockerFactory::Ptr ILockerFactory::Create()
{
   return ILockerFactory::Ptr(new CLockerFactoryWin());
}