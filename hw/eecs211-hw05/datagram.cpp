#include "datagram.h"
#include "parsing.h"
#include "errors.h"

#include <cstdlib>
#include <iostream>
#include <string>

using namespace std;

bool good_ip_checker(string s) {

    for(int i = 0; i < s.size(); i++) {
        if (s.at(i) < 46 || s.at(i) > 57) {
            return false;
        } else if (s.at(i) == 47) {
            return false;
        }
    }

    return true;
}

IP_address parse_IP(string s)
{
    IP_address result = {};


    /// converts good_ip_address dots to spaces
    if (good_ip_checker(s) == true) {
        for(int i = 0; i < s.size(); i++) {
            if (s.at(i) == '.') {
                s[i] = ' ';
            }
        }
    } else {
        throw err_code::bad_ip_address;
    }

    vector<string> parsedString = tokenize(s);

    for (int j = 0; j < parsedString.size(); j++) {
        result[j] = parse_int(parsedString[j]);
    }

    return result;
}






