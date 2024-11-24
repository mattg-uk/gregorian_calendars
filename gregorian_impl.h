/* ----------------------------------------------------------------------------- MIT License

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

#ifndef GREGORIAN_IMPL_H
#define GREGORIAN_IMPL_H

// This class is a stateless implementation of the worker functions required by the calendar.

// Alternatives to injecting this could be e.g. this as a base class, and inheriting it via
// templatized private inheritance.

// This class ITSELF must leverage a month class, but THIS class should be testable independently
// of that, so the month class itself is parametric.

#include <vector>

#include "calendar_types.h"

// Decouple the dependency on the Month class used
template <typename MonthType> class GregorianImpl {
  public:
    typedef MonthType MonthType_t;
    // These properties are specific to (but not unique to) an English Language Gregorian calendar
    static const inline Properties properties{
        7,
        {"January", "February", "March", "April", "May", "June", "July", "August", "September",
         "October", "November", "December"},
        {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
        {"Wk", "Mo", "Tu", "We", "Th", "Fr", "Sa", "Su"},
        {CellType::Label, CellType::Workday, CellType::Workday, CellType::Workday,
         CellType::Workday, CellType::Workday, CellType::Weekend1, CellType::Weekend2},
        {CellType::Label, CellType::Label, CellType::Label, CellType::Label, CellType::Label,
         CellType::Label, CellType::Weekend1, CellType::Weekend2},
    };

    Year populateYear(int year) const;

    size_t getBaseIndex(int year) const;
    bool isLeapYear(int year) const;
    std::pair<size_t, size_t> validate(size_t year, size_t monthIndex, size_t endRange) const;

    // These indices define the start of the Gregorian calendar
    static const size_t gregStartYear = 1582;
    static const size_t gregStartMonthIndex = 9;
    static const size_t gregStartDate = 15;

    // used in leap year calcs
    static const size_t indexFebruary = 1;
};

// TEMPLATE IMPLEMENTATION
// ----------------------------------------------------------------------------

template <typename MonthType> Year GregorianImpl<MonthType>::populateYear(int year) const {

    size_t yearStartIndex = getBaseIndex(year);

    // Create a parameterized factory function-object and a Year with an empty data vector
    MonthType generator{properties};
    Year data{year, YearData()};

    auto &months = data.second;
    for (size_t monthIndex = 0; monthIndex < 12; ++monthIndex) {

        size_t monthEnd = properties.daysPerMonth[monthIndex];
        size_t monthStartOffset = 0;
        for (size_t i = 0; i < monthIndex; ++i) {
            monthStartOffset += properties.daysPerMonth[i];
        }
        if (isLeapYear(year)) {
            if (monthIndex > indexFebruary) {
                ++monthStartOffset;
            }
            if (monthIndex == indexFebruary) {
                ++monthEnd;
            }
        }

        size_t monthStartWeek = (yearStartIndex + monthStartOffset) / properties.daysInAWeek + 1;
        auto [dateStart, dateEnd] = validate(year, monthIndex, monthEnd);
        // Start the calendar on the correct index of row 1, unless days are skipped
        size_t monthStartDayIndex =
            (yearStartIndex + monthStartOffset) % properties.daysInAWeek + (dateStart - 1);

        months.push_back(generator(properties.monthNames[monthIndex], dateStart, dateEnd,
                                   monthStartDayIndex, monthStartWeek));
    }
    return data;
}

// A leap year occurs if the year is divisible by 4, but not by 100, unless it is divisble by 400 -
// in which case it is
template <typename MonthType> bool GregorianImpl<MonthType>::isLeapYear(int year) const {
    return (year % 400 == 0) || ((year % 4 == 0) && (year % 100 != 0));
}

template <typename MonthType> size_t GregorianImpl<MonthType>::getBaseIndex(int year) const {
    // Oct 15, 1582 is a Friday (index 4). Jan 1st 1582 also index 4 - remove invalid dates later
    // Index changes by 365 % 7, i.e. +1 per year; +2 for a leap year

    size_t baseIndex = 4;
    for (int yearIndex = gregStartYear; yearIndex < year; ++yearIndex) {
        baseIndex += 1 + static_cast<size_t>(isLeapYear(yearIndex));
    }
    return baseIndex % 7;
}

// Some dates are not valid for the gregorian calendar - convert month range to a valid one
template <typename MonthType>
std::pair<size_t, size_t> GregorianImpl<MonthType>::validate(size_t year, size_t monthIndex,
                                                             size_t endDate) const {

    // Use all - it is after the Gregorian Start Month
    if (year > gregStartYear || year == gregStartYear && monthIndex > gregStartMonthIndex) {
        return {1, endDate};
    }

    // Use none, the year is pre-Gregorian or the month is pre-Gregorian within
    // the Gregorian Year
    if (year < gregStartYear || monthIndex < gregStartMonthIndex) {
        return {endDate, endDate - 1};
    }

    // Neither after the gregMonth nor before it
    return {15, endDate};
}
#endif // GREGORIAN_IMPL_H
