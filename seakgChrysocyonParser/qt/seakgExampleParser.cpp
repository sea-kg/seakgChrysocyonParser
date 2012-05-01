#include "seakgExampleParser.h"

/*
template <class T>
seakgExampleReader<T>::seakgExampleReader()
{
	
};

template <class T>
bool seakgExampleReader<T>::Eof()
{
	return ( m_str.length() < m_nInd );
};

template <class T>
T seakgExampleReader<T>::GetNextElement()
{
	T res;// = m_str[m_nInd];
	m_nInd++;
	return res;
};

template <class T>
void seakgExampleReader<T>::setString(std::string str)
{
	m_str = str;
	m_nInd = 0;
	return;
};
*/

template<>
seakgExampleReader<char>::seakgExampleReader()
{
	
};

template <>
bool seakgExampleReader<char>::Eof()
{
	return ( int(m_str.length()) < m_nInd );
};

template <>
char seakgExampleReader<char>::GetNextElement()
{
	char res = m_str[m_nInd];
	m_nInd++;
	return res;
};

template <>
void seakgExampleReader<char>::setString(std::string str)
{
	m_str = str;
	m_nInd = 0;
	return;
};


/*
template<>
std::string seakgChrysocyon::GetNormalContainer( seakgChrysocyonContainer<char> & )
{
	
}; */
	
//class seakgChrysocyonContainer<char>;

// PUPPY : DOUBLE_QUOTES

template <class Element>
seakgDoubleQuotesPuppy<Element>::seakgDoubleQuotesPuppy()
{
	m_nState = 0;
};

template <>
seakgChrysocyon::seakgChrysocyonAnswer seakgDoubleQuotesPuppy<char>::SendElement(char &ch)
{
	if( m_nState == 3 ) m_nState = 0;
		
	if( ch == '\"' && m_nState == 0)
	{
		prev_ch = ch;
		m_nState = 1;
		//container->Push(ch);
		return seakgChrysocyon::schsOnlyMe;
	};
	
	if( ch != '\"' && m_nState == 1)
	{
		m_nState = 2;
		prev_ch = ch;
		//container.Push(ch);
		return seakgChrysocyon::schsOnlyMe;
	};
	
	if( ch == '\"' && m_nState == 2 && prev_ch != '\\')
	{
		m_nState = 3;
		prev_ch = ch;
		//container.Push(ch);
		return seakgChrysocyon::schsComplete;
	};
	
	if( m_nState == 0 && ch == 'L')
		return seakgChrysocyon::schsYetUnknown;
	
	return seakgChrysocyon::schsNone;
};

/*
template <>
seakgChrysocyon::seakgChrysocyonAnswer seakgDoubleQuotesPuppy<char>::SendElement(char &ch)
{
	if( ch == '\"')
	{
		
	};
	return seakgChrysocyon::schsNone;
};
*/

/*
template<class Element>
class seakgDoubleQuotesPuppy : public seakgChrysocyon::seakgChrysocyonReader<Element>
{
	public:
		virtual 
		virtual void GetResult(seakgChrysocyon::seakgChrysocyonContainer<Element> &);
		virtual void Reset();
		
	private:
		seakgChrysocyon::seakgChrysocyonContainer<Element> container;
};
*/