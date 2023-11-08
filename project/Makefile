# makfile configuration
COMMON_OBJECTS  = main.o
CPU             = msp430g2553
CFLAGS          = -mmcu=${CPU} -I../demos/h -L/opt/ti/msp430_gcc/include
# LDFLAGS		= -L/opt/ti/msp430_gcc/include

#switch the compiler (for the internal make rules)
CC              = msp430-elf-gcc
AS              = msp430-elf-as

all: button.elf # buzzer.elf
	libs

libs: 
	(cd ../demos && make)

#additional rules for files
# REPLACE ALL OF THESE WITH YOUR ACTUAL FILE
# button.elf: ${COMMON_OBJECTS} ../demos/lib/libTimer.a
# 	${CC} ${CFLAGS} ${LDFLAGS} -o $@ $^

# buzzer.elf: ${COMMON_OBJECTS} buzzer.o ../demos/lib/libTimer.a # buzzerMain.o
# 	${CC} ${CFLAGS} -o $@ $^

main.elf: ${COMMON_OBJECTS} buzzer.o ../demos/lib/libTimer.a #switches.o
	${CC} ${CFLAGS} -o $@ $^

load: main.elf # button.elf # buzzer.elf 
	msp430loader.sh $^

clean:
	rm -f *.o *.elf

buzzer.c: buzzer.h
# switches.c: switches.h
# buzzerMain.c: buzzer.h
