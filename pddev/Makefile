NAME=getspi
current: l_arm

l_arm: $(NAME).l_arm

.SUFFIXES: .l_arm
LINUXCFLAGS = -DPD -O2 -funroll-loops -fomit-frame-pointer \
    -fno-strict-aliasing -Wall -W -Wshadow -Wstrict-prototypes \
    -Wno-unused -Wno-parentheses -Wno-switch $(CFLAGS)

.c.l_arm:
	cc $(LINUXCFLAGS) $(LINUXINCLUDE) -o $*.o -c $*.c
	ld  -shared -o $*.l_arm $*.o -lc -lm -lwiringPi
	strip --strip-unneeded $*.l_arm
	rm $*.o

clean:
	rm -f *.o *.pd_* *.l_arm
