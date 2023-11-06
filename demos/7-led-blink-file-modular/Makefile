# makfile configuration
COMMON_OBJECTS  = 
CPU             = msp430g2553
CFLAGS          = -mmcu=${CPU} -I../h
LDFLAGS		= -L/opt/ti/msp430_gcc/include

#switch the compiler (for the internal make rules)
CC              = msp430-elf-gcc
AS              = msp430-elf-as

all: blink.elf 

#additional rules for files
blink.elf: ${COMMON_OBJECTS} blinkMain.o stateMachines.o led.o wdInterruptHandler.o ../lib/libTimer.a
	${CC} ${CFLAGS} ${LDFLAGS} -o $@ $^

load: blink.elf
	msp430loader.sh blink.elf

# vv assembly stuff
blink_s.elf: ${COMMON_OBJECTS} blinkMain.o stateMachines.o led_s.o wdInterruptHandler.o ../lib/libTimer.a
	${CC} ${CFLAGS} ${LDFLAGS} -o $@ $^

load_s: blink.elf
	msp430loader.sh blink_s.elf

led_s.o: led_s.s
	${CC} ${CFLAGS} ${LDFLAGS} -o $@ $^
# ^^ assembly stuff

clean:
	rm -f *.o *.elf

led.o: led.c led.h

wdInterruptHandler.o: stateMachines.h

stateMachines.o: led.h stateMachines.h
