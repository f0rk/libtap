[[meta title="libtap"]]

# NAME

libtap

# VERSION

0.15

# SYNOPSIS

  #include <stdio.h>
  #include <tap.h>
  

  int main() {
      tap_plan(16);
      

      tap_ok(1==1, "1==1");
      tap_not_ok(1==2, "1==2");
      

      tap_is(1, 1, "1 is 1");
      tap_is('a', 'a', "'a' is 'a'");
      tap_is(4.0, 4.0, "4.0 is 4.0");
      tap_isnt(1, 2, "1 isn't 2");
      tap_isnt('a', 'b', "'a' isn't 'b'");
      tap_isnt(2.0, 4.0, "2.0 isn't 4.0");
      

      tap_like("foobar", "^foo", "\"foobar\" is like \"^foo\"", REG_EXTENDED);
      tap_unlike("foobar", "foo$", "\"foobar\" is unlike \"foo$\"", REG_EXTENDED);
      

      tap_pass("just passing");
      

      return tap_status();
  }

# DESCRIPTION

libtap is a C library for producing TAP-compliant output from
compiled C executables. It can then be used with the Perl module
TAP::Harness (with exec => []) to validate the TAP output, providing
easy testing capabilities to C projects.

# Using libtap

libtap need not be installed before use. You may of course copy the
necessary files (tap.c and tap.h) into the same directory as your
project and build directly against them. If libtap is installed,
simply 
  #include <tap.h>
and you'll be ready to go.

## #include

Including libtap in your project (as shown above) will make available
all necessary functions, macros, and definitions to run your tests.
libtap `include`s <regex.h> for tap_like and tap_unlike, and makes
those functions available as well.

## Your first test

A basic test will look like the following:

  #include <tap.h>
  

  int main() {
      tap_plan(1);
      

      tap_ok(1==1, "1==1");
      

      return tap_status();
  }

`tap_plan` takes one argument, an int describing the number of tests
you plan to run. This is not required, but strongly recommended. You
should always have a test plan, in case your tests unknowlingly die
in the middle of their run. `main` should `return tap_status()`, as
the return code signals to TAP::Harness the result of the test. In between
`tap_plan` and `tap_status`, should be your tests, which are described
below in L<Comparison methods>.

## Comparison methods

libtap provides 6 comparison methods, and two comparison macros. They are as follows:

  int tap_ok(int boolean, char *message);
  int tap_not_ok(int boolean, char *message);
  #define tap_is(A,B,C) tap_ok(A==B,C)
  #define tap_isnt(A,B,C) tap_ok(A!=B,C)
  int tap_is_str(char *lval, char *rval, char *message);
  int tap_isnt_str(char *lval, char *rval, char *message);
  int tap_like(char *val, char *regex, char *message, int flags);
  int tap_unlike(char *val, char *regex, char *message, int flags);

All of these methods require a message, which will be printed as a
diagnostic along with the test result (`ok` or `not ok`). In the case of the
macros, A and B are two C primitive types (which will be compared using `==`
or `!=`) and C is the message to be printed. Using any of these counts as a
test (including the macros), so make sure this is reflected in your plan.

## Control methods

libtap provides 8 control methods. They are as follows:

  int tap_pass(char *message);
  int tap_fail(char *message);
  int tap_bail(char *message);
  int tap_skip(int number, char *message);
  int tap_skip_all(char *message);
  int tap_todo(int number, char *message);
  int tap_todo_all(char *message);
  int tap_done();

These are used to produce passing, failing, skip, todo, and bail
conditions. `tap_done` is used to signal that we have finished testing,
and is only necessary in the event that there is no test plan.

# METHODS

## tap_plan

__Signature:__ int tap_plan(int num_tests)

`tap_plan` takes a single argument, the number of tests you plan to run.
It returns the number of tests that have been planned.

## tap_ok

__Signature:__ int tap_ok(int boolean, char *message)

`tap_ok` takes two arguments, a boolean indicating a successful test,
and a status message for that test.

## tap_not_ok

__Signature:__ int tap_not_ok(int boolean, char *message)

`tap_not_ok` takes two arguments, a boolean indicating an unsuccessful test,
and a status message for that test.

## tap_is

__Signature:__ #define tap_is(A,B,C) tap_ok(A==B,C)

`tap_is` takes three arguments, a C primitive value (`A`), a C primitive value that
`A` should be equal to (`B`), and a status message for that test (`C`).

## tap_isnt

__Signature:__ #define tap_isnt(A,B,C) tap_ok(A!=B,C)

`tap_is` takes three arguments, a C primitive value (`A`), a C primitive value that
`A` should not be equal to (`B`), and a status message for that test (`C`).

## tap_is_str

__Signature:__ int tap_is_str(char *lval, char *rval, char *message)

`tap_is_str` takes three arguments, a C string (`lval`), another C string (`rval`)
that `lval` should be equal to, and a status message for that test.

## tap_isnt_str

__Signature:__ int tap_isnt_str(char *lval, char *rval, char *message)

`tap_isnt_str` takes three arguments, a C string (`lval`), another C string (`rval`)
that `lval` should not be equal to, and a status message for that test.

## tap_like

__Signature:__ int tap_like(char *val, char *regex, char *message, int flags)

`tap_like` takes four arguments, a C string, a C string representing a regular expression that should match the provided string,
a status message for that test, and the appropriate flags for that regular expression, as
found in `regex.h`. See also `man regex`.

## tap_unlike

__Signature:__ int tap_unlike(char *val, char *regex, char *message, int flags)

`tap_unlike` takes four arguments, a C string, a C string representing a regular expression that shouldn't match the provided string,
a status message for that test, and the appropriate flags for that regular expression, as
found in `regex.h`. See also `man regex`.

## tap_pass

__Signature:__ int tap_pass(char *message)

`tap_pass` takes a single argument, a status message, and generates a passing test.

## tap_fail

__Signature:__ int tap_fail(char *message)

`tap_fail` takes a single argument, a status message, and generates a failing test.

## tap_bail

__Signature:__ int tap_bail(char *message)

`tap_bail` takes a single argument, a status message, and causes the testing program to bail out.

## tap_skip

__Signature:__ int tap_skip(int number, char *message)

`tap_skip` takes two arguments, the number of tests to skip, and a skipped reason message. libtap
will then skip the given number of tests.

## tap_skip_all

__Signature:__ int tap_skip_all(char *message)

`tap_skip_all` takes a single argument, the skipped message. `tap_skip_all` can be placed at the
top of a testing file and be used to skip all the tests in that file.

## tap_todo

__Signature:__ int tap_todo(int number, char *message)

`tap_todo` takes two arguments, the number of tests to todo, and the reason they are todo. libtap
will then todo the given number of tests.

## tap_todo_all

__Signature:__ int tap_todo_all(char *message)

`tap_todo_all` takes a single argument, the todo message. `tap_todo_all` can be placed at the
top of a testing file and beused to todo all the tests in that file.

## tap_done

__Signature:__ int tap_done()

`tap_done` takes no arguments, and is used to signal that a testing run with no plan should
complete and emit the number of tests performed.

## tap_status

__Signature:__ int tap_status()

`tap_status` takes no arguments, and returns the status of the testing run. Its return value
should be return from `main` so that TAP::Harness knows the status of the testing run for that
test file.

# REPOSITORY

The source code repository for this project is located at:

  http://github.com/f0rk/libtap

# AUTHOR

  Ryan P. Kelly <rpkelly@cpan.org>

# COPYRIGHT AND LICENSE

This software is Copyright (c) 2010 by Ryan P. Kelly.

This is free software, licensed under:

  The MIT (X11) License