#include <iostream>

#include "circular-linked-list.hpp"

int main() {
    CircularLinkedList<int> test;
    test.InsertInOrder(17);
    std::cout << test << std::endl;
    test.InsertInOrder(38);
    std::cout << test << std::endl;
    test.InsertInOrder(26);
    std::cout << test << std::endl;
    test.InsertInOrder(34);
    std::cout << test << std::endl;
    test.InsertInOrder(13);
    std::cout << test << std::endl;
    test.InsertInOrder(5);
    std::cout << test << std::endl;
    test.Reverse();
    std::cout << test << std::endl;
    CircularLinkedList<int> to_copy;
    to_copy.Reverse();
    CircularLinkedList<int> one_item;
    one_item.InsertInOrder(3);
    // CircularLinkedList<int> copy = test;
    CircularLinkedList<int> copy;
    copy = test;
    std::cout << copy << std::endl;
    copy = to_copy;
    std::cout << copy << std::endl;
    std::cout << to_copy << std::endl;
    copy = one_item;
    std::cout << copy << std::endl;
    one_item.Reverse();
    copy = one_item;
    std::cout << copy << std::endl;
}
