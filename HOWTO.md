# CrashTest v0.0.0 documentation

## Creating a test

A test is created using the `define_test` macro :

```c
define_test(my_test) {
	// code to execute and assertions
}
```

## Grouping tests inside suites

A suite is created using the `define_suite` macro :

```c
define_suite(my_suite) {
	test(my_test); // include previously declared my_test
	suite(my_other_suite); // nested suites
	// ...
}
```

## Running all the tests

The main suite is declared using the `run` macro :

```c
run() {
	suite(my_suite); // running a suite
	test(my_other_test); // running stray tests
	// ... 
}