#include "parsing.h"
#include "interface.h"

#include <iostream>
#include <string>
#include <vector>

using namespace std;

int parse_int(const string& s) {
    int front = 0, result = 0;

    if (s.size() == 1 && s[0] == '0') {
        return 0;
    }
    while (s.at(front) == '0') {
        front++;
    }

    for (int i = front; i < s.size(); i++) {
        if (s.at(i) >= 48 && s.at(i) <= 57 )
            result = result*10 + (s.at(i)-48);
        else
            throw runtime_error("string must consist of positive integers and zero");
    }

    return result;

}

vector<string> tokenize(const string& line) {
    // [YOUR CODE HERE]
    cout << "TOKENIZE CALLED WITH LINE: " << line << "\n";
    vector<string> result = {};
    int curr = 0, dqCounter = 0;
    int end = curr + 1;

    // double quote pair checker
    for (int i = 0; i < line.size(); i++) {
        if (line.at(i) == '\"') {
            dqCounter++;
        }
    }

    if (dqCounter%2 != 0) {
        throw runtime_error("number of double quotation marks must be even number");
    }

    cout << "TEST TEST TEST\n";
    for (curr = 0; curr < line.size(); ) {
        end = curr + 1;
        cout << "CURR IS " << curr << "\n";
        cout << "END IS " << end << "\n";
        if (curr == line.size() - 1 ) {
            cout << "CURR IS AT THE END NOW!!!!!!!!!!!\n";
            result.push_back(line.substr(curr, 1));
            break;
        } else if (line.at(curr) == '\"') {
            while (line.at(end) != '\"' && (end < line.size())) {
                end++;
            }
            cout << "curr: " << curr << ", end: " << end << ", line size: " << line.size() << "\n";
            result.push_back(line.substr(curr + 1, end-curr-1));
            curr = end + 1;
        } else if (line.at(curr) != ' ') {

            while ((line.at(end) != '\"') && (line.at(end) != ' ') && (end < line.size())) {
                end++;
            }

            cout << "curr: " << curr << ", end: " << end << ", line size: " << line.size() << "\n";


            result.push_back(line.substr(curr, end-curr));
            curr = end + 1;
        } else {
            curr++;
        }
    }

    cout << "RETURNING FROM PARSESTRING NOW!!! LINE WAS: " << line << "\n";

    return result;
}




