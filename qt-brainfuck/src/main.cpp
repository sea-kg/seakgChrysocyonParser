// #include "../seakgChrysocyonParser/qt.h"
#include "core-brainfuck.h"
#include <QFile>
#include <QTextStream>
#include <iostream>

using namespace std;

void help()
{
	std::cout << "\n\tusage: qt-brainfuck [options] [<code>|<file>]\n\n"
	" OPTIONS: \n"
	// " -i - info 'on' (for example: \"++++i\") \n"
	"\t-f     - from file\n"
	"\t--help - this help\n"
	"\n"
	"\tfor example 1:\n\t\t./qt-brainfuck \"++++++++++[>+++++++<-]>++.\"\n"
	"\tfor example 2:\n\t\t./qt-brainfuck -f hello_world.brainfuck\n"
	"\n";
};

int main(int argc, char* argv[])
{
	if( (argc == 1) || (argc > 1 && QString(argv[1]) == "--help") )
	{
		help();
		return 0; 
	};

	QString strCode = "";

	if(argc == 3 && QString(argv[1]) == "-f")
	{
		QString strFileName(argv[2]);
		QFile file(strFileName);
		if(!file.open(QIODevice::ReadOnly))
		{
			std::cout << "could not open file: '" << strFileName.toStdString().c_str() << "' \n";
			return 0; 	
		}

		QTextStream stream(&file);
		strCode = stream.readLine();
		while(!stream.atEnd()) 
			strCode += stream.readLine();

		file.close();
	}
	else if(argc == 2)
	{
		strCode = QString(argv[1]);
	}

	if(strCode.length() == 0)
	{
		cout << "no code\n";
	};

  brainfuck::core * pCore = new brainfuck::core();
	
	//std::cout << "test-code: \n" << strCode.toStdString().c_str() << "\n";	
	//std::cout << "length-code: \n" << strCode.length() << "\n";

	//return 0;
	
	for(int i = 0; i < strCode.length(); i++)
		pCore->add_command(strCode[i]);
	
	pCore->execute();

	std::cout << "\n";
	return 0;
}

