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

// The implementation returns a vector of 'cells' which contain headers, week numbers, dates
// and blank spaces.

#include <string>

#include "calendar_types.h"

class MonthElement {
  public:
    explicit MonthElement(const Properties &params);

    Month operator()(const std::string &monthName, size_t dateStart, size_t dateEnd,
                     size_t monthStartDayIndex, size_t weekNumber) const;

  private:
    void addCell(const std::string &celldata, MonthData &data) const;

    Properties properties;
    size_t m_tableColumns;
    size_t m_tableDataRows;
};

#endif // MONTH_ELEMENT_H
