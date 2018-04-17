
BINDIR=../bin
OBJECTS=main.o BanglaUtf8.o CommandLine.o
PLAT_FLAGS=-m32
all: ${BINDIR}/generate-bangla

clean:
	$(RM) -fr $(BINDIR)/generate-bangla *.o

${BINDIR}/generate-bangla: ${OBJECTS}
	$(CXX) $(PLAT_FLAGS) $^ -o $@

%.o: %.cpp
	$(CXX) -g $(PLAT_FLAGS) -Wall -Wextra -std=c++14 $^ -c
