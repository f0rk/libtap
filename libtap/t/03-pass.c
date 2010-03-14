#include <stdio.h>
#include "tap.h"

int main() {
    tap_plan(4);
    
    tap_pass("passing a test");
    tap_pass("passing another test");
    tap_pass("passing a third test");
    tap_pass("passing the last test");
    
    return tap_status();
}
