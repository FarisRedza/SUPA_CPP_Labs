CC=g++
FLAGS=-std=c++20 -w
TARGET=AnalyseData
OBJECTS=AnalyseData.o CustomFunctions.o

${TARGET}:${OBJECTS}
	@echo "Linking..."
	${CC} ${FLAGS} ${OBJECTS} -o ${TARGET}
	@make clean

CustomFunctions.o: CustomFunctions.cxx CustomFunctions.h
	${CC} ${FLAGS} -c CustomFunctions.cxx

AnalyseData.o: AnalyseData.cxx CustomFunctions.h
	${CC} ${FLAGS} -c AnalyseData.cxx

clean:
	@rm -f *.o *~

cleantarget:
	@rm -f ${TARGET}

run: ${TARGET}
	./${TARGET}

.PHONY: run clean cleantarget