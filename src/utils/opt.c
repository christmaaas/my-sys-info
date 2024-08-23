#include "opt.h"

#include <stdio.h>

void print_opt_help()
{
    printf("MySysInfo is a program that collects and displays system data and resources.\n");
	printf("Users can monitor and analyze processor workload, memory, and network load.\n");
	printf("It operates in the terminal, providing detailed information about the system.\n");
	printf("Dynamic graphs and visualization tools are used to present the information.\n\n");
	printf("Here are the options:\n");
	printf("  'm' - Selection Menu. Menu does next options:\n");
    printf("   - 1. Prints help page that contains all options and general system information like OS version and hostname.\n");
    printf("   - 2. Prints CPU information ('<' - prev | '>' - next)\n");
	printf("   - 3. Prints CPU load versus time graph\n");
	printf("   - 4. Set time interval of screen refreshes\n");
	printf("   - 5. Prints CPU each load versus time graph\n");
	printf("   - 6. Prints memory information and memory load versus time diagramms\n");
    printf("   - 7. Prints memory & swap load versus time graph\n");
    printf("   - 8. Prints network interfaces information and network load versus time graph ('<' - prev | '>' - next)\n");
	printf("   - 9. Generates a report of current collected data by the programm in a txt file\n");
    printf("   - 10.Prints PCI devices information ('<' - prev | '>' - next)\n");
	printf("   - 11.Prints temperature sensors information and temperature load versus time diagramms\n");
	printf("  'q' - Quit from MySysInfo\n\n");
	printf("@Made by Artem Slinko. 2024\n");
}