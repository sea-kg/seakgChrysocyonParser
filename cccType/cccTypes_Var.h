//  cross compile code c++ 1.0

#ifndef _CCCTYPES_VAR_
#define _CCCTYPES_VAR_

#include "cccTypes.h"
#include "cccTypes_Content.h"

class cccVar
{
  public:
    cccVar(cccContent var) { m_Content = var.getContent(); };
	cccVar(cccVar var) { m_Content = var.getContent(); };
	cccVar(cccChar var) { m_Content = var.getContent(); };
	cccVar(cccString var) { m_Content = var.getContent(); };
    cccVar(cccInt var) { m_Content = var.getContent(); };
    cccVar(cccFloat var) { m_Content = var.getContent(); };
    cccVar(cccEnum var) { m_Content = var.getContent(); };
    cccError(cccError var) { m_Content = var.getContent(); };
	
	virtual cccContent &getContent();
	
	cccContaner m_Content;
};

// class cccVector;
// class ccc



class cccInt : public cccVar
{
};


class cccString : public cccType
{
 public:
  cccString();
  ~cccString();
  int getLength();
   
}

#endif // _CCCTYPES_VAR_