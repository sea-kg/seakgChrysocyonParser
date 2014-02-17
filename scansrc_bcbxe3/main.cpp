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
UnicodeString prefixforid = L"";
int i = 0;
int g_nInc = 0;

// ---------------------------------------

class seakgOutput {
  public:
    virtual void addline(UnicodeString str) = 0;
};

// ---------------------------------------

class seakgOutput_std : public seakgOutput {
  public:
    virtual void addline(UnicodeString str) {
      std::wcout << str.c_str() << "\n";
    };
};

class seakgOutput_list : public seakgOutput {
   TStringList *m_pList;
  public:
    seakgOutput_list(TStringList *list) : m_pList(list) {}
    virtual void addline(UnicodeString str) {
      m_pList->Add(str);
//      std::wcout << str.c_str() << "\n";
    };
};

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
  str = StringReplace(str, "\r\n", "\n", TReplaceFlags() << rfReplaceAll);
  str = StringReplace(str, "\r", "", TReplaceFlags() << rfReplaceAll);
  return str;
}

// ---------------------------------------

void PrintDoc(seakgOutput *pOutput, UnicodeString filename, UnicodeString name, UnicodeString uuid, UnicodeString code) {
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

  id = prefixforid + id;

  pOutput->addline("\t<doc>");
  pOutput->addline("\t\t<field name=\"id\">" + id + "</field>");
  pOutput->addline("\t\t<field name=\"project\">" + projectName + "</field>");
  pOutput->addline("\t\t<field name=\"name\">" + name + "</field>");
  pOutput->addline("\t\t<field name=\"uuid\">" + uuid.UpperCase() + "</field>");
  pOutput->addline("\t\t<field name=\"source_filepath\">" + filename + "</field>");
  pOutput->addline("\t\t<field name=\"full_source_code\">\n" + code + "\n\t\t</field>");
  pOutput->addline("\t</doc>");
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

void ScanAndPrint(seakgOutput *pOutput, UnicodeString fullname) {
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

        code += str + "\n";
      };

	  PrintDoc(pOutput, fullname, interfacename2, uuid, code);
//      std::wcout << str.c_str();
    };
  };



  /*std::wcout << "createuuidprojectname: " <<  << "\r\n";
  std::wcout << "projectname: " << projectName.c_str() << "\r\n";
  std::wcout << "fullname: " << fullname.c_str() << "\r\n";*/
};

// ---------------------------------------

void SearchAndScan(seakgOutput *pOutput, UnicodeString DirName/*, TDateTime &D, UnicodeString &S*/)
{
	TSearchRec sr;
	for(int r=FindFirst( DirName + "\\*.*", faDirectory,sr); !r; r=FindNext(sr))
	{
		if((sr.Name == ".")||(sr.Name==".."))
			continue;

		if(sr.FindData.dwFileAttributes&FILE_ATTRIBUTE_DIRECTORY) {
			SearchAndScan(pOutput, DirName + "\\" + sr.Name);
		} else {
		   // if(FileDateToDateTime(sr.Time) > D)
			if ( isSupportsExt(ExtractFileExt(sr.Name)) ) {
//					D = FileDateToDateTime(sr.Time);
					// S = DirName + "\\" + sr.Name;
          UnicodeString fullpath = DirName + L"\\" + sr.Name;
          ScanAndPrint(pOutput, fullpath);
					//std::wcout << fullpath.c_str() << "\r\n";
			}
		}
	}
	FindClose(sr);
}

// ---------------------------------------

int _tmain(int argc, _TCHAR* argv[])
{
  seakgOutput *pOutput = 0;
  TStringList *list = new TStringList();
  if (argc == 5) {
    pOutput = new seakgOutput_list(list);    
  } else if (argc == 4) {
    pOutput = new seakgOutput_std();    
  } else {
    std::wcout << "usage: input_folder project_name prefix_id output_file\n";
    std::wcout << "or usage: input_folder project_name prefix_id\n";
    return -1;
  }

//  
//  output->Add("<add>");
  pOutput->addline("<add>");
  rootPath = UnicodeString(argv[1]); // L"C:\\Projects\\ACTApro.git";
  projectName = UnicodeString(argv[2]); // L"ACTApro 2.0 (rev. )";
  prefixforid = UnicodeString(argv[3]);
  g_nInc = 0;
  SearchAndScan(pOutput, rootPath);
  // output->Add("</add>");
  pOutput->addline("</add>");

  if (argc == 5) {
    UnicodeString outputFile = UnicodeString(argv[4]);
    list->SaveToFile(outputFile);    
  }

  return 0;
}

