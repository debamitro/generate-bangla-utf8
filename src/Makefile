
BINDIR=../bin
OBJECTS=main.o BanglaUtf8.o CommandLine.o
all: ${BINDIR}/generate-bangla

clean:
	$(RM) -fr $(BINDIR)/generate-bangla *.o

${BINDIR}/generate-bangla: ${OBJECTS}
	$(CXX) -m32 $^ -o $@

%.o: %.cpp
	$(CXX) -g -m32 -Wall -Wextra -std=c++14 $^ -c
