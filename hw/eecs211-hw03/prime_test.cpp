#include "prime_lib.h"

#include <UnitTest++/UnitTest++.h>
#include <stdexcept>
#include <vector>

using namespace std;

// Checks if a given number is a prime
TEST(IS_PRIME)
{
    CHECK_EQUAL(false, is_prime(1));
    CHECK_EQUAL(true, is_prime(2));
    CHECK_EQUAL(true, is_prime(3));
    CHECK_EQUAL(false, is_prime(4));
    CHECK_EQUAL(true, is_prime(5));
}

TEST(IS_PRIME_ERRORS)
{
    CHECK_THROW(is_prime(-3), runtime_error);
}

// Write unit tests for generate_primes
TEST(GENERATE_PRIME)
{
    vector<int> v1 = {2,3,5,7,11};
    vector<int> v2 = {2,3,5,7,11,13,17,19};
    CHECK_ARRAY_EQUAL(v1, generate_primes(11), 5); // when n is a prime number
    CHECK_ARRAY_EQUAL(v2, generate_primes(20), 8); // when n is not a prime number

    CHECK_EQUAL(3, generate_primes(5).size());
    CHECK_EQUAL(2, generate_primes(5).at(0));
    CHECK_EQUAL(3, generate_primes(5).at(1));
    CHECK_EQUAL(5, generate_primes(5).at(2)); // input prime
    CHECK_EQUAL(5, generate_primes(6).at(2)); // input non-prime
}

TEST(GENERATE_PRIME_ERRORS)
{
    CHECK_THROW(generate_primes(-3),runtime_error);
}

// Write unit tests for check_is_prime
TEST(CHECK_IS_PRIME)
{
    CHECK_EQUAL(false, check_is_prime(generate_primes(11), 1));
    CHECK_EQUAL(true, check_is_prime(generate_primes(11), 2));
    CHECK_EQUAL(true, check_is_prime(generate_primes(11), 3));
    CHECK_EQUAL(false, check_is_prime(generate_primes(11), 4));
    CHECK_EQUAL(true, check_is_prime(generate_primes(11), 5));

    CHECK_EQUAL(is_prime(4), check_is_prime(generate_primes(11), 4));  // false calse
    CHECK_EQUAL(is_prime(5), check_is_prime(generate_primes(11), 5)); // true case

}

TEST(CHECK_IS_PRIME_ERRORS)
{
    // this is when const reference vector primes is empty (size 0)
    CHECK_THROW(check_is_prime(generate_primes(0), 11), runtime_error);

}
