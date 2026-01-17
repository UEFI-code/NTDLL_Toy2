# include "utils.h"
void execute_command(char* command)
{
    if (strcmp(command, "SLEEP") == 0)
    {
        printf("Sleeping for 2 seconds...\n");
        native_sleep(2000);
        printf("Awake!\n");
    }
    else if(strcmp(command, "EXIT") == 0)
    {
        printf("Exiting...\n");
        RtlExitUserProcess(0);
    }
    else
    {
        printf("Unknown command: %s\n", command);
    }
}