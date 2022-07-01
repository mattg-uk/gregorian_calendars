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

// This class represents a generalized calendar. The Gregorian specific implementation
// will be injected as a strategy.

#include <iostream>
#include <vector>

// Implementation is passed via stateless dependency injection
template <class IMPL>
class Calendar {
public:
    Calendar(int year, IMPL implementation);
    void htmlPrint(std::iostream& stream);
    int getYear();
private:
    IMPL m_impl;
    int m_year;
    std::vector<typename IMPL::MonthType_t> m_months;
};

template <class IMPL>
Calendar<IMPL>::Calendar(int year, IMPL implementation) : 
                                     m_impl(implementation),
                                     m_year(year), 
                                     m_months(m_impl.populateMonths(year))
{
}

template <class IMPL>
void Calendar<IMPL>::htmlPrint(std::iostream& stream)
{
    m_impl.htmlOut(stream, m_months);
}

template <class IMPL>
int Calendar<IMPL>::getYear()
{
    return m_year;
}

#endif  // CALENDAR_H