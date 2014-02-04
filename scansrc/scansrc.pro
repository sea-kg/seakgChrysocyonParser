TEMPLATE = app
SOURCES += src/main.cpp \
  src/task.cpp \
  seakgXMLInterface/seakgXMLInterface.cpp

HEADERS += src/main.h \
  src/task.h \
  src/Reader_ScanDir.h \
  seakgXMLInterface/seakgXMLInterface.h

QT += core \
 xml \
 script \
 gui \
 xmlpatterns
