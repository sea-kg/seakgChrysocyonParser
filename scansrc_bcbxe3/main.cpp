#include <vcl.h>
#include <windows.h>
#include <iostream.h>
#include <ActiveX.hpp>
#include <ComObj.hpp>
#include <Sysutils.hpp>

#pragma hdrstop
#pragma argsused

#include <tchar.h>
#include <stdio.h>

UnicodeString rootPath = L"";
UnicodeString projectName = L"";

// ---------------------------------------

bool isSupportsExt(UnicodeString ext) {
	ext = ext.UpperCase();
	return ext == ".H" || ext == ".CPP" || ext == ".CC";
}

// ---------------------------------------

void PrintDoc(UnicodeString filename, UnicodeString name, UnicodeString uuid, UnicodeString code) {
  filename = filename.SubString(rootPath.Length()+1, filename.Length() - rootPath.Length());
  UnicodeString id = "";
//  UnicodeString id = "";
 
  code = StringReplace(code, "&", "&amp;", TReplaceFlags() << rfReplaceAll);
  code = StringReplace(code, "<", "&lt;", TReplaceFlags() << rfReplaceAll);
  code = StringReplace(code, ">", "&gt;", TReplaceFlags() << rfReplaceAll);

  TGUID g;
  OleCheck(CoCreateGuid(&g));
  Sysutils::GUIDToString(g);

  std::wcout << "\t<doc>\r\n";  
  std::wcout << "\t\t<field name=\"id\">" << Sysutils::GUIDToString(g).c_str() << "</field>\r\n";  
  std::wcout << "\t\t<field name=\"project\">" << projectName.c_str() << "</field>\r\n";  
  std::wcout << "\t\t<field name=\"name\">" << name.c_str() << "</field>\r\n";  
  std::wcout << "\t\t<field name=\"uuid\">" << uuid.UpperCase().c_str() << "</field>\r\n";  
  std::wcout << "\t\t<field name=\"source_filepath\">" << filename.c_str() << "</field>\r\n";
  std::wcout << "\t\t<field name=\"full_source_code\">\r\n" << code.c_str() << "\r\n\t\t</field>\r\n";
  std::wcout << "\t</doc>\r\n";
};

// ---------------------------------------

void ScanAndPrint(UnicodeString fullname) {
  TStringList *list = new TStringList();  
  list->LoadFromFile(fullname);
  int nCount = list->Count;
  for (int i = 0; i < nCount; i++)
  {
    UnicodeString str = list->Strings[i];
	  if (str.Pos(L"class") > 0 && str.Pos("__declspec") > 0) {
      UnicodeString code = str + "\r\n";
      str = str.Trim();
      UnicodeString uuid = str.SubString(str.Pos("\"") + 1, 36);
      UnicodeString interfacename = str.SubString(str.Pos("I"), str.Length() - str.Pos("I") + 1);
      bool bStop = false;
      int nIncr = 0;
      while (bStop == false && i < nCount) {
        i++;
        str = list->Strings[i];
        if (str.Pos("{") > 0) {
          nIncr++;
        };

        if (str.Pos("}") > 0) {
          nIncr--;
          if(nIncr == 0) bStop = true;
        };

        code += str + "\r\n";
      };

      PrintDoc(fullname, interfacename, uuid, code);
//      std::wcout << str.c_str();
    };
  };



  /*std::wcout << "createuuidprojectname: " <<  << "\r\n";
  std::wcout << "projectname: " << projectName.c_str() << "\r\n";
  std::wcout << "fullname: " << fullname.c_str() << "\r\n";*/
};

// ---------------------------------------

void SearchAndScan(UnicodeString DirName/*, TDateTime &D, UnicodeString &S*/)
{
	TSearchRec sr;
	for(int r=FindFirst( DirName + "\\*.*", faDirectory,sr); !r; r=FindNext(sr))
	{
		if((sr.Name == ".")||(sr.Name==".."))
			continue;

		if(sr.FindData.dwFileAttributes&FILE_ATTRIBUTE_DIRECTORY) {
			SearchAndScan(DirName + "\\" + sr.Name);
		} else {
		   // if(FileDateToDateTime(sr.Time) > D)
			if ( isSupportsExt(ExtractFileExt(sr.Name)) ) {
//					D = FileDateToDateTime(sr.Time);
					// S = DirName + "\\" + sr.Name;
          UnicodeString fullpath = DirName + L"\\" + sr.Name;
          ScanAndPrint(fullpath);
					//std::wcout << fullpath.c_str() << "\r\n";
			}
		}
	}
	FindClose(sr);
}

int _tmain(int argc, _TCHAR* argv[])
{
  if (argc != 3)
  {
    std::wcout << "usage: input_folder project_name";
    return -1;
  }

  std::wcout << "<add>\r\n";
  rootPath = UnicodeString(argv[1]); // L"C:\\Projects\\ACTApro.git";
  projectName = UnicodeString(argv[2]); // L"ACTApro 2.0 (rev. )";
  SearchAndScan(rootPath);
  std::wcout << "</add>\r\n";
  return 0;
}

