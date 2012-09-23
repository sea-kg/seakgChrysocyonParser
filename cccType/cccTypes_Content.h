//  cross compile code c++ 1.0

#ifndef _CCCTYPES_CONTENT_
#define _CCCTYPES_CONTENT_

#include "cccTypes.h"

class cccContent
{
	public:
		cccContent() {};		
		~cccContent() {};
		
	#ifdef __BORLANDC__	
		cccContent(AnsiString str) { m_content = str; };
	public:
		void set( AnsiString strContent ) { m_content = strContent; };
		void set( cccContent &content ) { m_content = content.get(); };
		AnsiString get() { return m_content; };
		void operator = ( cccContent &content ) { set(content.get()); };
		void operator = ( AnsiString strContent ) { set(strContent); };
		bool operator == ( const cccContent &content ) { return (content.get() == m_content); };
		bool operator != ( cccContent &content ) { return (content.get() != m_content); };
	private:
		AnsiString m_content;
	#endif // __BORLANDC__
	
	
};

#endif // _CCCTYPES_CONTENT_