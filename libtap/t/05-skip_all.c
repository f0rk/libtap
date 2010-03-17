#include <stdio.h>
#include "tap.h"

int main() {
    tap_plan(18);
    
    tap_skip_all("not implemented");
    
    //is/isn't
    tap_is('a','a', "'a' is 'a'");
    tap_is(1, 1, "1 is 1");
    tap_is(4.0, 4.0, "4.0 is 4.0");
    tap_isnt('a', 'b', "'a' isn't 'b'");
    tap_isnt(0, 1, "0 isn't 1");
    tap_isnt(2.0, 4.0, "2.0 isn't 4.0");
    
    //is/isn't str
    tap_is_str("foo", "foo", "\"foo\" is \"foo\"");
    tap_is_str("1", "1", "\"1\" is \"1\"");
    tap_isnt_str("foo", "bar", "\"foo\" isn't \"bar\"");
    tap_isnt_str("0", "1", "\"0\" isn't \"1\"");
    
    //like/unlike
    tap_like("foobar", "foo*", REG_EXTENDED, "\"foobar\" is like \"foo*\"");
    tap_like("foobar", "^foo", REG_EXTENDED, "\"foobar\" is like \"^foo\"");
    tap_like("foobar", "bar$", REG_EXTENDED, "\"foobar\" is like \"bar$\"");
    tap_like("foobar", "fooba[rz]", REG_EXTENDED, "\"foobar\" is like \"fooba[rz]\"");
    tap_unlike("foobar", "foobaz", REG_EXTENDED, "\"foobar\" is unlike \"foobaz\"");
    tap_unlike("foobar", "baz$", REG_EXTENDED, "\"foobar\" is unlike \"baz$\"");
    tap_unlike("foobar", "foo$", REG_EXTENDED, "\"foobar\" is unlike \"foo$\"");
    tap_unlike("foobar", "^foo$", REG_EXTENDED, "\"foobar\" is unlike \"^foo$\"");
    
    return tap_status();
}
