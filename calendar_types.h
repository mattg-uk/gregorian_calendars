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

#ifndef CALENDAR_TYPES_H
#define CALENDAR_TYPES_H

#include <string>
#include <vector>
// namespace Cal {
enum class CellType { Label, Workday, Weekend1, Weekend2 };

using DataStorage = std::vector<std::pair<CellType, std::string>>;

// Allows a completely generic definition of a calender
class Properties {
  public:
    const size_t daysInAWeek;
    const std::vector<std::string> monthNames;
    const std::vector<std::size_t> daysPerMonth;
    const std::vector<std::string> headerNames;
    const std::vector<CellType> dataType;
    const std::vector<CellType> headerType;
};
//} // namespace Cal
#endif
