/* ------------------------------------------------------------------------------
MIT License

Copyright (c) 2022-2025 Matthew Nathan Green

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation outputs (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.
-------------------------------------------------------------------------------- */

#include "html_writer.h"

void HtmlWriter::outputDocument(std::iostream &output, const std::string &htmlTemplate,
                                size_t coreYear, const Years &data) const {
    outputDocumentHeaderHtml(output, htmlTemplate);
    for (auto &year : data) {
        HtmlWriter::outputYearHeaderHtml(output, year.first, data);
        HtmlWriter::outputYearMonthsHtml(output, year.second);
        output << HtmlWriter::sectionClose() << "\n\n";
    }
    outputDocumentFooterHtml(output, coreYear);
}

void HtmlWriter::outputDocumentHeaderHtml(std::iostream &output, const std::string &htmlTemplate) {
    output << htmlTemplate;
    output << HtmlWriter::bodyOpen() << "\n\n";
}

void HtmlWriter::outputYearHeaderHtml(std::iostream &output, size_t year, const Years &years) {

    // Header for this year with coded ID for linkage
    output << HtmlWriter::headerOpen(yearId(year)) << "Calendar Year " << year
           << HtmlWriter::headerClose() << "\n\n";

    output << HtmlWriter::sectionOpen() << "\n";

    // Year selector: years in order, with the current year hard-coded and the others as links
    output << HtmlWriter::tab2 << HtmlWriter::divTagOpen("year_selector") + "\n";
    for (auto &linkYear : years) {
        if (linkYear.first == year) {
            output << HtmlWriter::tab4 << year << "\n";
        } else {
            output << HtmlWriter::tab4 << HtmlWriter::aTagOpen(yearHref(linkYear.first))
                   << linkYear.first << HtmlWriter::aTagClose() << "\n";
        }
    }
    output << HtmlWriter::tab2 << HtmlWriter::divTagClose() << "\n";
}

void HtmlWriter::outputYearMonthsHtml(std::iostream &output, const YearData &data) {
    for (auto &month : data) {
        outputMonthHtml(output, month.first, month.second);
    }
}

void HtmlWriter::outputMonthHtml(std::iostream &output, const std::string &monthName,
                                 const MonthData &data) {

    output << HtmlWriter::tab2 << HtmlWriter::monOpen() << '\n';
    output << HtmlWriter::tab4 << HtmlWriter::divTagOpen("month-name") << monthName
           << HtmlWriter::divTagClose() << '\n';
    output << HtmlWriter::tab4 << HtmlWriter::divTagOpen("grid-container") << '\n';
    for (const auto &item : data) {
        output << HtmlWriter::tab6 << HtmlWriter::divTagOpen(HtmlWriter::styleAsString(item.first))
               << item.second << HtmlWriter::divTagClose() << '\n';
    }
    output << HtmlWriter::tab4 << HtmlWriter::divTagClose() << '\n';
    output << HtmlWriter::tab2 << HtmlWriter::monClose() << '\n';
}

void HtmlWriter::outputDocumentFooterHtml(std::iostream &output, size_t viewStartYear) {
    // Close out the final parts of the html
    output << HtmlWriter::footerOpen() << HtmlWriter::footerClose() << "\n\n";
    output << HtmlWriter::bodyClose() << "\n\n";

    // Add a tiny script to move the html view to the centre year upon opening the html page
    output << HtmlWriter::scriptOpen() << "\n";
    output << HtmlWriter::tab2 << HtmlWriter::locationReplace(HtmlWriter::yearHref(viewStartYear))
           << "\n";
    output << HtmlWriter::scriptClose() << "\n\n";

    output << HtmlWriter::htmlClose() << "\n";
}
