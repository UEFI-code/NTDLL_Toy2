#include "utils.h"
#include <stdio.h>
//#include <ntifs.h>

#define FILE_LIST_DIRECTORY       ( 0x0001 )    // directory
#define FILE_ATTRIBUTE_DIRECTORY            0x00000010
#define FILE_SHARE_READ                 0x00000001
#define FILE_SHARE_WRITE                0x00000002
#define FILE_DIRECTORY_FILE             0x00000001
#define FILE_SYNCHRONOUS_IO_NONALERT    0x00000020
#define FileDirectoryInformation        0x00000001

typedef struct _FILE_DIRECTORY_INFORMATION {
    ULONG         NextEntryOffset;
    ULONG         FileIndex;
    LARGE_INTEGER CreationTime;
    LARGE_INTEGER LastAccessTime;
    LARGE_INTEGER LastWriteTime;
    LARGE_INTEGER ChangeTime;
    LARGE_INTEGER EndOfFile;
    LARGE_INTEGER AllocationSize;
    ULONG         FileAttributes;
    ULONG         FileNameLength;
    WCHAR         FileName[1];
} FILE_DIRECTORY_INFORMATION, * PFILE_DIRECTORY_INFORMATION;

FILE_DIRECTORY_INFORMATION dir_info_buf[128];

void list_dir(char *ascii_path)
{
    ANSI_STRING AnsiString;
    RtlInitAnsiString(&AnsiString, ascii_path);
    UNICODE_STRING dir;
    RtlAnsiStringToUnicodeString(&dir, &AnsiString, TRUE);

    OBJECT_ATTRIBUTES oa;
    InitializeObjectAttributes(
        &oa,
        &dir,
        OBJ_CASE_INSENSITIVE,
        NULL,
        NULL
    );

    HANDLE hDir;
    IO_STATUS_BLOCK iosb;
    NTSTATUS status = NtCreateFile(
        &hDir,
        FILE_LIST_DIRECTORY | SYNCHRONIZE,
        &oa,
        &iosb,
        NULL,
        FILE_ATTRIBUTE_DIRECTORY,
        FILE_SHARE_READ | FILE_SHARE_WRITE,
        FILE_OPEN,
        FILE_DIRECTORY_FILE | FILE_SYNCHRONOUS_IO_NONALERT,
        NULL,
        0
    );
    if (!NT_SUCCESS(status))
    {
        printf("NtCreateFile failed: 0x%X\n", RtlNtStatusToDosError(status));
        return;
    }

    status = NtQueryDirectoryFile(
        hDir,
        NULL,
        NULL,
        NULL,
        &iosb,
        dir_info_buf,
        sizeof(dir_info_buf),
        FileDirectoryInformation,
        FALSE,
        NULL,
        TRUE
    );
    if (status == STATUS_NO_MORE_FILES)
    {
        printf("STATUS_NO_MORE_FILES\n");
        NtClose(hDir);
        return;
    }

    PFILE_DIRECTORY_INFORMATION info = dir_info_buf;
    while (1)
    {
        wprintf(
            L"AccessTime: %X, Size: %X, Attr: %X, Name: %.*s\n",
            (UINT64)info->LastAccessTime.QuadPart,
            (UINT64)info->EndOfFile.QuadPart,
            info->FileAttributes,
            info->FileNameLength / 2,
            info->FileName
        );
        if (info->NextEntryOffset == 0)
            break;
        info = (PFILE_DIRECTORY_INFORMATION)((UINT8 *)info + info->NextEntryOffset);
    }

    NtClose(hDir);
}