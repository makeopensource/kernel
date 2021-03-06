#include <efi.h>
#include <efilib.h>
 
// https://wiki.osdev.org/Loading_files_under_UEFI
EFI_FILE_HANDLE GetVolume(EFI_HANDLE image)
{
  EFI_LOADED_IMAGE *loaded_image = NULL;                  /* image interface */
  EFI_GUID lipGuid = EFI_LOADED_IMAGE_PROTOCOL_GUID;      /* image interface GUID */
  EFI_FILE_IO_INTERFACE *IOVolume;                        /* file system interface */
  EFI_GUID fsGuid = EFI_SIMPLE_FILE_SYSTEM_PROTOCOL_GUID; /* file system interface GUID */
  EFI_FILE_HANDLE Volume;                                 /* the volume's interface */
 
  /* get the loaded image protocol interface for our "image" */
  uefi_call_wrapper(BS->HandleProtocol, 3, image, &lipGuid, (void **) &loaded_image);
  /* get the volume handle */
  uefi_call_wrapper(BS->HandleProtocol, 3, loaded_image->DeviceHandle, &fsGuid, (VOID*)&IOVolume);
  uefi_call_wrapper(IOVolume->OpenVolume, 2, IOVolume, &Volume);
  return Volume;
}

UINT64 FileSize(EFI_FILE_HANDLE FileHandle)
{
  UINT64 ret;
  EFI_FILE_INFO *FileInfo;         /* file information structure */
  /* get the file's size */
  FileInfo = LibFileInfo(FileHandle);
  ret = FileInfo->FileSize;
  FreePool(FileInfo);
  return ret;
}
 
EFI_STATUS efi_main (EFI_HANDLE image_handle, EFI_SYSTEM_TABLE *systab)
{
	InitializeLib(image_handle, systab);
	EFI_FILE_HANDLE Volume = GetVolume(image_handle);
	
	CHAR16 *FileName = L"kernel.bin";
 	EFI_FILE_HANDLE FileHandle;

	uefi_call_wrapper(Volume->Open, 5, Volume, &FileHandle, FileName, EFI_FILE_MODE_READ, EFI_FILE_READ_ONLY | EFI_FILE_HIDDEN | EFI_FILE_SYSTEM);
	
	UINT64 ReadSize = FileSize(FileHandle);
	UINT8 *Buffer = AllocatePool(ReadSize);
 
  	uefi_call_wrapper(FileHandle->Read, 3, FileHandle, &ReadSize, Buffer);
	uefi_call_wrapper(FileHandle->Close, 1, FileHandle);
	
	// I'm so sorry for what I'm about to do
	void* kernel = (void*)(Buffer);
	kernel += 0x1000; // _start
	void (*entry)(uint64_t) = (void (*)(uint64_t))(kernel);
	entry(ReadSize);
	//EFI_BOOT_SERVICES.Exit();
	return EFI_SUCCESS;
}
