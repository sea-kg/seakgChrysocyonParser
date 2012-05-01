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
//typedef seakgPuppyString<QChar,QString> PuppyString;
//typedef seakgPuppyLine<QChar,QString> PuppyLine;

int main()
{
	QChar ch;
	
	/*QString str = "123f 234 5677      12345 abbc hello people! 453";*/
	
	QString strTest = "func add123( int a = 123, int b = 989 ) { "
	"  cout a+b; "
	" } ";
	
	std::cout << "-----------\r\n";
	std::cout << "[" << strTest.toStdString() << "]:" << strTest.length() << "\r\n";
	std::cout << "-----------\r\n";
	
	CharReader *pReader = new CharReader(); 
	pReader->setString( strTest );
	
	CharParser *pParser = new CharParser(pReader);
	
	pParser->AddPuppy( new PuppyNumber() );
	pParser->AddPuppy( new PuppyName() );
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
	
	while( ! pParser->Eof() )
	{
		QString strResult;
		int err;
		if( pParser->GetNextElement( strResult, err) )
		{
			std::cout << "[" << strResult.toStdString() << "]\n";
		}
		else
		{
			std::cout << "[err=" << (int)err << "]\n";
		};
	};
	std::cout << "\r\n-----------";
	std::cout << "\r\n";
	
	/*
	while( !reader->Eof() )
	{
		QChar ch;
		int err;
		if( reader->GetNextElement( ch, err) )
		{
			std::cout << ch.toAscii();
		}
		else
		{
			std::cout << "[err]"; 
		};
	};
	std::cout << "\r\n-----------";
	std::cout << "\r\n";
	*/
	
	
	
	/*
	seakgExampleReader<char> reader; 
	
	std::string str = "Hallo vasy! \"Me\\\"ine\" Telefonnummer ist 676767."; 
	
	reader.setString(str);
	
	seakgChrysocyon::seakgChrysocyonContainer<char> *container;

	container = new seakgChrysocyon::seakgChrysocyonContainer<char>();

	//char ch = 0x33;
	//container->Push(ch);

	//seakgChrysocyon::seakgChrysocyonParser<char> parser();//();
	//parser = new seakgChrysocyon::seakgChrysocyonParser<char>();



	//parser->AddPuppy()

	std::cout << "\n";
	int sch = 0;
	while(!reader.Eof())
	{
		char ch = reader.GetNextElement();
		container->Push(ch);
		std::cout << ch;
		sch++;
	}
	std::cout << "\n\n";

	seakgChrysocyon::seakgChrysocyonContainer<char> *container2;
	container2 = new seakgChrysocyon::seakgChrysocyonContainer<char>();
	
	 
	container->PushAllTo(container2);
	
	
	std::cout << "container : ";
	for(int i=0; i<sch; i++)
	{
		char ch1 = container->Pop();
		std::cout << ch1;
	}

	std::cout << "\n\n";
	
	std::cout << "container2 : ";
	for(int i=0; i<sch; i++)
	{
		char ch1 = container2->Pop();
		std::cout << ch1;
	}

	std::cout << "\n\n";
	*/
	return 0;
};