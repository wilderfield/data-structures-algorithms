####################################
HELLOWORLD_C:
	cd HELLOWORLD/C && $(MAKE)

HELLOWORLD_CPP:
	cd HELLOWORLD/CPP && $(MAKE)

HELLOWORLD_PYTHON:
	cd HELLOWORLD/PYTHON && $(MAKE)
####################################
ARRAY_C:
	cd ARRAY/C && $(MAKE)

ARRAY_CPP:
	cd ARRAY/CPP && $(MAKE)

ARRAY_PYTHON:
	cd ARRAY/PYTHON && $(MAKE)
####################################
####################################
LINKEDLIST_C:
	cd LINKEDLIST/C && $(MAKE)

LINKEDLIST_CPP:
	cd LINKEDLIST/CPP && $(MAKE)

LINKEDLIST_PYTHON:
	cd LINKEDLIST/PYTHON && $(MAKE)
####################################
clean:
	cd HELLOWORLD/C && $(MAKE) clean
	cd HELLOWORLD/CPP && $(MAKE) clean
	cd HELLOWORLD/PYTHON && $(MAKE) clean
	cd ARRAY/C && $(MAKE) clean
	cd ARRAY/CPP && $(MAKE) clean
	cd ARRAY/PYTHON && $(MAKE) clean
	cd LINKEDLIST/C && $(MAKE) clean
	cd LINKEDLIST/CPP && $(MAKE) clean
	cd LINKEDLIST/PYTHON && $(MAKE) clean
