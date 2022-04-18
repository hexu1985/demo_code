AS = as
ASFLAGS = --32 -g
LD = ld 
LDFLAGS = -m elf_i386

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

