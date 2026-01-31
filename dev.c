#include "utils.h"
#include <stdio.h>
//#include <ntifs.h>

#define DIRECTORY_QUERY 0x0001

typedef struct _OBJECT_DIRECTORY_INFORMATION {
    UNICODE_STRING Name;
    UNICODE_STRING TypeName;
} OBJECT_DIRECTORY_INFORMATION, *POBJECT_DIRECTORY_INFORMATION;

OBJECT_DIRECTORY_INFORMATION dir_info_buf[512];

void list_dev(char *ascii_path)
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
    NTSTATUS status = NtOpenDirectoryObject(
        &hDir,
        DIRECTORY_QUERY,
        &oa
    );
    if (!NT_SUCCESS(status))
    {
        printf("NtOpenDirectoryObject failed: 0x%X\n", RtlNtStatusToDosError(status));
        return;
    }
    
    ULONG context = 0;
    ULONG retLen;
    status = NtQueryDirectoryObject(
        hDir,
        dir_info_buf,
        sizeof(dir_info_buf),
        FALSE,
        FALSE,
        &context,
        &retLen
    );
    if (!NT_SUCCESS(status))
    {
        printf("NtQueryDirectoryObject failed: 0x%X\n", RtlNtStatusToDosError(status));
        NtClose(hDir);
        return;
    }

    POBJECT_DIRECTORY_INFORMATION info = dir_info_buf;
    while (info->Name.Buffer)
    {
        wprintf(
            L"Name: %wZ, Type: %wZ\n",
            &info->Name,
            &info->TypeName
        );
        info++;
    }

    NtClose(hDir);
}