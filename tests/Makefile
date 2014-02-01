###
# @author VaL Doroshchuk
# @license GNU GPL v2
###

# Points to the root of Google Test, relative to where this file is.
GTEST_DIR = ../lib/gtest
# Where to find user code.
USER_DIR = ../core
LIB_DIR = ../lib

# Flags passed to the preprocessor.
# Set Google Test's header directory as a system directory, such that
# the compiler doesn't generate warnings in Google Test headers.
CPPFLAGS += -isystem $(GTEST_DIR)/include

# Flags passed to the C++ compiler.
CXXFLAGS += -g -Wall -Wextra -pthread -std=c++0x

# All tests produced by this Makefile.  Remember to add new tests you
# created to the list.
TESTS = HEngine_test HEngine_s_test HEngine_sn_test HEngine_sn_dict_test query duplicates matches

# All Google Test headers.  Usually you shouldn't change this
# definition.
GTEST_HEADERS = $(GTEST_DIR)/include/gtest/*.h \
                $(GTEST_DIR)/include/gtest/internal/*.h

# House-keeping build targets.

all : $(TESTS)

clean :
	rm -f $(TESTS) gtest.a gtest_main.a *.o

# Builds gtest.a and gtest_main.a.

# Usually you shouldn't tweak such internal variables, indicated by a
# trailing _.
GTEST_SRCS_ = $(GTEST_DIR)/src/*.cc $(GTEST_DIR)/src/*.h $(GTEST_HEADERS)

# For simplicity and to avoid depending on Google Test's
# implementation details, the dependencies specified below are
# conservative and not optimized.  This is fine as Google Test
# compiles fast and for ordinary users its source rarely changes.
gtest-all.o : $(GTEST_SRCS_)
	$(CXX) $(CPPFLAGS) -I$(GTEST_DIR) $(CXXFLAGS) -c \
            $(GTEST_DIR)/src/gtest-all.cc

gtest_main.o : $(GTEST_SRCS_)
	$(CXX) $(CPPFLAGS) -I$(GTEST_DIR) $(CXXFLAGS) -c \
            $(GTEST_DIR)/src/gtest_main.cc

gtest.a : gtest-all.o
	$(AR) $(ARFLAGS) $@ $^

gtest_main.a : gtest-all.o gtest_main.o
	$(AR) $(ARFLAGS) $@ $^

# Builds a sample test.  A test should link with either gtest.a or
# gtest_main.a, depending on whether it defines its own main()
# function.

HEngine.o : $(USER_DIR)/HEngine.cpp $(USER_DIR)/HEngine.h $(GTEST_HEADERS)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $(USER_DIR)/HEngine.cpp

HEngine_test.o : $(USER_DIR)/HEngine_test.cpp \
                     $(USER_DIR)/HEngine.h $(GTEST_HEADERS)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $(USER_DIR)/HEngine_test.cpp

HEngine_test : HEngine.o HEngine_test.o gtest_main.a
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -lpthread $^ -o $@


HEngine_s.o : $(USER_DIR)/HEngine_s.cpp $(USER_DIR)/HEngine_s.h $(GTEST_HEADERS)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $(USER_DIR)/HEngine_s.cpp

HEngine_s_test.o : $(USER_DIR)/HEngine_s_test.cpp \
                     $(USER_DIR)/HEngine_s.h $(GTEST_HEADERS)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $(USER_DIR)/HEngine_s_test.cpp

HEngine_s_test : HEngine.o HEngine_s.o HEngine_sn.o HEngine_s_test.o gtest_main.a
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -lpthread $^ -o $@



HEngine_sn.o : $(USER_DIR)/HEngine_sn.cpp $(USER_DIR)/HEngine_sn.h $(GTEST_HEADERS)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $(USER_DIR)/HEngine_sn.cpp

HEngine_sn_test.o : $(USER_DIR)/HEngine_sn_test.cpp \
                     $(USER_DIR)/HEngine_sn.h $(GTEST_HEADERS)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $(USER_DIR)/HEngine_sn_test.cpp

HEngine_sn_test : HEngine.o HEngine_s.o HEngine_sn.o HEngine_sn_test.o gtest_main.a
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -lpthread $^ -o $@

HEngine_sn_dict_test.o : $(USER_DIR)/HEngine_sn_dict_test.cpp \
                     $(USER_DIR)/HEngine_sn.h $(GTEST_HEADERS)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $(USER_DIR)/HEngine_sn_dict_test.cpp
HEngine_sn_dict_test :  HEngine.o HEngine_s.o HEngine_sn.o HEngine_sn_dict_test.o gtest_main.a
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -lpthread $^ -o $@


query.o : $(USER_DIR)/query.cpp $(USER_DIR)/HEngine_sn.h $(GTEST_HEADERS)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $(USER_DIR)/query.cpp

query :  query.o HEngine.o HEngine_s.o HEngine_sn.o
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -lpthread $^ -o $@

duplicates.o : $(USER_DIR)/duplicates.cpp $(USER_DIR)/HEngine_sn.h $(GTEST_HEADERS)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $(USER_DIR)/duplicates.cpp

duplicates :  duplicates.o HEngine.o HEngine_s.o HEngine_sn.o
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -lpthread $^ -o $@

matches.o : $(USER_DIR)/matches.cpp $(USER_DIR)/HEngine_sn.h $(GTEST_HEADERS)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $(USER_DIR)/matches.cpp

matches :  matches.o HEngine.o HEngine_s.o HEngine_sn.o
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -lpthread $^ -o $@
