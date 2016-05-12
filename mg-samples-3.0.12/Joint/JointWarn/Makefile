

all:
	$(CC) $(CFLAGS) -c -o JointWarn_Logic.o JointWarn_Logic.c
	$(CC) $(CFLAGS) -c -o JointWarn_confirm.o JointWarn_confirm.c
	$(CC) $(CFLAGS) -c -o JointWarn_UImain.o JointWarn_UImain.c
	$(CC) $(CFLAGS) -c -o JointWarn_Main.o JointWarn_Main.c
	$(CC) $(CFLAGS) -c -o JointWarn_lib.o JointWarn_lib.c
	$(CC) $(CFLAGS) -c -o JointWarn_Json.o JointWarn_Json.c
	$(CC) $(CFLAGS) -c -o JointWarn_105.o JointWarn_105.c
	$(CC) $(CFLAGS) -c -o JointWarn_106.o JointWarn_106.c
	$(CC) -o JointWarn JointWarn_confirm.o \
			   JointWarn_UImain.o \
			   JointWarn_Logic.o \
			   JointWarn_Main.o \
			   JointWarn_lib.o \
			   JointWarn_Json.o \
			   JointWarn_105.o \
			   JointWarn_106.o \
		           $(LDFLAGS) $(LIBS)
	
clean:
	rm -rf *.o *.gdb JointWarn
