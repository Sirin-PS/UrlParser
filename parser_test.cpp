#include "parser.h"
#include <iostream>
#include <gtest/gtest.h>

class TestFunctionUrl : public ::testing::Test {
};

TEST_F(TestFunctionUrl, ZeroString)
{
    std::string url1 = "";
    Parser test_object{url1};
    std::string msg1 = test_object.GetInfoVect()[0].description;
    std::string msg2 = "string is empty";
    ASSERT_EQ(msg1, msg2);
}

TEST_F(TestFunctionUrl, StringOfWhitespaces)
{
    std::string url1 = "   \n \t\n   \r ";
    Parser test_object{url1};
    std::string msg1 = test_object.GetInfoVect()[0].description;
    std::string msg2 = "string is empty";
    ASSERT_EQ(msg1, msg2);
}

TEST_F(TestFunctionUrl, NotValidatedString)
{
    std::string url1 = "7894kjdv/ 08";
    Parser test_object{url1};
    std::string msg1 = test_object.GetInfoVect()[0].description;
    std::string msg2 = "string is not a URL";
    ASSERT_EQ(msg1, msg2);
}

TEST_F(TestFunctionUrl, StringWithWhitespace)
{
    std::string url1 = "ftp://:@somehost: 1234/cwd1/cwd2/cwd3";
    Parser test_object{url1};
    std::string msg1 = test_object.GetInfoVect()[0].description;
    std::string msg2 = "string is not a URL";
    ASSERT_EQ(msg1, msg2);
}

TEST_F(TestFunctionUrl, StringForFrim)
{
    std::string url1 = " \thttp://somehost:1234/path1?search \n ";
    Parser test_object{url1};
    std::string res = test_object.GetStoredURL();
    std::string check = "http://somehost:1234/path1?search";
    ASSERT_EQ(res, check);
}

TEST_F(TestFunctionUrl, LongExample)
{
    std::string url1 = "https://somehost/path1?search_for_research";
    Parser test_object{url1};
    int res = test_object.GetInfoVect().size();
    ASSERT_TRUE(res = 5);
}

TEST_F(TestFunctionUrl, ShortExample)
{
    std::string url1 = "mailto:some-addr.ru";
    Parser test_object{url1};
    int res = test_object.GetInfoVect().size();
    ASSERT_TRUE(res = 2);
}

int main(int argc, char **argv)
{    
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}