
BINDIR=.

SRCDIR=../src/

all: ${BINDIR}/test-bangla

clean:
	$(RM)  $(BINDIR)/test-bangla *.o

${BINDIR}/test-bangla: main.o ${SRCDIR}/BanglaUtf8.o
	$(CXX) -m32 $^ -o $@

%.o: %.cpp
	$(CXX) -g -I ${SRCDIR} -m32 -Wall -Wextra -std=c++14 $^ -c -o $@
