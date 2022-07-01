// This file should be included by those wishing to generate Gregorian calenders and print them out to html.

// (This would act as a library interface, and screens the implementation details from the 'user' (main).)


#ifndef GREGORIAN_H
#define GREGORIAN_H

#include <string>
#include <fstream>

// Create 3 adjacent Gregorian calenders adjacent and including 'year', print to 'file' as html
bool generateCalendars(std::fstream& file, size_t year, std::string htmlTemplate);

// Gregorian supplies a specifically Gregorian implementation of the calendar, no years before 1582
size_t getLowerBound();

#endif // GREGORIAN_H
