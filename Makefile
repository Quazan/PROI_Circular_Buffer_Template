C=gcc
CXX=g++
RM=rm -f
CPPFLAGS= -std=c++11
LDFLAGS=
LDLIBS= -lm

SRCS=main.cpp 
OBJS=$(subst .cpp,.o,$(SRCS))

all: buffer_bin
debug: CPPFLAGS+=-g
debug: LDFLAGS+=-g
debug: buffer_bin

buffer_bin: $(OBJS)
	$(CXX) $(LDFLAGS)  $(OBJS) -o buffer_bin  $(LDLIBS) 

main.o: main.cpp buffer.h

buffer.o: buffer.h

clean:
	$(RM) $(OBJS)

distclean: clean
	$(RM) buffer_bin
