User messages and errors
========================

.. macro:: info(...)

   Display an informational message.

   It should be called with printf-like arguments.

.. macro:: warn(...)

   Display a warning message.

   It should be called with printf-like arguments.

.. macro:: skip(...)

   Stops and ignore the test.

   It can be called without arguments, or with printf-style arguments to display
   a message explaining why the test has been ignored.

.. macro:: err(...)

   Make the test fail and display an error message.

   It should be called with printf-like arguments.

.. macro:: panic(...)

   Stops the execution of all the tests and display an error message.

   It should be called with printf-like arguments.