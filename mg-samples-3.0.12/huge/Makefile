

all:
	$(CC) $(CFLAGS) -c -o pos_main.o pos_main.c
	$(CC) $(CFLAGS) -c -o pos_realtime.o pos_realtime.c
	$(CC) $(CFLAGS) -c -o pos_query.o pos_query.c
	$(CC) $(CFLAGS) -c -o pos_item.o pos_item.c
	$(CC) $(CFLAGS) -c -o pos_cosset.o pos_cosset.c
	$(CC) -o hufg_pos pos_main.o \
			  pos_realtime.o \
			  pos_query.o \
			  pos_item.o \
			  pos_cosset.o \
			  $(LDFLAGS) $(LIBS)
	
clean:
	rm -rf *.o *.gdb hufg_pos
