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

#ifndef MONTH_ELEMENT_H
#define MONTH_ELEMENT_H

// A simple class to abstract the creation of individual month blocks in the calendar.

// The implementation stores a vector of 'cells' which contain headers, week numbers, dates
// and blank spaces.

// The no html work is done by this class: htmlOut delegates conversion to Util in util.cpp.

#include <iostream>
#include <string>

#include "calendar_types.h"

class MonthElement {
  public:
    // End range is one past highest value
    explicit MonthElement(const std::string &monthName, size_t dateStart, size_t dateRangeEnd,
                          size_t monthStartIndex, size_t weekNumber, const Properties &params);

    // Everything about this month that is needed in html - output to a stream
    void htmlOut(std::iostream &stream) const;

  private:
    void addCell(const std::string &data, const Properties &params);

    DataStorage m_contents;
    std::string m_monthName;
    size_t m_tableColumns;
    size_t m_tableDataRows;
};

#endif // MONTH_ELEMENT_H
