#include "pci_ui.h"

void print_pci_devices_page(WINDOW* main_page, pci_t* pci, const int pci_dev_id)
{
	PAGE_TITLE("PCI Devices Info");

	pcidev_t pci_dev = pci->devices[pci_dev_id];

    wattrset(main_page, COLOR_PAIR(PAIR_WHITE_BLUE));
    mvwprintw_clr(main_page, 0, 0, "PCI Device %s (%d/%d)", pci_dev.device_location, pci_dev_id + 1, pci->devices_num);

	wattrset(main_page, COLOR_PAIR(PAIR_BLUE_WHITE));
	for (int i = 0; i < MAX_COLS_COUNT; i++) 
		mvwaddch(main_page, 1, i, '=');

	wattrset(main_page, COLOR_PAIR(PAIR_BLUE_WHITE));
	wattron(main_page, A_BOLD);
	mvwprintw_clr(main_page, 3, 1, "Domain:   %04x", pci_dev.domain);
	mvwprintw_clr(main_page, 4, 1, "Bus:      %02x", pci_dev.bus);
	mvwprintw_clr(main_page, 5, 1, "Device:   %02x", pci_dev.device);
	mvwprintw_clr(main_page, 6, 1, "Function: %x", pci_dev.function);
	wattroff(main_page, A_BOLD);

	wattrset(main_page, COLOR_PAIR(PAIR_BLACK_WHITE));
	mvwprintw_clr(main_page, 8, 1, "Class:     %s", pci_dev.class_name);
	mvwprintw_clr(main_page, 9, 1, "Subclass:  %s", pci_dev.subclass_name ? pci_dev.subclass_name : "Not Found");
	mvwprintw_clr(main_page, 10, 1, "Interface: %s", pci_dev.interface_name ? pci_dev.interface_name : "Not Found");
	
	wattrset(main_page, COLOR_PAIR(PAIR_RED_WHITE));
	mvwprintw_clr(main_page, 12, 1, "Vendor Name: %s", pci_dev.vendor_name);
	mvwprintw_clr(main_page, 13, 1, "Vendor ID:   %04x", pci_dev.vendor_id);
	mvwprintw_clr(main_page, 15, 1, "Device Name: %s", pci_dev.device_name ? pci_dev.device_name : "Not Found");
	mvwprintw_clr(main_page, 16, 1, "Device ID:   %04x", pci_dev.device_id);

	wattrset(main_page, COLOR_PAIR(PAIR_BLUE_WHITE));
	mvwprintw_clr(main_page, 18, 1, "Driver:   %s", pci_dev.driver_name);
	mvwprintw_clr(main_page, 20, 1, "Revision: %02x", pci_dev.revision);

	pnoutrefresh(main_page, 0, 0, 1, 1, LINES - 2, COLS - 2);
}