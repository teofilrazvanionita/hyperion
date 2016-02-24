include ../../Makefile.inc 

LINUX_EXE = hyperiond

EXE = ${LINUX_EXE}

ARCH := $(shell uname -m)
	
ifeq ($(ARCH), x86_64) 
    LIBDIRSUFFIX = 64
else 
    LIBDIRSUFFIX =
endif

all : ${EXE}

${EXE}: main.o server.o mesaj.o client.o crypto.o
	${CPPC} main.o server.o mesaj.o client.o crypto.o /usr/lib${LIBDIRSUFFIX}/randombytes.o -o ${EXE} ${LDLIBS}

main.o: main.cpp ${HYPERION_INCL_DIR}/server/server.h
	${CPPC} main.cpp ${CPPFLAGS} -I${HYPERION_INCL_DIR}/server -c -o $@

server.o: server.cpp ${HYPERION_INCL_DIR}/server/server.h ${HYPERION_INCL_DIR}/server/mesaj.h ${HYPERION_INCL_DIR}/server/crypto.h ${HYPERION_INCL_DIR}/server/client.h
	${CPPC} server.cpp $(CPPFLAGS) -I${HYPERION_INCL_DIR}/server -c -o $@

mesaj.o: mesaj.cpp ${HYPERION_INCL_DIR}/server/mesaj.h
	${CPPC} mesaj.cpp $(CPPFLAGS) -I${HYPERION_INCL_DIR}/server -c -o $@

client.o: client.cpp ${HYPERION_INCL_DIR}/server/client.h ${HYPERION_INCL_DIR}/server/crypto.h 
	${CPPC} client.cpp $(CPPFLAGS) -I${HYPERION_INCL_DIR}/server -c -o $@

crypto.o: crypto.cpp ${HYPERION_INCL_DIR}/server/crypto.h
	${CPPC} crypto.cpp $(CPPFLAGS) -I${HYPERION_INCL_DIR}/server  -c -o $@

allgen : ${GEN_EXE}

clean : 
	${RM} ${EXE} *.o *~

showall :
	@ echo ${EXE}

#${EXE} : ${LPLIB}		# True as a rough approximation
