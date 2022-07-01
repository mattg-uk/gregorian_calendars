

// This class represents a generalized calendar. The Gregorian specific implementation
// will be injected as a strategy.

#ifndef CALENDAR_H
#define CALENDAR_H

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