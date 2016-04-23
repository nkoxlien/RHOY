include Build/Common/CommonDefs.mak

BIN_DIR = Bin

INC_DIRS = \
	Include = /usr/include/ni \
	./

SRC_FILES = ./*.cpp

USED_LIBS += OpenNI

EXE_NAME = HandDisplay

LIB_DIRS += lib
include Build/Common/CommonCppMakefile   
