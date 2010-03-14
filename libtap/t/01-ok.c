#include <stdio.h>
#include "tap.h"

int main() {
    tap_plan(2);
    
    tap_ok(1==1, "1==1");
    tap_ok(4.0==4.0, "4.0==4.0");
    
    return tap_status();
}
