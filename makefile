CXX ?= g++
CXXFLAGS := $(CXXFLAGS) -Wall -Werror -pedantic -std=c++11
ifeq ($(BUILD),release)
    CXXFLAGS := $(CXXFLAGS) -DNDEBUG -O2
else
    CXXFLAGS := $(CXXFLAGS) -D_DEBUG -g
endif

rshell.TARGET := bin/rshell
rshell.SOURCE := \
    src/Command.cpp \
    src/InitialCommand.cpp \
    src/SequentialCommand.cpp \
    src/ConjunctiveCommand.cpp \
    src/DisjunctiveCommand.cpp \
    src/Tokenizer.cpp \
    src/Parser.cpp \
    src/Executor.cpp \
    src/PosixExecutor.cpp \
    src/Execution.cpp \
    src/Shell.cpp \
    src/main.cpp
rshell.OBJECT := $(patsubst %.cpp,%.o,$(rshell.SOURCE))
rshell.DEPEND := $(patsubst %.cpp,%.d,$(rshell.SOURCE))

.PHONY: all clean distclean
all: all-rshell
clean: clean-rshell
distclean: distclean-rshell
	$(RM) -r bin

bin:
	mkdir -p bin

.PHONY: doc all-doc clean-doc distclean-doc
doc:
	doxygen doc/Doxyfile
all-doc: doc
clean-doc:
	$(RM) -r doc/output
distclean-doc: doc

.PHONY: rshell all-rshell clean-rshell distclean-rshell
rshell: all-rshell
all-rshell: $(rshell.TARGET)
clean-rshell:
	$(RM) $(rshell.OBJECT)
	$(RM) $(rshell.DEPEND)
distclean-rshell: clean-rshell
	$(RM) $(rshell.TARGET)
$(rshell.TARGET): bin $(rshell.OBJECT)
	$(CXX) $(CXXFLAGS) -o $@ $(rshell.OBJECT)
-include $(rshell.DEPEND)

%.o: %.cpp makefile
	$(CXX) $(CXXFLAGS) -MMD -MP -MT $@ -o $@ -c $<
