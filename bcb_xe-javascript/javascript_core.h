//---------------------------------------------------------------------------

#ifndef javascript_coreH
#define javascript_coreH
//---------------------------------------------------------------------------
#include <vector.h>
#include <vcl.h>
#include <conio.h>

namespace javascript
{
  class core
  {
    public:
      core();
      void next_line();
      bool addFunction(UnicodeString name);
      vector<UnicodeString> &getFunctions();

      bool Debug;
    private:
      vector<int> m_vSlots;
      unsigned int m_nPos;
      unsigned int m_nLine;
      vector<UnicodeString> m_vFunctions;
  };
}; // namespace javascript

#endif
