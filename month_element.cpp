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

#include "month_element.h"
#include "util.h"

struct demo {
    int classVar;
    int method(int param) {
        int methodLocalVar;
        return classVar + methodLocalVar + param;
    }
};

MonthElement::MonthElement(size_t monthIndex, size_t yearStartIndex, bool leapYear, int year)
    : m_monthIndex(monthIndex) {
    // Obtain the number of days this month
    size_t daysToPopulate = Util::daysPerMonth[monthIndex];
    if (leapYear && monthIndex == Util::indexFebruary) {
        ++daysToPopulate;
    }

    // Obtain the index of the day that the month starts on (the monthStartIndex)
    size_t monthStartDayNumber = 0;
    for (size_t i = 0; i < monthIndex; ++i) {
        monthStartDayNumber += Util::daysPerMonth[i];
    }
    if (leapYear && monthIndex > Util::indexFebruary) {
        ++monthStartDayNumber;
    }
    size_t monthStartIndex = (yearStartIndex + monthStartDayNumber) % Util::daysInAWeek;

    // Populate headers
    for (const auto &item : Util::headerNames) {
        addCell(item);
    }
    // First row: populate the week number and the leading blank cells
    size_t week = monthStartDayNumber / Util::daysInAWeek + 1;
    addCell(std::to_string(week));
    for (size_t count = 0; count < monthStartIndex; ++count) {
        addCell(std::string());
    }
    // Fill in the dates
    for (size_t date = 1; date <= daysToPopulate; ++date) {
        size_t cellIndex = m_contents.size();
        if (cellIndex % Util::tableColumns == 0) {
            addCell(std::to_string(++week));
        }
        std::string cellData = validityCheck(std::to_string(date), date, monthIndex, year);
        addCell(cellData);
    }
    // Fill in the empty spaces at the end - allow an extra row for the headers
    // Must be actual space otherwise the renderer will truncate the output
    while (m_contents.size() < Util::tableColumns * (Util::tableDataRows + 1)) {
        addCell(std::string(" "));
    }
}

void MonthElement::addCell(const std::string &data) {
    size_t cellIndex = m_contents.size();
    std::string cellType;
    if (cellIndex < Util::tableColumns) {
        cellType = Util::headerType[cellIndex];
    } else {
        cellType = Util::columnType[cellIndex % Util::tableColumns];
    }
    m_contents.emplace_back(cellType, data);
}

void MonthElement::htmlOut(std::iostream &file) const {
    file << Util::tab2 << Util::monOpen() << '\n';
    file << Util::tab4 << Util::divTagOpen("month-name") << Util::monthNames[m_monthIndex]
         << Util::divTagClose() << '\n';
    file << Util::tab4 << Util::divTagOpen("grid-container") << '\n';
    for (const auto &item : m_contents) {
        file << Util::tab6 << Util::divTagOpen(item.first) << item.second << Util::divTagClose()
             << '\n';
    }
    file << Util::tab4 << Util::divTagClose() << '\n';
    file << Util::tab2 << Util::monClose() << '\n';
}

std::string MonthElement::validityCheck(std::string &&input, size_t date, size_t monthIndex,
                                        size_t year) {
    // Guard out the most common cases
    std::string returnValue = std::move(input);
    if (year > Util::gregYear) {
        return returnValue;
    }

    if (year < Util::gregYear) {
        returnValue.clear();
        return returnValue;
    }

    // So it's 1582: must check both the month and the date
    if (monthIndex < Util::gregMonthIndex) {
        returnValue.clear();
    } else if (monthIndex == Util::gregMonthIndex) {
        if (date < Util::gregDate) {
            returnValue.clear();
        }
    }
    return returnValue;
}
