CC = gcc
CXX = g++
CFLAGS = -g -O2 -fPIC
CXXFLAG =  -std=c++14 -O2 -Wall -ggdb -m64 -D_GNU_SOURCE=1 -D_REENTRANT -D__GUNC__ -fPIC -DNODE_BEAT=10.0

ARCH:=$(shell uname -m)

ARCH32:=i686
ARCH64:=x86_64

ifeq ($(ARCH),$(ARCH64))
SYSTEM_LIB_PATH:=/usr/lib64
else
SYSTEM_LIB_PATH:=/usr/lib
endif
LIB3RD_PATH = ../../../NebulaDepend
NEBULA_PATH = ../../../Nebula
PLUGIN_PATH = ../../

VPATH = $(PLUGIN_PATH)/src
SUB_DIRS := $(foreach dir, $(VPATH), $(shell find $(dir) -maxdepth 5 -type d))
DIRS := $(SUB_DIRS)


INC := $(INC) \
       -I $(LIB3RD_PATH)/include \
       -I $(NEBULA_PATH)/include \
       -I $(PLUGIN_PATH)/src


LDFLAGS := $(LDFLAGS) -D_LINUX_OS_ \
           -L$(NEBULA_PATH)/lib -lnebula \
           -L$(LIB3RD_PATH)/lib -lhiredis \
           -L$(LIB3RD_PATH)/lib -lcryptopp \
           -L$(LIB3RD_PATH)/lib -lprotobuf \
           -L$(LIB3RD_PATH)/lib -lev \
           -L$(SYSTEM_LIB_PATH) -lc -lrt -ldl

CPP_SRCS = $(foreach dir, $(DIRS), $(wildcard $(dir)/*.cpp))
CC_SRCS = $(foreach dir, $(DIRS), $(wildcard $(dir)/*.cc))
C_SRCS = $(foreach dir, $(DIRS), $(wildcard $(dir)/*.c))
OBJS = $(patsubst %.cpp,%.o,$(CPP_SRCS)) $(patsubst %.c,%.o,$(C_SRCS)) $(patsubst %.cc,%.o,$(CC_SRCS))

SO_PATH = . 
STEP_PATH = .

SO_PATH = . 
SO_DEP_PATH = $(SO_PATH) $(PLUGIN_PATH)/src
STEP_PATH = .
CMD_SO_CPP_SRCS = $(foreach dir, $(SO_PATH), $(wildcard $(dir)/Cmd*.cpp))
MODULE_SO_CPP_SRCS = $(foreach dir, $(SO_PATH), $(wildcard $(dir)/Module*.cpp))
SO_CPP_SRCS = $(CMD_SO_CPP_SRCS) $(MODULE_SO_CPP_SRCS)
STEP_CPP_SRCS = $(foreach dir, $(STEP_PATH), $(wildcard $(dir)/Step*.cpp))
CMD_DEP_CPP_SRCS = $(foreach dir, $(SO_DEP_PATH), $(wildcard $(dir)/*.cpp))
STEP_OBJS = $(patsubst %.cpp,%.o,$(STEP_CPP_SRCS))
SO_OBJS = $(patsubst %.cpp,%.o,$(SO_CPP_SRCS))
CMD_DEP_OBJS = $(patsubst %.cpp,%.o,$(CMD_DEP_CPP_SRCS))
PB_OBJS = $(patsubst %.pb.cc,%.pb.o,$(CC_SRCS))
SOS = $(patsubst %.o,%.so,$(SO_OBJS))

TARGET = $(SOS)

all: $(TARGET)

.SECONDARY: $(PB_OBJS) $(CMD_DEP_OBJS)

Cmd%.so:Cmd%.o $(PB_OBJS) $(CMD_DEP_OBJS)
	$(CXX) -fPIE -rdynamic -shared -g -o $@ $^ $(LDFLAGS)
Module%.so:Module%.o $(PB_OBJS) $(CMD_DEP_OBJS)
	$(CXX) -fPIE -rdynamic -shared -g -o $@ $^ $(LDFLAGS)

%.o:%.cpp
	$(CXX) $(INC) $(CXXFLAG) -c -o $@ $< $(LDFLAGS)
%.o:%.cc
	$(CXX) $(INC) $(CXXFLAG) -c -o $@ $< $(LDFLAGS)
%.o:%.c
	$(CC) $(INC) $(CXXFLAG) -c -o $@ $< $(LDFLAGS)
clean:
	rm -f $(PB_OBJS) $(CMD_DEP_OBJS)
	rm -f $(TARGET)
        
        
