.PHONY: all clean

CFLAGS := -Werror -Wall -Wextra -MMD
LDLIBS := -ldwarf

SRC_FILES := ptracer.c
SRC_FILES += parse_args.c
SRC_FILES += trace.c
SRC_FILES += results.c

OBJ_FILES := $(patsubst %.c,%.o,$(SRC_FILES))
DEP_FILES := $(patsubst %.c,%.d,$(SRC_FILES))
PROGRAM := ptracer

all: $(PROGRAM)

$(PROGRAM): $(OBJ_FILES)

$(OBJ_FILES): Makefile

-include $(DEP_FILES)

clean:
	find -name "*~" -delete
	rm -f $(PROGRAM) $(OBJ_FILES) $(DEP_FILES)
