
GOOGLE_BENCHMARK_ROOT_DIR=$(HOME)/local/google_benchmark/

RM = rm -f
CXX = g++
CXXFLAGS = -Wall -g -std=c++14
INCLUDES = -I$(GOOGLE_BENCHMARK_ROOT_DIR)/include
LDFLAGS = -pthread -lbenchmark
LDPATH = -Wl,-rpath,$(GOOGLE_BENCHMARK_ROOT_DIR)/lib -Wl,--enable-new-dtags -L$(GOOGLE_BENCHMARK_ROOT_DIR)/lib
VPATH = 

SOURCES = $(shell ls *.cpp)
PROGS = benchmark_sample

all: $(PROGS)
	@echo "PROGS = $(PROGS)" 

clean:
	$(RM) $(PROGS)

$(PROGS): $(SOURCES) $(LIB_SOURCES)
	$(CXX) -o $@ $(CXXFLAGS) $(INCLUDES) $^ $(LDFLAGS) $(LDPATH)
