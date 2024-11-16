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

#ifndef UTIL_H
#define UTIL_H

// This class contains common static methods that do not belong to one class but to the html
// calender as a whole

#include "calendar_types.h"
#include <iostream>
#include <string>
#include <unordered_map>

class Util {
  public:
    // A leap year occurs if the year is divisible by 4, but not by 100, unless it is divisble by
    // 400 - in which case it is

    // Create a html tag
    static std::string headerOpen(const std::string &id) {
        return std::string("<header id=\"") + id + "\">";
    }
    static std::string headerClose() { return "</header>"; }

    static std::string sectionOpen() { return "<section>"; }
    static std::string sectionClose() { return "</section>"; }

    static std::string aTagOpen(const std::string &hRef) {
        return std::string("<a href=\"") + hRef + "\">";
    }
    static std::string aTagClose() { return "</a>"; }

    static std::string divTagOpen(const std::string &htmlClass) {
        return std::string("<div class=\"") + htmlClass + "\">";
    }
    static std::string divTagClose() { return "</div>"; }

    static std::string monOpen() { return "<mon>"; }
    static std::string monClose() { return "</mon>"; }

    static std::string bodyOpen() { return "<body>"; }
    static std::string bodyClose() { return "</body>"; }

    static std::string footerOpen() { return "<footer>"; }
    static std::string footerClose() { return "</footer>"; }

    static std::string scriptOpen() { return "<script>"; }
    static std::string scriptClose() { return "</script>"; }
    static std::string locationReplace(const std::string &hRef) {
        return std::string("location.replace('") + hRef + "')";
    }

    static std::string htmlOpen() { return "<html>"; }
    static std::string htmlClose() { return "</html>"; }

    static const inline std::string tab2 = std::string(2, ' ');
    static const inline std::string tab4 = std::string(4, ' ');
    static const inline std::string tab6 = std::string(6, ' ');

    // These html class names are output directly into the html, and must match those used in the
    // config file. These govern the style used in the ouput
    static const inline std::string classLabel = std::string("label");
    static const inline std::string classDay = std::string("day");
    static const inline std::string classSpec1 = std::string("spec1");
    static const inline std::string classSpec2 = std::string("spec2");

    static const inline std::unordered_map<CellType, std::string> styleMap{
        {CellType::Label, classLabel},
        {CellType::Workday, classDay},
        {CellType::Weekend1, classSpec1},
        {CellType::Weekend2, classSpec2}};

    static std::string styleAsString(const CellType &style) { return styleMap.at(style); }
    static std::string monthAsHtmlString(const std::string &monthName, const DataStorage &data);
};

#endif // UTIL_H
