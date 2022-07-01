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
// and blank spaces, alongside html class information.

// The output is a series of div tags that can be interpretted in html as a table.

#include <vector>
#include <string>
#include <iostream>

class MonthElement {
public:
    
    MonthElement(size_t monthIndex, size_t yearStartIndex, bool leapYear, int year);
    
    // Everything about this month that is needed in html - output to a stream
    void htmlOut(std::iostream& stream) const;
    
    void addCell(const std::string& data);

    // Blank out a string based on the validity of the year - consumes input
    static std::string validityCheck(std::string&& input, size_t date, size_t monthIndex, size_t year);

private:
    std::vector<std::pair<std::string, std::string>> m_contents;
    size_t m_monthIndex;
};

#endif // MONTH_ELEMENT_H