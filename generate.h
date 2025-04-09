/* ------------------------------------------------------------------------------
MIT License

Copyright (c) 2022-2025 Matthew Nathan Green

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.
-------------------------------------------------------------------------------- */

#ifndef GENERATE_H
#define GENERATE_H


// This file should be included by those wishing to generate Gregorian calendars and write them out
// to .html. Parameters are passed to the first three arguments only; use the default values for the
// other two. The injection is 'exposed' to the client here; but in a library context a wrapper
// function to hide the injection details could be provided.

#include <iostream>
#include <string>

#include "gregorian_impl.h"
#include "html_writer.h"
#include "month_element.h"

template <typename Generator = GregorianImpl<MonthElement>, typename Writer = HtmlWriter>
void generateCalendarsGregorian(std::iostream &file, size_t year, std::string htmlTemplate,
                                const Generator &implementation = GregorianImpl<MonthElement>(),
                                const Writer &writer = HtmlWriter()) {

    std::vector<size_t> years{year - 1, year, year + 1};
    Years data;
    for (auto generationYear : years) {
        data.push_back(implementation.populateYear(generationYear));
    }
    writer.outputDocument(file, htmlTemplate, year, data);
}

inline const size_t lowerGregorianBound = GregorianImpl<MonthElement>::calenderStartYear;

#endif // GENERATE_H
