#include "prime_lib.h"

#include <iostream>
#include <stdexcept>
#include <vector>
#include <cmath>

using namespace std;

//
// returns a boolean value whether given number is a prime number
//
bool is_prime(int p)
{
    if (p < 0)
        throw runtime_error("input must be a positive integer.");
    if (p ==1)
        return false;

    int i; int wall = sqrt(p); // int on sqrt will round down the given value to fit the wall

        for (i=2; i<=wall; i++) {
            if (p%i == 0)
                return false;
        }

        return true;

}

//
// gets the vector from vector<int> generate_primes(int n) and check if the given number, p, is a prime number
//
bool check_is_prime(const std::vector<int>& primes, int p)
{
    if (primes.size() == 0)
        throw runtime_error("Primes can not be an empty vector");
    if (p == 1)
        return false;

    for (int pr: primes) {
        if (p == pr)
            return true;
        else if (p % pr == 0)
            return false;
    }
    return true;
}

//
// returns a vector of prime numbers smaller than the input number
//
vector<int> generate_primes(int n)
{
    if (n < 0)
        throw runtime_error("input must be a positive integer.");

    vector<bool> sieve; vector<int> primes;
    int wall = ceil(sqrt(n));

    for (int i = 0; i<n+1; i++) {
        sieve.push_back(true);
    }

    for (int i = 2; i<=wall; i++) {
        for (int j = 2; (i * j) < sieve.size(); j++) {
            if (sieve[i] == true)
                sieve[i * j] = false;
        }
    }

    for (int i =2; i<n+1; i++) {
        if (sieve[i] == true)
            primes.push_back(i);
    }

    return primes;

}

