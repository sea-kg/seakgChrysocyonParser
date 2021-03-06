#ifndef __SEAKG_CHRYSOCYON_INTERFACES_H__
#define __SEAKG_CHRYSOCYON_INTERFACES_H__

#include "enums.h"
#include "stack.h"

namespace seakgChrysocyon
{

	//-----------------------------------------------
	// INTERFACE : READER
	
	template<typename Element>
	class InterfaceChrysocyonReader // interface
	{
		public:
		   virtual bool GetNextElement( Element &, int & ) = 0;
			virtual bool Eof() = 0;
	};
	
	//-----------------------------------------------
	// INTERFACE : PUPPY
	
	template<typename Element, typename ArrayOfElement>
	class InterfaceChrysocyonPuppy // interface
	{
		public:
			virtual chrysocyonAnswer SendElement(Element) = 0;
			virtual void GetResult( seakgChrysocyon::Stack< ArrayOfElement > * ) = 0;
			virtual void Reset() = 0;
			virtual bool StepBack() = 0;
	};
};

#endif // __SEAKG_CHRYSOCYON_INTERFACES_H__
