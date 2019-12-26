.POSIX:

include config.mk

PREFIX = /usr/local
MANPREFIX= ${PREFIX}/shar/man

SRCPATH=./src
OBJPATH=./obj
BINPATH=./bin

CFLAGS =  -pedantic -Wall -Os -DLOG_USE_COLOR
LDLIBS = -lX11 -lrt -lasound -lm

CC = gcc

SRC = bar.c block.c main.c util.c sys.c includes/log/src/log.c
COM =\
	 blocks/battery.c\
	 blocks/arch_updates.c\
	 blocks/datetime.c\
	 blocks/wifi.c\
	 blocks/volume.c\
	 blocks/cpu.c\
	 blocks/ram.c\
	 blocks/netspeeds.c
OBJ = ${SRC:.c=.o} ${COM:.c=.o}

all: options dwmblocks 

options:
	@echo dwmblocks build options:
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

install: all
	mkdir -p ${DESTDIR}${PREFIX}/bin
	cp -f dwmblocks ${DESTDIR}${PREFIX}/bin
	chmod 755 ${DESTDIR}${PREFIX}/bin/dwmblocks
	cp -f dwmblocks_sig_volume ${DESTDIR}${PREFIX}/bin
	chmod 775 ${DESTDIR}${PREFIX}/bin/dwmblocks_sig_volume

uninstall:
	rm -f ${DESTDIR}${PREFIX}/bin/dwmblocks\
		${DESTDIR}${PREFIX}/bin/dwmblocks_sig_volume

#REQ = util

#${COM:=.o}: config.mk ${REQ:=.h}
#main.o: main.c sys.h component.h components.h config.h config.mk ${REQ:=.h}

#yadsbar: main.o ${COM:=.o} ${REQ:=.o}
#	${CC} -o $@ ${COM:=.o} ${REQ:=.o} main.o ${LDLIBS}

#clean:
#	rm -f yadsbar main.o ${REQ:=.o} ${COM:=.o} 
