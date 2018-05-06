# Version 4.7.4

# $@: The filename representing the target (file to be generated)
# $%: The filename element of an archive member specification.
# $<: The filename of the first prerequisite (first input)
# $?: The names of all prerequisites that are newer than the target, separated by spaces.
# $^: The filenames of all the prerequisites, separated by spaces (no duplicates)

PROJECT := AUTOSAR
PPCCC := powerpc-linux-gnu-gcc
MODULES := . Can CanIf COM PduR
SRC_DIR	:= $(addprefix ./,$(MODULES))
#SRC_DIR	:= $(addprefix /,$(MODULES))
BUILD_DIR := $(addprefix build/,$(MODULES))
SRC	:= $(foreach srcdir,$(SRC_DIR),$(wildcard $(srcdir)/*.c))
OBJ := $(patsubst ./%.c, build/%.o, $(SRC))
INCLUDE := $(addprefix -I,$(SRC_DIR))
#CFLAGS := -Wall -Werror ${INCLUDE} -D 'PROJECTNAME="${PROJECT}"'
CFLAGS := -Wall -Werror ${INCLUDE}
vpath %.c $(SRC_DIR)

define make-build-dir
$1/%.o : %.c
	$(PPCCC) $(CFLAGS) -c $$< -o $$@
	# $(PPCCC) $(INCLUDE) -c $$< -o $$@
endef

help:
	@echo Objects: $(OBJECTS)
	@echo $(OBJ)
	@echo $(SRC_DIR)
	@echo $(BUILD_DIR)
	@echo $(SRC)
	@echo $(INCLUDE)

.PHONY: all checkbuildir clean
all: checkbuildir build/AUTOSAR

build/AUTOSAR: $(OBJ)
	# $(PPCCC) $^ -o $@
	$(PPCCC) $(CFLAGS) $^ -o $@

$(BUILD_DIR):
	@mkdir -p $@

#.PHONY: clean
clean:
	@rm -rf $(BUILD_DIR)

$(foreach buildir, $(BUILD_DIR), $(eval $(call make-build-dir,$(buildir))))