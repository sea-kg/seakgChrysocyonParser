
#define CCC_USE_QT
#include "cccContent.h"
#include "cccString.h"
#include "cccInteger.h"


// #include "../ccc/cccString.h"
// #include "../ccc/cccString.h"
// #include "../ccc/cccStream.h"

#include <iostream>
using namespace std;

int main()
{
  QString str = "hello";
	cccContent content;
  content.setFullContent("string", "simple", str.length(), str);
	
	cout << content.getFullContent().toStdString() << "\n";

	cccContent content2;

  content2.setFullContent("[string:simple:5:hello]");
	cccVar var(content2);
	
	cout << var.getValue().getFullContent().toStdString() << "\n";
	
	{
		cccString c_str("hello world!");
		cout << c_str.getValue().getFullContent().toStdString() << "\n";
  }
	
	{
		cccInteger c_int(67876);
		cout << c_int.getValue().getFullContent().toStdString() << "\n";
	};


  {
	  cccString c_str("hello world!");
    cccInteger c_int(67876);

		cccVar c_var = c_str + c_int;
		cout << c_var.getValue().getFullContent().toStdString() << "\n";
  }


	return 0;
}
