#include "opt_utils.h"

#include <stdio.h>

void print_opt_help()
{
    printf("MySysInfo is a program that collects and displays system data and resources.\n");
	printf("Users can monitor and analyze processor workload, memory, and network load.\n");
	printf("It operates in the terminal, providing detailed information about the system.\n");
	printf("Dynamic graphs and visualization tools are used to present the information.\n\n");
	printf("Here are the options:\n");
    printf("  'h' - Prints help page that contains all options and general system information like OS version and hostname.\n");
	printf("  'r' - Generates a report of current collected data by the programm in a txt file\n");
	printf("  'l' - Prints CPU cores load versus time graph\n");
    printf("  'n' - Prints network interfaces information and network load versus time graph ('<' - prev | '>' - next)\n");
	printf("  'm' - Prints memory information and memory load versus time diagramms\n");
    printf("  'M' - Prints memory & swap load versus time graph\n");
	printf("  's' - Prints temperature sensors information and temperature load versus time diagramms\n");
    printf("  'p' - Prints PCI devices information ('<' - prev | '>' - next)\n");
	printf("  'C' - Prints CPU load versus time graph\n");
    printf("  'c' - Prints CPU information ('<' - prev | '>' - next)");
	printf("  't' - Set time interval of screen refreshes\n");
	printf("  'q' - Quit\n\n");
	printf("@Made by Artem Slinko. 2024\n");
}