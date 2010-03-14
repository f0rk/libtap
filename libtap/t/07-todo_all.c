#include <stdio.h>
#include "tap.h"

int main() {
    tap_plan(18);
    
    tap_todo_all("not implemented");
    
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
    tap_like("foobar", "foo*", "\"foobar\" is like \"foo*\"", REG_EXTENDED);
    tap_like("foobar", "^foo", "\"foobar\" is like \"^foo\"", REG_EXTENDED);
    tap_like("foobar", "bar$", "\"foobar\" is like \"bar$\"", REG_EXTENDED);
    tap_like("foobar", "fooba[rz]", "\"foobar\" is like \"fooba[rz]\"", REG_EXTENDED);
    tap_unlike("foobar", "foobaz", "\"foobar\" is unlike \"foobaz\"", REG_EXTENDED);
    tap_unlike("foobar", "baz$", "\"foobar\" is unlike \"baz$\"", REG_EXTENDED);
    tap_unlike("foobar", "foo$", "\"foobar\" is unlike \"foo$\"", REG_EXTENDED);
    tap_unlike("foobar", "^foo$", "\"foobar\" is unlike \"^foo$\"", REG_EXTENDED);
    
    return tap_status();
}
