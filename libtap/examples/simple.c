#include <tap.h>
  
int main() {
    tap_plan(11);

    tap_ok(1==1, "1==1");
    tap_not_ok(1==2, "1==2");

    tap_is(1, 1, "1 is 1");
    tap_is('a', 'a', "'a' is 'a'");
    tap_is(4.0, 4.0, "4.0 is 4.0");
    tap_isnt(1, 2, "1 isn't 2");
    tap_isnt('a', 'b', "'a' isn't 'b'");
    tap_isnt(2.0, 4.0, "2.0 isn't 4.0");

    tap_like("foobar", "^foo", REG_EXTENDED, "\"foobar\" is like \"^foo\"");
    tap_unlike("foobar", "foo$", REG_EXTENDED, "\"foobar\" is unlike \"foo$\"");

    tap_pass("just passing");
    
    return tap_status();
}
