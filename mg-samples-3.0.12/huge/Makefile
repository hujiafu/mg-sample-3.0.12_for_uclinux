

all:
	$(CC) $(CFLAGS) -c -o pos_main.o pos_main.c
	$(CC) $(CFLAGS) -c -o pos_realtime.o pos_realtime.c
	$(CC) -o hufg_pos pos_main.o \
			  pos_realtime.o \
			  $(LDFLAGS) $(LIBS)
	
clean:
	rm -rf *.o *.gdb hufg_pos
