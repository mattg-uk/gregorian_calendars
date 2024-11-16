
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
#include <sstream>

std::string Util::monthAsHtmlString(const std::string &monthName, const DataStorage &data) {
    std::stringstream output;

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
    return output.str();
}
