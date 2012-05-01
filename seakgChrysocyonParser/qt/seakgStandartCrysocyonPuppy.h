#ifndef __SEAKG_STANDART_CRYOSOCYON_PUPPY_H__
#define __SEAKG_STANDART_CRYOSOCYON_PUPPY_H__

#include "../seakgChrysocyonParser.h"
#include <QChar>
#include <QString>
#include <iostream>

//------------------------------------------------------------------------------------

template<typename Element, typename ArrayOfElement> class seakgPuppyNumber;
template <>
class seakgPuppyNumber<QChar,QString> : public seakgChrysocyon::InterfaceChrysocyonPuppy<QChar, QString>
{
	public:
		seakgPuppyNumber() { m_strContent = ""; };

		// InterfaceChrysocyonPuppy
		virtual seakgChrysocyon::chrysocyonAnswer SendElement(QChar ch)
		{
			if ((m_strContent.length() == 0) && ch.isNumber() )
			{
				m_strContent = m_strContent + ch;
				return seakgChrysocyon::schsMaybe;
			}
			if ((m_strContent.length() > 0) && ch.isNumber() )
			{
				//std::cout << "=2\n";
				m_strContent = m_strContent + ch;
				return seakgChrysocyon::schsOnlyMe;
			}
			else if (m_strContent.length() > 0  && !ch.isNumber())
			{
				//std::cout << "=3\n";
				//std::cout << " seakgPuppyNumber::SendElement return Completed\n";
				return seakgChrysocyon::schsComplete;
			}
			return seakgChrysocyon::schsNone;
		};
		
		virtual QString &GetResult()
		{
			//std::cout << " seakgPuppyNumber::GetResult [" << m_strContent.toStdString() << "] \n";
			
			m_strResult = "number:" + m_strContent;
			return m_strResult;
		};
		
		virtual void Reset()
		{
			m_strContent = "";
		};
		
		virtual bool StepBack()
		{
			return true;
		};
		
	private:
		QString m_strContent;
		QString m_strResult;
};
//------------------------------------------------------------------------------------

/* schsNone = 0, // точно нет или я отказываюсь
		schsYetUnknown = 1, //еще не знаю или еще не определился давай дальше
		schsMaybe = 2, // Может быть мое
		schsOnlyMe = 3, // Точно мое ( и должно быть только мое )
		schsComplete = 4, // да я закончил можешь забирать результат */



template<typename Element, typename ArrayOfElement> class seakgPuppyName;
template <>
class seakgPuppyName<QChar,QString> : public seakgChrysocyon::InterfaceChrysocyonPuppy<QChar, QString>
{
	public:
		seakgPuppyName() { m_strContent = ""; m_bStepBack = false; };

		// InterfaceChrysocyonPuppy
		virtual seakgChrysocyon::chrysocyonAnswer SendElement(QChar ch)
		{
			
			if ((m_strContent.length() == 0) && ch.isLetter())
			{
				m_strContent += ch;
				return seakgChrysocyon::schsMaybe;
			}
			else if (m_strContent.length() > 0 && ch.isLetterOrNumber())
			{
				m_strContent += ch;
				return seakgChrysocyon::schsOnlyMe;
			}
			else if (m_strContent.length() > 0 )
			{
				m_bStepBack = true;
				return seakgChrysocyon::schsComplete;
			};
			return seakgChrysocyon::schsNone;
		};
		
		virtual QString &GetResult()
		{
			m_strResult = "name:" + m_strContent;
			return  m_strResult;
		};

		virtual void Reset()
		{
			m_strContent = "";
			m_bStepBack = false;
		};

		virtual bool StepBack()
		{
			return true;
		};
		
	private:
		QString m_strContent;
		QString m_strResult;
		bool m_bStepBack;
};

template<typename Element, typename ArrayOfElement> class seakgPuppyAnySimbol;
template <>
class seakgPuppyAnySimbol<QChar,QString> : public seakgChrysocyon::InterfaceChrysocyonPuppy<QChar, QString>
{
	public:
		seakgPuppyAnySimbol(QChar chSimbol) { m_strContent = ""; m_chSimbol = chSimbol; };

		// InterfaceChrysocyonPuppy
		virtual seakgChrysocyon::chrysocyonAnswer SendElement(QChar ch)
		{
			if ((m_strContent.length() == 0) && (ch == m_chSimbol) )
			{
				m_strContent = m_strContent + ch;
				return seakgChrysocyon::schsOnlyMe;
			}
			if ((m_strContent.length() > 0) && (ch == m_chSimbol) )
			{
				m_strContent = m_strContent + ch;
				return seakgChrysocyon::schsOnlyMe;
			}
			else if (m_strContent.length() > 0  && (ch != m_chSimbol) )
			{
				return seakgChrysocyon::schsComplete;
			}
			return seakgChrysocyon::schsNone;
		};
		
		virtual QString &GetResult()
		{
			m_strResult = "{" + m_strContent + "}"; 
			return m_strContent;
		};
		
		virtual void Reset()
		{
			m_strContent = "";
		};
		
		virtual bool StepBack()
		{
			return true;
		};
		
	private:
		QChar m_chSimbol;
		QString m_strContent;
		QString m_strResult;
};
//------------------------------------------------------------------------------------


/*

// PUPPY : DOUBLE_QUOTES 

template<class Element>
class seakgDoubleQuotesPuppy : public seakgChrysocyon::seakgChrysocyonReader<Element>
{
	public:
		seakgDoubleQuotesPuppy();
		
		virtual seakgChrysocyon::seakgChrysocyonAnswer SendElement(Element &);
		virtual void GetResult(seakgChrysocyon::seakgChrysocyonContainer<Element> &);
		virtual void Reset();
		
	private:
		seakgChrysocyon::seakgChrysocyonContainer<Element> *container;
		int m_nState;
		char prev_ch;
};
*/

/*
template <class T>
class seakgCppDoubleQuotePuppy : public seakgChrysocyon::seakgChrysocyonReader<T>
{
	public:
		seakgExampleReader();

		virtual bool Eof();
		virtual T GetNextElement();
		
		// other 
		
		void setString(std::string str);
		
	private:
		int m_nInd;
		std::string m_str;
};
*/

//class seakgExampleReader<char>;

#endif // __SEAKG_STANDART_CRYOSOCYON_PUPPY_H__
