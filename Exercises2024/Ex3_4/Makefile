CC=g++ #Name of compiler
FLAGS=-std=c++20 -w #Compiler flags (the s makes it silent)
TARGET=Test #Executable name
OBJECTS=Test.o FiniteFunctions.o CustomFunctions.o
LIBS=-I ../../GNUplot/ -lboost_iostreams

#First target in Makefile is default
${TARGET}:${OBJECTS} #Make target from objects
	@echo "Linking..."
	${CC} ${FLAGS} ${OBJECTS} ${LIBS} -o ${TARGET}
	@make clean

Test.o : Test.cxx FiniteFunctions.h
	${CC} ${FLAGS} ${LIBS} -c Test.cxx

FiniteFunctions.o : FiniteFunctions.cxx FiniteFunctions.h
	${CC} ${FLAGS} ${LIBS} -c FiniteFunctions.cxx

clean: #No targets just run shell command to rm object files and emacs backups
	@rm -fv *.o *~

cleantarget: #Delete the exectuable
	@rm -fv ${TARGET}

CustomFunctions.o: ../Ex1_2/CustomFunctions.cxx ../Ex1_2/CustomFunctions.h
	${CC} ${FLAGS} -c ../Ex1_2/CustomFunctions.cxx

run: ${TARGET}
	./${TARGET}
