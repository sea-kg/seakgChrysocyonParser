//---------------------------------------------------------------------------

#ifndef javascript_coreH
#define javascript_coreH
//---------------------------------------------------------------------------
#include <vector.h>
#include <vcl.h>
#include <iostream.h>
#include <conio.h>

namespace javascript
{
  class error;
  class var;
  class function;
  class core;


  class error
  {
    public:
      error(int code, UnicodeString msg);
      const wchar_t *getMsgW();

      javascript::core *Core;
      UnicodeString Message;
      int Code;
  };
  
  class var
  {
    public:
      var();
      UnicodeString Name;
      UnicodeString Value;
  };
  
  class function
  {
    public:
      function();
      virtual javascript::var Exec(javascript::var vars[]);
      virtual javascript::var Exec();
      vector<UnicodeString> VarNames;
      UnicodeString SourceName; // source
      int CountParameters;
      UnicodeString Name;
      UnicodeString Implementation;
      javascript::core *Core;
  };
  
  
  
  class core
  {
    public:
      core();
      void next_line();
      bool addFunction( javascript::function &func );
      bool addVariable( javascript::var &var );
      bool findFunction( UnicodeString Name, int CountParameters, javascript::function &func );
      bool findVariable( UnicodeString Name, javascript::var &var );

      bool Debug;

    private:
      unsigned int m_nPos;
      unsigned int m_nLine;
	  
      vector<javascript::function> m_vFunctions;
      vector<javascript::var> m_vVariable;
  };
  
  
}; // namespace javascript

#endif
