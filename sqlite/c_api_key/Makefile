
RM = rm -f
CXX = g++
CXXFLAGS = -Wall -g -DSQLITE_HAS_CODEC
INCLUDES = -I../sqlite3
LDFLAGS = ../sqlite3/libsqlite-see.a -lpthread -ldl
LDPATH = 

PROGS = create_dbfile create_table delete insert select update

all: $(PROGS)
	@echo "PROGS = $(PROGS)" 

clean:
	$(RM) $(PROGS) *.db *.o

%.o:%.cpp
	$(CXX) -o $@ -c $< $(CXXFLAGS) $(INCLUDE)

create_dbfile: create_dbfile.o open_db.o
	$(CXX) -o $@ $^ $(LDFLAGS) $(LDPATH)

create_table: create_table.o open_db.o
	$(CXX) -o $@ $^ $(LDFLAGS) $(LDPATH)

delete: delete.o open_db.o
	$(CXX) -o $@ $^ $(LDFLAGS) $(LDPATH)

insert: insert.o open_db.o
	$(CXX) -o $@ $^ $(LDFLAGS) $(LDPATH)

select: select.o open_db.o
	$(CXX) -o $@ $^ $(LDFLAGS) $(LDPATH)

update: update.o open_db.o
	$(CXX) -o $@ $^ $(LDFLAGS) $(LDPATH)

