#include "parsing.h"
#include "interface.h"

#include <iostream>
#include <string>
#include <vector>

using namespace std;

///
/// \param string of integers
/// \return a integer value of a given string of integer
int parse_int(const string& s) {
    int result = 0;

    if (s.size() == 0) {
        throw runtime_error("string is empty");
    }

    for (int i = 0; i < s.size(); i++) {
        if ((s.at(i) == '0') && (s.size() == 1)) {
            return 0;
        } else if (s.at(i) < '0' || s.at(i) > '9') {
            throw runtime_error("string must consist of "
                                        "positive integers and zero");
        } else {
            result = result*10 + (s.at(i) - 48);
        }
    }
    return result;
}

///
/// \param string
/// \return parses the string based on 1)double quotation 2)space
vector<string> tokenize(const string& line)
{
    vector<string> result;
    int dqCounter = 0; int front = 0, end = 1;

    for(int i = 0; i < line.size(); i++) {
        if (line.at(i) == '\"') {
            dqCounter++;
        }
    }

    if (dqCounter%2 != 0) {
        throw runtime_error("double quotes must be in pair");
    }

    for (front = 0; front < line.size(); ) {
        end = front + 1;
        if ( (front == line.size() - 1) && (line.at(front) != ' ') ) {
            result.push_back(line.substr(front,1));
            break;
        } else if (line.at(front) == '\"') {
            while ( (line.at(end) != '\"') && (end < line.size()) ) {
                end++;
            }
            result.push_back(line.substr(front+1, end-front-1));
            front = end + 1;
        } else if (line.at(front) != ' ') {
            while ( (line.at(end) != '\"') && (line.at(end) != ' ')
                    && (end < line.size()) ) {
                end++;
                if (end == line.size()) {
                    break;
                }
            }
            result.push_back(line.substr(front, end - front));
            front = end;
        } else {
            front++;
        }
    }

    return result;
}
