CXXFLAGS=-ansi -pedantic -g -Wall
LDFLAGS=-lX11 -lXtst

OBJECT=main.o app.o grab.o notify.o grabnotify.o\
       recordasyncnotify.o\
       recordnotify.o signalhandler.o
TARGET=xab

$(TARGET):$(OBJECT)
	g++ -o $(TARGET) $(OBJECT) $(LDFLAGS) 

main.o:main.cpp app.h grabnotify.h recordnotify.h\
		recordasyncnotify.h notify.h\
		signalhandler.h
app.o:app.cpp app.h eventhandler.h
grab.o:grab.cpp grab.h exc.h
notify.o:notify.cpp notify.h
grabnotify.o:grabnotify.cpp grabnotify.h grab.h exc.h notify.h app.h
recordasyncnotify.o:recordasyncnotify.cpp recordasyncnotify.h notify.h app.h
recordnotify.o:recordnotify.cpp recordnotify.h notify.h app.h
signalhandler.o:signalhandler.cpp signalhandler.h eventhandler.h

.PHONY:clean
clean:
	rm -f $(TARGET) $(OBJECT)

.PHONY:man
man:$(TARGET).1.gz

$(TARGET).1.gz:$(TARGET)
	help2man --opt-include README $(TARGET) -N | /bin/gzip > $(TARGET).1.gz

.PHONY:archive
archive:$(TARGET).tar.gz

$(TARGET).tar.gz:
	git-archive --format=tar HEAD | gzip > $(TARGET).tar.gz

