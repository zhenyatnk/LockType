#ifndef _U_TST_H_
#define _U_TST_H_

#define RUN_UTST(TestName)\
   std::cout << "Run test:" << #TestName << std::endl; \
   std::cout<<" Result test:"<<TestName()<<std::endl;
   
#define UASSERT(expr)\
   if(!(expr))\
   {\
   std::cout << "\tFail expression:" << #expr << std::endl; \
      return 0;\
   }
   
#endif