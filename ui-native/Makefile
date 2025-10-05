# ui-native/Makefile

TARGET = libui_native.so
CC = gcc
CFLAGS = -fPIC -O2 -I${JAVA_HOME}/include -I${JAVA_HOME}/include/linux
LDFLAGS = -shared
TARGET_ARM = libui_native_arm64.so
CC_ARM = aarch64-linux-gnu-gcc
CFLAGS_ARM = -fPIC -O2 -I$(JAVA_HOME)/include -I$(JAVA_HOME)/include/linux
LDFLAGS_ARM = -shared

SOURCES = framebuffer.c jni_interface.c
OBJECTS = $(SOURCES:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(LDFLAGS) -o $@ $^
	
arm64: $(SOURCES)
	$(CC_ARM) $(CFLAGS_ARM) $(LDFLAGS_ARM) -o $(TARGET_ARM) $(SOURCES)

clean:
	rm -f *.o *.so

