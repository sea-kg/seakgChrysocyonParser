
/*
* cross compile code c++ 1.0
* mrseakg@gmail.com 2012 september 
*
*/

#ifndef _CCCSTRING_CONTAINER_
#define _CCCSTRING_CONTAINER_

#include "cccVersion.h"
//#include "cccInteger.h"
//#include "cccStream.h"

	#ifdef CCC_USE_QT
		#include <QString>

		#define CCCSTRING QString
	
		CCCSTRING String_Init(CCCSTRING) { return ""; };
		CCCSTRING String_Init(CCCSTRING, const CCCSTRING& t) { return t; };
		cccInt String_Length(const QString& t) { return cccInt( t.length() ); };
		// void String_PushToStream(cccStream &strm, CCCSTRING t) { strm << t; };

	#endif

#endif // _CCCSTRING_CONTAINER_
