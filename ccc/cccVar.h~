
/*
* cross compile code c++ 1.0
* mrseakg@gmail.com 2012 september 
*
*/

#ifndef _CCCVAR_
#define _CCCVAR_

#include "cccContent.h"
#include "cccVar_Container.h"

class cccVar
{
	public:
		cccVar() {};
		cccVar(cccVar &var) { m_Value = var.getValue(); };
		cccVar(const cccVar &var) { m_Value = var.getValue(); };

		cccVar(cccContent &content) { m_Value = content; };

		cccContent getValue() const { return m_Value; };

		void operator = (cccVar& var) { m_Value = var.getValue(); };
		void operator = (const cccVar& var) { m_Value = var.getValue(); };
		void operator = (cccContent& content) { m_Value = content; };

		virtual void operator + (cccVar& var) {};
		virtual void operator ++ () {};
		virtual void operator - () {};
		
	private:
		cccContent m_Value;
};

#endif
