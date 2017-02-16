#include "errors.h"
#include "parsing.h"
#include "datagram.h"

#include <UnitTest++/UnitTest++.h>
#include <memory>
#include <iostream>
#include <stdexcept>
#include <vector>

using namespace std;


//
//// The tokenization of ‘   de@f.com  "ghi j-k " w == "z"’ is, in C++ syntax,
//// tokens == {"de@f.com", "ghi j-k ", "w", "==", "z"}
//// vector<string> tokens = tokenize("   de@f.com  \"ghi j-k \" w == \"z\"");
//
//TEST(parsing_Test) {
//    vector<string> expect3 = {"192", "168", "0", "1"};
//    CHECK_ARRAY_EQUAL(expect3, tokenize("192 168 0 1"), 4);
//
//    vector<string> expect = {"de@f.com", "ghi j-k ", "w", "==", "z"};
////    vector<string> tokens = tokenize("   de@f.com  \"ghi j-k \" w == \"z\"");
////    CHECK_EQUAL(expected, tokens);
////    CHECK(expected == tokens);
//    CHECK_ARRAY_EQUAL(expect, tokenize("   de@f.com  \"ghi j-k \" w == \"z\""), 5);
//
////    The tokenization of ‘hel"l"o world "" "eecs   211"’ is, in C++ syntax,
////    tokens == {"hel", "l", "o", "world", "", "eecs   211"}
////    vector<string> tokens = tokenize("hel\"l\"o world \"\" \"eecs   211\"");
//    vector<string> expect2 = {"hel", "l", "o", "world", "", "eecs   211"};
//    CHECK_ARRAY_EQUAL(expect2, tokenize("hel\"l\"o world \"\" \"eecs   211\""), 6);
//
//
////    vector<string> output = tokenize("192 168 0 1");
////    for (string token : output) {
////        cout << token;
////    }
////    CHECK_ARRAY_EQUAL(expect3, expect3, 4);
//
//}
//
//
/////
///// parse_int test
/////
TEST(parse_int_Test) {
    CHECK_EQUAL(0, parse_int("0"));
    CHECK_EQUAL(1, parse_int("1"));
    CHECK_EQUAL(29, parse_int("29"));
    CHECK_EQUAL(12345, parse_int("12345"));
    CHECK_EQUAL(456000, parse_int("00456000"));
    CHECK_EQUAL(1, parse_int("00000001"));

}
//

///
/// parse_IP test
///
TEST(parse_IP_Test) {
    IP_address arr1 = {192, 168, 0, 3};
    IP_address arrOrigin = parse_IP("192.168.0.3");
//    CHECK_EQUAL(arr1[1], arrOrigin[1]);
    CHECK_ARRAY_EQUAL(arr1, parse_IP("192.168.0.3"), 4);
}
