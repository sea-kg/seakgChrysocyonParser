#ifndef __SEAKG_CRYOSOCYON_READER_SCANDIR_H__
#define __SEAKG_CRYOSOCYON_READER_SCANDIR_H__

#include "../../seakgChrysocyonParser/seakgChrysocyonParser.h"
#include <QString>
#include <QStack>

template<typename T> class seakgChryReader_ScanDir;

template<>
class seakgChryReader_ScanDir<QString> : public seakgChrysocyon::InterfaceChrysocyonReader<QString>
{
	public:
		seakgChryReader_ScanDir() { 
			/*m_stackDirs = new QVector<QString>();
			m_stackFiles = new QVector<QString>();*/
		};
		void setDir(const QString &strDir)
		{ 
			QDir dir = QDir(strDir);
			m_nCountFiles = 0;
			m_nCountDirs = 0;
			m_stackDirs.clear();
			m_stackFiles.clear();
			m_stackDirs.push_back(dir.absolutePath());
			scanDir();
		};

		// InterfaceChrysocyonReader
		virtual bool Eof() { 
			if(m_stackDirs.size() > 0 && m_stackFiles.size() == 0)
				scanDir();
			return m_stackFiles.size() == 0; 
		};
		
		virtual bool GetNextElement( QString &path, int &nOutErrorCode )
		{
			nOutErrorCode = 0;
			if(!this->Eof())
			{
				path = QString(m_stackFiles.last());
				m_stackFiles.pop_back();
				if(m_stackFiles.size() == 0) scanDir();
				return true;
			}

			nOutErrorCode = seakgChrysocyon::chsErrEof;
			return false;
		};
		
		int getCountFiles() { return m_nCountFiles; };
		int getCountDirs() { return m_nCountDirs; };
		int getCountAll() { return m_nCountDirs + m_nCountFiles; };
		
	private:
		QVector<QString> m_stackDirs;
		QVector<QString> m_stackFiles;
		int m_nCountFiles;
		int m_nCountDirs;
		
		void scanDir() {

			while(m_stackDirs.size() > 0 && m_stackFiles.size() == 0)
			{
				QDir dir(m_stackDirs.last());
				m_stackDirs.pop_back();
				
				// std::cout << "next dir: " << dir.absolutePath().toStdString() << "\n";
				QStringList listDirs = dir.entryList(QDir::AllDirs | QDir::NoSymLinks);
				for(int i = 0; i < listDirs.size(); i++)
				{
					QString dirname = listDirs.at(i);
					QString dirfullname = dir.absolutePath() + "/" + dirname;
					if(dirname != "." && dirname != "..")
					{
						m_stackDirs.push_back(dirfullname);
						m_nCountDirs++;
						// std::cout << "dirfullname: " << dirfullname.toStdString() << "\n";						
					}
				}
	
				QStringList listFiles = dir.entryList(QDir::Files | QDir::NoSymLinks);
				for(int i = 0; i < listFiles.size(); i++)
				{
					QString filename = listFiles.at(i);
					QString filefullname = dir.absolutePath() + "/" + filename;
					m_stackFiles.push_back(filefullname);
					m_nCountFiles++;
					// std::cout << "filefullname: " << filefullname.toStdString() << "\n";
				}
			}
		}
};

#endif // __SEAKG_CRYOSOCYON_READER_SCANDIR_H__
