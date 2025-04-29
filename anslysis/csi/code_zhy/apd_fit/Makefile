ROOTINC = $(shell root-config --cflags)
ROOTLIB = $(shell root-config --libs)

	
BIN     = .
CC      =  g++
CCFLAG   = -O -Wall -fPIC




PID:	root_fit.c
## pid:	fit_csi_multithread.cpp
###
		$(CC) $(CCFLAG) $(ROOTINC) $(CCENV) -lm $< -o $(BIN)/$@ $(ROOTLIB)
		
