#include <stdio.h>
#include "utils.h"

int main()
{
	UNICODE_STRING Text = RTL_CONSTANT_STRING(L"Msg From ntdll!NtDrawText\n");
	NTSTATUS Status = NtDrawText(&Text);
    //NOP_Toy();
	//PrintString("Msg From ntdll!PrintString: %d, %s\n", 233, "Hello Native World");
	// open keyboard device
	HANDLE KeyboardHandle; char c;
	Status = OpenKeyboard(&KeyboardHandle);
	if (!NT_SUCCESS(Status))
	{
		ULONG win32Err = RtlNtStatusToDosError(Status);
		printf("Failed to open keyboard device: %x\n", win32Err);
		//NOP_Toy();
		native_sleep(5000);
		return;
	}
	while (1)
	{
		native_get_keyboard_char(KeyboardHandle, &c);
		printf("Received keyboard char: %c\n", c);
		if (c == 27) // ESC key to exit
		{
			break;
		}
	}
	return;
}

// link main.obj toolget.obj ntdll.lib /SUBSYSTEM:NATIVE /machine:x64 /ENTRY:entry /out:NativeEXE_1.exe

// ref https://medium.com/windows-os-internals/windows-native-api-programming-hello-world-8f256abe1c85