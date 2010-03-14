#define TAP_SUCCESS 0;
#define TAP_DIED 255;
#define TAP_WRONG 255;
#define TAP_TSUCCESS 1;
#define TAP_TFAIL 0;

/* setup */
int tap_plan(int num_tests);

/* comparisons */
int tap_ok(int boolean, char *message);
int tap_not_ok(int boolean,  char *message);
#define tap_is(A,B,C) tap_ok(A==B,C)
#define tap_isnt(A,B,C) tap_ok(A!=B,C)
int tap_is_str(char *lval, char *rval,  char *message);
int tap_isnt_str(char *lval, char *rval,  char *message);
int tap_like(char *val, char *regex,  char *message, int flags);
int tap_unlike(char *val, char *regex,  char *message, int flags);

/* test control */
int tap_pass(char *message);
int tap_fail(char *message);
int tap_bail(char *message);
int tap_skip(int number, char *message);
int tap_skip_all(char *message);
int tap_todo(int number, char *message);
int tap_todo_all(char *message);
int tap_done();

/* finish */
int tap_status();
