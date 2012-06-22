//---------------------------------------------------------------------------


#pragma hdrstop

#include "javascript_core.h"

namespace javascript
{
  error::error(int code, UnicodeString msg)
  {
	  Code = code;
	  Message = msg;
  };

  const wchar_t *error::getMsgW()
  {
	  UnicodeString msg = L"error " + IntToStr(Code) + L": " + Message;
	  return msg.c_str();
  }
  
  var::var()
  {
    Name = L"";
	  Value = L"";
  };
  
  function::function()
  {
    SourceName = L"";
	  CountParameters = 0;
   	Name = L"";
	  Implementation = L"";
  };

  javascript::var &function::Exec(javascript::var vars[])
  {
    int count = sizeof(vars) / sizeof(javascript::var);
    if( count != CountParameters )
    {
      wcout << error( 1018, L" in function '" + Name + "' - want " + IntToStr(CountParameters) + " parametrs, but get " + IntToStr(count) + L" parametrs \n").getMsgW();

      throw 1; // not correct
    };
  	// to do parse and execute
  };
  
  
  core::core()
  {
    m_nLine = 0;
/*  m_nPos = 0;
    m_vSlots.clear();
    int n = 0;
    m_vSlots.push_back(n);
    Debug = false;*/
  };


  void core::next_line()
  {
    m_nLine++;
  };

  bool core::addFunction( javascript::function &func )
  {
    javascript::function tempFunction;
    if( !findFunction(func.Name, func.CountParameters, tempFunction) )
    {
      m_vFunctions.push_back( func );
    }
    else
    {
      wcout << error( 1019, L"'" + func.Name + "' - function with " + IntToStr(func.CountParameters) + L" parametrs alrady exists \n").getMsgW();
    };
  };
  
  bool core::addVariable( javascript::var &var )
  {
    //wcout << L"{add variable: " << var.Name.c_str() << L"}";
    javascript::var tempVar;
    if( !findVariable(var.Name, tempVar) )
    {
      tempVar.Name = var.Name;
      tempVar.Value = var.Value;
      m_vVariable.push_back( tempVar );
    }
    else
    {
      wcout << error( 1020, L"'" + var.Name + "' - variable alrady exists \n").getMsgW();
    };
  };
  
  bool core::findFunction( UnicodeString Name, int CountParameters, javascript::function &func )
  {
    for(unsigned int i = 0; i < m_vFunctions.size(); i++ )
    {
      if( (m_vFunctions[i].Name == Name) && ( m_vFunctions[i].CountParameters == CountParameters ) )
      {
        func = m_vFunctions[i];
        return true;
      };

    };
    return false;
  };
  
	bool core::findVariable( UnicodeString Name, javascript::var &var )
	{
    for(unsigned int i = 0; i < m_vVariable.size(); i++ )
    {
      if(m_vVariable[i].Name == Name)
      {
        var = m_vVariable[i];
        return true;
      };
    };
    return false;
  }
  //---------------------------------------------------------------------------

}; // namespace javascript

#pragma package(smart_init)
