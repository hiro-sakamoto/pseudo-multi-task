CC	= g++
LD	= g++

CFLAGS	= -c -g -Wall -I../include
LDFLAGS	=
LIBS	= -lpthread

OBJS	= SampleTest.o

TARGET	= SampleTest

all:	$(TARGET)

.cpp.o:
	$(CC) $(CFLAGS) -o $@ $<

$(TARGET):	$(OBJS)
	$(LD) $(LDFLAGS) -o $@ $(OBJS) $(LIBS)

clean:
	rm -f $(OBJS) $(TARGET)

SampleTest.o:	../include/BaseTask.hpp