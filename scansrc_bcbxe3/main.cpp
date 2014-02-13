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
int i = 0;
int g_nInc = 0;
// ---------------------------------------

bool isSupportsExt(UnicodeString ext) {
	ext = ext.UpperCase();
	return ext == ".H" || ext == ".CPP" || ext == ".CC";
}

// ---------------------------------------

UnicodeString encoding_html(UnicodeString str)
{
  str = StringReplace(str, "&", "&amp;", TReplaceFlags() << rfReplaceAll);
  str = StringReplace(str, "<", "&lt;", TReplaceFlags() << rfReplaceAll);
  str = StringReplace(str, ">", "&gt;", TReplaceFlags() << rfReplaceAll);
  return str;
}

// ---------------------------------------

void PrintDoc(UnicodeString filename, UnicodeString name, UnicodeString uuid, UnicodeString code) {
  filename = filename.SubString(rootPath.Length()+1, filename.Length() - rootPath.Length());
  UnicodeString id = "";
//  UnicodeString id = "";

  code = encoding_html(code);
  name = encoding_html(name);

  TGUID g;
  OleCheck(CoCreateGuid(&g));
  //Sysutils::GUIDToString(g);
  //id = Sysutils::GUIDToString(g);
  //id = id.SubString(2,37) + "[" + IntToStr(g_nInc++) + "]";

  id = IntToStr(g_nInc++);
  while (id.Length() < 6)
    id = "0" + id;

  std::wcout << "\t<doc>\r\n";
  std::wcout << "\t\t<field name=\"id\">" << id.c_str() << "</field>\r\n";
  std::wcout << "\t\t<field name=\"project\">" << projectName.c_str() << "</field>\r\n";
  std::wcout << "\t\t<field name=\"name\">" << name.c_str() << "</field>\r\n";
  std::wcout << "\t\t<field name=\"uuid\">" << uuid.UpperCase().c_str() << "</field>\r\n";
  std::wcout << "\t\t<field name=\"source_filepath\">" << filename.c_str() << "</field>\r\n";
  std::wcout << "\t\t<field name=\"full_source_code\">\r\n" << code.c_str() << "\r\n\t\t</field>\r\n";
  std::wcout << "\t</doc>\r\n";
};

// ---------------------------------------

UnicodeString getName(UnicodeString str) {
 UnicodeString name = str;

 if (name.Pos(":") > 0)
   name = name.SubString(1, name.Pos(":")-1);
 UnicodeString alphabet = L"QWERTYUIOPASDFGHJKLZXCVBNMqwertyuiopasdfghjklzxcvbnm1234567890_";

 while (true) {
   if (name.Length() == 0)
     break;
   UnicodeString ch = name.SubString(name.Length(), 1);
   if (alphabet.Pos(ch) > 0 && name.Length() > 0)
     break;
   name = name.SubString(1, name.Length()-1);
 }

 UnicodeString temp_name;
 while (true) {
   if (name.Length() == 0)
     break;
   UnicodeString ch = name.SubString(name.Length(), 1);
   if (alphabet.Pos(ch) > 0 && name.Length() > 0)
     temp_name = ch + temp_name;
   else
     break;
   name = name.SubString(1, name.Length()-1);
 }

 return temp_name;
}

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

      UnicodeString uuid = "none";
      if (str.Pos("\"") > 0)
        uuid = str.SubString(str.Pos("\"") + 1, 36);

      UnicodeString interfacename = str.SubString(str.Pos("I"), str.Length() - str.Pos("I") + 1);
      UnicodeString interfacename2 = getName(str);
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

	  PrintDoc(fullname, interfacename2, uuid, code);
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
  g_nInc = 0;
  SearchAndScan(rootPath);
  std::wcout << "</add>\r\n";
  return 0;
}

