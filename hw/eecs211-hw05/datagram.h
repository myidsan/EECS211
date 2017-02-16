#pragma once

#include <array>
#include <string>

using IP_address = std::array<int, 4>;

IP_address parse_IP(std::string s);
bool good_ip_checker(std:: string s);