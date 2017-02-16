#include "datagram.h"
#include "parsing.h"
#include "errors.h"

#include <cstdlib>
#include <iostream>
#include <string>

using namespace std;

bool good_ip_checker(string);

///
/// \param string
/// \return a correct form of IP address to a string with '.'
///         replaced to ' '

IP_address parse_IP(string s) {
    IP_address result;
    vector<string> parsedString;


    if (good_ip_checker(s) == true) {
        for (int i = 0; i < s.size(); i++) {
            if (s.at(i) == '.') {
                s.at(i) = ' ';
            }
        }
    } else {
        throw err_code::bad_ip_address;
    }


    try {
        parsedString = tokenize(s);
    }
    catch (runtime_error) {
        throw err_code::bad_ip_address;
    }


    if (parsedString.size() != 4) {
        throw err_code::bad_ip_address;
    }

    for (int i = 0; i < parsedString.size(); i++) {
        result[i] = parse_int(parsedString[i]);
        if (result[i] > 255) {
            throw err_code::bad_ip_address;
        }
    }

    return result;
}

///
/// helper function for parse_IP
/// \param : string
/// \return true when given string is in the correct IP address format
///         otherwise (other symbol than '.' || more than 3 '.' ||
///                    negative number) return false
bool good_ip_checker(string s) {

    int dotCounter = 0;

    for (int j = 0; j < s.size(); j++) {
        if (s.at(j) == '.') {
            dotCounter++;
        }
    }

    if (dotCounter != 3) {
        return false;
    }

    for(int i = 0; i < s.size(); i++) {
        if (s.at(i) < 46 || s.at(i) > 57) {
            return false;
        } else if (s.at(i) == 47) {
            return false;
        }
    }

    return true;
}