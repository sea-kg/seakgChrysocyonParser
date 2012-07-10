//---------------------------------------------------------------------------

#include <vcl.h>
#include <iostream.h>
#include <conio.h>
#pragma hdrstop


#include <tchar.h>
#include "puppies_JavaScript_firstlayer.h"
#include "puppies_JavaScript_secondlayer.h"

//#include "../seakgChrysocyonParser/bcb_xe.h"

//typedef seakgChrysocyon::Parser<wchar_t,UnicodeString> CharParser;
typedef seakgReaderFromUnicodeString<wchar_t> CharReader;
typedef seakgReaderFromUnicodeString<UnicodeString> CharReader2;

//typedef javascript::puppyNumber<wchar_t,UnicodeString> PuppyNumber;
typedef javascript::puppyName<wchar_t,UnicodeString> PuppyName;
typedef javascript::puppySpace<wchar_t,UnicodeString> PuppySpace;
typedef javascript::puppyMultiLineComments<wchar_t,UnicodeString> PuppyMultiLineComments;
typedef javascript::puppyLineComment<wchar_t,UnicodeString> PuppyLineComment;
typedef javascript::puppyLine<wchar_t,UnicodeString> PuppyLine;
typedef javascript::puppySimbol<wchar_t,UnicodeString> PuppySimbol;
typedef javascript::puppyStringInDoubleQuotes<wchar_t,UnicodeString> PuppyStringInDoubleQuotes;


typedef javascript::puppyDeclareVariables<UnicodeString,UnicodeString> PuppyDeclareVariables;
typedef javascript::puppyDeclareFunctions<UnicodeString,UnicodeString> PuppyDeclareFunctions;
/*
typedef seakgPuppyAnySimbol<wchar_t,UnicodeString> PuppyAnySimbol;
typedef seakgPuppyStringInDoubleQuotes<wchar_t,UnicodeString> PuppyStringInDoubleQuotes;
*/
//typedef seakgPuppyLine<QChar,QString> PuppyLine;

//----------------------------------------------------------------------------

void init_layer_first( CharParser *pParser , javascript::core *pCore)
{
//	pParser->AddPuppy( new PuppyNumber() );
  pParser->AddPuppy( new PuppyName(pCore) );
  pParser->AddPuppy( new PuppySpace(pCore) );
  pParser->AddPuppy( new PuppyLine(pCore) );
  pParser->AddPuppy( new PuppyMultiLineComments(pCore) );
  pParser->AddPuppy( new PuppyLineComment(pCore) );
  pParser->AddPuppy( new PuppySimbol(pCore, '(') );
  pParser->AddPuppy( new PuppySimbol(pCore, ')') );
  pParser->AddPuppy( new PuppySimbol(pCore, '{') );
  pParser->AddPuppy( new PuppySimbol(pCore, '}') );
  pParser->AddPuppy( new PuppyStringInDoubleQuotes(pCore) );
  pParser->AddPuppy( new PuppySimbol(pCore, ';') );
  pParser->AddPuppy( new PuppySimbol(pCore, '=') );
  pParser->AddPuppy( new PuppySimbol(pCore, '+') );
  pParser->AddPuppy( new PuppySimbol(pCore, ',') );
};
//----------------------------------------------------------------------------

void init_layer_second( JavaScriptParser *pParser , javascript::core *pCore)
{
  pParser->AddPuppy( new PuppyDeclareVariables(pCore) );
  pParser->AddPuppy( new PuppyDeclareFunctions(pCore) );

  /*
//	pParser->AddPuppy( new PuppyNumber() );
	pParser->AddPuppy( new PuppyName(pCore) );
  pParser->AddPuppy( new PuppySpace(pCore) );
  pParser->AddPuppy( new PuppyLine(pCore) );
  pParser->AddPuppy( new PuppyMultiLineComments(pCore) );
  pParser->AddPuppy( new PuppyLineComment(pCore) );
  pParser->AddPuppy( new PuppySimbol(pCore, '(') );
  pParser->AddPuppy( new PuppySimbol(pCore, ')') );
  pParser->AddPuppy( new PuppySimbol(pCore, '{') );
  pParser->AddPuppy( new PuppySimbol(pCore, '}') );
  pParser->AddPuppy( new PuppyStringInDoubleQuotes(pCore) );
  pParser->AddPuppy( new PuppySimbol(pCore, ';') );
  */
};
//----------------------------------------------------------------------------

#pragma argsused
int _tmain(int argc, _TCHAR* argv[])
{
  if( argc != 2 )
  {
    wcout << "Usage: javascript <filename>";
    return 0;
  };

  UnicodeString strFilename(argv[1]);

  TStringList *list = new TStringList();
  list->LoadFromFile(strFilename);

  CharReader *pReader = new CharReader();
	pReader->setString( list->Text );

	CharParser *pParserLayerFirst = new CharParser(pReader);
  JavaScriptParser *pParserLayerSecond = new JavaScriptParser(pParserLayerFirst);


  javascript::core * pCore = new javascript::core();

	init_layer_first( pParserLayerFirst,  pCore);
  init_layer_second( pParserLayerSecond,  pCore);


  //init_layer_second( )

  while( !pParserLayerSecond->Eof() )
  {
    UnicodeString strResult;
    int err;
    if( pParserLayerSecond->GetNextElement( strResult, err ) )
    {
      /*
      if( strResult.Length() > 0 )
   			std::wcout << L"[" << strResult.c_str() << L"]\n";
      */
      if( strResult.Length() > 0 )
        std::wcout << strResult.c_str() << " ";
    }
    else
    {
      std::wcout << L"[err=" << UnicodeString(err).c_str() << L"]\n";
      break;
    };
  };
  std::cout << "\r\n-----------";
  std::cout << "\r\n";

  javascript::var f1;
  javascript::var f2;
  javascript::var f3;

  /*
  std::wcout << L" find variables: \r\n";

  if( pCore->findVariable( L"f1", f1 ) )
    std::wcout << L"var f1 = " << f1.Value.c_str() << L"\r\n";

  if( pCore->findVariable( L"f2", f2 ) )
    std::wcout << L"var f2 = " << f2.Value.c_str() << L"\r\n";

  if( pCore->findVariable( L"f3", f3 ) )
    std::wcout << L"var f3 = " << f3.Value.c_str() << L"\r\n";
  */

  javascript::function mainfunc;
  if( pCore->findFunction( L"main", 0, mainfunc ) )
  {
    mainfunc.Exec();
  }
  else
  {
    wcout << L"not found function 'main' !!! \n";
  };

  //getch();
  return 0;
}
//---------------------------------------------------------------------------
