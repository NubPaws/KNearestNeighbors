# Setup the src path and the bin path.
PROJDIR := $(realpath $(CURDIR))
SRCDIR := $(PROJDIR)/src
BINDIR := $(PROJDIR)/bin

# Decide whether the commands will be shown or not.
VERBOSE = FALSE

# Create the list of directories.
DIRS = . calculations containers input utils
# First add the prefixes
_SOURCEDIRS = $(foreach dir, $(DIRS), $(addprefix $(SRCDIR)/, $(dir)))
_TARGETDIRS = $(foreach dir, $(DIRS), $(addprefix $(BINDIR)/, $(dir)))
# Then, whenever we encounter /. we we want to substitute it with nothing as
# to not make paths that are valid, but weird, like /./
SOURCEDIRS = $(foreach dir, $(_SOURCEDIRS), $(subst /.,,$(dir)))
TARGETDIRS = $(foreach dir, $(_TARGETDIRS), $(subst /.,,$(dir)))

# Generate the GCC includes parameters by adding -I before each source folder.
INCLUDES = $(foreach dir, $(SOURCEDIRS), $(addprefix -I, $(dir)))

# Add this list to VPATH, the place make will look for the source files.
VPATH = $(SOURCEDIRS)

# CReate a list of *.cpp sources in DIRS.
SOURCES = $(foreach dir, $(SOURCEDIRS), $(wildcard $(dir)/*.cpp))

# Define objects for all sources.
OBJS := $(subst $(SRCDIR),$(BINDIR),$(SOURCES:.cpp=.o))

# Define dependencies files for all objects
DEPS = $(OBJS:.o=.d)

# Choose the compiler.
CC = g++ -std=c++11

# $(info $$SRCDIR is [${SRCDIR}])
# $(info $$BINDIR is [${BINDIR}])
# $(info $$OBJS is [${OBJS}])
# $(info $$TARGETDIRS is [${TARGETDIRS}])

# OS Specific part.
ifeq ($(OS),Windows_NT)
	TARGET = a.exe
	RM = del /F /Q
	RMDIR = -rmdir /S /Q
	MKDIR = -mkdir
	ERRIGNORE = 2>NUL || VER>NUL
	SEP=\\ 
else
	TARGET = a.out
	RM = rm -rf
	RMDIR = rm -rf
	MKDIR = mkdir -p
	ERRIGNORE = 2>/dev/null
	SEP=/ 
endif

# Remove space after seperator
PSEP = $(strip $(SEP))

# Hide or not the calls depending of VERBOSE
ifeq ($(VERBOSE), TRUE)
	HIDE =
else
	HIDE = @
endif

# Define the function that will generate each rule.
define generateRules
$(1)/%.o: %.cpp
	@echo BUILDING $$@
	$(HIDE)$(CC) -c $$(INCLUDES) -o $$(subst /,$$(PSEP),$$@) $$(subst /,$$(PSEP),$$<) -MMD
endef

.PHONY: all clean directories

all: directories $(TARGET)

$(TARGET): $(OBJS)
	$(HIDE)echo Linking $@
	$(HIDE)$(CC) $(OBJS) -o $(TARGET)

# Include dependencies.
-include $(DEPS)

# Generate rules
$(foreach targetdir, $(TARGETDIRS), $(eval $(call generateRules, $(targetdir))))

directories:
	$(HIDE)$(MKDIR) $(subst /,$(PSEP),$(TARGETDIRS)) $(ERRIGNORE)

# Remove all objects, dependencies and executable files generated during the build.
clean:
	$(HIDE)$(RMDIR) $(subst /,$(PSEP),$(TARGETDIRS)) $(ERRIGNORE)
	$(HIDE)$(RM) $(TARGET) $(ERRIGNORE)
	@echo Cleaning done!

# Exercise 2 test.
ex2_test: all
	./$(TARGET) 3 ./datasets/iris/iris_classified.csv MAN
