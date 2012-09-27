
#define CCC_USE_QT
#include "cccContent.h"

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
	
	cout << content2.getFullContent().toStdString() << "\n";

	return 0;
}
