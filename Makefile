CPP             = g++
RM              = rm -f
CPP_FLAGS       = -Wall -c -I. -I./deps/include/ -O2 -std=c++11

LIBRARY_DIR		= /usr/local/php/lib/php/extensions/debug-non-zts-20170718/

PHP_CONFIG_DIR	= /usr/local/php/etc/conf.d

LD              = g++
#LD_FLAGS        = -Wall -Wl,-rpath=./deps/lib -shared -O2  -L/usr/local/lib
LD_FLAGS        = -Wall -shared -O2 
RESULT          = plog.so

PHPINIFILE		= plog.ini

SOURCES			= $(wildcard *.cpp)
OBJECTS         = $(SOURCES:%.cpp=%.o)

all:	${OBJECTS} ${RESULT}

${RESULT}: ${OBJECTS}
		${LD} ${LD_FLAGS} -o $@ ${OBJECTS} -lphpcpp -lglog

${OBJECTS}: 
		${CPP} ${CPP_FLAGS} -fpic -o $@ ${@:%.o=%.cpp}

clean:
		${RM} *.obj *~* ${OBJECTS} ${RESULT}

install:
		cp -f ${RESULT} ${LIBRARY_DIR}
		cp -f ${PHPINIFILE}	${PHP_CONFIG_DIR}
