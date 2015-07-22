M2S_ROOT=$(HOME)/Documents/hpca2015/nyanRepo

all: main

main: main.cc
	g++ -m32 main.cc -o main -I$(M2S_ROOT)/runtime/include/ \
		-L$(M2S_ROOT)/lib/.libs -lm2s-opencl
