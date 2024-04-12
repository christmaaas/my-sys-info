#include "logic/info/sys.h"
#include "logic/info/cpu_utils.h"
#include "ui/main_ui.h"
#include "logic/report/report.h"

#include <cpuid.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/utsname.h>
#include <linux/sysinfo.h>

#define MAIN_UI_FINISHED 0

int main() 
{
    make_system_report(NULL);

    if (start_main_ui() == MAIN_UI_FINISHED)
        return 0;

    return 0;
}
