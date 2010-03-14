#include <stdio.h>
#include "tap.h"

int main() {
    tap_plan(0);
    
    return tap_status();
}
