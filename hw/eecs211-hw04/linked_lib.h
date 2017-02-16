#pragma once

#include <memory>

struct ListNode
{
  int data;
  std::shared_ptr<ListNode> next;
};

using List = std::shared_ptr<ListNode>;

void filter_lt(List& front, int limit);
void push_back(List& front, int data);
List pop_front(List& front);
int& nth_element(List& front, size_t n);
