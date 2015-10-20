include ../../Makefile.inc 

LINUX_EXE = hyperion

EXE = ${LINUX_EXE}

all : ${EXE}

${EXE}: main.o client.o server.o crypto.o
	${CPPC} main.o client.o server.o crypto.o /usr/lib64/randombytes.o -o ${EXE} ${LDLIBS}

main.o: main.cpp ${HYPERION_INCL_DIR}/client/client.h
	${CPPC} main.cpp ${CPPFLAGS} -I${HYPERION_INCL_DIR}/client -c -o $@

server.o: server.cpp ${HYPERION_INCL_DIR}/client/server.h ${HYPERION_INCL_DIR}/client/crypto.h
	${CPPC} server.cpp $(CPPFLAGS) -I${HYPERION_INCL_DIR}/client -c -o $@

client.o: client.cpp ${HYPERION_INCL_DIR}/client/client.h ${HYPERION_INCL_DIR}/client/crypto.h ${HYPERION_INCL_DIR}/client/server.h
	${CPPC} client.cpp $(CPPFLAGS) -I${HYPERION_INCL_DIR}/client -c -o $@

crypto.o: crypto.cpp ${HYPERION_INCL_DIR}/client/crypto.h
	${CPPC} crypto.cpp $(CPPFLAGS) -I${HYPERION_INCL_DIR}/client  -c -o $@

allgen : ${GEN_EXE}

clean : 
	${RM} ${EXE} *.o *~

showall :
	@ echo ${EXE}

#${EXE} : ${LPLIB}		# True as a rough approximation
