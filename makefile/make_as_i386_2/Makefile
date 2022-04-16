
# This quick and dirty makefile for  
# Programming from ground up vol.1 book by
# Jonathan Bartlett written by hands

# I strongly adivise you against making 
# your own makefile by hand from scratch
# There are enormous amount of files 
# written by hand by authors who tought
# (and still thinks) that they are absolutely sure
# what they are doing! They are mistaken!

# Use CMake, or similar tools instead!

.POSIX:
.SUFFIXES:

AS = as
ASFLAGS += --32
LD = ld
LDFLAGS += -melf_i386

WRITERECORDS = write-records
WRITERECORDSOBJ := write-record.o write-records.o

READRECORDS = read-records
READRECORDSOBJ := read-record.o count-chars.o write-newline.o read-records.o

ADDYEAR = add-year
ADDYEAROBJ := add-year.o

.PHONY: all

all: write-records read-records add-year 

write-record.o: write-record.s
	$(AS) $(ASFLAGS) $^ -o $@

write-records.o: write-records.s
	$(AS) $(ASFLAGS) $^ -o $@

write-records: write-record.o write-records.o
	$(LD) $(LDFLAGS) $^ -o $@

read-record.o: read-record.s
	$(AS) $(ASFLAGS) $^ -o $@

count-chars.o: count-chars.s
	$(AS) $(ASFLAGS) $^ -o $@

write-newline.o: write-newline.s
	$(AS) $(ASFLAGS) $^ -o $@

read-records.o: read-records.s
	$(AS) $(ASFLAGS) $^ -o $@

read-records: read-record.o count-chars.o \
	      write-newline.o read-records.o
	$(LD) $(LDFLAGS) $^ -o $@

add-year.o: add-year.s
	$(AS) $(ASFLAGS) $^ -o $@

add-year: add-year.o read-record.o write-record.o
	$(LD) $(LDFLAGS) $^ -o $@

clean:
	rm -f $(WRITERECORDS) $(WRITERECORDSOBJ) $(READRECORDS) $(READRECORDSOBJ) $(ADDYEAR) $(ADDYEAROBJ)


