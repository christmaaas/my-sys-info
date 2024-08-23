#ifndef _PCI_UI_H
#define _PCI_UI_H

#include "common.h"

#include "../logic/info/sys.h"

void print_pci_devices_page(WINDOW* main_page, pci_t* pci, const int pci_dev_id);

#endif /* _PCI_UI_H */