#https://wiki.osdev.org/UEFI_App_Bare_Bones#Running_as_a_USB_stick_image

#run before using this file
# $git clone https://git.code.sf.net/p/gnu-efi/code gnu-efi
# $cd gnu-efi
# $make


GNUEFI_DIR = gnu-efi
OVMF_DIR = /usr/share/ovmf

# .c that gets made into the .efi program
TARGET = main


include $(GNUEFI_DIR)/Make.defaults
INCDIR = -I$(GNUEFI_DIR) -I$(GNUEFI_DIR)/inc -I$(GNUEFI_DIR)/inc/$(ARCH) \
           -I$(GNUEFI_DIR)/inc/protocol

include $(GNUEFI_DIR)/Make.rules

#### THE FOLLOWING IS TAKEN FROM gnu-efi/apps/Makefile with modifications ####

#modified paths to fit with this Makefile
#order and spacing has also been modified

CRTOBJS = $(GNUEFI_DIR)/$(ARCH)/gnuefi/crt0-efi-$(ARCH).o
LINUX_HEADERS = /usr/src/sys/build
CPPFLAGS += -D__KERNEL__ -I$(LINUX_HEADERS)/include

LDSCRIPT	= $(GNUEFI_DIR)/gnuefi/elf_$(ARCH)_efi.lds
ifneq (,$(findstring FreeBSD,$(OS)))
LDSCRIPT	= $(GNUEFI_DIR)/gnuefi/elf_$(ARCH)_fbsd_efi.lds
endif

LDFLAGS		+= -shared -Bsymbolic -L$(GNUEFI_DIR)/$(ARCH)/ -L$(GNUEFI_DIR)/$(ARCH)/gnuefi/ -T $(LDSCRIPT) $(CRTOBJS)

LOADLIBES	+= -l/libefi -lgnuefi
LOADLIBES	+= $(LIBGCC)

ifneq ($(HAVE_EFI_OBJCOPY),)

FORMAT		:= --target efi-app-$(ARCH)
$(TARGET_BSDRIVERS): FORMAT=--target efi-bsdrv-$(ARCH)
$(TARGET_RTDRIVERS): FORMAT=--target efi-rtdrv-$(ARCH)

else

SUBSYSTEM	:= 0xa
$(TARGET_BSDRIVERS): SUBSYSTEM = 0xb
$(TARGET_RTDRIVERS): SUBSYSTEM = 0xc

FORMAT		:= -O binary
LDFLAGS		+= --defsym=EFI_SUBSYSTEM=$(SUBSYSTEM)

endif
##############################################################################

all: ${TARGET}.iso

%.img : %.efi
	mv $< BOOTX64.EFI
	dd if=/dev/zero of=$@ bs=1k count=1440
	mformat -i $@ -f 1440 ::
	mmd -i $@ ::/EFI
	mmd -i $@ ::/EFI/BOOT
	mcopy -i $@ BOOTX64.EFI ::/EFI/BOOT
	rm -fr BOOTX64.EFI
	rm -fr $<

%.iso : %.img
	mkdir -p iso
	cp $< iso
	xorriso -as mkisofs -R -f -e $< -no-emul-boot -o $@ iso
	rm -r iso
	rm -fr $< *.so *.o

#the debug iso uses a program that does nothing to get directly into the GUI
#the target can be run from a file via the GUI
debug.iso : ${TARGET}.efi.debug debug.img
	mv ${TARGET}.efi.debug ${TARGET}.efi
	mmd -i debug.img ::/EFI/TEST
	mcopy -i debug.img ${TARGET}.efi ::/EFI/TEST
	mkdir -p iso
	cp debug.img iso
	xorriso -as mkisofs -R -f -e debug.img -no-emul-boot -o $@ iso
	rm -r iso
	rm -fr *.efi *.img *.so *.o
	
debug : debug.iso
	sudo qemu-system-x86_64 -drive file=${OVMF_DIR}/OVMF.fd,format=raw,if=pflash -cdrom debug.iso
	
run : ${TARGET}.iso
	sudo qemu-system-x86_64 -drive file=${OVMF_DIR}/OVMF.fd,format=raw,if=pflash -cdrom $<
	
clean:
	rm -fr *.iso *.efi *.img *.efi.debug
