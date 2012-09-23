
/*
* cross compile code c++ 1.0
* mrseakg@gmail.com 2012 september 
*
*/

#ifndef _CCCCONTENT_
#define _CCCCONTENT_

#include "cccTypes.h"
#include "cccContent_Container.h"

class cccContent
{
	public:
		cccContent() {};
		cccContent(cccContent &content) { this->m_Content = content.getContent(); };
		cccContent(const cccContent &content) { this->m_Content = content.getContent(); };
		CCCCONTENT getContent() const { return m_Content; };

		//void operator = (const cccContent &content) { m_Content = content.getContent(); };
		//void operator = (CCCCONTENT &content) { m_Content = content; };

	private:
		CCCCONTENT m_Content;
};

#endif
