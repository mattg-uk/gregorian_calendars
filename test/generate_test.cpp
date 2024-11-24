

#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <sstream>

#include "calendar_types.h"
#include "generate.h"
#include "month_element.h"

using namespace testing;

// In the inheritance / virtual function dependency injection scheme, one passes mocks to classes
// which receive injected dependencies, for testing. Where they create the dependency, the source of
// the dependency has to be stubbed.
//
// But here, where the dependency is a template, so that the situation is more complex. There
// is no way to stop the function under test from generating source code unless we inject a
// specialization prior to it being called.
//
// THIS TEST IS A TEST OF THE SOURCE CODE, NOT THE COMPILED TRANSLATION UNIT.
// --> This allows the testing of a static function
// --------------------------------------------------------------------------------------------

Month MonthElement::operator()(const std::string &monthName, size_t dateStart, size_t dateEnd,
                               size_t monthStartDayIndex, size_t weekNumber) const {
    return Month();
}

MonthElement::MonthElement(const Properties &params) : properties(params) {}

class MockImpl {
  public:
    MOCK_METHOD(Year, populateYear, (int), (const));
};
class MockWriter {
  public:
    MOCK_METHOD(void, outputDocument, (std::iostream &, std::string, int, Years));
};

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

// --------------------------------------------------------------------------------------------
// TEST
// --------------------------------------------------------------------------------------------

TEST(GenerateTest, generate) {

    // We are able to leverage the template specialization, setting the expectations in the
    // specialization constructor rather than having to stub everything out.

    MockImpl testImplementation;
    std::stringstream testStream;
    size_t testCoreYear = coreTestYear;
    std::string testHtmlTemplate = "Dummy Template";
    MockWriter testWriter;

    Years writerExpectedCallData;
    for (auto year : expectedCallYears) {
        EXPECT_CALL(testImplementation, populateYear(year))
            .Times(1)
            .WillOnce(Return(generateDummyYear(year)));
        writerExpectedCallData.emplace_back(generateDummyYear(year));
    }

    EXPECT_CALL(testWriter,
                outputDocument(_, testHtmlTemplate, coreTestYear, writerExpectedCallData))
        .Times(1);
    generate(testImplementation, testStream, testCoreYear, testHtmlTemplate, testWriter);
}
