#ifndef __SEAKG_STANDART_CRYOSOCYON_PUPPY_H__
#define __SEAKG_STANDART_CRYOSOCYON_PUPPY_H__

#include "../seakgChrysocyonParser.h"
#include <vcl.h>
#include <iostream>

//------------------------------------------------------------------------------------
bool isNumber(wchar_t ch)
{
  return (ch >= L'0' && ch <= L'9');
}
//------------------------------------------------------------------------------------

bool isLetter(wchar_t ch)
{
  return (ch >= L'A' && ch <= L'Z') || (ch >= L'a' && ch <= L'z');
}

bool isLetterOrNumber(wchar_t ch)
{
  return isNumber(ch) || isLetter(ch);
};


template<typename Element, typename ArrayOfElement> class seakgPuppyNumber;
template <>
class seakgPuppyNumber<wchar_t,UnicodeString> : public seakgChrysocyon::InterfaceChrysocyonPuppy<wchar_t,UnicodeString>
{
	public:
		seakgPuppyNumber() { m_strContent = ""; };

		// InterfaceChrysocyonPuppy
		virtual seakgChrysocyon::chrysocyonAnswer SendElement(wchar_t ch)
		{
			if ((m_strContent.Length() == 0) && isNumber(ch) )
			{
				m_strContent = m_strContent + ch;
				return seakgChrysocyon::schsMaybe;
			}
			if ((m_strContent.Length() > 0) && isNumber(ch) )
			{
				//std::cout << "=2\n";
				m_strContent = m_strContent + ch;
				return seakgChrysocyon::schsOnlyMe;
			}
			else if (m_strContent.Length() > 0  && !isNumber(ch))
			{
				//std::cout << "=3\n";
				//std::cout << " seakgPuppyNumber::SendElement return Completed\n";
				return seakgChrysocyon::schsComplete;
			}
			return seakgChrysocyon::schsNone;
		};
		
		virtual void GetResult( seakgChrysocyon::Stack<UnicodeString> *pStackResult )
		{
			pStackResult->Push( UnicodeString("number:" + m_strContent) );
		};
		
		/*
		virtual UnicodeString &GetResult( ) // seakgChrysocyon::Stack<UnicodeString> *pStackResult)
		{
			//std::cout << " seakgPuppyNumber::GetResult [" << m_strContent.toStdString() << "] \n";
			//pStackResult->Push();
			m_strResult = "number:" + m_strContent;
			return m_strResult;
		};
		*/
		
		virtual void Reset()
		{
			m_strContent = "";
		};
		
		virtual bool StepBack()
		{
			return true;
		};
		
	private:
		UnicodeString m_strContent;
		UnicodeString m_strResult;
};
//------------------------------------------------------------------------------------

/* schsNone = 0, // точно нет или я отказываюсь
		schsYetUnknown = 1, //еще не знаю или еще не определился давай дальше
		schsMaybe = 2, // Может быть мое
		schsOnlyMe = 3, // Точно мое ( и должно быть только мое )
		schsComplete = 4, // да я закончил можешь забирать результат */



template<typename Element, typename ArrayOfElement> class seakgPuppyName;
template <>
class seakgPuppyName<wchar_t,UnicodeString> : public seakgChrysocyon::InterfaceChrysocyonPuppy<wchar_t, UnicodeString>
{
	public:
		seakgPuppyName() { m_strContent = ""; m_bStepBack = false; };

		// InterfaceChrysocyonPuppy
		virtual seakgChrysocyon::chrysocyonAnswer SendElement(wchar_t ch)
		{
			
			if ((m_strContent.Length() == 0) && isLetter(ch))
			{
				m_strContent += ch;
				return seakgChrysocyon::schsMaybe;
			}
			else if (m_strContent.Length() > 0 && isLetterOrNumber(ch))
			{
				m_strContent += ch;
				return seakgChrysocyon::schsOnlyMe;
			}
			else if (m_strContent.Length() > 0 )
			{
				m_bStepBack = true;
				return seakgChrysocyon::schsComplete;
			};
			return seakgChrysocyon::schsNone;
		};
		
		virtual void GetResult( seakgChrysocyon::Stack<UnicodeString> *pStackResult )
		{
			pStackResult->Push( UnicodeString("name:" + m_strContent) );
		};
		
		/*
		virtual UnicodeString &GetResult()
		{
			m_strResult = ;
			return  m_strResult;
		};
		*/
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
		UnicodeString m_strContent;
		UnicodeString m_strResult;
		bool m_bStepBack;
};


template<typename Element, typename ArrayOfElement> class seakgPuppyStringInDoubleQuotes;
template <>
class seakgPuppyStringInDoubleQuotes<wchar_t,UnicodeString> : public seakgChrysocyon::InterfaceChrysocyonPuppy<wchar_t, UnicodeString>
{
	public:
		seakgPuppyStringInDoubleQuotes() { m_strContent = ""; nR = 0; m_bStepBack = false; };

		// InterfaceChrysocyonPuppy
		virtual seakgChrysocyon::chrysocyonAnswer SendElement(wchar_t ch)
		{
			if( (m_strContent.Length() == 0) && (ch == '\"') )
			{
				m_strContent += ch;
				return seakgChrysocyon::schsOnlyMe;
			}
			else if( (m_strContent.Length() > 0) && (ch == '\\') && (nR == 0) )
			{
				m_strContent += ch;
				nR = 1;
				return seakgChrysocyon::schsOnlyMe;
			}
			else if( (m_strContent.Length() > 0) && (nR != 1) && (ch == '\"') )
			{
				m_bStepBack = false;
				m_strContent += ch;
				return seakgChrysocyon::schsComplete;
			}
			else if( m_strContent.Length() > 0 )
			{
				m_strContent += ch;
				nR = 0;
				return seakgChrysocyon::schsOnlyMe;
			};
			
			return seakgChrysocyon::schsNone;
		};
		
		virtual void GetResult( seakgChrysocyon::Stack<UnicodeString> *pStackResult )
		{
			pStackResult->Push( UnicodeString("string:" + m_strContent) );
		};
		/*
		virtual UnicodeString &GetResult()
		{
			m_strResult = "string:" + m_strContent;
			return  m_strResult;
		};
*/

		virtual void Reset()
		{
			m_strContent = "";
			m_bStepBack = false;
		};

		virtual bool StepBack()
		{
			return m_bStepBack;
		};
		
	private:
		UnicodeString m_strContent;
		UnicodeString m_strResult;
		bool m_bStepBack;
		int nR;
};

template<typename Element, typename ArrayOfElement> class seakgPuppyAnySimbol;
template <>
class seakgPuppyAnySimbol<wchar_t,UnicodeString> : public seakgChrysocyon::InterfaceChrysocyonPuppy<wchar_t, UnicodeString>
{
	public:
		seakgPuppyAnySimbol(wchar_t chSimbol) { m_strContent = ""; m_chSimbol = chSimbol; };

		// InterfaceChrysocyonPuppy
		virtual seakgChrysocyon::chrysocyonAnswer SendElement(wchar_t ch)
		{
			if ((m_strContent.Length() == 0) && (ch == m_chSimbol) )
			{
				m_strContent = m_strContent + ch;
				return seakgChrysocyon::schsOnlyMe;
			}
			if ((m_strContent.Length() > 0) && (ch == m_chSimbol) )
			{
				m_strContent = m_strContent + ch;
				return seakgChrysocyon::schsOnlyMe;
			}
			else if (m_strContent.Length() > 0  && (ch != m_chSimbol) )
			{
				return seakgChrysocyon::schsComplete;
			}
			return seakgChrysocyon::schsNone;
		};
		
		virtual void GetResult( seakgChrysocyon::Stack<UnicodeString> *pStackResult )
		{
			pStackResult->Push( UnicodeString("{" + m_strContent + "}") );
		};
		/*
		virtual UnicodeString &GetResult()
		{
			m_strResult = ; 
			return m_strContent;
		};
		*/
		
		virtual void Reset()
		{
			m_strContent = "";
		};
		
		virtual bool StepBack()
		{
			return true;
		};
		
	private:
		wchar_t m_chSimbol;
		UnicodeString m_strContent;
		UnicodeString m_strResult;
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
