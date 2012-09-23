/*
* cross compile code c++ 1.0
* mrseakg@gmail.com 2012 september 
*
*/

#ifndef _CCCSTREAM_
#define _CCCSTREAM_

#include <iostream>
#include "cccContainer.h"

class cccStream
{
	public:
		cccStream() {};

		cccStream& operator << (const cccContainer t)
	  {
			t.ToStream(*this);
			return *this;
		};


		//Data
/*
		cccStream& operator << (int t)
		{
			std::cout << t;
			return *this; 
		};
*/

/*
		cccStream& operator << (cccInt * t)
	  {
			std::cout << (t->getInt());
			return *this; 
		};

		cccStream& operator << (cccInt t)
	  {
			std::cout << (t.getInt());
			return *this; 
		};

*/
/*		cccStream& operator << (const cccContainer * t)
	  {
			t->ToStream(*this);
			return *this; 
		};*/

	private:
		// 
};

#endif

