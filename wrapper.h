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

#ifndef WRAPPER_H
#define WRAPPER_H


// This file should be included by those wishing to generate Gregorian calendars and write them out
// to .html

// It requires an open file fstream to write to, and a .html template pre-amble, presented as a
// string

#include <iostream>
#include <string>

// Create 3 adjacent Gregorian calenders adjacent and including 'year', print to 'file' as html
void generateCalendarsGregorian(std::iostream &file, size_t year, std::string htmlTemplate);

size_t getLowerGregorianBound();

#endif // WRAPPER_H
