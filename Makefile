# Example usage:
# If you have testbench/my_test.c, you can execute the following to create a MIPS binary
# make testbench/my_test.mips.bin

# For simulator
CC = g++
CPPFLAGS = -std=c++11 -W -Wall

# For MIPS binaries. Turn on all warnings, enable all optimisations and link everything statically
MIPS_CC = mips-linux-gnu-gcc
MIPS_OBJCOPY = mips-linux-gnu-objcopy
MIPS_OBJDUMP = mips-linux-gnu-objdump
MIPS_CPPFLAGS = -W -Wall -O3 -fno-builtin -march=mips1 -mfp32
MIPS_LDFLAGS = -nostdlib -Wl,-melf32btsmip -march=mips1 -nostartfiles -mno-check-zero-division -Wl,--gpsize=0 -static -Wl,-Bstatic -Wl,--build-id=none

# Compile C file (.c) into MIPS object file (.o)
%.mips.o: %.c
	$(MIPS_CC) $(MIPS_CPPFLAGS) -c $< -o $@

# Assemble MIPS assembly file (.s) into MIPS object file (.o)
%.mips.o: %.s
	$(MIPS_CC) $(MIPS_CPPFLAGS) -c $< -o $@

# Link MIPS object file (.o), producing .elf, using memory locations specified in spec
%.mips.elf: %.mips.o
	$(MIPS_CC) $(MIPS_CPPFLAGS) $(MIPS_LDFLAGS) -T linker.ld $< -o $@

# Extract binary instructions only from linked object file (.elf)
%.mips.bin: %.mips.elf
	$(MIPS_OBJCOPY) -O binary --only-section=.text $< $@

# Disassemble linked object file (.elf), pulling out instructions as MIPS assembly file (.s)
%.mips.s : %.mips.elf
	$(MIPS_OBJDUMP) -j .text -D $< > $@

# Build simulator
#bin/mips_simulator: simulator.cpp comop.cpp rtype.cpp itype.cpp jtype.cpp comop.hpp rtype.hpp itype.hpp jtype.hpp
	#mkdir -p bin/
	#$(CC) $(CPPFLAGS) -c comop.cpp -o bin/comop.o
	#$(CC) $(CPPFLAGS) -c rtype.cpp -o bin/rtype.o
	#$(CC) $(CPPFLAGS) -c itype.cpp -o bin/itype.o
	#$(CC) $(CPPFLAGS) -c jtype.cpp -o bin/jtype.o
	#$(CC) $(CPPFLAGS) -c simulator.cpp -o bin/simulator.o

	#$(CC) $(CPPFLAGS) bin/*.o -o bin/mips_simulator

# Dummy for build simulator to conform to spec
#simulator: bin/mips_simulator

simulator : simulator.o rtype.o itype.o jtype.o comop.o
	mkdir -p bin
	rm -f bin/mips_simulator
	$(CC) $(CPPFLAGS) ./src/*.o -o bin/mips_simulator


simulator.o: ./src/simulator.cpp
	$(CC) $(CPPFLAGS) -c ./src/simulator.cpp -o ./src/simulator.o

rtype.o: ./src/rtype.cpp ./src/rtype.hpp
	$(CC) $(CPPFLAGS) -c ./src/rtype.cpp -o ./src/rtype.o

itype.o: ./src/itype.cpp ./src/itype.hpp
	$(CC) $(CPPFLAGS) -c ./src/itype.cpp -o ./src/itype.o

jtype.o: ./src/jtype.cpp ./src/jtype.hpp
	$(CC) $(CPPFLAGS) -c ./src/jtype.cpp -o ./src/jtype.o

comop.o: ./src/comop.cpp ./src/comop.hpp
	$(CC) $(CPPFLAGS) -c ./src/comop.cpp -o ./src/comop.o


# Dummy for build testbench to conform to spec. Could do nothing
testbench:
	@echo "Nothing to do"
