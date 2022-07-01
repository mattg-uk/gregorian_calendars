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

// This class contains common static methods that do not belong to one class but to the html calender as a whole

#include <vector>
#include <string>

class Util {
public:

// A leap year occurs if the year is divisible by 4, but not by 100, unless it is divisble by 400 - in which case it is

    // Create a html tag
    static std::string headerOpen(const std::string& id) { return std::string("<header id=\"") + id + "\">"; }
    static std::string headerClose()    { return "</header>"; }

    static std::string sectionOpen()    { return "<section>"; }
    static std::string sectionClose()   { return "</section>"; }

    static std::string aTagOpen(const std::string& hRef) { return std::string("<a href=\"") + hRef + "\">"; }
    static std::string aTagClose()      { return "</a>"; }

    static std::string divTagOpen(const std::string& htmlClass) { return std::string("<div class=\"") + htmlClass + "\">"; }
    static std::string divTagClose()    { return "</div>"; }

    static std::string monOpen()        { return "<mon>"; }
    static std::string monClose()       { return "</mon>"; }
    
    static std::string bodyOpen()       { return "<body>"; }
    static std::string bodyClose()      { return "</body>"; }
        
    static std::string footerOpen()     { return "<footer>"; }
    static std::string footerClose()    { return "</footer>"; }
        
    static std::string htmlOpen()       { return "<html>"; }
    static std::string htmlClose()      { return "</html>"; }

    // Gregorian year booundary (month is zero indexed)
    static const size_t gregYear = 1582;
    static const size_t gregMonthIndex = 9;
    static const size_t gregDate = 15;

    // Fundamental properties of weeks, months; calendars properties
    static const size_t daysInAWeek   = 7;
    static const size_t indexFebruary = 1;
    static const size_t indexOctober  = 9;
    static const size_t tableColumns  = 8;
    static const size_t tableDataRows = 6;

    static const inline std::string tab2 = std::string(2, ' ');
    static const inline std::string tab4 = std::string(4, ' ');
    static const inline std::string tab6 = std::string(6, ' ');

    static const inline std::string classLabel  = std::string("label");
    static const inline std::string classDay    = std::string("day");
    static const inline std::string classSat    = std::string("sat");
    static const inline std::string classSun    = std::string("sun");

    static const inline std::vector<std::string> monthNames {"January", "February", "March", "April", 
                                                             "May", "June", "July", "August", 
                                                             "September", "October", "November", "December"};    
    static const inline std::vector<std::size_t> daysPerMonth{ 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    static const inline std::vector<std::string> headerNames{"Wk", "Mo", "Tu", "We", "Th", "Fr", "Sa", "Su"};
    
    // This governs the style of the output in the html document - these are the html class of the column
    static const inline std::vector<std::string> columnType { classLabel, classDay, classDay, classDay, 
                                                              classDay, classDay, classSat, classSun };
    static const inline std::vector<std::string> headerType { classLabel, classLabel, classLabel, classLabel, 
                                                              classLabel, classLabel, classSat, classSun };
};

#endif // UTIL_H