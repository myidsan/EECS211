#include "linked_lib.h"

#include <UnitTest++/UnitTest++.h>
#include <memory>
#include <iostream>
#include <stdexcept>

using namespace std;

// Example test case for push_back
// Testing push_back on a singleton
TEST(PUSH_BACK_OF_ONE_ELEMENT) {
  // Initialize the input linked-list to push_back
  List xs = make_shared<ListNode>();
  xs->data = 514;
  List ys = xs;

  push_back(xs, 2017211);

  // Check that the output is a 2-element linked-list with correct order
  CHECK_EQUAL(ys, xs);
  CHECK_EQUAL(514, xs->data);
  CHECK(xs->next != nullptr);
  CHECK_EQUAL(2017211, xs->next->data);
  // Note: It is impossible to apply CHECK_EQUAL on nullptr, so we use
  // CHECK and manually compares for equality
  CHECK(xs->next->next == nullptr);
}

//
// USER MADE UNIT TEST STARTS HERE
//
TEST(PUSH_BACK_OF_MORE_THAN_ONE_ELEMENTS) {
    List xs = make_shared<ListNode>();
    xs->data = 100;
    List ys = xs;

    push_back(xs,200);
    push_back(xs,300);
    push_back(xs,400);

    CHECK_EQUAL(ys,xs);
    CHECK_EQUAL(100, xs->data);
    CHECK(xs->next != nullptr);
    CHECK_EQUAL(200, xs->next->data);
    CHECK_EQUAL(300, xs->next->next->data);
    CHECK_EQUAL(400, xs->next->next->next->data);
    CHECK(xs->next->next->next != nullptr);
    CHECK_EQUAL(300, ys->next->next->data);
}

TEST(PUSH_BACK_OF_NULLPTR) {
    List xs = nullptr;

    push_back(xs,200);
    push_back(xs,300);
    push_back(xs,400);
    List ys = xs;

    CHECK_EQUAL(ys,xs);
    CHECK_EQUAL(200, xs->data);
    CHECK_EQUAL(200, xs->data);
    CHECK(xs->next != nullptr);
    CHECK_EQUAL(300, xs->next->data);
    CHECK_EQUAL(400, xs->next->next->data);
    CHECK(xs->next->next->next == nullptr);
    CHECK_EQUAL(400, ys->next->next->data);
}

TEST(POP_FRONT_TEST) {
    List xs = make_shared<ListNode>();
    xs->data = 100;
    push_back(xs, 200);
    push_back(xs, 300);

    CHECK_EQUAL(100, pop_front(xs)->data);
    CHECK_EQUAL(200, xs->data);
}

//
// test when the given ptr is a nullptr
//
TEST(POP_FRONT_EXCEPTION) {
    List xs = nullptr;
    CHECK_THROW(pop_front(xs), runtime_error);
}

TEST(NTH_ELEMENT_TEST) {
    List xs = make_shared<ListNode>();
    xs->data = 100;
    push_back(xs, 200);
    push_back(xs, 300);
    push_back(xs, 400);
    List ys = xs;

    CHECK_THROW(nth_element(xs, 10), runtime_error);
    CHECK_EQUAL(200, nth_element(xs, 1));
    CHECK_EQUAL(300, nth_element(ys, 2));
}

TEST(FILTER_LT_TEST) {
    List xs = make_shared<ListNode>();
    xs->data = 100;
    push_back(xs, 200);
    push_back(xs, 300);
    push_back(xs, 400);
    push_back(xs, -100);
    push_back(xs, 500);
    push_back(xs, -200);

    filter_lt(xs, 300);

    CHECK_EQUAL(100, xs->data);
    CHECK_EQUAL(200, xs->next->data);
    CHECK_EQUAL(-100, xs->next->next->data);
    CHECK_EQUAL(-200, xs->next->next->next->data);
    CHECK_EQUAL(-100, xs->next->next->data);
}

TEST(FILTER_IT_SECONDARY){
    List testy = make_shared<ListNode>();
    testy -> data = 100;
    List testy1 = testy;
    //pushes back 200 to the end of testy, making list length 2.
    push_back(testy, 200);
    //pushes back 300 to the end of testy, making list length 3.
    push_back(testy, 300);
    push_back(testy, 400);
    push_back(testy, 370);

    filter_lt(testy, 400);

    CHECK_EQUAL(100, testy -> data);
    CHECK_EQUAL(200, testy -> next -> data);
    CHECK(nullptr != testy -> next);
    CHECK(nullptr == testy -> next -> next -> next -> next);
    CHECK_EQUAL(370, testy -> next -> next -> next -> data);
    CHECK(nullptr == testy -> next -> next -> next -> next);
}


TEST(POP_FRONT_FRONT_NULLPTR) {
    List xs = make_shared<ListNode>();
    xs = nullptr;
    CHECK_THROW (pop_front(xs), runtime_error);
}

TEST(NTH_ELEMENT) {
    // Create a list of two elements in length
    List xs = make_shared<ListNode>(); xs->data = 514;
    List ys = make_shared<ListNode>(); ys->data = 712;
    xs->next = ys;
    ys->next = nullptr;

    CHECK_THROW(nth_element(xs, 2), runtime_error); // Throw error when given n out of bounds
    CHECK(nth_element(xs, 0) == 514); // Return value of data for input that is not longer than length of
}

// This function overloads the '<<' operator to enable printing on List
// types. For example, 'cout << xs << '\n';' will compile and print its
// content. However, we are still not able to write tests such as
// CHECK_EQUAL(nullptr, xs) since nullptr might be of any pointer type
// and the '<<' operator does not know how to print it.
ostream &operator<<(ostream &out, const List &lst) {
    if (lst) {
        out << "<ListNode@" << static_cast<void *>(lst.get());
        out << " data=" << lst->data;
        out << " next=" << static_cast<void *>(lst->next.get());
        out << ">";
    } else {
        out << "(nullptr)";
    }
    return out;
}


