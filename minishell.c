#include "utils.h"

void list_dir(char *ascii_path);
void list_dev(char *ascii_path);
void create_process(char *ascii_path);

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
    else if (my_strncmp(command, "LISTDIR ", 8) == 0)
    {
        printf("Listing directory contents: %s\n", command + 8);
        list_dir(command + 8);
    }
    else if (my_strncmp(command, "LISTDEV ", 8) == 0)
    {
        printf("Listing device contents: %s\n", command + 8);
        list_dev(command + 8);
    }
    else if (my_strncmp(command, "RUN ", 4) == 0)
    {
        printf("Creating process: %s\n", command + 4);
        create_process(command + 4);
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