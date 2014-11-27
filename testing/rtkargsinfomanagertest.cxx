#include <rtkGgoArgsInfoManager.h>
#include <cstdlib>
#include <iostream>

class args_info_test
{
public:
  int testVar;
  args_info_test() : testVar(true) 
  {}
};

class cleanup_functor
{
public:
  void operator()( args_info_test * args_info )
    {
    args_info->testVar = false;
    }
};

void cleanup_function( args_info_test * args_info )
{
  args_info->testVar = false;
}

int main(int argc, char** argv)
{
  args_info_test args_info_1, args_info_2;

  { // new scope - manager does cleanup on destruction
  args_info_manager< args_info_test > manager_1( args_info_1, cleanup_function );

  cleanup_functor functor;
  args_info_manager< args_info_test, cleanup_functor > manager_2( args_info_2, functor );
  }

  if( args_info_1.testVar )
    {
    std::cout << "Test FAILED -- cleanup using a function didn't work." << std::endl;
    return EXIT_FAILURE;
    }

  if( args_info_2.testVar )
    {
    std::cout << "Test FAILED -- cleanup using a functor didn't work." << std::endl;
    return EXIT_FAILURE;
    }

  // otherwise
  return EXIT_SUCCESS;
}



