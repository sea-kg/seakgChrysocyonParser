//---------------------------------------------------------------------------

#include <vcl.h>
#include <iostream.h>
#pragma hdrstop


#include <tchar.h>
#include "../seakgChrysocyonParser/bcb_xe.h"

typedef seakgReaderFromUnicodeString<wchar_t> CharReader;

//---------------------------------------------------------------------------

#pragma argsused
int _tmain(int argc, _TCHAR* argv[])
{
  UnicodeString str;

  UnicodeString strTest = "func add123( int a = 123, int b = 989, string str = \" \\\"dfsdf\\\\ \" ) { "
 	  "  cout a+b; \r\n"
  	" } ";

	CharReader *pReader = new CharReader();
	pReader->setString( strTest );

  wchar_t ch;

  while( !pReader->Eof() )
  {
    int errCode;
    pReader->GetNextElement(ch, errCode);
    wcout << ch;
  };

  return 0;
}
//---------------------------------------------------------------------------
