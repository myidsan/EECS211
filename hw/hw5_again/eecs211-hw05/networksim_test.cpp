#include "errors.h"
#include "parsing.h"
#include "datagram.h"

#include <UnitTest++/UnitTest++.h>
#include <memory>
#include <iostream>
#include <stdexcept>

using namespace std;


#define CHECK_THROW_ENUM(expression, EnumType, EnumValue) \
   UNITTEST_MULTILINE_MACRO_BEGIN \
   bool caught_ = false; \
   try { expression; } \
   catch (EnumType e) { caught_ = e == EnumType::EnumValue; } \
   catch (...) {} \
   if (!caught_) \
      UnitTest::CurrentTest::Results()->OnTestFailure( \
          UnitTest::TestDetails(*UnitTest::CurrentTest::Details(), \
                                __LINE__), \
          "Expected exception: \"" #EnumValue "\" not thrown"); \
   UNITTEST_MULTILINE_MACRO_END


TEST(parsing_Test) {
    vector<string> expect3 = {"192", "168", "0", "1"};
    CHECK_ARRAY_EQUAL(expect3, tokenize("192 168 0 1"), 4);

    vector<string> expect = {"de@f.com", "ghi j-k ", "w", "==", "z"};
    CHECK_ARRAY_EQUAL(expect, tokenize("   de@f.com  \"ghi j-k \" w == \"z\""), 5);

    vector<string> expect2 = {"hel", "l", "o", "world", "", "eecs   211"};
    CHECK_ARRAY_EQUAL(expect2, tokenize("hel\"l\"o world \"\" \"eecs   211\""), 6);

    // when the given string ends without any space or double quotation
    vector<string> expect4 = {"what", "a", "beautiful", "day", "we", "have", "to", "day"};
    CHECK_ARRAY_EQUAL(expect4, tokenize("     what a beautiful day we have to day"), 8);

    vector<string> expect5 = {"what", "a", "beautiful", "day", "we", "have", "to", "day"};
    CHECK_ARRAY_EQUAL(expect5, tokenize("     what a beautiful day we have to day "), 8);

    vector<string> expect6 = {};
    CHECK_ARRAY_EQUAL(expect6, tokenize(" "), 0);

    vector<string> expect7 = {"."};
    CHECK_ARRAY_EQUAL(expect7, tokenize(" . "), 1);

    vector<string> expect8 = {""} ;
    CHECK_ARRAY_EQUAL(expect8, tokenize(" "), 0);

    vector<string> expect9 = {""} ;
    CHECK_ARRAY_EQUAL(expect9, tokenize("   "), 0);

    vector<string> expect10 = {"ab"};
    CHECK_ARRAY_EQUAL(expect10, tokenize(" ab"), 1);

    vector<string> expect11 = {"ab", "cd"};
    CHECK_ARRAY_EQUAL(expect11, tokenize(" ab cd"), 2);

    // empty cases
    vector<string> expect12{};
    CHECK_ARRAY_EQUAL(expect12, tokenize("      "), 0);
    CHECK(tokenize("").empty());
    CHECK(tokenize(" ").empty());
    CHECK(tokenize("    ").empty());

    vector<string> expect13 = {"h"};
    CHECK_ARRAY_EQUAL(expect13, tokenize("h     "), 1);

    // "\"\"" as input, aka two consecutive "s as input
    vector<string> expect14 = {""};
    CHECK_ARRAY_EQUAL(expect14, tokenize("\"\""), 1);
    // "\\" as input
    vector<string> expect15 = {"\\"};
    CHECK_ARRAY_EQUAL(expect15, tokenize("\\"), 1);
}


TEST(parsing_ERROR) {
    // odd number of double quotation marks
    CHECK_THROW(tokenize("hel\"l\"o world \"\"\" \"eecs 211\"") ,runtime_error);
    CHECK_THROW(tokenize("much room\"f\"or\"error eecs211"), runtime_error);
    // odd number of dq in a string variable
    string mess4 = "hi\" there I'm hungry";
    CHECK_THROW(tokenize(mess4), runtime_error);
}


TEST(parse_int_Test) {
    CHECK_EQUAL(0, parse_int("0"));
    CHECK_EQUAL(1, parse_int("1"));
    CHECK_EQUAL(29, parse_int("29"));
    CHECK_EQUAL(12345, parse_int("12345"));
    CHECK_EQUAL(456000, parse_int("00456000"));
    CHECK_EQUAL(1, parse_int("00000001"));

}

TEST(parse_int_ERROR) {
    // negative integer as input
    CHECK_THROW(parse_int("-10"), runtime_error);
    // random symbol that is not a positive interger or zero
    CHECK_THROW(parse_int("&"), runtime_error);
    // number followed by symbols
    CHECK_THROW(parse_int("897^&^*"), runtime_error);
    // ASCII value for \ is 47 while "0" is 48
    CHECK_THROW(parse_int("\\"), runtime_error);
    // space
    CHECK_THROW(parse_int(" "), runtime_error);
    // numbers with space in the middle
    CHECK_THROW(parse_int("10203 090 "), runtime_error);
    // numbers with space at the end
    CHECK_THROW(parse_int("10203090 "), runtime_error);
    // new lines
    CHECK_THROW(parse_int("\n"), runtime_error);
    // new lines with numbers
    CHECK_THROW(parse_int("10 \n 20"), runtime_error);
    // negative number
    CHECK_THROW(parse_int("10 -10"), runtime_error);
    // number with symbol
    CHECK_THROW(parse_int("10^"), runtime_error);
    // empty input
    CHECK_THROW(parse_int(""), runtime_error);
    // string of characters
    CHECK_THROW(parse_int("just a normal word"), runtime_error);
}


TEST(parse_IP_Test) {
    // normal ip address without 0
    IP_address arr1 = {192, 168, 1, 3};
    CHECK_ARRAY_EQUAL(arr1, parse_IP("192.168.1.3"), 4);  //
    // normal ip address with 0
    IP_address arr2 = {255, 255, 255, 0};
    CHECK_ARRAY_EQUAL(arr2, parse_IP("255.255.255.0"), 4);
    // all zeros
    IP_address arr3 = {0, 0, 0, 0};
    CHECK_ARRAY_EQUAL(arr3, parse_IP("0.0.0.0"), 4);
    // element starting with 0 but not 0
    IP_address arr4 = {192, 3, 23, 255};
    CHECK_ARRAY_EQUAL(arr4, parse_IP("192.003.23.255"), 4);
    // string with \.
    IP_address arr5 = {104, 46, 34, 0};
    CHECK_ARRAY_EQUAL(arr5, parse_IP("104.46\.34.0"), 4);
}


TEST(parse_IP_ERROR) {
    // character other than number of dot(.) aka wrong symbol
    CHECK_THROW_ENUM(parse_IP("192.168*10.1"), err_code, bad_ip_address);
    // less than 3 dots
    CHECK_THROW_ENUM(parse_IP("192.168,10.1"), err_code, bad_ip_address);
    // more than 4 segement of IP (or more than 3 dots)
    CHECK_THROW_ENUM(parse_IP("192.168.10.1.10"), err_code, bad_ip_address);
    // 4 segements but more than 3 dots)
    CHECK_THROW_ENUM(parse_IP("192.168.10..1"), err_code, bad_ip_address);
    //wrong length on one segment
    CHECK_THROW_ENUM(parse_IP("2555.25.25.25"), err_code, bad_ip_address);
    //missing one segment in one of the 4 elem array
    CHECK_THROW_ENUM(parse_IP("255..255.10"), err_code, bad_ip_address);
    //missig the last one, but correct number of dots
    CHECK_THROW_ENUM(parse_IP("233.33.233."), err_code, bad_ip_address);
    //negative number
    CHECK_THROW_ENUM(parse_IP("-172.16.18.1"), err_code, bad_ip_address);
    CHECK_THROW_ENUM(parse_IP("172.16.18.-1"), err_code, bad_ip_address);
    // element exceeding normal range (0~255)
    CHECK_THROW_ENUM(parse_IP("256.255.255.0"), err_code, bad_ip_address);
    // just too big & single element
    CHECK_THROW_ENUM(parse_IP("255555555555"), err_code, bad_ip_address);
    //two segments only & wrong length
    CHECK_THROW_ENUM(parse_IP("23333.223."), err_code, bad_ip_address);
    //
    // parse_IP: runtime_error from tokenize but
    // catches and throws bad_ip_address
    CHECK_THROW_ENUM(parse_IP("192.168.0.\"1"), err_code, bad_ip_address);
    CHECK_THROW_ENUM(parse_IP("104.46\\.34.0"), err_code, bad_ip_address);
    CHECK_THROW_ENUM(parse_IP("192.\"*168.0.\"1"), err_code, bad_ip_address);
    CHECK_THROW_ENUM(parse_IP("192.168.0.((1"), err_code, bad_ip_address);
}





