
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

    MOCK_METHOD(Year, populateMonths, (int year), (const));
};

TEST(CalendarTest, DataHandling) {
    using namespace testing;
    const size_t dummyYear = 1999;
    const auto dummyMonth1 = Month{"Jan", MonthData()};
    const auto dummyMonth2 = Month{"Feb", MonthData()};
    const auto dummyMonth3 = Month{"Mar", MonthData()};

    Year testVal{dummyYear, {dummyMonth1, dummyMonth2, dummyMonth3}};

    MockImpl impl;

    // All this class actually does now is to call implementation.populateMonths and store
    // the result. If the get data result is the same --> job done.

    EXPECT_CALL(impl, populateMonths(1999)).Times(1).WillOnce(Return(testVal));

    Calendar testCal(1999, impl);
    EXPECT_EQ(testVal, testCal.getData());
}
