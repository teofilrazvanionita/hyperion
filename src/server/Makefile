include ../../Makefile.inc 

LINUX_EXE = hyperiond

EXE = ${LINUX_EXE}

all : ${EXE}

${EXE}: main.o server.o mesaj.o client.o crypto.o
	${CPPC} main.o server.o mesaj.o client.o crypto.o -o ${EXE} ${LDLIBS}

main.o: main.cpp ${HYPERION_INCL_DIR}/server.h
	${CPPC} main.cpp ${CPPFLAGS} -c -o $@

server.o: server.cpp ${HYPERION_INCL_DIR}/server.h ${HYPERION_INCL_DIR}/mesaj.h ${HYPERION_INCL_DIR}/crypto.h
	${CPPC} server.cpp $(CPPFLAGS) -c -o $@

mesaj.o: mesaj.cpp ${HYPERION_INCL_DIR}/mesaj.h
	${CPPC} mesaj.cpp $(CPPFLAGS) -c -o $@

client.o: client.cpp ${HYPERION_INCL_DIR}/client.h ${HYPERION_INCL_DIR}/crypto.h 
	${CPPC} client.cpp $(CPPFLAGS) -c -o $@

crypto.o: crypto.cpp ${HYPERION_INCL_DIR}/crypto.h
	${CPPC} crypto.cpp $(CPPFLAGS) -c -o $@

allgen : ${GEN_EXE}

clean : 
	${RM} ${EXE} *.o *~

showall :
	@ echo ${EXE}

#${EXE} : ${LPLIB}		# True as a rough approximation
