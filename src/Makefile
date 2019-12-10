.POSIX:

include config.mk

PREFIX = /usr/local
MANPREFIX= ${PREFIX}/shar/man

SRCPATH=./src
OBJPATH=./obj
BINPATH=./bin

CFLAGS =  -pedantic -Wall -Os -DLOG_USE_COLOR
LDLIBS = -lX11 -lrt

CC = gcc

SRC = bar.c block.c main.c util.c sys.c includes/log/src/log.c
COM =\
	 blocks/battery.c\
	 blocks/arch_updates.c\
	 blocks/datetime.c\
	 blocks/wifi.c
OBJ = ${SRC:.c=.o} ${COM:.c=.o}

all: options dwmblocks 

options:
	@echo yadsbar build options:
	@echo "CFLAGS = ${CFLAGS}"
	@echo "LDLIBS = ${LDLIBS}"
	@echo "CC     = ${CC}"

.c.o:
	${CC} -o $@ -c ${CFLAGS} $<

${OBJ}: config.h blocks.h log.h util.h	

dwmblocks: ${OBJ}
	${CC} -o $@ ${OBJ} ${LDLIBS}

clean:
	rm -f dwmblocks ${OBJ}

#REQ = util

#${COM:=.o}: config.mk ${REQ:=.h}
#main.o: main.c sys.h component.h components.h config.h config.mk ${REQ:=.h}

#yadsbar: main.o ${COM:=.o} ${REQ:=.o}
#	${CC} -o $@ ${COM:=.o} ${REQ:=.o} main.o ${LDLIBS}

#clean:
#	rm -f yadsbar main.o ${REQ:=.o} ${COM:=.o} 
