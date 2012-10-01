#ifndef __CCCVAR_H__
#define __CCCVAR_H__

#include "cccContent.h"

class cccVar
{
	public:
		cccVar() {};
		cccVar(cccVar &var) { m_Value = var.getValue(); };
		cccVar(cccContent &content) { m_Value = content; };
		cccVar(const cccVar &var) { m_Value = var.getValue(); };
		//cccVar(const cccContent &content) { m_Value = cccContent(content); };

		cccContent getValue() const { return m_Value; };
		void setValue(cccContent &content) { m_Value = content; };
		
		void operator = (cccVar& var) { m_Value = var.getValue(); };
		//void operator = (const cccVar& var) { m_Value = var.getValue(); };
		//void operator = (cccContent& content) { m_Value = content; };

		virtual cccVar operator + (cccVar& var) 
		{
			cccContent content;
			content.setContent(var.getValue().getContent() + m_Value.getContent());
			return cccVar(content); 
		};
		virtual void operator ++ () {};
		virtual void operator - () {};
		
	private:
		cccContent m_Value;
};


#endif // __CCCVAR_H__
