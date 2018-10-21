include ../../Makefile.inc 

LINUX_EXE = hyperion

EXE = ${LINUX_EXE}

ARCH := $(shell uname -m)
	
ifeq ($(ARCH), x86_64) 
    LIBDIRSUFFIX = 64
else 
    LIBDIRSUFFIX =
endif

objects = main.o client.o server.o crypto.o

all : ${EXE}

${EXE}: $(objects)
	${CPPC} $(objects) /usr/lib${LIBDIRSUFFIX}/randombytes.o -o ${EXE} ${LDLIBS}

main.o: main.cpp ${HYPERION_INCL_DIR}/client/client.h
	${CPPC} main.cpp ${CPPFLAGS} -I${HYPERION_INCL_DIR}/client -c -o $@

server.o: server.cpp ${HYPERION_INCL_DIR}/client/server.h ${HYPERION_INCL_DIR}/client/crypto.h
	${CPPC} server.cpp $(CPPFLAGS) -I${HYPERION_INCL_DIR}/client -c -o $@

client.o: client.cpp ${HYPERION_INCL_DIR}/client/client.h ${HYPERION_INCL_DIR}/client/crypto.h ${HYPERION_INCL_DIR}/client/server.h
	${CPPC} client.cpp $(CPPFLAGS) -I${HYPERION_INCL_DIR}/client -c -o $@

crypto.o: crypto.cpp ${HYPERION_INCL_DIR}/client/crypto.h
	${CPPC} crypto.cpp $(CPPFLAGS) -I${HYPERION_INCL_DIR}/client  -c -o $@

.PHONY : clean
clean : 
	-${RM} ${EXE} $(objects) *~

showall :
	@ echo ${EXE}


