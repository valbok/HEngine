###
# @author VaL Doroshchuk
# @license GNU GPL v2
###

USER_DIR = ../core

# Flags passed to the preprocessor.
CPPFLAGS += -I$(USER_DIR)

# Flags passed to the C++ compiler.
CXXFLAGS += -g -Wall -Wextra -pthread -std=c++0x

FCGI = fastcgi

all : $(FCGI)

clean :
	rm -f $(FCGI) *.o

HEngine.o : $(USER_DIR)/HEngine.cpp $(USER_DIR)/HEngine.h
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $(USER_DIR)/HEngine.cpp

HEngine_s.o : $(USER_DIR)/HEngine_s.cpp $(USER_DIR)/HEngine_s.h
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $(USER_DIR)/HEngine_s.cpp

HEngine_sn.o : $(USER_DIR)/HEngine_sn.cpp $(USER_DIR)/HEngine_sn.h
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $(USER_DIR)/HEngine_sn.cpp

fastcgi.o : fastcgi.cpp $(USER_DIR)/HEngine_sn.h
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c fastcgi.cpp

fastcgi :  fastcgi.o HEngine.o HEngine_s.o HEngine_sn.o
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $^ -lfcgi -lpthread -lmysqlcppconn  -o $@
