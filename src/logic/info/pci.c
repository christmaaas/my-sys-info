#include "pci.h"

#include <stdlib.h>

void init_pci(pci_t** pci)
{
    *pci = (pci_t*)calloc(1, sizeof(pci_t));
    
    init_pci_devices(*pci);
    scan_pci_devices_info(*pci);
}

void free_pci(pci_t* pci)
{
    if (!pci)
        return;
        
    for (uint32_t dev = 0; dev < pci->devices_num; dev++)
    {
        free(pci->devices[dev].class_name);
        free(pci->devices[dev].device_name);
        free(pci->devices[dev].driver_name);
        free(pci->devices[dev].interface_name);
        free(pci->devices[dev].slot_name);
        free(pci->devices[dev].subclass_name);
        free(pci->devices[dev].vendor_name);
    }   
    free(pci->devices);
    free(pci);
}