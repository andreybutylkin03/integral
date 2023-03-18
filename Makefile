CFLAGS ?= -O2 -g

CFLAGS += -std=gnu99

CFLAGS += -Wall -Wformat-security -Wignored-qualifiers -Winit-self \
    -Wswitch-default -Wpointer-arith -Wtype-limits -Wempty-body \
    -Wstrict-prototypes -Wold-style-declaration -Wold-style-definition \
    -Wmissing-parameter-type -Wmissing-field-initializers -Wnested-externs \
    -Wstack-usage=4096 -Wfloat-equal

CFLAGS += -fsanitize=undefined -fsanitize-undefined-trap-on-error

CC = gcc

CC += -m32 -no-pie -fno-pie

LDLIBS = -lm

AS = nasm

ASMFLAGS = -f elf32

.PHONY: all clean

all: integral

integral: functions.o integral.o
	$(CC) $(CFLAGS) $^ $(LDLIBS) -o $@

integral.o: integral.c
	$(CC) $(CFLAGS) -c $^ -o $@

functions.o: functions.asm
	$(AS) $(ASMFLAGS) $^ -o $@

test: integral
	./integral -R 4:5:0:0.5:0.00005:0.2679492
	./integral -R 4:6:2:2.5:0.00005:2.4305009
	./integral -R 5:6:1:2:0.00005:1.7416574 
	./integral -I 4:0.2679492:2.4305009:0.0001:9.7062299
	./integral -I 5:0.2679492:1.7416574:0.0001:4.4069673
	./integral -I 6:1.7416574:2.4305009:0.0001:1.51245

clean: 
	rm -rf *.o