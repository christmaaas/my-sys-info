#include <cpuid.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/utsname.h>
#include <linux/sysinfo.h>

#include "sys.h"
#include "cpu_utils.h"
#include "../ui/main_ui.h"

int main() 
{
    if (main_window() == 0)
        return 0;

    return 0;
}
