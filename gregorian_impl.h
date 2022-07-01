
// This class is a stateless implementation of the worker functions required by the calendar.

// Alternatives to injecting this could be e.g. this as a base class, and inheriting it via 
// templatized private inheritance.

// This class ITSELF must leverage a month class, but THIS class should be testable independently
// of that, so the month class itself is parametric.

#ifndef GREGORIAN_IMPL_H
#define GREGORIAN_IMPL_H

#include <iostream>
#include <vector>
#include <string>

// Decouple the dependency on the Month class used
template <typename MonthType>
class GregorianImpl {
public:
    typedef MonthType MonthType_t;

    void htmlOut(std::iostream& stream, const std::vector<MonthType>& months);
    std::vector<MonthType> populateMonths(int year);
    
    bool   isLeapYear(int year);
    size_t getBaseIndex(int year);
};


// TEMPLATE IMPLEMENTATION ----------------------------------------------------------------------------

template <typename MonthType>
void GregorianImpl<MonthType>::htmlOut(std::iostream& stream, const std::vector<MonthType>& months)
{
    for (const auto& month : months) {
        month.htmlOut(stream);
    }
}

template <typename MonthType>
std::vector<MonthType> GregorianImpl<MonthType>::populateMonths(int year)
{
    
    size_t yearStartIndex = getBaseIndex(year);
    
    std::vector<MonthType> months;
    for (size_t monthIndex = 0; monthIndex < 12; ++monthIndex) {
        months.emplace_back(monthIndex, yearStartIndex, isLeapYear(year), year);
    }
    return months;
}

// A leap year occurs if the year is divisible by 4, but not by 100, unless it is divisble by 400 - in which case it is
template <typename MonthType>
bool GregorianImpl<MonthType>::isLeapYear(int year) 
{ 
    return (year % 400 == 0) || ((year % 4 == 0) && (year % 100 != 0)); 
}

template <typename MonthType>
size_t GregorianImpl<MonthType>::getBaseIndex(int year)
{
    // Oct 15, 1582 is a Friday (index 4). Jan 1st 1582 also index 4 - remove invalid dates later 
    // Index changes by 365 % 7, i.e. +1 per year; +2 for a leap year
    
    size_t baseIndex = 4;
    for (int yearIndex = 1582; yearIndex < year; ++yearIndex) {
        baseIndex += 1 + static_cast<size_t>(isLeapYear(yearIndex));
    }
    return baseIndex % 7;
}

#endif  // GREGORIAN_IMPL_H
