
RM = rm -f
CXX = gcc
CXXFLAGS = -Wall -g #-std=c++11
INCLUDES = 
LDFLAGS = -lX11 -lXrandr -lXinerama -lXext -lXtst -lpthread -lm
LDPATH =

SOURCES = $(shell ls *.c)
PROGS = $(subst .c,,$(SOURCES))
#PROGS = $(SOURCES:%.c=%)

all: $(PROGS)
	@echo "PROGS = $(PROGS)" 

clean:
	$(RM) $(PROGS)

%: %.c
	$(CXX) -o $@ $(CXXFLAGS) $(INCLUDES) $^ $(LDFLAGS) $(LDPATH)
