Program structure
=================

.. _tests:

Creating unit tests
-------------------

A test is created with the ``define_test`` macro:

.. code-block:: c

   define_test(mytest)
   {
       // code and assertions
   }

Inside the body of a test, you can use any of the code you would use inside a
function.

.. note::
   Using ``return`` will stop the test and make it successful.


Creating test suites
--------------------

Test suites are groups of tests and other suites. A suite is created using the
``define_suite`` macro:

.. code-block:: c

   define_suite(mysuite)
   {
       test(mytest); // include a test
       suite(suite2); // include another suite
       // ...
   }

Only the ``test`` and ``suite`` macros may be used inside suite bodies.

.. warning::
   Including a suite inside itself will result in infite recursion.


Running the tests
-----------------

After the all the tests and suites are created, you can use the ``run`` macro to
execute them:

.. code-block:: c

   run()
   {
       suite(mysuite); // running a suite
       test(mytest); // running a stray test
       // ...
   }

The ``run`` macro will declare the main suite, and implement the main function
of your program.