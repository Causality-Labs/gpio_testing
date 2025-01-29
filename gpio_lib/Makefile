CC = $(CROSS_COMPILER)gcc

INCLUDEDIR = inc
SRCDIR = src
BUILD_DIR = obj

ifndef CFLAGS
	CFLAGS += -D_POSIX_C_SOURCE=2 -std=c99
endif

SRC = $(SRCDIR)/ldd_gpio_api.c
OBJ = $(BUILD_DIR)/ldd_gpio_api.o

$(OBJ): $(SRC)
	mkdir -p $(BUILD_DIR)
	$(CC) -c $(CFLAGS) -I$(INCLUDEDIR) $< -o $@


.PHONY: all
all: $(OBJ)
 
.PHONY: clean
clean:
	rm -rf $(OBJ)
