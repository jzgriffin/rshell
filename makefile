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
    src/ExecutableCommand.cpp \
    src/SequentialCommand.cpp \
    src/ConjunctiveCommand.cpp \
    src/DisjunctiveCommand.cpp \
    src/ExitBuiltinCommand.cpp \
    src/TestBuiltinCommand.cpp \
    src/Tokenizer.cpp \
    src/Parser.cpp \
    src/Executor.cpp \
    src/PosixExecutor.cpp \
    src/Shell.cpp \
    src/ExitException.cpp \
    src/ArgVector.cpp \
    src/main.cpp
rshell.OBJECT := $(patsubst %.cpp,%.o,$(rshell.SOURCE))
rshell.DEPEND := $(patsubst %.cpp,%.d,$(rshell.SOURCE))

.PHONY: all clean distclean
all: all-rshell
clean: clean-rshell clean-doc
distclean: distclean-rshell distclean-doc
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

.PHONY: test all-test clean-test distclean-test
test:
	sh tests/all.sh
all-test: test
clean-test:
distclean-test:

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
