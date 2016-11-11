CROSS_COMPILE=

CC=$(CROSS_COMPILE)gcc
CFLAGS=-c -g -rdynamic -funwind-tables -Wall -I../include
LDFLAGS=  -lpthread -lrt
 
STRIP=$(CROSS_COMPILE)strip

SOURCES= main.c scroll_data.c 

OBJECTS=$(SOURCES:.c=.o)

TARGET=scrolling_display

all: $(SOURCES) $(TARGET)

$(TARGET): $(OBJECTS)

	$(CC) $(OBJECTS) -o $@ $(LDFLAGS)
# 	$(STRIP) $(TARGET)
.c.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	$(RM) *.o $(TARGET)
