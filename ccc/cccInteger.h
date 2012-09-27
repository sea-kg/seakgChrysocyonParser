
/*
* cross compile code c++ 1.0
* mrseakg@gmail.com 2012 september 
*
*/

#ifndef _CCCINTEGER_
#define _CCCINTEGER_

#include "cccVar.h"

class cccInteger : public cccVar
{
	public:
		cccInteger() { m_t = 0; };
		cccInteger(int t) { m_t = t; };

/*		virtual void ToStream(cccStream &strm) 
		{
				// strm << m_t;
		}; */    

//    int getInt() { return m_t; };
		//Data

	private:
		int m_t;
};

typedef cccInteger cccInt;

#endif
