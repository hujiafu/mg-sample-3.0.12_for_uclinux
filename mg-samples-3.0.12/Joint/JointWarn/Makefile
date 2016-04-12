

all:
	$(CC) $(CFLAGS) -c -o JointWarn_Logic.o JointWarn_Logic.c
	$(CC) $(CFLAGS) -c -o JointWarn_confirm.o JointWarn_confirm.c
	$(CC) $(CFLAGS) -c -o JointWarn_UImain.o JointWarn_UImain.c
	$(CC) $(CFLAGS) -c -o JointWarn_Main.o JointWarn_Main.c
	$(CC) -o JointWarn JointWarn_confirm.o JointWarn_UImain.o JointWarn_Logic.o JointWarn_Main.o $(LDFLAGS) $(LIBS)
	
clean:
	rm -rf *.o *.gdb JointWarn
