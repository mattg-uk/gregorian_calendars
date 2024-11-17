/* ------------------------------------------------------------------------------
MIT License

Copyright (c) 2022 Matthew Nathan Green

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.
-------------------------------------------------------------------------------- */

#ifndef INTERFACE_H
#define INTERFACE_H

// This file should be included by those wishing to generate Gregorian calendars and write them out
// to .html

// It requires an open file fstream to write to, and a .html template pre-amble, presented as a
// string

// The .cpp acts as the dependency injection site.

#include <fstream>
#include <string>

// Create 3 adjacent Gregorian calenders adjacent and including 'year', print to 'file' as html
bool generateCalendars(std::fstream &file, size_t year, std::string htmlTemplate);

// Gregorian supplies a specifically Gregorian implementation of the calendar, no years before 1582
size_t getLowerBound();

#endif // INTERFACE_H
