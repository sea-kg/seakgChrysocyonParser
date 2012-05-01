#ifndef __SEAKG_STANDART_CRYOSOCYON_READER_FROM_QSTRING_H__
#define __SEAKG_STANDART_CRYOSOCYON_READER_FROM_QSTRING_H__

#include "../seakgChrysocyonParser.h"
#include <QChar>
#include <QString>

template<typename T> class seakgReaderFromQString;

template<>
class seakgReaderFromQString<QChar> : public seakgChrysocyon::InterfaceChrysocyonReader<QChar>
{
	public:
		seakgReaderFromQString() { m_strContent = ""; m_nInd = 0; };
		void setString(const QString &str) 
		{ 
			m_strContent = str; 
			m_nInd = 0;
		};

		// InterfaceChrysocyonReader
		virtual bool Eof() { return (m_nInd >= m_strContent.length()); };
		virtual bool GetNextElement( QChar &ch, int &nOutErrorCode ) 
		{
			if( (!this->Eof()) && (m_strContent.length() > 0) )
			{
				ch = m_strContent.at(m_nInd);
				nOutErrorCode = 0;
				m_nInd++;
				return true;
			}
			nOutErrorCode = seakgChrysocyon::chsErrEof;
			return false;
		};
		
	private:
		int m_nInd;
		QString m_strContent;
};

#endif // __SEAKG_STANDART_CRYOSOCYON_READER_FROM_QSTRING_H__
