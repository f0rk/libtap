#include <stdio.h>
#include "tap.h"

int main() {
    tap_plan(18);
    
    tap_ok(1, "1");
    tap_ok(1==1, "1==1");
    tap_ok(4.0==4.0, "4.0==4.0");
    tap_ok(1!=2, "1!=2");
    tap_ok('a'=='a', "'a'=='a'");
    tap_not_ok(0, "0");
    tap_not_ok(1==2, "1==2");
    tap_not_ok(2.0==4.0, "2.0==4.0");
    tap_not_ok('a'=='b', "'a'=='b'");
    
    return tap_status();
}
