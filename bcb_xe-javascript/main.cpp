//---------------------------------------------------------------------------

#include <vcl.h>
#include <iostream.h>
#include <conio.h>
#pragma hdrstop


#include <tchar.h>
#include "puppies_JavaScript_firstlayer.h"
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
};
//----------------------------------------------------------------------------

void init_layer_second( CharParser *pParser , javascript::core *pCore)
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

  javascript::core * pCore = new javascript::core();

	init_layer_first( pParserLayerFirst,  pCore);

	while( !pParserLayerFirst->Eof() )
	{
		UnicodeString strResult;
		int err;
		if( pParserLayerFirst->GetNextElement( strResult, err ) )
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
			std::cout << "[err=" << (int)err << "]\n";
			break;
		};
	};
	std::cout << "\r\n-----------";
	std::cout << "\r\n";

  getch();
  return 0;
}
//---------------------------------------------------------------------------
