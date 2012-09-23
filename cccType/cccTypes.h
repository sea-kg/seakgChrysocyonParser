//  cross compile code c++ 1.0

#ifndef _CCCTYPES_
#define _CCCTYPES_

// datatype

class cccContent;
class cccVar;
class cccChar : public cccVar;
class cccString : public cccVar;
class cccInt : public cccVar;
class cccFloat : public cccVar;
class cccEnum : public cccVar;
class cccError : public cccVar;

// streams
class cccStream;
class cccInput : public cccStream;
class cccOutput : public cccStream;
class cccErrorput : public cccStream;
class cccRead : public cccStream;
class cccWrite : public cccStream;


class cccWidget;
class cccWindow : public cccWidget;
class cccButton : public cccWidget;
class cccText : public cccWidget;
class cccTreeView : public cccWidget;

class cccTread;
class cccDatabase;
class cccSocket;

#endif
