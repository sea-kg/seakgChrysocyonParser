#ifndef __SEAKG_CHRYSOCYON_STACK_H__
#define __SEAKG_CHRYSOCYON_STACK_H__

namespace seakgChrysocyon
{
	template<class T> class ElemStack
	{
		public:
			ElemStack()
			{
				&m_pElem = NULL;
				m_pElemPrev = NULL;
				m_pElemNext = NULL; 
			};
			
			ElemStack(T pElem, ElemStack<T> *pElemPrev, ElemStack<T> *pElemNext)
			{
				m_pElem = pElem;
				m_pElemPrev = pElemPrev;
				m_pElemNext = pElemNext; 
			};
			
			T &getContains() { return m_pElem; };
			ElemStack<T> *getPrevious() { return m_pElemPrev; };
			ElemStack<T> *getNext() { return m_pElemNext; };
			void setPrevious(ElemStack<T> *pE) { m_pElemPrev = pE; };
			void setNext(ElemStack<T> *pE) { m_pElemNext = pE; };
		
		private:
			T m_pElem;
			ElemStack<T> *m_pElemPrev;
			ElemStack<T> *m_pElemNext;
	};
	
	template<class ArrayOfElement>
	class Stack
	{
		public:
			Stack() 
			{
				m_pFirst = NULL; 
				//m_pCurrent = NULL; 
				m_pLast = NULL; 
				count = 0; 
			};
			
			// ------- push -------------------
			void Push(ArrayOfElement el) 
			{
				ElemStack<ArrayOfElement> *pE;
				pE = new ElemStack<ArrayOfElement>(el, m_pLast, NULL);
				if( count == 0 ) m_pFirst = pE;
				
				m_pLast = pE;
				count++;
			};
			
			// ------- pop -------------------
			bool Pop( ArrayOfElement & pArrEl)
			{
				if( m_pLast != NULL )
				{
					pArrEl = m_pLast->getContains();
					
					ElemStack<ArrayOfElement> *pTemp = m_pLast;
					
					m_pLast = pTemp->getPrevious();
					
					if(m_pLast != NULL )
						m_pLast->setNext(NULL);
					
					pTemp->~ElemStack<ArrayOfElement>();
					if(count > 0 ) count--;
					return true;
				}
				return false;
				
			};
			
			// ------- count -------------------
			int getCount() { return count; };
			
		private:
			//ElemStack<ArrayElement> * m_pCurrent; 
			ElemStack<ArrayOfElement> * m_pFirst; 
			ElemStack<ArrayOfElement> * m_pLast;
			int count;
	};
}; // namespace seakgChrysocyon

#endif // __SEAKG_CHRYSOCYON_STACK_H__
