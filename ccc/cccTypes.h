
/*
* cross compile code c++ 1.0
* mrseakg@gmail.com 2012 september 
*
*/

#ifndef _CCCTYPE_
#define _CCCTYPE_

#include "cccVersion.h"

enum cccType
{
	eVar = 0,
	eInt = 1,
	eChar = 2,
	eString = 3
};

class cccContent;
class cccVar;
class cccInteger;
class cccChar; // : public cccVar;
class cccString; //: public cccVar;

//class cccInt : public cccVar;
//class cccFloat : public cccVar;
//class cccEnum : public cccVar;
//class cccError : public cccVar;

#endif
