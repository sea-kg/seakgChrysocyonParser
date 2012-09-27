#include "cccContent.h"

#ifdef CCC_USE_QT

	// -----------------------------------------------------------------------
  CCCFULLCONTENT Content_getFullContent(const CCCTYPE & type, const CCCTYPE & subtype, const CCCLENGTH & length, const CCCCONTENT & content)
	{
		// XML
		// return QString( "<content value='" + content + "' type='" + QString(type) + "' length='" + QString(length) + "' />");
		// JSON
		// return QString( "{ \"type\": \"" + type + "\", \"value\": \"" + content + "\", \"length\": " + QString(length) + " }" );
		// simple
		QString len;
		len.setNum(length, 10);
		return QString( "[" + type + ":" + subtype + ":" + len + ":" + content + "]" );
	};
	
	// -----------------------------------------------------------------------
	void Content_setFullContent(
			const CCCFULLCONTENT & fullContent,					
			CCCTYPE & dst_type,
			CCCSUBTYPE & dst_subtype, 
			CCCLENGTH & dst_length,
			CCCCONTENT & dst_content)
	{
		// TODO: parsing
		int nState = 0;
		dst_type = "";
		for(int i = 0; i < fullContent.length(); i++)
		{
			QChar ch = fullContent.at(i); 
			if(nState == 0 && ch != '[') break;
			else
			if(nState == 0 && ch == '[') nState = 1;
			else
			if(nState == 1 && ch == ':') nState = 2;
			else
			if(nState == 2 && ch == ':') nState = 3;
			else
			if(nState == 3 && ch == ':') nState = 4;
			else
			if(nState == 4 && ch == ']' && (i == fullContent.length()-1)) nState = 5;
			else
			if(nState == 1) dst_type += ch;
			else
			if(nState == 2) dst_subtype += ch;
			else
			if(nState == 4) dst_content += ch;
		}
		dst_length = dst_content.length();
		return;
	};

#endif // CCC_USE_QT



  // -----------------------------------------------------------------------
  // cccMethods
  // -----------------------------------------------------------------------

	cccContent::cccContent()
	{

	};

  // -----------------------------------------------------------------------

	cccContent::cccContent(cccContent &content) 
	{ 
		CopyFrom(content);
	};

  // -----------------------------------------------------------------------

	cccContent::cccContent(const cccContent &content) 
	{
		CopyFrom(content);
	};

  // -----------------------------------------------------------------------

	void cccContent::CopyFrom(const cccContent &content)
	{
		this->m_Content = content.getContent();
		this->m_Length = content.getLength();
		this->m_Type = content.getType();
		this->m_SubType = content.getSubType(); 
	};

  // -----------------------------------------------------------------------

	CCCCONTENT cccContent::getContent() const 
	{ 
		return m_Content; 
	};

  // -----------------------------------------------------------------------

	CCCTYPE cccContent::getType() const
	{ 
		return m_Type; 
	};

  // -----------------------------------------------------------------------

	CCCSUBTYPE cccContent::getSubType() const
	{ 
		return m_SubType;
	};

  // -----------------------------------------------------------------------

	CCCLENGTH cccContent::getLength() const
	{ 
		return m_Length; 
	};

	// -----------------------------------------------------------------------

	CCCFULLCONTENT cccContent::getFullContent() const
	{
		return Content_getFullContent(m_Type, m_SubType, m_Length, m_Content);
	};

	// -----------------------------------------------------------------------

	void cccContent::setFullContent(const CCCTYPE & type, const CCCTYPE & subtype, const CCCLENGTH & length, const CCCCONTENT & content)
	{
		m_Content = content;
		m_Type = type; 
		m_SubType = subtype;
		m_Length = length;
	};

	// -----------------------------------------------------------------------
	void cccContent::setFullContent(CCCFULLCONTENT fullContent)
  {
		Content_setFullContent(fullContent, m_Type, m_SubType, m_Length, m_Content);  			
  };

