#ifndef _PCI_H
#define _PCI_H

#include "pci_utils.h"

void init_pci(pci_t** pci);
void free_pci(pci_t* pci);

#endif /* _PCI_H */