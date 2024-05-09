#include "opt_utils.h"

#include <stdio.h>

void print_opt_help()
{
    printf("MySysInfo is a program that collects and displays system data and resources.\n");
	printf("Users can monitor and analyze processor workload, memory, and network load.\n");
	printf("It operates in the terminal, providing detailed information about the system.\n");
	printf("Dynamic graphs and visualization tools are used to present the information.\n\n");
	printf("Here are the options:\n");
    printf("  '0' - Prints help page that contains all options and general system information like OS version and hostname.\n");
    printf("  '1' - Prints CPU information ('<' - prev | '>' - next)");
	printf("  '2' - Prints CPU load versus time graph\n");
	printf("  '3' - Prints CPU each load versus time graph\n");
	printf("  '4' - Prints memory information and memory load versus time diagramms\n");
    printf("  '5' - Prints memory & swap load versus time graph\n");
    printf("  '6' - Prints network interfaces information and network load versus time graph ('<' - prev | '>' - next)\n");
	printf("  '7' - Generates a report of current collected data by the programm in a txt file\n");
    printf("  '8' - Prints PCI devices information ('<' - prev | '>' - next)\n");
	printf("  '9' - Prints temperature sensors information and temperature load versus time diagramms\n");
	printf("  't' - Set time interval of screen refreshes\n");
	printf("  'q' - Quit\n\n");
	printf("@Made by Artem Slinko. 2024\n");
}