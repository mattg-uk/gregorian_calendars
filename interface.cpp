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

#include "interface.h"

// Introduce the implementation dependencies and the calendar class
#include "calendar.h"
#include "gregorian_impl.h"
#include "month_element.h"

#include "util.h"

#include <algorithm>

// This function pushes out the style section of the html, and, for each year, pushes headers, a link
// banner, and then creates a calendar object for that year and uses it to generate the tables
bool generateCalendars(std::fstream& file, size_t year, std::string htmlTemplate)
{
    // The implementation is stateless
    using Implementation = GregorianImpl<MonthElement>;
    Implementation imlementation;
    
    // For each of the 3 years we need a number, an id, a link, and a selector permutation 
    std::vector<size_t> yearNumbers {year - 1, year, year + 1};
    std::vector<std::string> yearString;
    std::vector<std::string> yearId;
    std::vector<std::string> yearHref;

    enum class Option { Number, Link };
    std::vector<Option> selectorPermutation;
    bool first = true;

    // Populate these containers
    for (auto number : yearNumbers ) {
        yearId.push_back(std::string("year_") + std::to_string(number));
        yearHref.push_back(std::string("#") + yearId.back());
        selectorPermutation.push_back(first ? Option::Number : Option::Link);
        first = false;
    }

    file << htmlTemplate;
    file << Util::bodyOpen() << "\n\n";

    for (size_t index = 0; index < yearNumbers.size(); ++index) {
        std::cout << "Creating html for year : " << yearNumbers[index] << std::endl;
        
        // Header for this year, coding in id so that it can be linked to
        std::string headerText = std::string("Calendar Year ") + std::to_string(yearNumbers[index]);
        file << Util::headerOpen(yearId[index]) << headerText << Util::headerClose() << "\n\n";
        file << Util::sectionOpen() << "\n";
        file << Util::tab2 << Util::divTagOpen("year") + "\n";
        
        // Print year selector: years in order, with the current year hard-coded and the other two as links
        for (size_t subIndex = 0; subIndex < yearNumbers.size(); ++subIndex) {
            switch (selectorPermutation[subIndex]) {
            case Option::Number:
                file << Util::tab4 << yearNumbers[subIndex] << "\n";
                break;
            case Option::Link:
                file << Util::tab4 << Util::aTagOpen(yearHref[subIndex]) << yearNumbers[subIndex] << Util::aTagClose() << "\n";
                break;
            }
        }
        std::next_permutation(selectorPermutation.begin(), selectorPermutation.end());
        file << Util::tab2 << Util::divTagClose();
        
        // Finally, push out the divs from which the html will create the calendar tables
        Calendar yearCalender (yearNumbers[index], imlementation);
        yearCalender.htmlPrint(file);
        
        file << Util::sectionClose() << "\n\n";
    }

    // Close out the final parts of the html - the file itself is closed in main by ~fstream()
    file << Util::footerOpen() << Util::footerClose() << "\n\n";
    file << Util::bodyClose() << "\n";
    file << Util::htmlClose() << "\n";

    return true;
}

size_t getLowerBound()
{
    return Util::gregYear;
}

