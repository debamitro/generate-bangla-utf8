

all: build

build:
	cd src; $(MAKE) all

clean:
	cd src; $(MAKE) clean

tests:
	cd test; $(MAKE) clean all
