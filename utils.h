#define _AMD64_
#include <ntdef.h>
#include <ntstatus.h>

typedef ULONG ACCESS_MASK;
typedef struct _IO_STATUS_BLOCK {
    union {
        NTSTATUS Status;
        PVOID Pointer;
    };

    ULONG_PTR Information;
} IO_STATUS_BLOCK, * PIO_STATUS_BLOCK;
typedef VOID (NTAPI* PIO_APC_ROUTINE) (
    _In_ PVOID ApcContext,
    _In_ PIO_STATUS_BLOCK IoStatusBlock,
    _In_ ULONG Reserved
    );
#define STANDARD_RIGHTS_REQUIRED         (0x000F0000L)
#define SYNCHRONIZE                      (0x00100000L)
#define FILE_SUPERSEDE                  0x00000000
#define FILE_OPEN                       0x00000001
#define FILE_CREATE                     0x00000002
#define FILE_OPEN_IF                    0x00000003
#define FILE_OVERWRITE                  0x00000004
#define FILE_OVERWRITE_IF               0x00000005
#define FILE_MAXIMUM_DISPOSITION        0x00000005
#define FILE_ALL_ACCESS (STANDARD_RIGHTS_REQUIRED | SYNCHRONIZE | 0x1FF)
#define GENERIC_READ                     (0x80000000L)
#define GENERIC_WRITE                    (0x40000000L)
#define GENERIC_EXECUTE                  (0x20000000L)
#define GENERIC_ALL                      (0x10000000L)

// ntdll functions
NTSTATUS NtDrawText(PUNICODE_STRING Text);
NTSTATUS NtDisplayString(PUNICODE_STRING DisplayString);
NTSTATUS NtDelayExecution(BOOLEAN Alertable, PLARGE_INTEGER DelayInterval);
NTSTATUS NtOpenFile(OUT PHANDLE FileHandle,
                    ACCESS_MASK DesiredAccess,
                    POBJECT_ATTRIBUTES ObjectAttributes,
                    PIO_STATUS_BLOCK IoStatusBlock,
                    ULONG ShareAccess,
                    ULONG OpenOptions);
NTSTATUS NtCreateFile(
    OUT PHANDLE FileHandle,
    ACCESS_MASK DesiredAccess,
    POBJECT_ATTRIBUTES ObjectAttributes,
    PIO_STATUS_BLOCK IoStatusBlock,
    PLARGE_INTEGER AllocationSize,
    ULONG FileAttributes,
    ULONG ShareAccess,
    ULONG CreateDisposition,
    ULONG CreateOptions,
    PVOID EaBuffer,
    ULONG EaLength
);
NTSTATUS NtOpenDirectoryObject(
  _Out_ PHANDLE DirectoryHandle,
  _In_ ACCESS_MASK DesiredAccess,
  _In_ POBJECT_ATTRIBUTES ObjectAttributes
);
NTSTATUS NtCreateEvent(
    OUT PHANDLE EventHandle,
    ACCESS_MASK DesiredAccess,
    POBJECT_ATTRIBUTES ObjectAttributes,
    EVENT_TYPE EventType,
    BOOLEAN InitialState
);
NTSTATUS NtClearEvent(
    IN HANDLE EventHandle
);
NTSTATUS NtReadFile(
    HANDLE FileHandle,
    HANDLE Event,
    PIO_APC_ROUTINE ApcRoutine,
    PVOID ApcContext,
    PIO_STATUS_BLOCK IoStatusBlock,
    PVOID Buffer,
    ULONG Length,
    PLARGE_INTEGER ByteOffset,
    PULONG Key
);
NTSTATUS NtWaitForSingleObject(
    HANDLE Handle,
    BOOLEAN Alertable,
    PLARGE_INTEGER Timeout
);
ULONG NTAPI RtlNtStatusToDosError(
    NTSTATUS Status
);
NTSTATUS NTAPI NtQueryDirectoryFile (
    _In_ HANDLE FileHandle,
    _In_opt_ HANDLE Event,
    _In_opt_ PIO_APC_ROUTINE ApcRoutine,
    _In_opt_ PVOID ApcContext,
    _Out_ PIO_STATUS_BLOCK IoStatusBlock,
    _Out_writes_bytes_(Length) PVOID FileInformation,
    _In_ ULONG Length,
    _In_ UINT32 FileInformationClass,
    _In_ BOOLEAN ReturnSingleEntry,
    _In_opt_ PUNICODE_STRING FileName,
    _In_ BOOLEAN RestartScan
);
NTSTATUS NTAPI NtQueryDirectoryObject (
  _In_ HANDLE DirectoryHandle,
  _Out_opt_ PVOID Buffer,
  _In_ ULONG Length,
  _In_ BOOLEAN ReturnSingleEntry,
  _In_ BOOLEAN RestartScan,
  _Inout_ PULONG Context,
  _Out_opt_ PULONG ReturnLength
);

VOID NtClose(IN HANDLE Handle);
VOID RtlExitUserProcess(NTSTATUS ExitStatus);
VOID NtTerminateProcess(
    IN HANDLE ProcessHandle,
    IN NTSTATUS ExitStatus
);

// structures
#include <ntddkbd.h>

// my utility functions
void NOP_Toy();
int my_vsprintf(char* buffer, const char* format, va_list args);
int my_strcmp(const char* str1, const char* str2);
int my_strncmp(const char* str1, const char* str2, size_t n);
void PutChar(char c);
void native_sleep(unsigned int ms);
int PrintString(char* fmt,...);
char scancode_2_char(UINT16 scancode);
NTSTATUS OpenKeyboard(OUT PHANDLE pKeyboardHandle, IO_STATUS_BLOCK *pIoStatusBlock);
NTSTATUS native_get_keyboard_scancode(HANDLE KeyboardHandle, IO_STATUS_BLOCK *pIoStatusBlock, HANDLE EventHandle, KEYBOARD_INPUT_DATA *pInputData);
NTSTATUS native_get_keyboard_char(HANDLE KeyboardHandle, IO_STATUS_BLOCK *pIoStatusBlock, HANDLE EventHandle, CHAR *c);
NTSTATUS native_get_keyboard_str(HANDLE KeyboardHandle, IO_STATUS_BLOCK *pIoStatusBlock, HANDLE EventHandle, CHAR *buffer, UINT32 bufferSize);
void execute_command(char* command);