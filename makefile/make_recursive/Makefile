
SUBDIRS = public thread algo pcap socket \
	ipreg mysql dnsfake libnet
#SUBDIRS = public thread algo ipc ipv4 pcap socket \
#	fs ipreg mysql share 

all:
	@$(MAKE) $(MFLAGS) WHAT_TO_MAKE=$@ common

clean:
	@$(MAKE) $(MFLAGS) WHAT_TO_MAKE=$@ common

common:
	@for dir in $(SUBDIRS); do \
		echo "Making $(WHAT_TO_MAKE) in $$dir..."; \
		(cd $$dir && $(MAKE) $(MFLAGS) $(WHAT_TO_MAKE)) || exit 1; \
	done
