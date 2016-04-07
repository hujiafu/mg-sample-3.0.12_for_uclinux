

all:
	$(CC) $(CFLAGS) -c -o JointWarn_Main.o JointWarn_Main.c
	$(CC) $(CFLAGS) -c -o JointWarn_Logic.o JointWarn_Logic.c
	$(CC) $(FLAGS) -o JointWarn JointWarn_Main.o JointWarn_Logic.o $(LDFLAGS) $(LIBS)
	
clean:
	rm -rf *.o *.gdb JointWarn
