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

MonthElement::MonthElement(const std::string &monthName, size_t dateStart, size_t dateEnd,
                           size_t monthStartDayIndex, size_t weekNumber, const Properties &params)
    : m_monthName{monthName} {

    // This will throw an exception if there is not at least one month
    size_t longestMonth = *std::max_element(params.daysPerMonth.begin(), params.daysPerMonth.end());

    m_tableColumns = params.daysInAWeek + 1;
    m_tableDataRows = std::max(size_t(1), (longestMonth - 2) / params.daysInAWeek + 2);

    // Populate headers
    for (const auto &item : params.headerNames) {
        addCell(item, params);
    }

    // First row: populate the data rows, including blank cells. (insert week labels on new rows)
    size_t week = weekNumber;
    size_t date = dateStart;
    for (size_t dataIndex = 0; dataIndex < m_tableDataRows * params.daysInAWeek; ++dataIndex) {
        std::string data;
        if (dataIndex % params.daysInAWeek == 0) {
            addCell((date <= dateEnd) ? std::to_string(week++) : std::string(), params);
        }
        if (dataIndex >= monthStartDayIndex && date <= dateEnd) {
            data = std::to_string(date++);
        }
        addCell(data, params);
    }
}

void MonthElement::addCell(const std::string &data, const Properties &params) {
    size_t cellIndex = m_contents.size();
    CellType cellType;
    if (cellIndex < m_tableColumns) {
        cellType = params.headerType[cellIndex];
    } else {
        cellType = params.dataType[cellIndex % m_tableColumns];
    }
    m_contents.emplace_back(cellType, data);
}

std::pair<std::string, MonthData> MonthElement::getData() const {
    return std::pair(m_monthName, m_contents);
}
