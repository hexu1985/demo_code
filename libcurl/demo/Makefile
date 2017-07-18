# Makefile

RM = rm -f
CXX = gcc
CXXFLAGS = -Wall -g
INCLUDE = 
LDFLAGS = -lcurl
LDPATH = 

PROGS =	get_post get_post2 get_http save_http process resume

.PHONY: all
all: $(PROGS)
	@echo "build OK!"

clean:
	@$(RM) $(PROGS) *.o
	@echo "clean OK!"

%.o:%.c
	$(CXX) -o $@ -c $< $(CXXFLAGS) $(INCLUDE)

process.o:process.c
	$(CXX) -o $@ -c $< $(CXXFLAGS) $(INCLUDE) `pkg-config --cflags gtk+-2.0`

get_post: get_post.o
	$(CXX) -o $@ $^ $(LDFLAGS) $(LDPATH)

get_post2: get_post2.o
	$(CXX) -o $@ $^ $(LDFLAGS) $(LDPATH)

get_http: get_http.o
	$(CXX) -o $@ $^ $(LDFLAGS) $(LDPATH)

save_http: save_http.o
	$(CXX) -o $@ $^ $(LDFLAGS) $(LDPATH)

process: process.o
	$(CXX) -o $@ $^ $(LDFLAGS) $(LDPATH) `pkg-config --libs gtk+-2.0` -lgthread-2.0

resume: resume.o
	$(CXX) -o $@ $^ $(LDFLAGS) $(LDPATH)

