#ifndef __SEAKGCHRYSOCYONPARSER_H__
#define __SEAKGCHRYSOCYONPARSER_H__

#include <vector>
#include <iostream>

namespace seakgChrysocyon
{
	//-----------------------------------------------
	// ENUM ANSWER TYPE

	enum chrysocyonAnswer
	{
		schsNone = 0, // точно нет или я отказываюсь
		schsYetUnknown = 1, //еще не знаю или еще не определился давай дальше
		schsMaybe = 2, // Может быть мое
		schsOnlyMe = 3, // Точно мое ( и должно быть только мое )
		schsComplete = 4, // да я закончил можешь забирать результат
	};
	//-----------------------------------------------
	// READER
	
	template<typename Element>
	class InterfaceChrysocyonReader // interface
	{
		public:
			virtual bool Eof() = 0;
			virtual bool GetNextElement( Element &, int & ) = 0;
	};
	
	//-----------------------------------------------
	// PUPPY
	
	template<typename Element, typename ArrayOfElement>
	class InterfaceChrysocyonPuppy // interface
	{
		public:
			virtual chrysocyonAnswer SendElement(Element) = 0;
			virtual ArrayOfElement &GetResult() = 0;
			virtual void Reset() = 0;
			virtual bool StepBack() = 0;
	};
	
	//-----------------------------------------------
	// PARSER

	enum chrysocyonErrors
	{
		chsErrEof = -1, // неожиданные конец файла
		chsErrUnknownAnswer = -2, // неизвестный ответ
		chsErrNotFoundPuppy = -3, // ненайден щенок
		chsErrTooManyPuppiesSayOnlyMe = -4, // более одного щенка заявили на права
		chsErrTooManyPuppiesSayCompleted = -5, // более одного щенка заявили что закончили
		chsErrUnknown = -6, // более одного щенка заявили что закончили
		chsErrNotFoundPuppyComplete = -7 // Ошибка в базовом механизме
	};
	
	template<typename Element, typename ArrayOfElement>
	class chrysocyonParser : public InterfaceChrysocyonReader<ArrayOfElement> // parser
	{
		typedef InterfaceChrysocyonReader<Element> Reader;
		typedef InterfaceChrysocyonPuppy<Element, ArrayOfElement> Puppy;
		typedef std::vector<InterfaceChrysocyonPuppy<Element, ArrayOfElement> *> ArrayOfPuppy;
		
		//typedef seakgChrysocyonContainer<Element> Container;
		
		public: 
			chrysocyonParser(Reader *reader) : m_pReader(reader), m_bStepBack(false) { };
			void AddPuppy(Puppy* puppy) { m_vectorPuppies.push_back(puppy); };
			
			// InterfaceChrysocyonReader
			virtual bool Eof() { return m_pReader->Eof(); };
			
			// get next element
			virtual bool GetNextElement( ArrayOfElement &result,  int& nOutErrorCode = 0 )
			{
				//init
				m_vectorTempPuppies.clear();
				m_nErrorCode = 0;
				CopyArrayOfPuppy( m_vectorPuppies, m_vectorTempPuppies);
				
				// one step back
				if( m_bStepBack )
				{
					ProcessResult res = privateOneStep( m_elementStore, result, nOutErrorCode );
					if( ifReturn(res) ) return ( res == procFinish ) ;
					m_bStepBack = false;
					//if( res == procError ) return false;
					//if( res == procFinish ) return true;
				};
				
				
				while( !m_pReader->Eof() )
				{
					int nErrorCode = 0;
					Element elem;
					
					if( m_pReader->GetNextElement(elem, nErrorCode ) )
					{
						
						/*if( !private_ProcessAnswerPuppies_Step1( elem, nOutErrorCode ))
							return false;
							
						ProcessResult res = private_ProcessAnswerPuppies_Step2( result, nOutErrorCode ); 
						*/
						
						ProcessResult res = privateOneStep( elem, result, nOutErrorCode );
						
						//if( res == procError ) return false;
						//if( res == procFinish ) return true;
						 
						if( ifReturn(res) ) return ( res == procFinish );
						
					}
					else
					{
						// error : return error code
						nOutErrorCode = nErrorCode;
						return false;
					};
				};
				
				if( m_vectorTempPuppies.size() == 1 )
				{
					result = m_vectorTempPuppies[0]->GetResult();
					return true;
				}
 
				
//				std::cout << "after while\n";
				if( m_pReader->Eof() )
				{
					nOutErrorCode = chsErrEof;
					return false;
				};
				
				return true;
			};
			
		private:
			
			Reader * m_pReader;
			
			ArrayOfPuppy m_vectorPuppies; 
			ArrayOfPuppy m_vectorTempPuppies;
			ArrayOfPuppy m_vectorBufPuppies;
			ArrayOfPuppy m_vectorOnlyMePuppies;
			ArrayOfPuppy m_vectorCompletePuppies;
			
			int m_nErrorCode;
			
			// ------------
			void CopyArrayOfPuppy(const ArrayOfPuppy &src, ArrayOfPuppy &dst)
			{
				for(unsigned int i = 0; i < src.size(); i++)
					dst.push_back(src[i]);
				return;
			};			
			void ResetAllPuppy()
			{
				for(unsigned int i = 0; i < m_vectorPuppies.size(); i++)
					m_vectorPuppies[i]->Reset();
			};
			
			bool private_ProcessAnswerPuppies_Step1(Element elem, int &nOutErrorCode)
			{
				m_vectorBufPuppies.clear();
				m_vectorOnlyMePuppies.clear();
				m_vectorCompletePuppies.clear();
				
				for(unsigned int i = 0; i < m_vectorTempPuppies.size(); i++)
				{
					seakgChrysocyon::chrysocyonAnswer answer = m_vectorTempPuppies[i]->SendElement(elem);
					//std::cout << (int)answer << "\n";
					if( answer == schsNone )
						{ /* nothing */ }
					else if( answer == schsYetUnknown || answer == schsMaybe )
						m_vectorBufPuppies.push_back(m_vectorTempPuppies[i]);
					else if( answer == schsOnlyMe )
						m_vectorOnlyMePuppies.push_back(m_vectorTempPuppies[i]);
					else if( answer == schsComplete )
						m_vectorCompletePuppies.push_back(m_vectorTempPuppies[i]);
					else
					{
						nOutErrorCode = chsErrUnknownAnswer;
						return false;
					};
				};
				return true;
			};
			// ---------------------------------------------------------------
			
			enum ProcessResult { procError = -1, procFinish = 0, procNext = 1 };
			
			bool ifReturn( ProcessResult &res ) { return ( (res == procFinish) || (res == procError) ); };
			
			ProcessResult private_ProcessAnswerPuppies_Step2( ArrayOfElement &result, int &nOutErrorCode)
			{
				nOutErrorCode = 0;
				
				int nPuppyOnlyMe = m_vectorOnlyMePuppies.size();
				int nPuppyComplete = m_vectorCompletePuppies.size();
				int nBufPuppy = m_vectorBufPuppies.size();
				
				if( nPuppyOnlyMe == 0 && nPuppyComplete == 1 && nBufPuppy == 0)
				{
					
					nOutErrorCode = 0;
					result = m_vectorCompletePuppies[0]->GetResult();
					m_bStepBack = m_vectorCompletePuppies[0]->StepBack();
					ResetAllPuppy();
					return procFinish;
				}
				else if( nPuppyOnlyMe == 1 && nPuppyComplete == 0 && nBufPuppy == 0)
				{
					m_vectorTempPuppies.clear();
					m_vectorTempPuppies.push_back( m_vectorOnlyMePuppies[0] );
					return procNext;
				}
				else if( nPuppyOnlyMe == 0 && nPuppyComplete == 0 && nBufPuppy  > 0 )
				{
					
					m_vectorTempPuppies.clear();
					CopyArrayOfPuppy( m_vectorBufPuppies, m_vectorTempPuppies );
					m_vectorBufPuppies.clear();
					return procNext;
					
					// goto next step
				}
				else if( nPuppyOnlyMe == 0 && nPuppyComplete == 0 && nBufPuppy == 0 )
				{
					//std::cout << " not found puppy \n";
					nOutErrorCode = chsErrNotFoundPuppy;
					return procError;
				}
				else if( nPuppyOnlyMe > 1 && nPuppyComplete == 0 && nBufPuppy == 0 )
				{
					//std::cout << " too many only me \n";
					nOutErrorCode = chsErrTooManyPuppiesSayOnlyMe;
					return procError;
				}
				else if( nPuppyOnlyMe == 0 && nPuppyComplete > 1 && nBufPuppy == 0 )
				{
					//std::cout << " too many completed \n";
					nOutErrorCode = chsErrTooManyPuppiesSayCompleted;
					return procError;
				};
				
				//error Unknown
				nOutErrorCode = chsErrUnknown;
				return procError;
			}
			
			ProcessResult privateOneStep( Element &elem, ArrayOfElement &result, int& nOutErrorCode)
			{
				m_elementStore = elem;
				nOutErrorCode = 0;
				
				if( !private_ProcessAnswerPuppies_Step1( elem, nOutErrorCode ))
					return procError;
				
				return private_ProcessAnswerPuppies_Step2( result, nOutErrorCode );
			};
			
			
			
			bool m_bStepBack;
			Element m_elementStore;
	};
	
	//-----------------------------------------------
};

#endif // __SEAKGCHRYSOCYONPARSER_H__
