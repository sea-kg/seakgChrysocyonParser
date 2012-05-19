

#include "../stack.h"

namespace seakgChrysocyon
{
	
	bool test_Stack()
	{
		std::cout << "\r\n\t -- test chrysocyon.stack -- \r\n";

		seakgChrysocyon::Stack<char> *pStack = NULL;
		pStack = new seakgChrysocyon::Stack<char>();

		pStack->Push( 'A' );
		pStack->Push( 'B' );
		pStack->Push( 'C' );

		if(pStack->getCount() != 3)
		{
			std::cout << "\r\n\t !! not working !! (point 1) \r\n";
			return false;
		};
		
		char ch = ' ';
		pStack->Pop(ch);
		if( ch != 'C' )
		{
			std::cout << "\r\n\t !! not working !! (point 2) \r\n";
			return false;
		};

		pStack->Pop(ch);
		pStack->Pop(ch);

		if( ch != 'A' )
		{
			std::cout << "\r\n\t !! not working !! (point 3) \r\n";
			return false;
		};

		if(pStack->getCount() != 0)
		{
			std::cout << "\r\n\t !! not working !! (point 4) \r\n";
			return false;
		};

		return true;
	};
};


