
#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "calendar.h"

#include <vector>
#include <sstream>

// Just an example of how one would go about testing the Calendar class using dependency injection and
// mocking.

class MockImpl {

public:
    typedef int MonthType_t;
    
    MOCK_METHOD(void, htmlOut, (std::iostream& stream, const std::vector<MonthType_t>& months), (const));
    MOCK_METHOD(std::vector<MonthType_t>, populateMonths, (int year), (const));

    void DelegateToFake() {
    ON_CALL(*this, htmlOut).WillByDefault([this](std::iostream& stream, 
                                                 const std::vector<MonthType_t>& months) 
        {
            for (auto& item : months) {
                stream << item << " ";
            } 
        });
    } 
};

TEST(CalendarTest, DataHandling) {
    
    using namespace testing;
    MockImpl impl;
    
    std::vector<MockImpl::MonthType_t> testVal {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};

    EXPECT_CALL(impl, populateMonths(2000)).Times(1).WillOnce(Return(testVal));

    Calendar testCal(2000, impl);

    // getYear is trivial to test
    EXPECT_EQ(2000, testCal.getYear());

    // htmlPrint needs to pass our stream to the mock, and the appropriate vector
    std::stringstream stream;
    
    EXPECT_CALL(impl, htmlOut(_,_)).Times(1);
    
    impl.DelegateToFake();
    testCal.htmlPrint(stream);

    // Check that the delegate got the right stream and value by checking it wrote that
    // correct value into that stream. It should be the same as the value constructed here.
    std::stringstream expectedStream;
    for (auto& item : testVal) {
        expectedStream << item << " ";
    }
    EXPECT_EQ(expectedStream.str(), stream.str());
}

