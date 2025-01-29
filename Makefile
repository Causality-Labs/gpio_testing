# Directories
BINDIR       := bin
LIBDIR       := gpio_lib
LIBSRCDIR    := $(LIBDIR)/src
LIBINCDIR    := $(LIBDIR)/inc
SRCDIR       := src
INCLUDEDIR   := inc

# Target executable name
INTERRUPT_TEST := gpio-interrupt-test

# Compiler and Flags
CC     := gcc
CFLAGS := -Wall -Wextra -std=c99
LDFLAGS :=

# Object files for the library and the app
LIB_OBJECTS  := $(BINDIR)/ldd_gpio_api.o
APP_OBJECTS  := $(BINDIR)/gpio-interrupt-test.o

# Final objects to link into the executable
OBJECTS := $(LIB_OBJECTS) $(APP_OBJECTS)

# Default target: build the executable
all: $(BINDIR)/$(INTERRUPT_TEST)

#
# Compile library source -> object
#
$(BINDIR)/ldd_gpio_api.o: $(LIBSRCDIR)/ldd_gpio_api.c
	@mkdir -p $(BINDIR)
	$(CC) $(CFLAGS) -I$(LIBINCDIR) -c $< -o $@

#
# Compile application source -> object
#
$(BINDIR)/gpio-interrupt-test.o: $(SRCDIR)/gpio-interrupt-test.c
	@mkdir -p $(BINDIR)
	$(CC) $(CFLAGS) -I$(INCLUDEDIR) -I$(LIBINCDIR) -c $< -o $@

#
# Link all objects into the final executable
#
$(BINDIR)/$(INTERRUPT_TEST): $(OBJECTS)
	$(CC) $(OBJECTS) $(LDFLAGS) -o $@

#
# Clean rule
#
clean:
	rm -rf $(BINDIR)

.PHONY: all clean
