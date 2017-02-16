#include "linked_lib.h"

#include <memory>
#include <stdexcept>
#include <iostream>

using namespace std;

//
// this function will go through the linked-list
// and "drop the node" which has data that is bigger
// than limit and re-link it to the
// next node to compare its value to limit.
//
void filter_lt(List& front, int limit)
{
    List traverse = make_shared<ListNode>();
    List last = make_shared<ListNode>();
    List temp = make_shared<ListNode>();
    last = nullptr;
    traverse = front;
    if(front == nullptr){
        return;
    }
    while(traverse -> data >= limit){
        temp = traverse;
        traverse = traverse -> next;
        temp -> next = nullptr;
        if(traverse == nullptr){
            break;
        }
    }
    if(traverse == nullptr){
        front = traverse;
    }else{
        front = traverse;
        last = front;
        traverse = traverse -> next;
        while(last != nullptr && traverse != nullptr){
            if(traverse -> data >= limit){
                last -> next = traverse -> next;
            }else{
                last -> next = traverse;
                last = traverse;
            }
            traverse = traverse -> next;
        }
    }
}

//
// filter_lt using push_back
//
//void filter_lt(List& front, int limit) {
//    List new_list = nullptr;
//
//    while (front->data >= limit) {
//        front =  front->next;
//    }
//
//    push_back(new_list, front->data);
//
//    while (front->next != nullptr) {
//        if (front->next->data < limit) {
//            push_back(new_list, front->next->data);
//        }
//        front = front->next;
//    }
//    front = new_list;
//
//}

//
// 1. if front is a nullptr, it creates a ListNode and let
//    front point to the new linked-list
// 2. if front is not a nullptr, it creates a new Listnode and
//    let the front->next to point the ListNode
//
void push_back(List& front, int data)
{
    List marker = front;
    ListNode new_node;
    new_node.data = data;
    new_node.next = nullptr;

    if (front == nullptr) {
        front = make_shared<ListNode>(new_node);
    }
    else {
        while (marker->next != nullptr) {
            marker = marker->next;
        }

        marker->next = make_shared<ListNode>(new_node);
    }
}


//
// takes out the first node in the linked-list
// that front points to and move the front ptr to point
// at the second element of the original linked-list
// Throws an runtime_error when front is nullptr
//
List pop_front(List& front)
{
    List output = make_shared<ListNode>();

    if (front == nullptr)
        throw runtime_error
                ("front must not be a nullptr to perform pop_front");

    output = front;
    front = front->next;
    output->next = nullptr;


    return output;
}

//
// takes a pointer that points to a linked-list
// and search through the nth data and return the data.
// Throws a runtime_error when given n is bigger
// than the length of the linked-list
//
int& nth_element(List& front, size_t n)
{
    List marker = front;

    int len = 1;
    while (marker->next != nullptr) {
        marker = marker->next;
        len++;
    }

    if (n >= len)
        throw runtime_error
                ("n should be smaller than length of the linked list that front points to");
    else {
        while (n != 0) {
            front = front->next;
            n--;
        }

        return front->data;
    }

}
