#ifndef _PCI_UI_H
#define _PCI_UI_H

#include "common_ui.h"
#include "../logic/info/sys.h"

void print_pci_devices_page(WINDOW* main_page, pci_t* pci, int selected_pci_dev);

#endif /* _PCI_UI_H */