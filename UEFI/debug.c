#include <efi.h>
#include <efilib.h>
 
EFI_STATUS
efi_main (EFI_HANDLE image_handle, EFI_SYSTEM_TABLE *systab)
{
	InitializeLib(image_handle, systab);
	Print(L"Hello, world!\n");
	return EFI_SUCCESS;
}
