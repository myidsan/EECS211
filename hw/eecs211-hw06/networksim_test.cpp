#include "errors.h"
#include "parsing.h"
#include "datagram.h"
#include "machines.h"
#include "system.h"

#include <UnitTest++/UnitTest++.h>
#include <memory>
#include <iostream>
#include <stdexcept>
#include <string>

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


using namespace std;

///free function to get changeable ip address
IP_address ip_from_parts(int a, int b, int c, int d)
{
    std::ostringstream fmt;
    fmt << a << '.' << b << '.' << c << '.' << d;
    return IP_address(fmt.str());
}

///free function to get changeable machine name
string machine_name(int a)
{
    std::ostringstream fmt;
    fmt << "lab-" << a;
    return string(fmt.str());
}


// Sample test to demonstrate how to use shared_ptr::use_count() to test whether
// Node::disconnect() works or not. If it works, n1 and n2 should no longer hold
// reference to each other, so the use_count() will decrease to 1. After this
// test case returns, you should also be able to see the message "machine 'NODE_
// DISCONNECT Machine 2' deleted" nad "machine 'NODE_DISCONNECT Machine 1' deleted"
// because n1 and n2 are the only reference to these two machines. After they
// go out of scope, the memory they hold will be deallocated.
TEST(NODE_DISCONNECT)
{
    // Allocate the machine and connect them, as did in System::create_machine
    // and System::connect_machine.
    shared_ptr<Node> n1 = make_shared<Node>("NODE_DISCONNECT Machine 1", IP_address("1.2.3.4"));
    shared_ptr<Node> n2 = make_shared<Node>("NODE_DISCONNECT Machine 2", IP_address("5.6.7.8"));

    n1->connect(n2);
    n2->connect(n1);

    // Both n1 and n2 also hold a reference to each other.
    CHECK_EQUAL(2, n1.use_count());
    CHECK_EQUAL(2, n2.use_count());

    n1->disconnect(n2);
    n2->disconnect(n1);

    // No references other than 'n1' and 'n2' remained.
    CHECK_EQUAL(1, n1.use_count());
    CHECK_EQUAL(1, n2.use_count());
}


TEST(NODE_CONNECT)
{
    // Allocate the machine and connect them, as did in System::create_machine
    // and System::connect_machine.
    shared_ptr<Node> n1 = make_shared<Node>("NODE_CONNECT Machine 1", IP_address("1.2.3.4"));
    shared_ptr<Node> n2 = make_shared<Node>("NODE_CONNECT Machine 2", IP_address("5.6.7.8"));
    shared_ptr<Node> n3 = make_shared<Node>("NODE_CONNECT Machine 3", IP_address("10.11.12.13"));
    shared_ptr<Node> n4 = make_shared<Node>("NODE_CONNECT Machine 4", IP_address("15.16.17.18"));

    n1->connect(n2);
    n1->connect(n3);
    n1->connect(n4);

    n2->connect(n1);
    n2->connect(n3);
    n2->connect(n4);

    n3->connect(n1);
    n3->connect(n2);
    n3->connect(n4);

    n4->connect(n1);
    n4->connect(n2);
    n4->connect(n3);

    // Both n1 and n2 also hold a reference to each other.
    CHECK_EQUAL(4, n1.use_count());
    CHECK_EQUAL(4, n2.use_count());
}



/// connect machine
TEST(connect_machine) {
    System n1;
    n1.create_machine("laptop", "lap-2", IP_address("192.168.0.2"));
    n1.create_machine("laptop", "lap-3", IP_address("192.168.0.3"));
    n1.connect_machine(IP_address("192.168.0.2"), IP_address("192.168.0.3"));
}


/// tyring to connect machine that is non-existant
TEST(connect_machine_ERROR) {
    System n2;
    n2.create_machine("server", "svr-1", IP_address("172.16.0.1"));
    n2.create_machine("wan", "wan-3", IP_address("225.225.225.3"));
    CHECK_THROW_ENUM( n2.connect_machine(IP_address("172.16.0.1"),
                                         IP_address("0.0.0.0")), err_code, no_such_machine);
}

/// tyring to connect machine that is non-existant
TEST(delete_machine) {
    System n1;
    n1.create_machine("laptop", "lap-2", IP_address("192.168.0.2"));
    n1.create_machine("laptop", "lap-3", IP_address("192.168.0.3"));
    n1.delete_machine(IP_address("192.168.0.3"));
}


/// tyring to delete machine that is non-existant
TEST(delete_machine_test_and_ERROR) {
    System n1;
    n1.create_machine("laptop", "lap-2", IP_address("192.168.0.2"));
    n1.create_machine("laptop", "lap-3", IP_address("192.168.0.3"));
    n1.delete_machine(IP_address("192.168.0.3"));

    // machine not found in the network
    CHECK_THROW_ENUM(n1.delete_machine(IP_address("192.168.0.4")),
                     err_code, no_such_machine);
}

/// disconnect should never throw an error
TEST(disconnect_no_ERROR) {
    shared_ptr<Node> n1 = make_shared<Node>("NODE_DISCONNECT Machine 1",
                                            IP_address("1.2.3.4"));
    shared_ptr<Node> n2 = make_shared<Node>("NODE_DISCONNECT Machine 2",
                                            IP_address("5.6.7.8"));
    shared_ptr<Node> n3;

    // this test should not throw an error
    n1->disconnect(n2);
    // when disconnecting a nullptr
    n1->disconnect(n3);
}

/// system create
TEST(system_create) {
    System n1;
    n1.create_machine("laptop", "lap-1", IP_address("192.168.0.1"));
}

/// more number of nodes than MAX_MACHINE aka runout
TEST(create_machine_runout_ERROR) {
    System n1;

    // when no machines in network_.
    CHECK_THROW_ENUM (n1.delete_machine(IP_address("0.0.2.1")),
                      err_code, no_such_machine);


    for (int i = 0; i < MAX_MACHINES; i++) {
        n1.create_machine("laptop", machine_name(i), ip_from_parts(172,168,0,i));
    }

    CHECK_THROW_ENUM(n1.create_machine("wan", "wan-1", IP_address("172.16.82.100")),
                     err_code, network_full);
}


/// unknown machine type error
TEST(create_machine_unknown_ERROR) {
    System n1;
    CHECK_THROW_ENUM(n1.create_machine("desktop", "lap-1", IP_address("172.16.82.1")),
                     err_code, unknown_machine_type);
    CHECK_THROW_ENUM(n1.create_machine("wann", "lap-1", IP_address("172.16.82.2")),
                     err_code, unknown_machine_type);
}


/// construct and first octad
TEST(IP_ADDRESS_CONSTRUCTOR_AND_FIRST_OCTAD){
    IP_address ip1 = IP_address("22.200.11.123");
    array<int, 4> ip_1 = {22, 100, 11, 123};
    CHECK_EQUAL(ip_1[0], ip1.first_octad());

    IP_address ip2 = IP_address("0.0.0.0");
    array<int, 4> ip_2 = {0, 50, 0, 0};
    CHECK_EQUAL(ip_2[0], ip2.first_octad());

    IP_address ip3 = IP_address("22.200.11.123");
    array<int, 4> ip_3 = {22, 200, 21, 123};
    CHECK_EQUAL(ip_3[0], ip3.first_octad());
}

/// check if ip_addresses are equal
TEST(IP_address_EQUAL){
    //initialized two ip addresses that are identical.
    //Tests constructor and the == operator
    IP_address ip1 = IP_address("22.200.11.123");
    IP_address ip_1 = IP_address("22.200.11.123");
    CHECK(ip_1 ==  ip1);

    IP_address ip2 = IP_address("0.0.0.0");
    IP_address ip_2 = IP_address("0.0.0.0");
    CHECK(ip_2 == ip2);

    IP_address ip3 = IP_address("22.200.11.123");
    IP_address ip_3 = IP_address("22.200.11.123");
    CHECK(ip_3 == ip3);
}

/// check if ip_addresses are equal
TEST(IP_address_equal_ERROR){
    // error of the == operator: when the two address are not equal
    IP_address ip1 = IP_address("22.200.11.123");
    IP_address ip_1 = IP_address("22.20.11.123");
    CHECK_EQUAL(false, ip_1 ==  ip1);

    IP_address ip2 = IP_address("1.1.1.1");
    IP_address ip_2 = IP_address("0.7.0.8");
    CHECK_EQUAL(false, ip_2 == ip2);

    IP_address ip3 = IP_address("22.200.11.123");
    IP_address ip_3 = IP_address("22.210.21.13");
    CHECK_EQUAL(false, ip_3 == ip3);
}

/// constructor and get destination
TEST(IP_address_datagram_constructor_and_get_destination) {
    // Checking that is throws an exception for invalid input counts
    CHECK_THROW(IP_address("256.256.256.266"), err_code);
    CHECK_THROW(IP_address("a.b.c.d"), err_code);
    // Constructor and get_destination working case
    IP_address ip_source_1 = IP_address("0.0.0.0");
    IP_address ip_desti_1 = IP_address("4.4.4.4");
    Datagram package1 = Datagram(ip_source_1, ip_desti_1, "a message");
    CHECK(ip_desti_1 == package1.get_destination());
}

