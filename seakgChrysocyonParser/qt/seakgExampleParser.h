#ifndef __SEAKGEXAMPLEPARSER_H__
#define __SEAKGEXAMPLEPARSER_H__

#include "seakgChrysocyonParser.h"
#include <iostream>

template <class T>
class seakgExampleReader : public seakgChrysocyon::seakgChrysocyonReader<T>
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

#endif // __SEAKGEXAMPLEPARSER_H__
