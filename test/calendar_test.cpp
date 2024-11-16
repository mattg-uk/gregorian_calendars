
#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "calendar.h"

#include <sstream>
#include <vector>
// Just an example of how one would go about testing the Calendar class using dependency injection
// and mocking.

class MockImpl {

  public:
    using MonthType_t = int;

    MOCK_METHOD(std::vector<MonthType_t>, populateMonths, (int year), (const));
    static void htmlOut(std::iostream &stream, const std::vector<MonthType_t> &months) {
        StaticMock::get()->htmlOut(stream, months);
    };

    // htmlOut is static: delegates to a StaticMock object
    struct StaticMock {
        MOCK_METHOD(void, htmlOut, (std::iostream & stream, const std::vector<MonthType_t> &months),
                    (const));
        static StaticMock *const get() { return mock; }

      protected:
        void set(StaticMock *const staticMock) { mock = staticMock; }

      private:
        static inline StaticMock *mock;
    };
};

// The underlying mock should be set in a scope outside of the Test Body or Mock
// Constructor, but not be fully static. Otherwise, it leaks out of the test.
class CalendarTest : public ::testing::Test, private MockImpl::StaticMock {
  public:
    CalendarTest() { MockImpl::StaticMock::set(&staticMock); }
    MockImpl::StaticMock staticMock;
};

TEST_F(CalendarTest, DataHandling) {
    using namespace testing;
    std::vector<MockImpl::MonthType_t> testVal{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};

    MockImpl impl;
    std::stringstream actualStream;
    std::stringstream expectedStream;
    for (auto &item : testVal) {
        expectedStream << "Mock month:" << item << " ";
    }

    // We verify that that the call values are as expected, and that the correct stream
    // is modified by simulating the expected stream output in the callee.

    EXPECT_CALL(impl, populateMonths(2000)).Times(1).WillOnce(Return(testVal));
    EXPECT_CALL(staticMock, htmlOut(_, testVal)).Times(1);
    ON_CALL(staticMock, htmlOut)
        .WillByDefault([](std::iostream &stream, const std::vector<MockImpl::MonthType_t> &months) {
            for (auto &item : months) {
                stream << "Mock month:" << item << " ";
            }
        });

    Calendar testCal(2000, impl);
    testCal.htmlPrint(actualStream);
    EXPECT_EQ(expectedStream.str(), actualStream.str());
}
