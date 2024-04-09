#include "sys.h"
#include "cpu_utils.h"
#include "../ui/main_ui.h"

#include <cpuid.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/utsname.h>
#include <linux/sysinfo.h>

#define MAIN_UI_FINISHED 0

int main() 
{
    if (start_main_ui() == MAIN_UI_FINISHED)
        return 0;

    return 0;
}
