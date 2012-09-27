/*
 * cross compile code c++ 1.0
 * mrseakg@gmail.com 2012 september
 */
 
#ifndef __CCCCONTENT_H__
#define __CCCCONTENT_H__

#include "cccVersion.h"

#define I int

I func1(I i);


#ifdef CCC_USE_QT
	#include <QString>
	#define CCCCONTENT QString
	#define CCCTYPE QString
  #define CCCSUBTYPE QString
	#define CCCLENGTH int
	#define CCCFULLCONTENT QString

#endif // CCC_USE_QT


CCCFULLCONTENT cccContent_getFullContent(
		const CCCTYPE & type, 
		const CCCSUBTYPE & subtype, 
		const CCCLENGTH & length, 
		const CCCCONTENT & content);

void cccContent_setFullContent( 
			const CCCFULLCONTENT & fullContent,
			CCCTYPE & dst_type, 
			CCCSUBTYPE & dst_subtype, 
			CCCLENGTH & dst_length, 
			CCCCONTENT & dst_content);

/*
void cccContent_Copy( 
			const CCCFULLCONTENT & fullContent,
			CCCTYPE & dst_type, 
			CCCSUBTYPE & dst_subtype, 
			CCCLENGTH & dst_length, 
			CCCCONTENT & dst_content);
*/

class cccContent
{
	public:
		cccContent();
		cccContent(cccContent &content);
		cccContent(const cccContent &content);
		void CopyFrom(const cccContent &content);

		CCCCONTENT getContent() const;
		CCCTYPE getType() const;
		CCCTYPE getSubType() const;
		CCCLENGTH getLength() const;

		CCCFULLCONTENT getFullContent() const;
  	void setFullContent(const CCCTYPE & type, const CCCSUBTYPE & subtype, const CCCLENGTH & length, const CCCCONTENT & content);
		void setFullContent(CCCFULLCONTENT content);
		
		//void operator = (const cccContent &content) { m_Content = content.getContent(); };
		//void operator = (CCCCONTENT &content) { m_Content = content; };

	private:
		CCCTYPE m_Type;
		CCCSUBTYPE m_SubType;
		CCCLENGTH m_Length;
		CCCCONTENT m_Content;
};


#endif // __CCCCONTENT_H__
