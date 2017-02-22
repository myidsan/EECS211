#include "datagram.h"
#include "parsing.h"
#include "errors.h"

#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

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


///
/// \param string
/// \return a correct form of IP address to a string with '.'
///         replaced to ' '
IP_address::IP_address(string s) {
    std::array<int, 4> result;
    vector<string> parsedString;


    if (good_ip_checker(s) == true) {
        for (int i = 0; i < s.size(); i++) {
            if (s[i] == '.') {
                s[i] = ' ';
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

    ip_ = result;
}





bool IP_address::operator==(const IP_address& that) const
{
    for (int i = 0; i < this->ip_.size(); i++) {
        if (this->ip_[i] != that.ip_[i]) {
            return false;
        }
    }
    return true;
}

///
/// \return returns the first octad of a given ip address
///
int IP_address::first_octad() const
{
    return this->ip_[0];
}

std::ostream& operator<<(std::ostream& os, const IP_address& addr)
{
    return os << '"'
            << addr.ip_[0] << '.'
            << addr.ip_[1] << '.'
            << addr.ip_[2] << '.'
            << addr.ip_[3] << '"';
}

///
/// constructor : initializies the Datagram with given params
///
Datagram::Datagram(const IP_address& s, const IP_address& d, const string& m)
        : src_(s), dst_(d), msg_(m)
{};

IP_address Datagram::get_destination() const
{
    return dst_;
}

std::ostream& operator<<(std::ostream& os, const Datagram& dg)
{
    os << "datagram {";
    os << "src=" << dg.src_;
    os << ", dst=" << dg.dst_;
    os << ", length=" << dg.length_;
    os << ", msg=\"" << dg.msg_ << "\"";
    os << "}";
    return os;
}
