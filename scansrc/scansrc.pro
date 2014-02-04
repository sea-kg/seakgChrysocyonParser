TEMPLATE = app
SOURCES += src/main.cpp \
  src/task.cpp 

HEADERS += src/main.h \
  src/task.h \
  src/Reader_ScanDir.h

QT += core \
 xml \
 script \
 gui \
 xmlpatterns
