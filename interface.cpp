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

#include "interface.h"

// Introduce the implementation dependencies and the calendar class
#include "calendar.h"
#include "gregorian_impl.h"
#include "month_element.h"

#include "util.h"

// The GregorianImpl class generates data that is formatted by MonthElements and
// stored in Calendar objects.
// That data is retrieved and exported to Util which handles all Html formatting.
bool generateCalendars(std::fstream &file, size_t year, std::string htmlTemplate) {

    std::vector<size_t> years{year - 1, year, year + 1};

    // Injected implementation: this does the Gregorian calculations
    GregorianImpl<MonthElement> implementation;
    Years data;

    for (auto generationYear : years) {
        Calendar yearCalendar(generationYear, implementation);
        data.emplace_back(generationYear, yearCalendar.getData());
    }
    Util::outputDocument(file, htmlTemplate, year, data);

    return true;
}

size_t getLowerBound() { return GregorianImpl<MonthElement>::gregStartYear; }
