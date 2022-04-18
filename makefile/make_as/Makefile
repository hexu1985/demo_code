AS = as
ASFLAGS = -g
LD = ld 
LDFLAGS =

SOURCES = $(shell ls *.s)
PROGS = $(SOURCES:%.s=%)

all: $(PROGS)
	@echo "PROGS = $(PROGS)" 

clean:
	$(RM) $(PROGS) *.o

%.o:%.s
	$(AS) $(ASFLAGS) -o $@ $<

$(PROGS): %: %.o
	$(LD) $(LDFLAGS) -o $@ $<

