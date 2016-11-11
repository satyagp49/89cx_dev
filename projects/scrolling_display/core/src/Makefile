CROSS_COMPILE=

CC=$(CROSS_COMPILE)gcc
CFLAGS=-c -g -rdynamic -funwind-tables -Wall -I../include -I../../application/include -I../include/arch_89cx
# CFLAGS=-c -g -rdynamic -funwind-tables -I../include
LDFLAGS=  -lpthread -lrt
 
STRIP=$(CROSS_COMPILE)strip

SOURCES= main.c ../../application/src/led_message_scrolling.c ./arch_89cx/sys_init_89cx.c

OBJECTS=$(SOURCES:.c=.o)

TARGET=scrolling_display

all: $(SOURCES) $(TARGET)

$(TARGET): $(OBJECTS)

	$(CC) $(OBJECTS) -o ../$@ $(LDFLAGS)
# 	$(STRIP) $(TARGET)
.c.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	$(RM) *.o $(TARGET)
