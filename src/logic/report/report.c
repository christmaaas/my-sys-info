#include "report.h"

#include <stdio.h>
#include <string.h>
#include <time.h>

#define MAX_REPORT_NAME_SIZE 100

void make_system_report(system_t* data)
{
    time_t current_time     = time(NULL);
    struct tm* current_date = localtime(&current_time);

    char report_name[MAX_REPORT_NAME_SIZE];
    sprintf(report_name, "../../../resources/MySysInfo Report [%02d-%02d-%04d %02d:%02d:%02d]",
            current_date->tm_mday, current_date->tm_mon + 1, current_date->tm_year + 1900,
            current_date->tm_hour, current_date->tm_min, current_date->tm_sec);

    FILE* file_ptr = NULL;

    if ((file_ptr = fopen(report_name, "w")) == NULL) 
    {
        perror("Error to open file in \"report.c\" : make_system_report()");
        return;
    }

    fclose(file_ptr);
}

