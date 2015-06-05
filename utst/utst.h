#ifndef _U_TST_H_
#define _U_TST_H_

static unsigned int count_valid_test = 0;
static unsigned int count_invalid_test = 0;

#define START_UTST\
   count_valid_test = 0;\
   count_invalid_test = 0;

#define RUN_UTST(TestName)\
   if(!!TestName())\
      ++count_valid_test;\
   else\
   {\
      std::cout << "\tFail test:" << #TestName << std::endl; \
       ++count_invalid_test;\
   }

#define FINISH_UTST\
   if(!count_invalid_test)\
      std::cout << "Run tests:" << count_valid_test << std::endl;\
   else\
      std::cout << "Fail test:" << count_invalid_test << std::endl;
   
#define UASSERT(expr)\
   if(!(expr))\
   {\
      std::cout << "\t\tFail expression:" << #expr << std::endl;\
      return 0;\
   }
   
#endif