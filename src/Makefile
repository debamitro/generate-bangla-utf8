
BINDIR=../bin

all: ${BINDIR}/generate-bangla

clean:
	$(RM) -fr $(BINDIR)/generate-bangla *.o

${BINDIR}/generate-bangla: main.o
	$(CXX) -m32 $^ -o $@

%.o: %.cpp
	$(CXX) -m32 -Wall -std=c++14 $^ -c
