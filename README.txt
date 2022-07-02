This project will build a calendar application using cmake.

Pre-requisites
--------------

The build prerequisites are: cmake build-essential (ninja-build) and can be installed under Debian-like distros via:

sudo apt install build-essential cmake ninja-build

Convenience Script:
-------------------

run the following command in the source folder

./examples.sh <OUTPUT_FOLDER>

<OUTPUT FOLDER> is where example calendars for 1800, 1900, 2000, and 2017 will be generated.

N.B. This folder must already exist!


OR: ---

Build Instructions
------------------

From the unzipped project folder:
  cmake -Bbuild -GNinja .
  cmake --build build

N.B. : The build process copies the 'Config' folder to the target build location; the Config folder must be present for the executable to run.


Execution instructions
----------------------

Assuming that the build was directed to a sub-folder ./build as above,
  cd build
  ./calendar -y <YEAR> -o <FILENAME>

 --  where <YEAR> is the centre year desired and <FILENAME> is your chosen name for the output file. '.html' will be appended if not specified.

 example:

 ./calendar -2000 -o example

 result: a html file named example.html is output into the 'build' directory, containing calendars for 1999, 2000, 2001.

