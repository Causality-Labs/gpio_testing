BINDIR = bin
INCLUDEDIR = inc
SRCDIR = src

APP = gpio-test

ifndef CFLAGS
	CFLAGS += -D_POSIX_C_SOURCE=2 -std=c99
endif

################################## RULES ##################################
APP_OBJECTS += $(BINDIR)/gpio-test.o
APP_OBJECTS += $(BINDIR)/gpio_driver.o


$(BINDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(BINDIR)
	$(CC) -c $(CFLAGS) -I$(INCLUDEDIR) $< -o $@

$(BINDIR)/$(APP): ${APP_OBJECTS}
	$(CC) ${APP_OBJECTS} $(LDFLAGS) -o $@

.PHONY: all
all:	$(BINDIR)/$(APP)

.PHONY: clean
clean:
	rm -rf $(BINDIR)
