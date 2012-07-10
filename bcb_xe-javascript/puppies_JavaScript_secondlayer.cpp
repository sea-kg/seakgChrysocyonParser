//---------------------------------------------------------------------------


#pragma hdrstop

#include "puppies_JavaScript_secondlayer.h"

//---------------------------------------------------------------------------
namespace javascript
{

  // ============ variables

  template<>
  puppyDeclareVariables<UnicodeString, UnicodeString>::puppyDeclareVariables(javascript::core *pCore)
  : m_pCore(pCore)
  {
    m_strResult = "";
    m_nStep = 0;
  };

  //------------------------------------------------------------------------------------

  template<>
  seakgChrysocyon::chrysocyonAnswer puppyDeclareVariables<UnicodeString, UnicodeString>::SendElement(UnicodeString str)
  {
    //wcout << L"["  << str.c_str() << L"]";
    if( str.Length() == 0 )
      return seakgChrysocyon::schsYetUnknown;

    if( (m_nStep == 0) && (str == L"var") )
    {
      m_nStep = 1;
      m_strNameVar = "";
      m_strValueVar = "";
      return seakgChrysocyon::schsOnlyMe;
    }
    else if( m_nStep == 1 )
    {
      m_strNameVar = str;
      m_nStep = 2;
      return seakgChrysocyon::schsOnlyMe;
    }
    else if( m_nStep == 2 && str == ";" )
    {
      javascript::var var;
      var.Name = m_strNameVar;
      var.Value = m_strValueVar;
      m_pCore->addVariable(var);
      return seakgChrysocyon::schsComplete;
    }
    else if( m_nStep == 2 && str == "," )
    {
      javascript::var var;
      var.Name = m_strNameVar;
      var.Value = m_strValueVar;
      m_pCore->addVariable(var);
      m_nStep = 1;
      m_strNameVar = "";
      m_strValueVar = "";
      return seakgChrysocyon::schsOnlyMe;
    }
    else if ( m_nStep == 2 && str == "=" )
    {
      m_nStep = 3;
      return seakgChrysocyon::schsOnlyMe;
    }
    else if ( m_nStep == 3 )
    {
      m_strValueVar = str;
      m_nStep = 2;
      return seakgChrysocyon::schsOnlyMe;
    };

    return seakgChrysocyon::schsNone;
  };

  //------------------------------------------------------------------------------------

  template<>
  void puppyDeclareVariables<UnicodeString, UnicodeString>::GetResult( seakgChrysocyon::Stack<UnicodeString> *pStackResult )
  {
    pStackResult->Push( "" );
  };

  //------------------------------------------------------------------------------------

  template<>
  void puppyDeclareVariables<UnicodeString, UnicodeString>::Reset()
  {
    m_nStep = 0;
    m_strNameVar = "";
    m_strValueVar = "";
    m_strResult = "";
  };

  //------------------------------------------------------------------------------------

  template<>
  bool puppyDeclareVariables<UnicodeString,UnicodeString>::StepBack()
  {
    return false;
  };

  // ============ functions

  template<>
  puppyDeclareFunctions<UnicodeString, UnicodeString>::puppyDeclareFunctions(javascript::core *pCore)
  : m_pCore(pCore)
  {
    m_strResult = "";
    m_nStep = 0;
  };

  //------------------------------------------------------------------------------------

  template<>
  seakgChrysocyon::chrysocyonAnswer puppyDeclareFunctions<UnicodeString, UnicodeString>::SendElement(UnicodeString str)
  {
    //wcout << L"["  << str.c_str() << L"]";
    
    if( str.Length() == 0 )
      return seakgChrysocyon::schsYetUnknown;

    if( (m_nStep == 0) && (str == L"function") )
    {
      m_nStep = 1;
      m_strNameFunction = "";
//      m_strValueVar = "";
      return seakgChrysocyon::schsOnlyMe;
    }
    else if( m_nStep == 1 )
    {
      m_strNameFunction = str;
      m_nStep = 2;
      return seakgChrysocyon::schsOnlyMe;
    }
    else if( m_nStep == 2 && str == "(" )
    {
      m_nStep = 3;
      return seakgChrysocyon::schsOnlyMe;
    }
    else if( m_nStep == 3 && str == ")" )
    {
      m_nStep = 5;
      return seakgChrysocyon::schsOnlyMe;
    }
    else if( m_nStep == 3 )
    {
      m_vNameVariables.push_back(str);
      m_nStep = 4;
      return seakgChrysocyon::schsOnlyMe;
    }
    else if ( m_nStep == 4 && str == "," )
    {
      m_nStep = 3;
      return seakgChrysocyon::schsOnlyMe;
    }
    else if ( m_nStep == 4 && str == ")" )
    {
      m_nStep = 5;
      return seakgChrysocyon::schsOnlyMe;
    }
    else if( m_nStep == 5 && str == "{" )
    {
      if( m_nBreakOpen > 0 )
        m_strFunctionImpl += " " + str;

      m_nBreakOpen++;      
      return seakgChrysocyon::schsOnlyMe;
    }
    else if( m_nStep == 5 && str == "}" )
    {
      m_nBreakClose++;

      if(m_nBreakOpen > 0 && m_nBreakOpen == m_nBreakClose )
        return seakgChrysocyon::schsComplete;

      m_strFunctionImpl += " " + str;
      return seakgChrysocyon::schsOnlyMe;
    }
    else if( m_nStep == 5 )
    {
      if( m_nBreakOpen > 0 )
        m_strFunctionImpl += " " + str;

      return seakgChrysocyon::schsOnlyMe;
    };


    return seakgChrysocyon::schsNone;
  };

  //------------------------------------------------------------------------------------

  template<>
  void puppyDeclareFunctions<UnicodeString, UnicodeString>::GetResult( seakgChrysocyon::Stack<UnicodeString> *pStackResult )
  {
    javascript::function func;
    func.Name = m_strNameFunction;
    func.Implementation = m_strFunctionImpl;
    func.CountParameters = m_vNameVariables.size();

//    wcout << L"\n" << func.Name.c_str() << L"; impl : " << func.Implementation.c_str() << L"\n" ;
    for( unsigned int i = 0; i < m_vNameVariables.size(); i++)
      func.VarNames.push_back(m_vNameVariables[i]);  

    m_pCore->addFunction(func);

    /*
      vector<UnicodeString> m_vNameVariables;
      UnicodeString SourceName; // source
      int CountParameters;
      UnicodeString Name;
      UnicodeString Implementation;
    */    
    //
    pStackResult->Push( "" );
  };

  //------------------------------------------------------------------------------------

  template<>
  void puppyDeclareFunctions<UnicodeString, UnicodeString>::Reset()
  {
    m_nStep = 0;
    m_nBreakOpen = 0;
    m_nBreakClose = 0;
    //m_strNameVar = "";
    //m_strValueVar = "";
    m_vNameVariables.clear();
    m_strResult = "";
    m_strFunctionImpl = "";
  };

  //------------------------------------------------------------------------------------

  template<>
  bool puppyDeclareFunctions<UnicodeString,UnicodeString>::StepBack()
  {
    return false;
  };


}; // namespace javascript
  //------------------------------------------------------------------------------------

#pragma package(smart_init)
