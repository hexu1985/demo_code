AS = as --32 -g
LD = ld -m elf_i386

SOURCES = $(shell ls *.s)
PROGS = $(SOURCES:%.s=%)

all: $(PROGS)
	@echo "PROGS = $(PROGS)" 

clean:
	$(RM) $(PROGS) *.o

%.o:%.s
	$(AS) -o $@ $<

$(PROGS): %: %.o
	$(LD) -o $@ $<

