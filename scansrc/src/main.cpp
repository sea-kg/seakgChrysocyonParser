#include <iostream>
#include "../seakgChrysocyonParser/seakgChrysocyonParser.h"
#include <QString>
#include <QDir>
#include <QDirIterator>

#include "Reader_ScanDir.h"

int main(int argc, char *argv[]) {

	if(argc != 4) {
		std::cout << argv[0] << " <folder_with_sources> <project_name> <folder_for_output_xml> \n\n";
		return -1;
	};

	QString strDir = QString(argv[1]);
	seakgChryReader_ScanDir<QString> *reader = new seakgChryReader_ScanDir<QString>();
	reader->setDir(strDir);
	int nCount = 0;
	while(!reader->Eof())
	{
		QString str;
		int nOutErrorCode = 0;
		if( reader->GetNextElement(str, nOutErrorCode) ) {
			nCount++;
			// std::cout << "File: " << str.toStdString() << "\n";
		}
	}
	std::cout << "nCount: " << nCount << "\n";
	std::cout << "reader->getCountDirs(): " << reader->getCountDirs() << "\n";
	std::cout << "reader->getCountFiles(): " << reader->getCountFiles() << "\n";
	std::cout << "reader->getCountAll(): " << reader->getCountAll() << "\n";

	return 0;
};


