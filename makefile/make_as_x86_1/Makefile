AS = as --32
LD = ld -m elf_i386
all: exit minimum maximum maximum_255 maximum_counter maximum_ending_address hello-world power sum factorial toupper heynow

clean:
	rm *.o exit minimum maximum maximum_255 maximum_counter maximum_ending_address hello-world power sum factorial toupper heynow

exit.o: exit.s
	$(AS) -o $@ $< 

exit: exit.o
	$(LD) -o $@ $< 

minimum.o: minimum.s
	$(AS) -o $@ $< 

minimum: minimum.o
	$(LD) -o $@ $< 

maximum.o: maximum.s
	$(AS) -o $@ $< 

maximum: maximum.o
	$(LD) -o $@ $< 

maximum_255.o: maximum_255.s
	$(AS) -o $@ $< 

maximum_255: maximum_255.o
	$(LD) -o $@ $< 

maximum_counter.o: maximum_counter.s
	$(AS) -o $@ $< 

maximum_counter: maximum_counter.o
	$(LD) -o $@ $< 

maximum_ending_address.o: maximum_ending_address.s
	$(AS) -o $@ $< 

maximum_ending_address: maximum_ending_address.o
	$(LD) -o $@ $< 

hello-world.o: hello-world.s
	$(AS) -o $@ $< 

hello-world: hello-world.o
	$(LD) -o $@ $< 

power.o: power.s
	$(AS) -o $@ $< 

power: power.o
	$(LD) -o $@ $< 

sum.o: sum.s
	$(AS) -o $@ $< 

sum: sum.o
	$(LD) -o $@ $< 

factorial.o: factorial.s
	$(AS) -o $@ $< 

factorial: factorial.o
	$(LD) -o $@ $< 

toupper.o: toupper.s
	$(AS) -o $@ $< 

toupper: toupper.o
	$(LD) -o $@ $< 

heynow.o: heynow.s
	$(AS) -o $@ $< 

heynow: heynow.o
	$(LD) -o $@ $< 
