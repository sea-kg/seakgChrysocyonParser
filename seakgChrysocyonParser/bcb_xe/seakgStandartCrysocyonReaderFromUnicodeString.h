#ifndef __SEAKG_STANDART_CRYOSOCYON_READER_FROM_UNICODESTRING_H__
#define __SEAKG_STANDART_CRYOSOCYON_READER_FROM_UNICODESTRING_H__

#include "../seakgChrysocyonParser.h"
#include <tchar.h>
#include <vcl.h>

template<typename T> class seakgReaderFromUnicodeString;

template<>
class seakgReaderFromUnicodeString<wchar_t> : public seakgChrysocyon::InterfaceChrysocyonReader<wchar_t>
{
	public:
		seakgReaderFromUnicodeString() { m_strContent = ""; m_nInd = 0; };
		void setString(const UnicodeString &str)
		{ 
			m_strContent = str; 
			m_nInd = 0;
		};

		// InterfaceChrysocyonReader
		virtual bool Eof() { return (m_nInd >= m_strContent.Length()); };
		virtual bool GetNextElement( wchar_t &ch, int &nOutErrorCode )
		{
			if( (!this->Eof()) && (m_strContent.Length() > 0) )
			{
				ch = m_strContent[m_nInd + 1];
				nOutErrorCode = 0;
				m_nInd++;
				return true;
			}
			nOutErrorCode = seakgChrysocyon::chsErrEof;
			return false;
		};
		
	private:
		int m_nInd;
		UnicodeString m_strContent;
};

#endif // __SEAKG_STANDART_CRYOSOCYON_READER_FROM_UNICODESTRING_H__
