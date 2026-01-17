#include "utils.h"

void list_dir_demo();

void execute_command(char* command)
{
    if (my_strcmp(command, "HI") == 0)
    {
        printf("Hello, Native World!\n");
    }
    else if (my_strcmp(command, "SLEEP") == 0)
    {
        printf("Sleeping for 2 seconds...\n");
        native_sleep(2000);
        printf("Awake!\n");
    }
    else if (my_strcmp(command, "LISTDIR") == 0)
    {
        printf("Listing directory contents:\n");
        list_dir_demo();
    }
    else if(my_strcmp(command, "EXIT") == 0)
    {
        printf("Exiting...\n");
        RtlExitUserProcess(0);
    }
    else
    {
        printf("Unknown command: %s\n", command);
    }
}