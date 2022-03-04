OVMF_DIR = /usr/share/ovmf
C_FLAGS := -m32 -fno-pie -ffreestanding

all : os

%.o : %.asm
	nasm $< -f elf32 -o $@

%.o : %.c
	gcc ${C_FLAGS} -c $< -o $@

src/kernel.bin : src/kernel.o src/kernel_entry.o
	ld -m elf_i386 -o $@ -Ttext 0x1000 $^ 
	#This should be in binary format but for some reason ld makes the binary ~140mb
	
os : src/kernel.bin
	cd UEFI && $(MAKE)
	
run : os
	sudo qemu-system-x86_64 -drive file=${OVMF_DIR}/OVMF.fd,format=raw,if=pflash -cdrom UEFI/main.iso
	
debug: src/kernel.bin
	cd UEFI && $(MAKE) debug
	sudo qemu-system-x86_64 -drive file=${OVMF_DIR}/OVMF.fd,format=raw,if=pflash -cdrom UEFI/debug.iso
	
clean:
	rm -fr src/kernel.bin src/kernel_entry.o src/kernel.o
	cd UEFI && $(MAKE) clean
