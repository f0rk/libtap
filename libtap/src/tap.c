#include <stdio.h>
#include <string.h>
#include <regex.h>
#include <limits.h>
#include <stdlib.h>
#include "tap.h"

//general test info
int tap_test_planned = INT_MAX;
int tap_test_failures = 0;
int tap_test_total = 0;
int tap_plan_is_printed = 0;

//skip/todo
int tap_do_skip = 0;
char *tap_skip_message = "";
int tap_do_todo = 0;
char *tap_todo_message = "";

/* setup */
int tap_plan(int num_tests) {
    //you already told me how many
    //tests you planned.
    //are you some kind of liar?
    if(tap_test_planned != INT_MAX) {
        return -1;
    }
    
    //well this is embarassing, you
    //aren't smart enough to set your
    //tests up properly
    if(num_tests < 0) {
        tap_test_planned = 0;
        return 0;
    }
    
    //we've got a rocket scientist
    //with us, folks
    tap_test_planned = num_tests;
    return tap_test_planned;
}

/* comparisons */
int tap_ok(int boolean, char *message) {
    //have we begun?
    if(tap_plan_is_printed == 0 && tap_test_planned != INT_MAX) { //if int max, printing plan at end
        printf("1..%d\n", tap_test_planned);
        tap_plan_is_printed = 1;
    }
    
    //another day, another test
    ++tap_test_total;
    
    //huzzah!
    if(boolean) {
        if(tap_do_skip) {
            printf("%s %d # SKIP %s\n", "ok", tap_test_total, tap_skip_message);
            --tap_do_skip;
            return TAP_TSUCCESS;
        }
        
        if(tap_do_todo) {
            printf("%s %d # TODO %s\n", "ok", tap_test_total, tap_todo_message);
            --tap_do_todo;
            return TAP_TSUCCESS;
        }
        
        printf("%s %d %s\n", "ok", tap_test_total, message == 0 ? "" : message);
        return TAP_TSUCCESS;
    }
    
    //epic failure(s)
    ++tap_test_failures;
    
    //skipping anyway
    if(tap_do_skip) {
        printf("%s %d # SKIP %s\n", "not ok", tap_test_total, tap_skip_message);
        --tap_do_skip;
        return TAP_TFAIL;
    }
    
    //probably too lazy to get our act together
    if(tap_do_todo) {
        printf("%s %d # TODO %s\n", "not ok", tap_test_total, tap_todo_message);
        --tap_do_todo;
        return TAP_TFAIL;
    }
    
    //d'oh!
    printf("%s %d %s\n", "not ok", tap_test_total, message == 0 ? "" : message);
    return TAP_TFAIL;
}

int tap_not_ok(int boolean, char *message) {
    return tap_ok(!boolean, message);
}

int tap_is_str(char *lval, char *rval, char *message) {
    return tap_ok(!strcmp(lval, rval), message);
}

int tap_isnt_str(char *lval, char *rval, char *message) {
    return tap_ok(strcmp(lval, rval), message);
}

int tap_like(char *val, char *regex, int flags, char *message) {
    int res;
    regex_t re;
    res = regcomp(&re, regex, flags);
    if(res != 0) { //bad pattern, so it matches nothing(?)
        return tap_ok(0, message);
    }
    
    res = regexec(&re, val, 0, 0, 0);
    regfree(&re);
    
    if(res != 0) {
        return tap_ok(0, message);
    }
    
    return tap_ok(1, message);
}

int tap_unlike(char *val, char *regex, int flags, char *message) {
    int res;
    regex_t re;
    res = regcomp(&re, regex, flags);
    if(res != 0) { //bad pattern, so it matches nothing(?)
        return tap_ok(1, message);
    }
    
    res = regexec(&re, val, 0, 0, 0);
    regfree(&re);
    
    if(res != 0) {
        return tap_ok(1, message);
    }
    
    return tap_ok(0, message);
}

int tap_pass(char *message) {
    return tap_ok(1, message);
}

int tap_fail(char *message) {
    return tap_ok(0, message);
}

int tap_bail(char *message) {
    printf("Bail out! %s\n", message == 0 ? "" : message);
    exit(255); //TAP_DIED
}

int tap_skip(int number, char *message) {
    if(number < 0) {
        tap_do_skip = 0;
        return 0;
    }
    
    tap_do_skip = number;
    if(message == 0) {
        message = "";
    }
    tap_skip_message = message;
    
    return tap_do_skip;
}

int tap_skip_all(char *message) {
    if(message == 0) {
        message = "";
    }
    
    if(!tap_plan_is_printed) {
        printf("1..0 # SKIP %s\n", message);
        exit(0); //TAP_SUCCESS
    }
    
    tap_do_skip = INT_MAX;
    tap_skip_message = message;
    
    return tap_do_skip;
}

int tap_todo(int number, char *message) {
    if(number < 0) {
        tap_do_todo = 0;
        return 0;
    }
    
    tap_do_todo = number;
    if(message == 0) {
        message = "";
    }
    tap_todo_message = message;
    
    return tap_do_todo;
}

int tap_done() {
    if(!tap_plan_is_printed) {
        printf("1..%d\n", tap_test_total);
        tap_plan_is_printed = 1;
        return 1;
    }
    
    return 0;
}

int tap_status() {
    if(tap_test_total != tap_test_planned) {
        if(tap_test_planned == 1) {
            printf("# It looks like you planned %d test but ran %d.", tap_test_planned, tap_test_total);
        } else {
            printf("# It looks like you planned %d tests but ran %d.", tap_test_planned, tap_test_total);
        }
    }
    
    if(tap_plan_is_printed == 0) {
        if(tap_test_planned == INT_MAX) {
            printf("1..%d\n", tap_test_total);
        } else {
            printf("1..%d\n", tap_test_planned);
        }
        tap_plan_is_printed = 1;
    }
    
    if(tap_test_failures > 0) {
        return tap_test_failures > 254 ? 254 : tap_test_failures;
    }
    
    //all the other interesting codes
    //will exit on their own
    return TAP_SUCCESS;
}
