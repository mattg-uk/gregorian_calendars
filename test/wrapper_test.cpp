#include <gmock/gmock.h>
#include <gtest/gtest.h>

using namespace testing;

// Under test
#include "wrapper.h"

// Required for the stubs using for TU under test compilation
#include "html_writer.h"
#include "month_element.h"

// Required for the template specialization (interception) that will be used in testing
// (Similar to replacing generate production code with a stub / mock)

#include "generate.h"
#include "gregorian_impl.h"

// STUBS -------------------------------------------------------------------------------------
// Minimum implementation to instantiate GregorianImpl<MonthElement>

Month MonthElement::operator()(const std::string &monthName, size_t dateStart, size_t dateEnd,
                               size_t monthStartDayIndex, size_t weekNumber) const {
    return Month();
}

MonthElement::MonthElement(const Properties &params) : properties(params) {}

void HtmlWriter::outputDocument(std::iostream &output, const std::string &htmlTemplate,
                                size_t coreYear, const Years &data) {}

// Test class, required to support the mock used for the generate function
// -------------------------------------------------------------------------------------

class WrapperTest : public ::testing::Test {
    class GenerateMock {
      public:
        MOCK_METHOD(void, generate,
                    (GregorianImpl<MonthElement> implemenation, std::iostream &file,
                     size_t coreYear, std::string htmlTemplate, HtmlWriter writer),
                    (const));
    };

  public:
    WrapperTest() { mock = &mockGenerate; }
    GenerateMock mockGenerate;
    static inline GenerateMock *const getMock() { return mock; }

  private:
    static inline GenerateMock *mock;
};

// TEMPLATE INSTANTIATION INTERCEPT ----------------------------------------------------------------
template <>
void generate<GregorianImpl<MonthElement>, HtmlWriter>(GregorianImpl<MonthElement> &implementation,
                                                       std::iostream &file, size_t coreYear,
                                                       std::string htmlTemplate,
                                                       HtmlWriter &writer) {
    WrapperTest::getMock()->generate(implementation, file, coreYear, htmlTemplate, writer);
}
// TEMPLATE INSTANTIATION INTERCEPT END ------------------------------------------------------------

TEST_F(WrapperTest, callWrapper) {
    std::stringstream file;
    size_t coreTestYear = 2000;
    std::string htmlTemplate{"Dummy template"};

    EXPECT_CALL(mockGenerate, generate(_, _, coreTestYear, htmlTemplate, _)).Times(1);
    generateCalendarsGregorian(file, coreTestYear, htmlTemplate);

    size_t expectedYear = 1582;
    size_t actualYear = getLowerGregorianBound();
    EXPECT_EQ(expectedYear, actualYear);
}
