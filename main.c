#include <stdio.h>
#include "utils.h"

int main()
{
	UNICODE_STRING Text = RTL_CONSTANT_STRING(L"Msg From ntdll!NtDrawText\n");
    NtDrawText(&Text);
    //NOP_Toy();
	PrintString("Msg From ntdll!PrintString: %d, %s\n", 233, "Hello Native World");
	// open keyboard device
	HANDLE KeyboardHandle;
	IO_STATUS_BLOCK IoStatusBlock;
	NTSTATUS Status = OpenKeyboard(&KeyboardHandle, &IoStatusBlock);
	if (!NT_SUCCESS(Status))
	{
		ULONG win32Err = RtlNtStatusToDosError(Status);
		printf("Failed to open keyboard device: %x\n", win32Err);
		//NOP_Toy();
		//native_sleep(5000);
		//return;
	}
	char buf[256];
	while(1)
	{
		printf("Enter a command: ");
		fgets(buf, sizeof(buf), stdin);
		buf[strcspn(buf, "\n")] = 0;  // Remove newline character
		execute_command(buf);
	}
	
}