
BINDIR=.

SRCDIR=../src/
PLAT_FLAGS=-m32

all: ${BINDIR}/test-bangla
	$(BINDIR)/test-bangla
clean:
	$(RM)  $(BINDIR)/test-bangla *.o

${BINDIR}/test-bangla: main.o ${SRCDIR}/BanglaUtf8.o
	$(CXX) -g $(PLAT_FLAGS) $^ -o $@

%.o: %.cpp
	$(CXX) -g -I ${SRCDIR} $(PLAT_FLAGS) -Wall -Wextra -std=c++14 $^ -c -o $@
