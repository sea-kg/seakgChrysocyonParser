//---------------------------------------------------------------------------

#ifndef puppies_JavaScript_firstlayerH
#define puppies_JavaScript_firstlayerH
//---------------------------------------------------------------------------
#include <vector.h>
#include <vcl.h>
#include <conio.h>
#include "../seakgChrysocyonParser/bcb_xe.h"
#include "javascript_core.h"

typedef seakgChrysocyon::Parser<wchar_t,UnicodeString> CharParser;
typedef seakgReaderFromUnicodeString<wchar_t> CharReader;

namespace javascript
{

  template<typename Element, typename ArrayOfElement>
  class puppyName : public seakgChrysocyon::InterfaceChrysocyonPuppy<Element,ArrayOfElement>
  {
    public:
      puppyName(javascript::core *pCore);
      // InterfaceChrysocyonPuppy
      virtual seakgChrysocyon::chrysocyonAnswer SendElement(Element ch);
      virtual void GetResult( seakgChrysocyon::Stack<ArrayOfElement> *pStackResult );
      virtual void Reset();
      virtual bool StepBack();

    private:
      UnicodeString m_strResult;
      javascript::core *m_pCore;
  };

  template<typename Element, typename ArrayOfElement>
  class puppySpace : public seakgChrysocyon::InterfaceChrysocyonPuppy<Element,ArrayOfElement>
  {
    public:
      puppySpace(javascript::core *pCore);
      // InterfaceChrysocyonPuppy
      virtual seakgChrysocyon::chrysocyonAnswer SendElement(Element ch);
      virtual void GetResult( seakgChrysocyon::Stack<ArrayOfElement> *pStackResult );
      virtual void Reset();
      virtual bool StepBack();

    private:
      UnicodeString m_strResult;
      javascript::core *m_pCore;
  };

  template<typename Element, typename ArrayOfElement>
  class puppyMultiLineComments : public seakgChrysocyon::InterfaceChrysocyonPuppy<Element,ArrayOfElement>
  {
    public:
      puppyMultiLineComments(javascript::core *pCore);
      // InterfaceChrysocyonPuppy
      virtual seakgChrysocyon::chrysocyonAnswer SendElement(Element ch);
      virtual void GetResult( seakgChrysocyon::Stack<ArrayOfElement> *pStackResult );
      virtual void Reset();
      virtual bool StepBack();

    private:
      UnicodeString m_strResult;
      javascript::core *m_pCore;
      bool start_, end_;
  };

    template<typename Element, typename ArrayOfElement>
  class puppyLineComment : public seakgChrysocyon::InterfaceChrysocyonPuppy<Element,ArrayOfElement>
  {
    public:
      puppyLineComment(javascript::core *pCore);
      // InterfaceChrysocyonPuppy
      virtual seakgChrysocyon::chrysocyonAnswer SendElement(Element ch);
      virtual void GetResult( seakgChrysocyon::Stack<ArrayOfElement> *pStackResult );
      virtual void Reset();
      virtual bool StepBack();

    private:
      UnicodeString m_strResult;
      javascript::core *m_pCore;
  };

  template<typename Element, typename ArrayOfElement>
  class puppyLine : public seakgChrysocyon::InterfaceChrysocyonPuppy<Element,ArrayOfElement>
  {
    public:
      puppyLine(javascript::core *pCore);
      // InterfaceChrysocyonPuppy
      virtual seakgChrysocyon::chrysocyonAnswer SendElement(Element ch);
      virtual void GetResult( seakgChrysocyon::Stack<ArrayOfElement> *pStackResult );
      virtual void Reset();
      virtual bool StepBack();

    private:
      UnicodeString m_strResult;
      javascript::core *m_pCore;
      bool start_, end_;
  };

  template<typename Element, typename ArrayOfElement>
  class puppySimbol : public seakgChrysocyon::InterfaceChrysocyonPuppy<Element,ArrayOfElement>
  {
    public:
      puppySimbol(javascript::core *pCore, wchar_t chSimbol);
      // InterfaceChrysocyonPuppy
      virtual seakgChrysocyon::chrysocyonAnswer SendElement(Element ch);
      virtual void GetResult( seakgChrysocyon::Stack<ArrayOfElement> *pStackResult );
      virtual void Reset();
      virtual bool StepBack();

    private:
      UnicodeString m_strResult;
      wchar_t m_chSimbol;
      javascript::core *m_pCore;
  };

  template<typename Element, typename ArrayOfElement>
  class puppyStringInDoubleQuotes : public seakgChrysocyon::InterfaceChrysocyonPuppy<Element,ArrayOfElement>
  {
    public:
      puppyStringInDoubleQuotes(javascript::core *pCore);
      // InterfaceChrysocyonPuppy
      virtual seakgChrysocyon::chrysocyonAnswer SendElement(Element ch);
      virtual void GetResult( seakgChrysocyon::Stack<ArrayOfElement> *pStackResult );
      virtual void Reset();
      virtual bool StepBack();

    private:
      UnicodeString m_strResult;
      javascript::core *m_pCore;
      int nR;
  };

  /*
  template<typename Element, typename ArrayOfElement>
  class puppyNumber : public seakgChrysocyon::InterfaceChrysocyonPuppy<Element,ArrayOfElement>
  {
    public:
      puppyMain(javascript::core *pCore);
      // InterfaceChrysocyonPuppy
      virtual seakgChrysocyon::chrysocyonAnswer SendElement(Element ch);
      virtual void GetResult( seakgChrysocyon::Stack<ArrayOfElement> *pStackResult );
      virtual void Reset();
      virtual bool StepBack();

    private:
      wchar_t m_chResult;
      javascript::core *m_pCore;
  };
   */

  /*
  template<typename Element, typename ArrayOfElement>
  class puppyWhile : public seakgChrysocyon::InterfaceChrysocyonPuppy<Element,ArrayOfElement>
  {
    public:
      puppyWhile(javascript::core *pCore);
      // InterfaceChrysocyonPuppy
      virtual seakgChrysocyon::chrysocyonAnswer SendElement(Element ch);
      virtual void GetResult( seakgChrysocyon::Stack<ArrayOfElement> *pStackResult );
      virtual void Reset();
      virtual bool StepBack();

    private:
      wchar_t m_chResult;
      javascript::core *m_pCore;
      UnicodeString m_strWhile;
      UnicodeString m_strResultWhile;
      int m_nWhile;
  };
   */

/*
  template <>
  class brainfuckPuppyMain<wchar_t,wchar_t>
  {
    public:
      brainfuckPuppyMain(brainfuck::core *pCore);

      // InterfaceChrysocyonPuppy
      virtual seakgChrysocyon::chrysocyonAnswer SendElement(wchar_t ch);
      virtual void GetResult( seakgChrysocyon::Stack<wchar_t> *pStackResult );
      virtual void Reset();
      virtual bool StepBack();

    private:
      wchar_t m_chResult;
      brainfuck::core *m_pCore;
  };
*/

}; // namespace javascript

#endif
