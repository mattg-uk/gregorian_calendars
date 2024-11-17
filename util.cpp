
/* ------------------------------------------------------------------------------
MIT License

Copyright (c) 2022 Matthew Nathan Green

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation outputs (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.
-------------------------------------------------------------------------------- */

#include "util.h"

void Util::outputDocument(std::iostream &output, const std::string &htmlTemplate, size_t coreYear,
                          const Years &data) {
    outputDocumentHeaderHtml(output, htmlTemplate);
    for (auto &year : data) {
        Util::outputYearHeaderHtml(output, year.first, data);
        Util::outputYearMonthsHtml(output, year.second);
        output << Util::sectionClose() << "\n\n";
    }
    outputDocumentFooterHtml(output, coreYear);
}

void Util::outputDocumentHeaderHtml(std::iostream &output, const std::string &htmlTemplate) {
    output << htmlTemplate;
    output << Util::bodyOpen() << "\n\n";
}

void Util::outputYearHeaderHtml(std::iostream &output, size_t year, const Years &years) {

    // Header for this year with coded ID for linkage
    output << Util::headerOpen(yearId(year)) << "Calendar Year " << year << Util::headerClose()
           << "\n\n";

    output << Util::sectionOpen() << "\n";

    // Year selector: years in order, with the current year hard-coded and the others as links
    output << Util::tab2 << Util::divTagOpen("year_selector") + "\n";
    for (auto &linkYear : years) {
        if (linkYear.first == year) {
            output << Util::tab4 << year << "\n";
        } else {
            output << Util::tab4 << Util::aTagOpen(yearHref(linkYear.first)) << linkYear.first
                   << Util::aTagClose() << "\n";
        }
    }
    output << Util::tab2 << Util::divTagClose();
}

void Util::outputYearMonthsHtml(std::iostream &output, const YearData &data) {
    for (auto &month : data) {
        outputMonthHtml(output, month.first, month.second);
    }
}

void Util::outputMonthHtml(std::iostream &output, const std::string &monthName,
                           const MonthData &data) {

    output << Util::tab2 << Util::monOpen() << '\n';
    output << Util::tab4 << Util::divTagOpen("month-name") << monthName << Util::divTagClose()
           << '\n';
    output << Util::tab4 << Util::divTagOpen("grid-container") << '\n';
    for (const auto &item : data) {
        output << Util::tab6 << Util::divTagOpen(Util::styleAsString(item.first)) << item.second
               << Util::divTagClose() << '\n';
    }
    output << Util::tab4 << Util::divTagClose() << '\n';
    output << Util::tab2 << Util::monClose() << '\n';
}

void Util::outputDocumentFooterHtml(std::iostream &output, size_t viewStartYear) {
    // Close out the final parts of the html
    output << Util::footerOpen() << Util::footerClose() << "\n\n";
    output << Util::bodyClose() << "\n\n";

    // Add a tiny script to move the html view to the centre year upon opening the html page
    output << Util::scriptOpen() << "\n";
    output << Util::tab2 << Util::locationReplace(Util::yearHref(viewStartYear)) << "\n";
    output << Util::scriptClose() << "\n\n";

    output << Util::htmlClose() << "\n";
}
