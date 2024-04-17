#include "pci_utils.h"

#include "../../utils/file_utils.h"
#include "../../utils/string_utils.h"

#include <stdlib.h>
#include <dirent.h>
#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>

void init_pci_devices(pci_t* pci)
{
    pci->pci_dev_num = get_count_of_files(PATH_PCI_DEVICES_FILE);
    pci->devices = (pcidev_t*)calloc(pci->pci_dev_num, sizeof(pcidev_t));
}

// To check if current string of pci.ids file is vendor id
bool is_vendor_line(const char* str) 
{
    return isalpha(str[0]) || isdigit(str[0]);
}

void get_pci_vendor_device(pcidev_t* pci_dev, char* vendor, char* device)
{
    FILE* file_ptr = NULL;
    if ((file_ptr = fopen(PATH_PCI_IDS_FILE, "r")) == NULL) 
    {
        perror("Error to open file in \"pci_utils.c\" : get_pci_device_name()");
        return;
    }

    char **device_tokens = NULL, **vendor_tokens = NULL;
    int tokens_num = 0;
    char file_buffer[FILE_BUFFER_SIZE];

    char* file_device = strconcat("\t", device); // in pci.ids vendor id starts with tabulation

    while (fgets(file_buffer, FILE_BUFFER_SIZE, file_ptr)) 
    {
        if (strstr(file_buffer, vendor) != NULL && file_buffer[0] != '\t')
        {
            vendor_tokens = strsplit(file_buffer, "  ", &tokens_num);
            pci_dev->vendor_name = strduplicate(vendor_tokens[1]);
            CUT_STRING_BY_LENGTH(pci_dev->vendor_name);

            while (fgets(file_buffer, FILE_BUFFER_SIZE, file_ptr) && !is_vendor_line(file_buffer))
            {
                if (strstr(file_buffer, file_device) != NULL)
                {
                    device_tokens = strsplit(file_buffer, "  ", &tokens_num);
                    pci_dev->device_name = strduplicate(device_tokens[1]);
                    CUT_STRING_BY_LENGTH(pci_dev->device_name);

                    for (int i = 0; i < tokens_num; ++i)
                    {
                        free(device_tokens[i]);
                        free(vendor_tokens[i]);
                    }
                    free(vendor_tokens);
                    free(device_tokens);
                    free(file_device);

                    return;
                }
            }
        }
    }
    fclose(file_ptr);
}

// pci.ids
// # List of known device classes, subclasses and programming interfaces

// # Syntax:        
// # C class	class_name
// #	subclass	subclass_name  		<-- single tab
// #		prog-if  prog-if_name  	<-- two tabs

#define START_POINT_OF_CLASS_ATTRIBUTES "# List of known device classes, subclasses and programming interfaces"
#define CLASS_NAME_LEVEL_START          'C'

#define CLASS_ATTR_SPLIT_SIZE 2

void get_pci_class_attributes(pcidev_t* pci_dev, char* class)
{
    FILE* file_ptr = NULL;
    if ((file_ptr = fopen(PATH_PCI_IDS_FILE, "r")) == NULL) 
    {
        perror("Error to open file in \"pci_utils.c\" : get_pci_class_attributes()");
        return;
    }

    // split string to 3 strings by 2 chars - pci class attributes  
    char class_name[CLASS_ATTR_SPLIT_SIZE + 1];
    char subclass_name[CLASS_ATTR_SPLIT_SIZE + 1];
    char prog_if_name[CLASS_ATTR_SPLIT_SIZE + 1];
    strncpy(class_name, class, CLASS_ATTR_SPLIT_SIZE);
    class_name[2] = '\0';
    strncpy(subclass_name, class + 2, CLASS_ATTR_SPLIT_SIZE);
    subclass_name[2] = '\0';
    strncpy(prog_if_name, class + 4, CLASS_ATTR_SPLIT_SIZE);
    prog_if_name[2] = '\0';

    char file_buffer[FILE_BUFFER_SIZE];
    while (fgets(file_buffer, FILE_BUFFER_SIZE, file_ptr)) 
    {
        if (strstr(file_buffer, START_POINT_OF_CLASS_ATTRIBUTES) != NULL) 
            break;
    }

    char **class_tokens = NULL, **subclass_tokens = NULL, **prog_if_tokens = NULL;
    int tokens_num = 0;
    
    char* file_subclass = strconcat("\t", subclass_name); // in pci.ids sublcass line starts with tabulation
    char* file_prog_if = strconcat("\t\t", prog_if_name); // in pci.ids intf line starts with double tabulation

    while (fgets(file_buffer, FILE_BUFFER_SIZE, file_ptr)) 
    {
        if (strstr(file_buffer, class_name) != NULL && file_buffer[0] == CLASS_NAME_LEVEL_START) // class name line started with 'C'
        {
            class_tokens = strsplit(file_buffer, "  ", &tokens_num);
            pci_dev->class_name = strduplicate(class_tokens[1]);
            CUT_STRING_BY_LENGTH(pci_dev->class_name);

            while (fgets(file_buffer, FILE_BUFFER_SIZE, file_ptr) && file_buffer[0] == '\t')
            {
                if (strstr(file_buffer, file_subclass) != NULL && file_buffer[1] != '\t')
                {
                    subclass_tokens = strsplit(file_buffer, "  ", &tokens_num);
                    pci_dev->subclass_name = strduplicate(subclass_tokens[1]);
                    CUT_STRING_BY_LENGTH(pci_dev->subclass_name);

                    while (fgets(file_buffer, FILE_BUFFER_SIZE, file_ptr) && file_buffer[0] == '\t' && file_buffer[1] == '\t')
                    {
                        if (strstr(file_buffer, file_prog_if) != NULL)
                        {
                            prog_if_tokens = strsplit(file_buffer, "  ", &tokens_num);
                            pci_dev->interface_name = strduplicate(prog_if_tokens[1]);
                            CUT_STRING_BY_LENGTH(pci_dev->interface_name);

                            for (int i = 0; i < tokens_num; ++i)
                            {
                                free(class_tokens[i]);
                                free(subclass_tokens[i]);
                                free(prog_if_tokens[i]);
                            }
                            free(class_tokens);
                            free(subclass_tokens);
                            free(prog_if_tokens);
                            free(file_subclass);
                            free(file_prog_if);

                            return;
                        }
                    }
                    for (int i = 0; i < tokens_num; ++i)
                    {
                        free(class_tokens[i]);
                        free(subclass_tokens[i]);
                    }
                    free(class_tokens);
                    free(subclass_tokens);
                    free(file_subclass);
                    free(file_prog_if);
                    
                    return;
                }
            }
        }
    }
    fclose(file_ptr);
}

#define HEX_PREFIX_LEN 2

char* get_file_without_hex_prefix(const char* path) 
{
    char* content = get_file(path);

    size_t content_length = strlen(content);

    char* new_str = (char*)malloc((content_length - HEX_PREFIX_LEN + 1) * sizeof(char));
    strncpy(new_str, content + HEX_PREFIX_LEN, content_length - HEX_PREFIX_LEN);
    new_str[content_length - HEX_PREFIX_LEN] = '\0';

    free(content);
    return new_str;
}

void scan_pci_devices_info(pci_t* pci)
{
    DIR* dir = opendir(PATH_PCI_DEVICES_FILE);
    if (dir == NULL) 
    {
        perror("Error to open directory in \"pci_utils.c\" : scan_pci_devices_info()");
        return;
    }

    char* class = NULL;
    char cur_file_name[MAX_FILE_PATH_LEN];
    uint32_t count = 0;
    struct dirent* entry;
    while ((entry = readdir(dir)) != NULL && count != pci->pci_dev_num)
    {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
            continue;

        pci->devices[count].slot_name = strduplicate(entry->d_name);

        snprintf(cur_file_name, MAX_FILE_PATH_LEN, "/sys/bus/pci/devices/%s/%s", entry->d_name, "vendor");
        pci->devices[count].vendor_id = get_file_without_hex_prefix(cur_file_name);

        snprintf(cur_file_name, MAX_FILE_PATH_LEN, "/sys/bus/pci/devices/%s/%s", entry->d_name, "device");
        pci->devices[count].device_id = get_file_without_hex_prefix(cur_file_name);

        get_pci_vendor_device(&(pci->devices[count]), pci->devices[count].vendor_id, pci->devices[count].device_id);

        snprintf(cur_file_name, MAX_FILE_PATH_LEN, "/sys/bus/pci/devices/%s/%s", entry->d_name, "class");
        class = get_file_without_hex_prefix(cur_file_name);
        get_pci_class_attributes(&(pci->devices[count]), class); 

        snprintf(cur_file_name, MAX_FILE_PATH_LEN, "/sys/bus/pci/devices/%s/%s", entry->d_name, "modalias");
        pci->devices[count].modalias = get_file(cur_file_name);

        count++;
    }
    closedir(dir);
}