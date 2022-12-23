Assertion macros
================

.. warning::
   All the macros below can only be used inside a :ref:```define_tests`` <tests>` declaration.

.. note::
   All the macros below can be prefixed with ``assert_`` by defining
   ``ASSERT_PREFIX`` before importing the framework:

   .. code-block:: c

      #define ASSERT_PREFIX
      #include "crash.h"

Basic assertions
----------------

.. macro:: ok(value)

   Asserts that ``value`` is true.

.. macro:: no(value)

   Asserts that ``value`` is false.


Integers
--------

.. macro:: eq(expected, value)

   Asserts that ``value`` is equal to ``expected``.

.. macro:: ne(expected, value)

   Asserts that ``value`` isn't equal to ``expected``.


Floating-point numbers
----------------------

.. macro:: eq_flt(expected, value, prec)

   Asserts that ``value`` is equal to ``expected`` for the first ``prec``
   decimal places.

.. macro:: ne_flt(expected, value, prec)
   
   Asserts that ``value`` isn't almost equal to ``expected``.


Pointers
--------

.. macro:: eq_ptr(expected, value)

   Asserts that ``value`` and ``expected`` point to the same address.

.. macro:: ne_ptr(expected, value)

   Asserts that ``value`` and ``expected`` doesn't point to the same address.

.. macro:: null_ptr(value)

   Asserts that ``value`` is ``NULL``.


Strings
-------

.. macro:: same(expected, value)

   Asserts that ``value`` and ``expected`` contain the same characters.

.. macro:: diff(expected, value)

   Asserts that ``value`` and ``expected`` doesn't contain the same characters.

Memory
------

.. macro:: mem(expected, value, size)

   Asserts that the block of memory at address ``value`` is the same as at
   address ``expected``.
