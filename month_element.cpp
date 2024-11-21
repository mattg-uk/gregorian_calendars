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
#include <algorithm>

MonthElement::MonthElement(const Properties &params) : properties(params) {

    // This will throw an exception if there is not at least one month
    size_t longestMonth =
        *std::max_element(properties.daysPerMonth.begin(), properties.daysPerMonth.end());

    m_tableColumns = properties.daysInAWeek + 1;
    m_tableDataRows = std::max(size_t(1), (longestMonth - 2) / properties.daysInAWeek + 2);
}

void MonthElement::addCell(const std::string &celldata, MonthData &data) const {
    auto cellIndex = data.size();
    auto cellColumn = cellIndex % m_tableColumns;
    CellType cellType = cellIndex < m_tableColumns ? properties.headerType[cellColumn]
                                                   : properties.dataType[cellColumn];
    data.emplace_back(cellType, celldata);
}

Month MonthElement::operator()(const std::string &monthName, size_t dateStart, size_t dateEnd,
                               size_t monthStartDayIndex, size_t weekNumber) const {

    Month month;
    month.first = monthName;
    auto &data = month.second;

    // Populate headers
    for (const auto &item : properties.headerNames) {
        addCell(item, data);
    }

    // Populate the data rows, including blank cells. (insert week labels on new rows)
    size_t week = weekNumber;
    size_t date = dateStart;
    for (size_t dataIndex = 0; dataIndex < m_tableDataRows * properties.daysInAWeek; ++dataIndex) {
        std::string celldata;
        if (dataIndex % properties.daysInAWeek == 0) {
            if (date <= dateEnd) {
                addCell(std::to_string(week++), data);
            } else {
                addCell(std::string(), data);
            }
        }
        if (dataIndex >= monthStartDayIndex && date <= dateEnd) {
            celldata = std::to_string(date++);
        }
        addCell(celldata, data);
    }
    return month;
}
