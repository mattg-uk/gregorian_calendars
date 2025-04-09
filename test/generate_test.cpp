

#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <sstream>

#include "calendar_types.h"
#include "generate.h"

using namespace testing;

class MockImpl {
  public:
    MOCK_METHOD(Year, populateYear, (int), (const));
};
class MockWriter {
  public:
    MOCK_METHOD(void, outputDocument, (std::iostream &, std::string, int, Years), (const));
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

    MockImpl testImplementation;
    std::stringstream testStream;
    size_t testCoreYear = coreTestYear;
    std::string testHtmlTemplate = "Dummy Template";
    MockWriter testWriter;

    Years writerExpectedCallData;

    // We expect three calls to populateYear, one for each of the three years
    for (auto year : expectedCallYears) {
        EXPECT_CALL(testImplementation, populateYear(year))
            .Times(1)
            .WillOnce(Return(generateDummyYear(year)));
        writerExpectedCallData.emplace_back(generateDummyYear(year));
    }
    
    // Whatever data our mock threw out, we expect it to arrive intact in the call to outputDocument 
    EXPECT_CALL(testWriter,
                outputDocument(_, testHtmlTemplate, coreTestYear, writerExpectedCallData))
        .Times(1);

    generateCalendarsGregorian(testStream, testCoreYear, testHtmlTemplate, testImplementation, testWriter);
}
