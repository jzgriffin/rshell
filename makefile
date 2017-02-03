CXX ?= g++
CXXFLAGS := $(CXXFLAGS) -std=c++11 -I.
ifeq ($(BUILD),release)
    CXXFLAGS := $(CXXFLAGS) -DNDEBUG -O2
else
    CXXFLAGS := $(CXXFLAGS) -D_DEBUG -g
endif

rshell.TARGET := bin/rshell
rshell.SOURCE := \
    rshell/Command.cpp \
    rshell/InitialCommand.cpp \
    rshell/SequentialCommand.cpp \
    rshell/ConjunctiveCommand.cpp \
    rshell/DisjunctiveCommand.cpp \
    rshell/Tokenizer.cpp \
    rshell/Parser.cpp \
    rshell/main.cpp
rshell.OBJECT := $(patsubst %.cpp,%.o,$(rshell.SOURCE))
rshell.DEPEND := $(patsubst %.cpp,%.d,$(rshell.SOURCE))

.PHONY: all clean distclean
all: all-rshell
clean: clean-rshell
distclean: distclean-rshell

.PHONY: rshell all-rshell clean-rshell distclean-rshell
rshell: all-rshell
all-rshell: $(rshell.TARGET)
clean-rshell:
	$(RM) $(rshell.OBJECT)
	$(RM) $(rshell.DEPEND)
distclean-rshell: clean-rshell
	$(RM) $(rshell.TARGET)
$(rshell.TARGET): $(rshell.OBJECT)
	$(CXX) $(CXXFLAGS) -o $@ $^
-include $(rshell.DEPEND)

%.o: %.cpp makefile
	$(CXX) $(CXXFLAGS) -MMD -MP -MT $@ -o $@ -c $<
