// place your code here
#include <iostream>

#include "../seakgChrysocyonParser/qt.h"

//#include "seakgExampleParser.h"

//class seakgChrysocyon::seakgChrysocyonContainer<char>;

typedef seakgChrysocyon::chrysocyonParser<QChar,QString> CharParser;
typedef seakgReaderFromQString<QChar> CharReader;

typedef seakgPuppyNumber<QChar,QString> PuppyNumber;
typedef seakgPuppyName<QChar,QString> PuppyName;
typedef seakgPuppyAnySimbol<QChar,QString> PuppyAnySimbol;
typedef seakgPuppyStringInDoubleQuotes<QChar,QString> PuppyStringInDoubleQuotes;
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

int main()
{
	QChar ch;
	
	QString strTest = "func add123( int a = 123, int b = 989, string str = \" \\\"dfsdf\\\\ \" ) { "
	"  cout a+b; \r\n"
	" } ";
	
	std::cout << "-----------\r\n";
	std::cout << "[" << strTest.toStdString() << "]:" << strTest.length() << "\r\n";
	std::cout << "-----------\r\n";
	
	CharReader *pReader = new CharReader(); 
	pReader->setString( strTest );
	
	CharParser *pParserLayerFirst = new CharParser(pReader);
	
	init_layer_first( pParserLayerFirst );
	
	
	while( ! pParserLayerFirst->Eof() )
	{
		QString strResult;
		int err;
		if( pParserLayerFirst->GetNextElement( strResult, err) )
		{
			std::cout << "[" << strResult.toStdString() << "]\n";
		}
		else
		{
			std::cout << "[err=" << (int)err << "]\n";
			break;
		};
	};
	std::cout << "\r\n-----------";
	std::cout << "\r\n";
	return 0;
};