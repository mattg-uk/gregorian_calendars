
#include "calendar_types.h"
#include "html_writer.h"
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <sstream>
#include <string>

class HtmlTest : public ::testing::Test {
  public:
    const MonthData testMonthData = {{CellType::Label, "Arbitrary"},
                                     {CellType::Workday, "Test"},
                                     {CellType::Weekend1, "Input"},
                                     {CellType::Weekend2, "Data"}};
    YearData testYearData{{"Month1", testMonthData}, {"Month2", testMonthData}};
    Year testYear1{1000, testYearData};
    Year testYear2{2000, testYearData};
    Year testYear3{2500, testYearData};
    Years testYears{testYear1, testYear2, testYear3};

    std::string expectedYearMonths() {
        std::string expectedOutput;
        expectedOutput += "  <mon>\n";
        expectedOutput += "    <div class=\"month-name\">Month1</div>\n";
        expectedOutput += "    <div class=\"grid-container\">\n";
        expectedOutput += "      <div class=\"label\">Arbitrary</div>\n";
        expectedOutput += "      <div class=\"day\">Test</div>\n";
        expectedOutput += "      <div class=\"spec1\">Input</div>\n";
        expectedOutput += "      <div class=\"spec2\">Data</div>\n";
        expectedOutput += "    </div>\n";
        expectedOutput += "  </mon>\n";
        expectedOutput += "  <mon>\n";
        expectedOutput += "    <div class=\"month-name\">Month2</div>\n";
        expectedOutput += "    <div class=\"grid-container\">\n";
        expectedOutput += "      <div class=\"label\">Arbitrary</div>\n";
        expectedOutput += "      <div class=\"day\">Test</div>\n";
        expectedOutput += "      <div class=\"spec1\">Input</div>\n";
        expectedOutput += "      <div class=\"spec2\">Data</div>\n";
        expectedOutput += "    </div>\n";
        expectedOutput += "  </mon>\n";
        return expectedOutput;
    }
};

TEST_F(HtmlTest, YearHeader) {
    std::stringstream testStreamOutput;

    std::string expectedOutput;
    expectedOutput += "<header id=\"year_2000\">Calendar Year 2000</header>\n";
    expectedOutput += "\n";
    expectedOutput += "<section>\n";
    expectedOutput += "  <div class=\"year_selector\">\n";
    expectedOutput += "    <a href=\"#year_1000\">1000</a>\n";
    expectedOutput += "    2000\n";
    expectedOutput += "    <a href=\"#year_2500\">2500</a>\n";
    expectedOutput += "  </div>\n";

    HtmlWriter::outputYearHeaderHtml(testStreamOutput, 2000, testYears);
    EXPECT_EQ(testStreamOutput.str(), expectedOutput);
}

TEST_F(HtmlTest, MonthHtml) {
    // The test needs to verify the output format and contents: a month open tag, a div with
    // the month name, and a container filled with test data.
    std::stringstream testStreamOutput;
    std::string testMonthName = std::string("Test Month");

    std::string expectedOutput;
    expectedOutput += "  <mon>\n";
    expectedOutput += "    <div class=\"month-name\">Test Month</div>\n";
    expectedOutput += "    <div class=\"grid-container\">\n";
    expectedOutput += "      <div class=\"label\">Arbitrary</div>\n";
    expectedOutput += "      <div class=\"day\">Test</div>\n";
    expectedOutput += "      <div class=\"spec1\">Input</div>\n";
    expectedOutput += "      <div class=\"spec2\">Data</div>\n";
    expectedOutput += "    </div>\n";
    expectedOutput += "  </mon>\n";

    HtmlWriter::outputMonthHtml(testStreamOutput, testMonthName, testMonthData);
    EXPECT_EQ(testStreamOutput.str(), expectedOutput);
}

TEST_F(HtmlTest, YearMonthsHtml) {
    std::stringstream testStreamOutput;

    // The expected year months goes in a function because it will be needed
    // repeatedly
    std::string expectedOutput = expectedYearMonths();

    HtmlWriter::outputYearMonthsHtml(testStreamOutput, testYearData);
    EXPECT_EQ(testStreamOutput.str(), expectedOutput);
}

TEST_F(HtmlTest, DocumentFooter) {
    std::stringstream testStreamOutput;

    std::string expectedOutput;
    expectedOutput += "<footer></footer>\n\n";
    expectedOutput += "</body>\n\n";
    expectedOutput += "<script>\n";
    expectedOutput += "  location.replace('#year_2000')\n";
    expectedOutput += "</script>\n\n";
    expectedOutput += "</html>\n";

    HtmlWriter::outputDocumentFooterHtml(testStreamOutput, 2000);
    EXPECT_EQ(testStreamOutput.str(), expectedOutput);
}

TEST_F(HtmlTest, outputDocument) {

    //  The test is to ensure that the template, body directives, year headers,
    //  data, section close, document footer appear in the correct order.

    std::string testTemplate("<<<Test template>>>\n");
    std::stringstream testStreamOutput;

    std::string expectedOutput;
    expectedOutput += "<<<Test template>>>\n";
    expectedOutput += "<body>\n\n";
    expectedOutput += "<header id=\"year_1000\">Calendar Year 1000</header>\n";
    expectedOutput += "\n";
    expectedOutput += "<section>\n";
    expectedOutput += "  <div class=\"year_selector\">\n";
    expectedOutput += "    1000\n";
    expectedOutput += "    <a href=\"#year_2000\">2000</a>\n";
    expectedOutput += "    <a href=\"#year_2500\">2500</a>\n";
    expectedOutput += "  </div>\n";
    expectedOutput += expectedYearMonths();
    expectedOutput += "</section>\n\n";
    expectedOutput += "<header id=\"year_2000\">Calendar Year 2000</header>\n";
    expectedOutput += "\n";
    expectedOutput += "<section>\n";
    expectedOutput += "  <div class=\"year_selector\">\n";
    expectedOutput += "    <a href=\"#year_1000\">1000</a>\n";
    expectedOutput += "    2000\n";
    expectedOutput += "    <a href=\"#year_2500\">2500</a>\n";
    expectedOutput += "  </div>\n";
    expectedOutput += expectedYearMonths();
    expectedOutput += "</section>\n\n";
    expectedOutput += "<header id=\"year_2500\">Calendar Year 2500</header>\n";
    expectedOutput += "\n";
    expectedOutput += "<section>\n";
    expectedOutput += "  <div class=\"year_selector\">\n";
    expectedOutput += "    <a href=\"#year_1000\">1000</a>\n";
    expectedOutput += "    <a href=\"#year_2000\">2000</a>\n";
    expectedOutput += "    2500\n";
    expectedOutput += "  </div>\n";
    expectedOutput += expectedYearMonths();
    expectedOutput += "</section>\n\n";
    expectedOutput += "<footer></footer>\n\n";
    expectedOutput += "</body>\n\n";
    expectedOutput += "<script>\n";
    expectedOutput += "  location.replace('#year_2000')\n";
    expectedOutput += "</script>\n\n";
    expectedOutput += "</html>\n";

    HtmlWriter writer;
    writer.outputDocument(testStreamOutput, testTemplate, 2000, testYears);
    EXPECT_EQ(testStreamOutput.str(), expectedOutput);
}
