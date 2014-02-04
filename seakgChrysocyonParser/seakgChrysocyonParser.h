#ifndef __SEAKG_CHRYSOCYON_PARSER_H__
#define __SEAKG_CHRYSOCYON_PARSER_H__

#include "src/enums.h"
#include "src/interfaces.h"
#include "src/stack.h"
#include <QString>

#include <vector>
#include <iostream>

namespace seakgChrysocyon
{
  /* class BaseElement
   {  
      void SetType(QString);
      void SetValue(QString);
      void AddProperty(QString, QString);
      void AddChildElement(BaseElement *);
   };

   class BaseStack
   {
      BaseElement * CreateElement(BaseElement *Parent);
      void Push(BaseElement *);
      BaseElement * Peek();
      void Pop();
   };

   class Layer 
   {
      void AddSubLayer(Layer *);
   }
*/

  // LAYERS reg

  // LAYER
  /*
    template<typename Element, typename ArrayOfElement>
    



    class IChryElement
    {  
      SetType(QString);
      SetValue(QString);
      AddProperty(QString, QString);
      AddChildElement(IChryElement *);
    };

    class IChryStack
    {
      IChryElement * CreateElement(IChryElement *Parent);
      Push(IChryElement *);
      Pop();
    };


    template<typename Element, typename ArrayOfElement, Stack>
    class Layers
    {
      
    };

  */
	
	//-----------------------------------------------
	// PARSER
	
	template<typename Element, typename ArrayOfElement>
	class Parser : public InterfaceChrysocyonReader<ArrayOfElement> // parser
	{
		typedef InterfaceChrysocyonReader<Element> Reader;
		typedef InterfaceChrysocyonPuppy<Element, ArrayOfElement> Puppy;
		typedef std::vector<InterfaceChrysocyonPuppy<Element, ArrayOfElement> *> ArrayOfPuppy;
		
		//typedef seakgChrysocyon::Stack<Element> Container;
		
		public: 
			Parser(Reader *reader) : m_pReader(reader), m_bStepBack(false) 
			{ 
				pPrivateStack = new seakgChrysocyon::Stack<ArrayOfElement>();
			};
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
						ProcessResult res = privateOneStep( elem, result, nOutErrorCode );
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
					m_vectorTempPuppies[0]->GetResult(pPrivateStack);
					pPrivateStack->Pop(result);
					return true;
				}
				
				if( m_pReader->Eof() )
				{
					nOutErrorCode = chsErrEof;
					return false;
				};
				
				return true;
			};
			
		private:
			
			Reader * m_pReader;
			
			bool m_bStepBack;
			Element m_elementStore;
			
			seakgChrysocyon::Stack<ArrayOfElement> *pPrivateStack;
			
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
					
					m_vectorCompletePuppies[0]->GetResult(pPrivateStack);
					
					pPrivateStack->Pop(result);
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
					nOutErrorCode = chsErrNotFoundPuppy;
					return procError;
				}
				else if( nPuppyOnlyMe > 1 && nPuppyComplete == 0 && nBufPuppy == 0 )
				{
					nOutErrorCode = chsErrTooManyPuppiesSayOnlyMe;
					return procError;
				}
				else if( nPuppyOnlyMe == 0 && nPuppyComplete > 1 && nBufPuppy == 0 )
				{
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
	};
	
	//-----------------------------------------------
};

#endif // __SEAKG_CHRYSOCYON_PARSER_H__
