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

#include "calendar_types.h"
#include "gregorian_impl.h"
#include "html_writer.h"
#include "month_element.h"

void generateDocumentFromImplementation(Generator *implementation, std::iostream &file,
                                        size_t coreYear, std::string htmlTemplate,
                                        HtmlWriter *writer) {

    std::vector<size_t> years{coreYear - 1, coreYear, coreYear + 1};

    Years data;
    for (auto generationYear : years) {
        data.push_back(implementation->populateYear(generationYear));
    }
    writer->outputDocument(file, htmlTemplate, coreYear, data);
}

void generateCalendarsGregorian(std::iostream &file, size_t year, std::string htmlTemplate) {

    // Injected implementation: this does the Gregorian calculations
    GregorianImpl<MonthElement> implementation;
    HtmlWriter writer;
    generateDocumentFromImplementation(&implementation, file, year, htmlTemplate, &writer);
}

size_t getLowerGregorianBound() { return GregorianImpl<MonthElement>::gregStartYear; }
