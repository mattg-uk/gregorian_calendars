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

#include <getopt.h>

#include <filesystem>
#include <fstream>
#include <iostream>
#include <regex>
#include <sstream>

#include "interface.h"

namespace fs = std::filesystem;

fs::path stylePath = fs::current_path() / fs::path("Config") / fs::path("calendar_style.html");

std::string help =
    "\nThis application outputs the calendars for a given year and those adjacent."
    "\n--year,\t\t-y\tSpecify the year to generate a calendar for."
    "\n--outfile,\t-o\tSpecify the file name for output (.html will be appended if not supplied)."
    "\n--help,\t\t-h\tDisplay this message"
    "\n";

int main(int argc, char *argv[]) {

    namespace fs = std::filesystem;
    static struct option longOptions[] = {{"help", no_argument, nullptr, 'h'},
                                          {"year", required_argument, nullptr, 'y'},
                                          {"outfile", required_argument, nullptr, 'o'},
                                          {0, 0, 0, 0}};

    // Since the filename and year are OPTIONS, not arguments, defaults must be provided
    fs::path filepath{"default.html"};
    size_t year = 2000;

    // Parse options: year, filename - halt afterward on error, and halt on help
    bool halt = false;
    bool argsDone = false;
    while (!argsDone) {
        int option_index;
        int opt = getopt_long(argc, argv, "hy:o:", longOptions, &option_index);

        switch (opt) {
        case 'h':
            halt = true;
            argsDone = true;
            break;
        case 'y': {
            std::stringstream parse{optarg};
            parse >> year;
            halt |= (parse.fail() || year < getLowerBound());
            break;
        }
        case 'o':
            filepath = fs::path{optarg};
            halt |= filepath.string().empty();
            break;
        default:
            argsDone = true;
            break;
        }
    }

    if (halt) {
        std::cout << help;
        exit(-1);
    }

    // Append .html if missing, create the file and check it really exists
    if (!std::regex_match(filepath.string(), std::regex(".*\\.html$"))) {
        filepath += std::string(".html");
    }

    // Check that the style file exists in ./Config, then open and read it
    if (fs::exists(stylePath)) {
        std::cout << "Found config file: " << stylePath << "\n"; // It will appear in quotes
    } else {
        std::cout << "Config file not found! :" << stylePath << "\n";
        exit(-1);
    }

    std::ifstream styleFile{stylePath};
    std::stringstream style;
    style << styleFile.rdbuf();

    // Create the file for ouput, check that output was successful
    std::fstream file{filepath, std::ios_base::out};
    if (!fs::exists(filepath)) {
        std::cout << "\nCould not create file: " << filepath.string();
        exit(-1);
    }

    std::cout << "Creating file: " << filepath.string() << " for year " << year << std::endl;

    generateCalendars(file, year, style.str());

    return 0;
}
