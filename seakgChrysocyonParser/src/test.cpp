
//#include <iostream.h>
#include <iostream>
#include "unittest/unittest_stack.cpp"



namespace seakgChrysocyon
{
	bool AllTests()
	{
		std::cout << "\r\n --> seakgChrysocyon::test_Stack()\r\n" ;
		
		if( ! seakgChrysocyon::test_Stack() )
		{
			return false;
		}

		return true;
	};	
};

