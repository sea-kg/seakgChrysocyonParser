//---------------------------------------------------------------------------

#include <vcl.h>
#include <iostream.h>
#include <conio.h>
#pragma hdrstop


#include <tchar.h>
#include "../seakgChrysocyonParser/bcb_xe.h"

typedef seakgChrysocyon::Parser<wchar_t,UnicodeString> CharParser;
typedef seakgReaderFromUnicodeString<wchar_t> CharReader;

typedef seakgPuppyNumber<wchar_t,UnicodeString> PuppyNumber;
typedef seakgPuppyName<wchar_t,UnicodeString> PuppyName;
typedef seakgPuppyAnySimbol<wchar_t,UnicodeString> PuppyAnySimbol;
typedef seakgPuppyStringInDoubleQuotes<wchar_t,UnicodeString> PuppyStringInDoubleQuotes;
//typedef seakgPuppyLine<QChar,QString> PuppyLine;

//----------------------------------------------------------------------------

void init_layer_first( CharParser *pParser )
{
	pParser->AddPuppy( new PuppyNumber() );
	pParser->AddPuppy( new PuppyName() );
	pParser->AddPuppy( new PuppyStringInDoubleQuotes() );
	pParser->AddPuppy( new PuppyAnySimbol(' ') );
	pParser->AddPuppy( new PuppyAnySimbol('!') );
	pParser->AddPuppy( new PuppyAnySimbol(',') );
	pParser->AddPuppy( new PuppyAnySimbol(')') );
	pParser->AddPuppy( new PuppyAnySimbol('(') );
	pParser->AddPuppy( new PuppyAnySimbol('=') );
	pParser->AddPuppy( new PuppyAnySimbol('+') );
	pParser->AddPuppy( new PuppyAnySimbol(';') );
	pParser->AddPuppy( new PuppyAnySimbol('{') );
	pParser->AddPuppy( new PuppyAnySimbol('}') );
	pParser->AddPuppy( new PuppyAnySimbol('\r') );
	pParser->AddPuppy( new PuppyAnySimbol('\n') );
};
//----------------------------------------------------------------------------

#pragma argsused
int _tmain(int argc, _TCHAR* argv[])
{
  UnicodeString strTest = "func add123( int a = 123, int b = 989, string str = \" \\\"dfsdf\\\\ \" ) { "
 	  "  cout a+b; \r\n"
  	" } ";

  CharReader *pReader = new CharReader();
	pReader->setString( strTest );

	CharParser *pParserLayerFirst = new CharParser(pReader);

	init_layer_first( pParserLayerFirst );


	while( ! pParserLayerFirst->Eof() )
	{
		UnicodeString strResult;
		int err;
		if( pParserLayerFirst->GetNextElement( strResult, err ) )
		{
			std::wcout << L"[" << strResult.c_str() << L"]\n";
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
