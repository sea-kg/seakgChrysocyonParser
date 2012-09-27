#ifndef __CCCVAR_H__
#define __CCCVAR_H__

#include "cccContent.h"

class cccVar
{
	public:
		cccVar() {};
		cccVar(cccVar &var) { m_Value = var.getValue(); };
		cccVar(const cccVar &var) { m_Value = var.getValue(); };

		cccVar(cccContent &content) { m_Value = content; };

		cccContent getValue() const { return m_Value; };
//		virtual int getType() const { return m_Value.getType(); };

		void operator = (cccVar& var) { m_Value = var.getValue(); };
		void operator = (const cccVar& var) { m_Value = var.getValue(); };
		void operator = (cccContent& content) { m_Value = content; };

		virtual void operator + (cccVar&) {};
		virtual void operator ++ () {};
		virtual void operator - () {};
		
	private:
		cccContent m_Value;
};


#endif // __CCCVAR_H__
