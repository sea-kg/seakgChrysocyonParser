//---------------------------------------------------------------------------


#pragma hdrstop

#include "javascript_core.h"


namespace javascript
{
  core::core()
  {
    m_nLine = 0;
/*  m_nPos = 0;
    m_vSlots.clear();
    int n = 0;
    m_vSlots.push_back(n);
    Debug = false;*/
  };


  void core::next_line()
  {
    m_nLine++;
  };

  bool core::addFunction(UnicodeString name)
  {
    m_vFunctions.push_back(name);
  };

  vector<UnicodeString> &core::getFunctions()
  {
    return m_vFunctions;
  };
  //---------------------------------------------------------------------------

}; // namespace javascript

#pragma package(smart_init)
