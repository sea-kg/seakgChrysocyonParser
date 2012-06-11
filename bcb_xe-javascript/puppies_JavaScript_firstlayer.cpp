//---------------------------------------------------------------------------


#pragma hdrstop

#include "puppies_JavaScript_firstlayer.h"

namespace javascript
{
  //------------------------------------------------------------------------------------

  template<>
  puppyName<wchar_t,UnicodeString>::puppyName(javascript::core *pCore)
  : m_pCore(pCore)
  {
    m_strResult = "";
  };

  //------------------------------------------------------------------------------------

  template<>
  seakgChrysocyon::chrysocyonAnswer puppyName<wchar_t, UnicodeString>::SendElement(wchar_t ch)
  {
    int nLen = m_strResult.Length();
    if( nLen == 0 && isLetter(ch) )
    {
      m_strResult = m_strResult + ch;
      return seakgChrysocyon::schsMaybe;
    }
    else if( nLen > 0 && isLetterOrNumber(ch) )
    {
      m_strResult = m_strResult + ch;
      return seakgChrysocyon::schsMaybe;
    }
    else if( nLen > 0 && !isLetterOrNumber(ch) )
    {
      return seakgChrysocyon::schsComplete;
    };

    if( nLen > 0)
    {
      wcout << m_strResult.c_str() << "\n";
    };

    return seakgChrysocyon::schsNone;
  };

  //------------------------------------------------------------------------------------

  template<>
  void puppyName<wchar_t, UnicodeString>::GetResult( seakgChrysocyon::Stack<UnicodeString> *pStackResult )
  {
    pStackResult->Push( m_strResult );
  };

  //------------------------------------------------------------------------------------

  template<>
  void puppyName<wchar_t, UnicodeString>::Reset()
  {
    m_strResult = "";
  };

  //------------------------------------------------------------------------------------

  template<>
  bool puppyName<wchar_t, UnicodeString>::StepBack()
  {
    return true;
  };

  //------------------------------------------------------------------------------------

  template<>
  puppySpace<wchar_t,UnicodeString>::puppySpace(javascript::core *pCore)
  : m_pCore(pCore)
  {
    m_strResult = "";
  };

  //------------------------------------------------------------------------------------

  template<>
  seakgChrysocyon::chrysocyonAnswer puppySpace<wchar_t, UnicodeString>::SendElement(wchar_t ch)
  {
    if( m_strResult.Length() == 0 && ch == ' ' )
    {
      m_strResult = m_strResult + ch;
      return seakgChrysocyon::schsMaybe;
    }
    if( m_strResult.Length() > 0 && ch == ' ' )
    {
      m_strResult = m_strResult + ch;
      return seakgChrysocyon::schsOnlyMe;
    }
    else if( m_strResult.Length() > 0 && ch != ' ' )
    {
      return seakgChrysocyon::schsComplete;
    }
    return seakgChrysocyon::schsNone;
  };

  //------------------------------------------------------------------------------------

  template<>
  void puppySpace<wchar_t, UnicodeString>::GetResult( seakgChrysocyon::Stack<UnicodeString> *pStackResult )
  {
    m_strResult = "";
    pStackResult->Push( m_strResult );
  };

  //------------------------------------------------------------------------------------

  template<>
  void puppySpace<wchar_t, UnicodeString>::Reset()
  {
    m_strResult = "";
  };

  //------------------------------------------------------------------------------------

  template<>
  bool puppySpace<wchar_t, UnicodeString>::StepBack()
  {
    return true;
  };

  //------------------------------------------------------------------------------------


  template<>
  puppyMultiLineComments<wchar_t,UnicodeString>::puppyMultiLineComments(javascript::core *pCore)
  : m_pCore(pCore)
  {
    Reset();
  };

  //------------------------------------------------------------------------------------

  template<>
  seakgChrysocyon::chrysocyonAnswer puppyMultiLineComments<wchar_t, UnicodeString>::SendElement(wchar_t ch)
  {
    int nLen = m_strResult.Length();
    if( nLen == 0 && ch == '/' )
    {
      m_strResult = m_strResult + ch;

      return seakgChrysocyon::schsMaybe;
    }
    else if( nLen == 1 && m_strResult[1] == '/' && ch == '*' )
    {
      m_strResult = m_strResult + ch;
      return seakgChrysocyon::schsOnlyMe;
    }
    else if(nLen > 1 && ch == '*' )
    {
      m_strResult = m_strResult + ch;
      return seakgChrysocyon::schsOnlyMe;
    }
    else if( nLen > 1 && m_strResult[nLen] == '*' && ch != '/' )
    {
      m_strResult = m_strResult + ch;
      return seakgChrysocyon::schsOnlyMe;
    }
    else if( nLen > 1 && m_strResult[nLen] == '*' && ch == '/' )
    {
      m_strResult = m_strResult + ch;
      return seakgChrysocyon::schsComplete;
    }
    else if( nLen > 1 && ch != '*' )
    {
      m_strResult = m_strResult + ch;
      return seakgChrysocyon::schsOnlyMe;
    };
    return seakgChrysocyon::schsNone;
  };

  //------------------------------------------------------------------------------------

  template<>
  void puppyMultiLineComments<wchar_t, UnicodeString>::GetResult( seakgChrysocyon::Stack<UnicodeString> *pStackResult )
  {
    pStackResult->Push( m_strResult );
  };

  //------------------------------------------------------------------------------------

  template<>
  void puppyMultiLineComments<wchar_t, UnicodeString>::Reset()
  {
    m_strResult = "";
    start_ = false;
    end_ = false;
  };

  //------------------------------------------------------------------------------------

  template<>
  bool puppyMultiLineComments<wchar_t, UnicodeString>::StepBack()
  {
    return false;
  };

  //------------------------------------------------------------------------------------

  template<>
  puppyLineComment<wchar_t,UnicodeString>::puppyLineComment(javascript::core *pCore)
  : m_pCore(pCore)
  {
    Reset();
  };

  template<>
  seakgChrysocyon::chrysocyonAnswer puppyLineComment<wchar_t, UnicodeString>::SendElement(wchar_t ch)
  {
    int nLen = m_strResult.Length();
    if( nLen == 0 && ch == '/' )
    {
      m_strResult = m_strResult + ch;
      return seakgChrysocyon::schsMaybe;
    }
    else if( nLen == 1 && m_strResult[1] == '/' && ch == '/' )
    {
      m_strResult = m_strResult + ch;
      return seakgChrysocyon::schsOnlyMe;
    }
    else if(nLen > 1 && ( ch == '\n' || ch == '\r'))
    {
      return seakgChrysocyon::schsComplete;
    }
    else if( nLen > 1 && ch != '\n' )
    {
      m_strResult = m_strResult + ch;
      return seakgChrysocyon::schsOnlyMe;
    };
    return seakgChrysocyon::schsNone;
  };

  //------------------------------------------------------------------------------------

  template<>
  void puppyLineComment<wchar_t, UnicodeString>::GetResult( seakgChrysocyon::Stack<UnicodeString> *pStackResult )
  {
    pStackResult->Push( m_strResult );
  };

  //------------------------------------------------------------------------------------

  template<>
  void puppyLineComment<wchar_t, UnicodeString>::Reset()
  {
    m_strResult = "";
  };

  //------------------------------------------------------------------------------------

  template<>
  bool puppyLineComment<wchar_t, UnicodeString>::StepBack()
  {
    return false;
  };

  //------------------------------------------------------------------------------------


  template<>
  puppyLine<wchar_t,UnicodeString>::puppyLine(javascript::core *pCore)
  : m_pCore(pCore)
  {
    m_strResult = "";
  };

  //------------------------------------------------------------------------------------

  template<>
  seakgChrysocyon::chrysocyonAnswer puppyLine<wchar_t, UnicodeString>::SendElement(wchar_t ch)
  {
    if( ch == '\r' )
    {
      return seakgChrysocyon::schsComplete;
    }
    else if( ch == '\n' )
    {
      return seakgChrysocyon::schsComplete;
    }
    return seakgChrysocyon::schsNone;
  };

  //------------------------------------------------------------------------------------

  template<>
  void puppyLine<wchar_t, UnicodeString>::GetResult( seakgChrysocyon::Stack<UnicodeString> *pStackResult )
  {
    m_strResult = "";
    pStackResult->Push( m_strResult );
  };

  //------------------------------------------------------------------------------------

  template<>
  void puppyLine<wchar_t, UnicodeString>::Reset()
  {
    m_strResult = "";
  };

  //------------------------------------------------------------------------------------

  template<>
  bool puppyLine<wchar_t, UnicodeString>::StepBack()
  {
    return false;
  };

  //------------------------------------------------------------------------------------

  template<>
  puppySimbol<wchar_t,UnicodeString>::puppySimbol(javascript::core *pCore, wchar_t chSimbol)
  : m_pCore(pCore), m_chSimbol(chSimbol)
  {
    Reset();
  };

  //------------------------------------------------------------------------------------

  template<>
  seakgChrysocyon::chrysocyonAnswer puppySimbol<wchar_t, UnicodeString>::SendElement(wchar_t ch)
  {
    if( ch == m_chSimbol )
    {
      m_strResult = m_strResult + ch;
      return seakgChrysocyon::schsComplete;
    }
    return seakgChrysocyon::schsNone;
  };

  //------------------------------------------------------------------------------------

  template<>
  void puppySimbol<wchar_t, UnicodeString>::GetResult( seakgChrysocyon::Stack<UnicodeString> *pStackResult )
  {
    pStackResult->Push( m_strResult );
  };

  //------------------------------------------------------------------------------------

  template<>
  void puppySimbol<wchar_t, UnicodeString>::Reset()
  {
    m_strResult = "";
  };

  //------------------------------------------------------------------------------------

  template<>
  bool puppySimbol<wchar_t, UnicodeString>::StepBack()
  {
    return false;
  };

  //------------------------------------------------------------------------------------

  template<>
  puppyStringInDoubleQuotes<wchar_t,UnicodeString>::puppyStringInDoubleQuotes(javascript::core *pCore)
  : m_pCore(pCore)
  {
    Reset();
  };

  //------------------------------------------------------------------------------------

  template<>
  seakgChrysocyon::chrysocyonAnswer puppyStringInDoubleQuotes<wchar_t, UnicodeString>::SendElement(wchar_t ch)
  {
    int nLen = m_strResult.Length();
    if( (nLen == 0) && (ch == '\"') )
    {
      m_strResult += ch;
      return seakgChrysocyon::schsOnlyMe;
    }
    else if( (nLen > 0) && (ch == '\\') && (nR == 0) )
    {
      m_strResult += ch;
      nR = 1;
      return seakgChrysocyon::schsOnlyMe;
    }
    else if( (nLen > 0) && (nR != 1) && (ch == '\"') )
    {
      m_strResult += ch;
      return seakgChrysocyon::schsComplete;
    }
    else if( nLen > 0 )
    {
      m_strResult += ch;
      nR = 0;
      return seakgChrysocyon::schsOnlyMe;
    };

    return seakgChrysocyon::schsNone;
  };

  //------------------------------------------------------------------------------------

  template<>
  void puppyStringInDoubleQuotes<wchar_t, UnicodeString>::GetResult( seakgChrysocyon::Stack<UnicodeString> *pStackResult )
  {
    pStackResult->Push( m_strResult );
  };

  //------------------------------------------------------------------------------------

  template<>
  void puppyStringInDoubleQuotes<wchar_t, UnicodeString>::Reset()
  {
    m_strResult = "";
    nR = 0;
  };

  //------------------------------------------------------------------------------------

  template<>
  bool puppyStringInDoubleQuotes<wchar_t, UnicodeString>::StepBack()
  {
    return false;
  };

  //------------------------------------------------------------------------------------



/*
  template<>
  puppyWhile<wchar_t,wchar_t>::puppyWhile(brainfuck::core *pCore)
  : m_pCore(pCore)
  {
    m_chResult = 0;
    m_nWhile = 0;
    m_strWhile = "";
  };

  //------------------------------------------------------------------------------------

  template<>
  seakgChrysocyon::chrysocyonAnswer puppyWhile<wchar_t, wchar_t>::SendElement(wchar_t ch)
  {
    if( (ch == '[') && (m_nWhile == 0) )
    {
      m_nWhile = m_nWhile + 1;
      m_strWhile = L"";
//      wcout << "\r\n 1) if( (ch == '[') && (m_nWhile == 0) \r\n";

      if( m_pCore->Debug ) m_chResult = ch; else m_chResult = 0;

      return seakgChrysocyon::schsOnlyMe;
    }
    else if( (ch == '[') && (m_nWhile > 0) )
    {
      m_nWhile = m_nWhile + 1;

//      wcout << "\r\n 2) if ( (ch == '[') && (m_nWhile > 0) ) \r\n";
      if( m_pCore->Debug ) m_chResult = ch; else m_chResult = 0;
      return seakgChrysocyon::schsOnlyMe;
    }
    else if( ch != ']' && m_nWhile > 0 )
    {
      m_strWhile = m_strWhile + UnicodeString(ch);

      //wcout << "\r\n 3) if( ch != ']' && m_nWhile > 0 ) \r\n";

      //wcout << "\r\n" << m_strWhile.c_str() << "\r\n";
      if( m_pCore->Debug ) m_chResult = ch; else m_chResult = 0;
      return seakgChrysocyon::schsOnlyMe;
    }
    else if( ch == ']' && m_nWhile > 1 )
    {
      m_strWhile = m_strWhile + UnicodeString(ch);
      if( m_pCore->Debug ) m_chResult = ch; else m_chResult = 0;
      return seakgChrysocyon::schsOnlyMe;
    }
    else if( (ch == ']') && (m_nWhile == 1) )
    {
      m_nWhile--;

      // run block
      m_strResultWhile = "";
      while( m_pCore->get() != 0 )
      {
        CharReader *pReader = new CharReader();
        pReader->setString( m_strWhile );

        CharParser *pParser = new CharParser(pReader);
        typedef brainfuck::puppyMain<wchar_t,wchar_t> PuppyMain;
        typedef brainfuck::puppyWhile<wchar_t,wchar_t> PuppyWhile;

        pParser->AddPuppy( new PuppyMain(m_pCore) );
        pParser->AddPuppy( new PuppyWhile(m_pCore) );

        while( ! pParser->Eof() )
        {
          wchar_t chResult;
          int err;

          if( pParser->GetNextElement( chResult, err ) )
          {
            if(chResult != 0) m_strResultWhile += chResult;
          }
          else
          {
            return seakgChrysocyon::schsNone;
          }
        };
      }
      if( m_pCore->Debug ) m_chResult = ch; else m_chResult = 0;
      return seakgChrysocyon::schsComplete;
    };

    return seakgChrysocyon::schsNone;
  };

  //------------------------------------------------------------------------------------

  template<>
  void puppyWhile<wchar_t, wchar_t>::GetResult( seakgChrysocyon::Stack<wchar_t> *pStackResult )
  {
    for(int i = 1; i <= m_strResultWhile.Length(); i++ )
    {
      wchar_t ch = m_strResultWhile[i];
      pStackResult->Push( ch );
    };
    m_strResultWhile = L"";
  };

  //------------------------------------------------------------------------------------

  template<>
  void puppyWhile<wchar_t, wchar_t>::Reset()
  {
    m_chResult = ' ';
  };

  //------------------------------------------------------------------------------------

  template<>
  bool puppyWhile<wchar_t, wchar_t>::StepBack()
  {
    return false;
  };
//------------------------------------------------------------------------------------
*/

/* schsNone = 0, // точно нет или я отказываюсь
		schsYetUnknown = 1, //еще не знаю или еще не определился давай дальше
		schsMaybe = 2, // Может быть мое
		schsOnlyMe = 3, // Точно мое ( и должно быть только мое )
		schsComplete = 4, // да я закончил можешь забирать результат */


//---------------------------------------------------------------------------
}; //namespace brainfuck


//---------------------------------------------------------------------------

#pragma package(smart_init)
