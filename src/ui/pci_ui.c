#include "pci_ui.h"

void print_pci_devices_page(WINDOW* main_page, pci_t* pci, int selected_pci_dev)
{
	PAGE("PCI Devices Info");

	pcidev_t pci_dev = pci->devices[selected_pci_dev];

    wattrset(main_page, COLOR_PAIR(25));
    mvwprintw_clr(main_page, 0, 0, "PCI Device (%d/%d)", selected_pci_dev + 1, pci->devices_num);
	wattrset(main_page, COLOR_PAIR(14));
	for (int i = 0; i < MAX_COLS_COUNT; i++) 
		mvwaddch(main_page, 1, i, '=');

	wattrset(main_page, COLOR_PAIR(14));
	mvwprintw_clr(main_page, 3, 1, "Slot: %s", pci_dev.slot_name);
	wattrset(main_page, COLOR_PAIR(15));
	mvwprintw_clr(main_page, 4, 1, "Class: %s", pci_dev.class_name);
	mvwprintw_clr(main_page, 5, 1, "Subclass: %s", pci_dev.subclass_name ? pci_dev.subclass_name : "Not Found");
	mvwprintw_clr(main_page, 6, 1, "Interface: %s", pci_dev.interface_name ? pci_dev.interface_name : "Not Found");
	wattrset(main_page, COLOR_PAIR(19));
	mvwprintw_clr(main_page, 7, 1, "Vendor Name: %s", pci_dev.vendor_name);
	mvwprintw_clr(main_page, 8, 1, "Vendor ID: %s", pci_dev.vendor_id);
	wattrset(main_page, COLOR_PAIR(17));
	mvwprintw_clr(main_page, 9, 1, "Device Name: %s", pci_dev.device_name ? pci_dev.device_name : "Not Found");
	mvwprintw_clr(main_page, 10, 1, "Device ID: %s", pci_dev.device_id);
	wattrset(main_page, COLOR_PAIR(14));
	mvwprintw_clr(main_page, 11, 1, "Modalias: %s", pci_dev.modalias);

	pnoutrefresh(main_page, 0, 0, 1, 1, LINES - 2, COLS - 2);
}