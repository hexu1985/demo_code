
RM = rm -f
CXX = g++
CXXFLAGS = -Wall -g
INCLUDES = -I../../lib/
LDFLAGS = -lpcap
LDPATH =
VPATH = ../../lib

PROGS = httpreq_sniffer httpresp_sniffer

all: $(PROGS)
	@echo "PROGS = $(PROGS)" 

clean:
	$(RM) $(PROGS)

httpresp_sniffer: httpresp_sniffer.cpp httpresp.cpp http_parser.cpp
	$(CXX) -o $@ $(CXXFLAGS) $(INCLUDES) $^ $(LDFLAGS) $(LDPATH)

httpreq_sniffer: httpreq_sniffer.cpp httpreq.cpp http_parser.cpp
	$(CXX) -o $@ $(CXXFLAGS) $(INCLUDES) $^ $(LDFLAGS) $(LDPATH)
