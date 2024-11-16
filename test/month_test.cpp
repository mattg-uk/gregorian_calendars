
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <sstream>
#include <vector>

#include "month_element.h"
#include "util.h"

struct UtilMock {
    MOCK_METHOD(std::string, monthAsHtmlString,
                (const std::string &monthName, const DataStorage &data), (const));
    static UtilMock *const get() { return mock; }

  protected:
    void set(UtilMock *const staticMock) { mock = staticMock; }

  private:
    static inline UtilMock *mock;
};

std::string Util::monthAsHtmlString(const std::string &monthName, const DataStorage &data) {
    return UtilMock::get()->monthAsHtmlString(monthName, data);
}

// The underlying mock should be set in a scope outside of the Test Body or Mock
// Constructor, but not be fully static. Otherwise, it leaks out of the test.
class MonthTest : public ::testing::Test, private UtilMock {
  public:
    MonthTest() { UtilMock::set(&staticMock); }
    UtilMock staticMock;
};

TEST_F(MonthTest, DataHandling) {
    using namespace testing;
    // The (very) hyptothetical Davidian Calendar has 4 days per week, and 6 months a
    // year, and the days of the week are called, A, B, C, D. It's the 1000th year of
    // David, which started on 'A' day. Freakin' A!
    // The third month of the year is the month of Dave.
    // Bizarely, it starts on the 3rd day of the month, which in this case, is 'C' day.
    // Noone knows what happened to the first two days, but at least we know its 'generic'.
    // Because it has 19 days, it ends on the 21st, on 'A' day.
    // Since the year started on 'A' day, Dave starts half-way through the 11th week.

    // Test parameters
    Properties davidianCalendar{
        4,
        std::vector<std::string>{"Davidus", "David", "Dave", "Davina", "Dawid", "Bowie"},
        std::vector<size_t>{20, 22, 19, 22, 20, 22},
        std::vector<std::string>{"Wk", "A", "B", "C", "D"},
        std::vector<CellType>{CellType::Label, CellType::Workday, CellType::Workday,
                              CellType::Weekend1, CellType::Weekend2},
        std::vector<CellType>{CellType::Label, CellType::Label, CellType::Label, CellType::Weekend1,
                              CellType::Weekend2}};

    // System under Test
    MonthElement testElement("Dave", size_t(3), size_t(21), size_t(2), size_t(11),
                             davidianCalendar);

    // Expected outputs
    // Construct the vector that we expect MonthElement to hold and pass to Util.
    std::string expectedMonthName("Dave");
    std::string expectedStreamState("Mock return value");

    DataStorage expectedDataVector{
        {CellType::Label, "Wk"},    {CellType::Label, "A"},     {CellType::Label, "B"},
        {CellType::Weekend1, "C"},  {CellType::Weekend2, "D"},  {CellType::Label, "11"},
        {CellType::Workday, ""},    {CellType::Workday, ""},    {CellType::Weekend1, "3"},
        {CellType::Weekend2, "4"},  {CellType::Label, "12"},    {CellType::Workday, "5"},
        {CellType::Workday, "6"},   {CellType::Weekend1, "7"},  {CellType::Weekend2, "8"},
        {CellType::Label, "13"},    {CellType::Workday, "9"},   {CellType::Workday, "10"},
        {CellType::Weekend1, "11"}, {CellType::Weekend2, "12"}, {CellType::Label, "14"},
        {CellType::Workday, "13"},  {CellType::Workday, "14"},  {CellType::Weekend1, "15"},
        {CellType::Weekend2, "16"}, {CellType::Label, "15"},    {CellType::Workday, "17"},
        {CellType::Workday, "18"},  {CellType::Weekend1, "19"}, {CellType::Weekend2, "20"},
        {CellType::Label, "16"},    {CellType::Workday, "21"},  {CellType::Workday, ""},
        {CellType::Weekend1, ""},   {CellType::Weekend2, ""},   {CellType::Label, ""},
        {CellType::Workday, ""},    {CellType::Workday, ""},    {CellType::Weekend1, ""},
        {CellType::Weekend2, ""}};

    // Set expectations and make the driving call
    EXPECT_CALL(staticMock, monthAsHtmlString(expectedMonthName, expectedDataVector)).Times(1);
    ON_CALL(staticMock, monthAsHtmlString)
        .WillByDefault([&](const std::string &monthName, const DataStorage &data) {
            return expectedStreamState;
        });
    std::stringstream actualStreamState;
    testElement.htmlOut(actualStreamState);

    EXPECT_EQ(expectedStreamState, actualStreamState.str());
}
