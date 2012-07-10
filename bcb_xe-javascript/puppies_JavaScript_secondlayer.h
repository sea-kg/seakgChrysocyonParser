//---------------------------------------------------------------------------

#ifndef puppies_JavaScript_secondlayerH
#define puppies_JavaScript_secondlayerH
//---------------------------------------------------------------------------
#include <vector.h>
#include <vcl.h>
#include <conio.h>
#include "../seakgChrysocyonParser/bcb_xe.h"
#include "javascript_core.h"

typedef seakgChrysocyon::Parser<UnicodeString,UnicodeString> JavaScriptParser;
//typedef seakgReader<UnicodeStirng> Reader;

namespace javascript
{
  // variables
  template<typename Element, typename ArrayOfElement>
  class puppyDeclareVariables : public seakgChrysocyon::InterfaceChrysocyonPuppy<Element,ArrayOfElement>
  {
    public:
      puppyDeclareVariables(javascript::core *pCore);

      // InterfaceChrysocyonPuppy
      virtual seakgChrysocyon::chrysocyonAnswer SendElement(Element ch);
      virtual void GetResult( seakgChrysocyon::Stack<ArrayOfElement> *pStackResult );
      virtual void Reset();
      virtual bool StepBack();

    private:
      UnicodeString m_strResult;
      javascript::core *m_pCore;
      javascript::var *var;
      UnicodeString m_strNameVar;
      UnicodeString m_strValueVar;
      int m_nStep;
  };

  // functions
  template<typename Element, typename ArrayOfElement>
  class puppyDeclareFunctions : public seakgChrysocyon::InterfaceChrysocyonPuppy<Element,ArrayOfElement>
  {
    public:
      puppyDeclareFunctions(javascript::core *pCore);

      // InterfaceChrysocyonPuppy
      virtual seakgChrysocyon::chrysocyonAnswer SendElement(Element ch);
      virtual void GetResult( seakgChrysocyon::Stack<ArrayOfElement> *pStackResult );
      virtual void Reset();
      virtual bool StepBack();

    private:
      UnicodeString m_strResult;
      javascript::core *m_pCore;
      javascript::var *var;
      UnicodeString m_strNameFunction;
      UnicodeString m_strFunctionImpl;
      vector<UnicodeString> m_vNameVariables;
      int m_nCountVars;
      UnicodeString m_strValueVar;
      int m_nStep;
      int m_nBreakOpen;
      int m_nBreakClose;
  };


}; // namespace javascript


#endif
