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

#ifndef CALENDAR_H
#define CALENDAR_H

#include "calendar_types.h"

// The Calendar is a wrapper to store the output from the chosen implementation,
// upon instantiation the existance of the required functions will be verified.
template <class IMPL> class Calendar {
  public:
    explicit Calendar(int year, IMPL &implementation);
    Year getData();

  private:
    Year data;
};

template <class IMPL>
Calendar<IMPL>::Calendar(int year, IMPL &implementation)
    : data{implementation.populateMonths(year)} {}

// Get data generates a copy each time it is used to avoid lifetime issues
template <class IMPL> Year Calendar<IMPL>::getData() { return data; }

#endif // CALENDAR_H
