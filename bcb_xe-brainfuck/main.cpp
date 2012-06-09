//---------------------------------------------------------------------------

#include <vcl.h>
#include <iostream.h>
#pragma hdrstop

#include <tchar.h>
//---------------------------------------------------------------------------

#include "puppies_brainfuck.h"

//#include "../seakgChrysocyonParser/bcb_xe.h"

brainfuck::core *g_pCore;

typedef seakgChrysocyon::Parser<wchar_t,wchar_t> CharParser;
typedef seakgReaderFromUnicodeString<wchar_t> CharReader;


typedef brainfuck::puppyMain<wchar_t,wchar_t> PuppyMain;
typedef brainfuck::puppyWhile<wchar_t,wchar_t> PuppyWhile;


//typedef seakgPuppyLine<QChar,QString> PuppyLine;

//----------------------------------------------------------------------------

void init_layer_first( CharParser *pParser )
{

  pParser->AddPuppy( new PuppyMain(g_pCore) );
  pParser->AddPuppy( new PuppyWhile(g_pCore) );

//	pParser->AddPuppy( new PuppyNumber() );
//	pParser->AddPuppy( new PuppyName() );
//	pParser->AddPuppy( new PuppyStringInDoubleQuotes() );
/*	pParser->AddPuppy( new PuppyAnySimbol('<') );
	pParser->AddPuppy( new PuppyAnySimbol('>') );
	pParser->AddPuppy( new PuppyAnySimbol('+') );
	pParser->AddPuppy( new PuppyAnySimbol('-') );
	pParser->AddPuppy( new PuppyAnySimbol('.') );
	pParser->AddPuppy( new PuppyAnySimbol(',') );
	pParser->AddPuppy( new PuppyAnySimbol('[') );
	pParser->AddPuppy( new PuppyAnySimbol(']') );
	pParser->AddPuppy( new PuppyAnySimbol('\r') );
	pParser->AddPuppy( new PuppyAnySimbol('\n') );
*/

};

//----------------------------------------------------------------------------

#pragma argsused
int _tmain(int argc, _TCHAR* argv[])
{
  if( argc == 2 || argc == 3)
  {
    UnicodeString filename(argv[1]);
    TStringList *list = new TStringList();
    list->LoadFromFile(filename);
    g_pCore = new brainfuck::core();

    if(argc == 3)
    {
      UnicodeString debug(argv[2]);
      if(debug == "debug") g_pCore->Debug = true;
      else g_pCore->Debug = false;
    }

    CharReader *pReader = new CharReader();
   	pReader->setString( list->Text );
    CharParser *pParserLayerFirst = new CharParser(pReader);
	  init_layer_first( pParserLayerFirst );

    while( ! pParserLayerFirst->Eof() )
    {
      wchar_t chResult;
      int err;
      if( pParserLayerFirst->GetNextElement( chResult, err ) )
      {
        if(chResult != 0)
          std::wcout << chResult;
      }
      else
      {
        std::cout << "\r\n[err=" << (int)err << "]\n";
        break;
      };
    };
  }
  else
  {
    wcout << "Useage: brainfuck <filename> - for release\r\nor brainfuck <filename> debug - for debug\r\n";
  };
  return 0;
}
//---------------------------------------------------------------------------
