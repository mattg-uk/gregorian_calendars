
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
#ifndef GENERATE_H
#define GENERATE_H

#include "calendar_types.h"

template <typename Generator, typename Writer>
void generate(Generator &implementation, std::iostream &file, size_t coreYear,
              std::string htmlTemplate, Writer &writer) {

    std::vector<size_t> years{coreYear - 1, coreYear, coreYear + 1};

    Years data;
    for (auto generationYear : years) {
        data.push_back(implementation.populateYear(generationYear));
    }
    writer.outputDocument(file, htmlTemplate, coreYear, data);
}
#endif // GENERATE_H
