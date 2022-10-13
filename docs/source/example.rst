Usage example
=============

.. code-block:: c

   #include "crash.h"

   define_test(example_success)
   {
       eq(4, 2 + 2);
   }

   define_test(example_fail)
   {
       char *a = "hello";

       same("world", a);
   }

   run()
   {
       test(example_success);
       test(exmaple_fail);
   }