#include "gregorian_impl.h"
#include "html_writer.h"
#include "month_element.h"
#include <functional>
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <sstream>

#include "calendar_types.h"
#include "interface.h"
using namespace testing;

// STUBS
// --------------------------------------------------------------------------------------------

Month MonthElement::operator()(const std::string &monthName, size_t dateStart, size_t dateEnd,
                               size_t monthStartDayIndex, size_t weekNumber) const {
    return Month();
}

MonthElement::MonthElement(const Properties &props) : properties(props) {}

// MOCKS AND TEST INITIALISATION
// --------------------------------------------------------------------------------------------

class InterfaceTests : public ::testing::Test {

    class GregMock {
      public:
        MOCK_METHOD(Year, populateYear, (int year), (const));
    };

  public:
    InterfaceTests() { staticGregMock = &gregMock; }

    static inline size_t coreTestYear = 2000;
    static inline std::vector<size_t> expectedCallYears{1999, 2000, 2001};

    static Year generateDummyYear(size_t year) {
        Year returnValue(year, YearData());

        // The names don't have to be right, and it doesn't need to be a full year
        std::vector<std::string> dummyMonths{"Jan", "Feb", "Mar"};
        for (const auto &month : dummyMonths) {
            returnValue.second.emplace_back(month, MonthData());
        }
        return returnValue;
    }

    static GregMock *const getGregMock() { return staticGregMock; }
    GregMock gregMock;

  private:
    static inline GregMock *staticGregMock;
};

// MOCK PASSTHROUGH
// --------------------------------------------------------------------------------------------
template <> class GregorianImpl<MonthElement> {
  public:
    Year populateYear(int year) const { return InterfaceTests::getGregMock()->populateYear(year); }
};

// TEST
// --------------------------------------------------------------------------------------------

TEST_F(InterfaceTests, generateCalendarsFromInjection) {

    // We are able to leverage the template specialization, setting the expectations in the
    // specialization constructor rather than having to stub everything out.

    std::stringstream testStream;
    std::string htmlTemplate{"Dummy template"};

    for (auto year : InterfaceTests::expectedCallYears) {
        EXPECT_CALL(gregMock, populateYear(year))
            .Times(1)
            .WillOnce(Return(InterfaceTests::generateDummyYear(year)));
    }

    generateCalendarsGregorian(testStream, coreTestYear, htmlTemplate);
};
