# HTML Calendars from C++

This project will build a calendar application using cmake.

## The point of this application: It was a challenge problem

In 2022, I was asked to produce an application that outputs Gregorian calendars (i.e. standard modern calendars) in html format.
This was as a challenge problem - but it is not as simple as it seems at first, and it was subsequently withdrawn from that company's
interview process. However, it serves as a convenient demonstration project for dependency injection based testing, so here it is.

### Constraints

 - Must run from the CLI and implicity be in C++
 - Must output well-formatted HTML calendars for a specific year and the two adjacent years.
 - All dates must be correctly calculated by the application itself, without the use of any calendar library or fixed tables.

### Structure

 - app_main.cpp is a standard CLI parser
 - generate.h is an interface file which handles the dependency injection of the main classes and generates the 3 years' data.
 - gregorian_impl.h generates the specific date-ranges and start days associated with the months a specified calendar year.
 - month_element is a simple helper to tabulate and format the days / dates of a particular month
 - html_writer converts the tabulated data into visually pleasing html: it writes the html tags with the aid of a base template file.
 - Config/ contains the html base template
 - test/ contains the unit tests
 - cmake contains coverage.cmake - this massively simplifies the generation of coverage reports

So its has a CLI parser, data calculator / aggregator, a html output stage, a html template file and some unit tests.

### Dependency injection for flexibility and testing 

Dependencies are taken as parameters - by doing this, it is possible to inject different behaviours into the code. For example,
a non-Gregorian calendar, different month formatting, or a different html style.

_But much more importantly_ by taking the dependencies as parameters, this massively reduces the complexity of the unit testing:
this project demonstrates 100% test coverage with relatively simple test code - GTest mocks rather than complex stubs.

## Build and Usage

### Pre-requisites

The build prerequisites are: cmake build-essential (ninja-build) and can be installed under Debian-like distros via:

`sudo apt install build-essential cmake ninja-build`

### Generate Calendars from Convenience Script:

run the following command in the source folder

./examples.sh <OUTPUT_FOLDER>

<OUTPUT FOLDER> is where example calendars for 1800, 1900, 2000, and 2017 will be generated.

N.B. This folder must already exist!

### Build Instructions

From the unzipped project folder:

`cmake -Bbuild -GNinja .
 cmake --build build`

### Execution instructions

Assuming that the build was directed to a sub-folder ./build as above,

`cd build
 ./calendar -y <YEAR> -o <FILENAME>`

 example:

`./calendar -2000 -o example`

 result: a html file named example.html is output into the 'build' directory, containing calendars for 1999, 2000, 2001.

### Producing Test coverage reports

From the project root,

`cd build
 ninja coverage
 open coverage/index.html`

