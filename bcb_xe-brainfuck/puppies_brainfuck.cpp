//---------------------------------------------------------------------------

#include <vector.h>
#include <vcl.h>
#include <conio.h>
#pragma hdrstop

#include "puppies_brainfuck.h"

namespace brainfuck
{
  core::core()
  {
    m_nPos = 0;
    m_vSlots.clear();
    int n = 0;
    m_vSlots.push_back(n);
    Debug = false;
  };

  void core::next()
  {
    m_nPos++;
    if(m_nPos > (m_vSlots.size() - 1))
    {
      int n = 0;
      m_vSlots.push_back(n);
    };
  };

  void core::prev()
  {
    if(m_nPos > 0)
      m_nPos--;
  };

  void core::inc()
  {
    m_vSlots[m_nPos]++;
  };

  void core::decr()
  {
    m_vSlots[m_nPos]--;
  };

  int core::get()
  {
    return m_vSlots[m_nPos];
  };

  void core::set(int ch)
  {
    m_vSlots[m_nPos] = ch;
  };

  void core::print_state()
  {
    if(Debug)
    {
      std::wcout << L" #### core state #### \r\n";
      for(unsigned int i = 0; i < m_vSlots.size(); i++)
      {
        int ch = m_vSlots[i];
        std::wcout << L"slot " << i << L": int(" << ch << "), wchar_t(" << wchar_t(ch) << ") ;\r\n";
      }
      std::wcout << L" #### end #### \r\n";
    };
  };

  //------------------------------------------------------------------------------------

  template<>
  puppyMain<wchar_t,wchar_t>::puppyMain(brainfuck::core *pCore)
  : m_pCore(pCore)
  {
    m_chResult = 0;
  };

  //------------------------------------------------------------------------------------

  template<>
  seakgChrysocyon::chrysocyonAnswer puppyMain<wchar_t, wchar_t>::SendElement(wchar_t ch)
  {
    if( ch == '>' )
    {
      m_pCore->next();
      if( m_pCore->Debug ) m_chResult = ch; else m_chResult = 0;
      return seakgChrysocyon::schsComplete;
    }
    else if( ch == '<' )
    {
      m_pCore->prev();
      if( m_pCore->Debug ) m_chResult = ch; else m_chResult = 0;
      return seakgChrysocyon::schsComplete;
    }
    else if( ch == '+' )
    {
      m_pCore->inc();
      if( m_pCore->Debug ) m_chResult = ch; else m_chResult = 0;
      return seakgChrysocyon::schsComplete;
    }
    else if( ch == '-' )
    {
      m_pCore->decr();
      if( m_pCore->Debug ) m_chResult = ch; else m_chResult = 0;
      return seakgChrysocyon::schsComplete;
    }
    else if( ch == '.' )
    {
      m_chResult = m_pCore->get();
      return seakgChrysocyon::schsComplete;
    }
    else if( ch == ',' )
    {
      int chTemp = wchar_t(getch());
      m_pCore->set(chTemp);
//      m_chResult = chTemp;
      if( m_pCore->Debug ) m_chResult = chTemp; else m_chResult = 0;
      return seakgChrysocyon::schsComplete;
    }
    else if( ch == 's' )
    {
      m_pCore->print_state();
      if( m_pCore->Debug ) m_chResult = ch; else m_chResult = 0;
      return seakgChrysocyon::schsComplete;
    }
    else if( ch == '\r' )
    {
      if( m_pCore->Debug ) m_chResult = ch; else m_chResult = 0;
      return seakgChrysocyon::schsComplete;
    }
    else if( ch == '\n' )
    {
      if( m_pCore->Debug ) m_chResult = ch; else m_chResult = 0;
      return seakgChrysocyon::schsComplete;
    }
    else if( ch == ' ' )
    {
      if( m_pCore->Debug ) m_chResult = ch; else m_chResult = 0;
      return seakgChrysocyon::schsComplete;
    }

    return seakgChrysocyon::schsNone;
  };

  //------------------------------------------------------------------------------------

  template<>
  void puppyMain<wchar_t, wchar_t>::GetResult( seakgChrysocyon::Stack<wchar_t> *pStackResult )
  {
    pStackResult->Push( m_chResult );
  };

  //------------------------------------------------------------------------------------

  template<>
  void puppyMain<wchar_t, wchar_t>::Reset()
  {
    m_chResult = ' ';
  };

  //------------------------------------------------------------------------------------

  template<>
  bool puppyMain<wchar_t, wchar_t>::StepBack()
  {
    return false;
  };
//------------------------------------------------------------------------------------

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


/* schsNone = 0, // точно нет или я отказываюсь
		schsYetUnknown = 1, //еще не знаю или еще не определился давай дальше
		schsMaybe = 2, // Может быть мое
		schsOnlyMe = 3, // Точно мое ( и должно быть только мое )
		schsComplete = 4, // да я закончил можешь забирать результат */


//---------------------------------------------------------------------------
}; //namespace brainfuck

#pragma package(smart_init)


