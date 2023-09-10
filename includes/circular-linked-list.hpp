#ifndef CIRCULAR_LINKED_LIST_HPP
#define CIRCULAR_LINKED_LIST_HPP

#include <iostream>

#include "node.hpp"

enum class Order { kASC, kDESC };

template <typename T>
class CircularLinkedList {
public:
  CircularLinkedList() = default;
  CircularLinkedList(const CircularLinkedList<T>& source);
  CircularLinkedList<T>& operator=(const CircularLinkedList<T>& source);
  ~CircularLinkedList();

  void InsertInOrder(const T& data);
  void Reverse();

  template <typename U>
  friend std::ostream& operator<<(std::ostream& os,
                                  const CircularLinkedList<U>& cll);

private:
  Node<T>* head_ = nullptr;
  Node<T>* tail_ = nullptr;
  Order node_order_ = Order::kASC;
};

template<typename T>
CircularLinkedList<T>::CircularLinkedList(const CircularLinkedList<T>& source) 
: head_(nullptr), tail_(nullptr), node_order_(source.node_order_) {
  if (source.head_ == nullptr) return;
  Node<T>* curr = source.head_;
  Node<T>* to_add = new Node(source.head_->data);
  head_ = to_add;
  tail_ = to_add;
  head_->next = tail_;
  while (curr->next != source.head_) {
    curr = curr->next;
   this->InsertInOrder(curr->data);
  }
}
template<typename T>
CircularLinkedList<T>& CircularLinkedList<T>::operator=(const CircularLinkedList<T>& source) {
  if (this == &source) return *this;
  // if (source.head_ == nullptr) {
  //   this->~CircularLinkedList();
  //   return *this;
  // }
  this->~CircularLinkedList();
  if (source.head_ == nullptr) return *this;
  node_order_ = source.node_order_;
  Node<T>* curr = source.head_;
  Node<T>* to_add = new Node(source.head_->data);
  head_ = to_add;
  tail_ = to_add;
  head_->next = tail_;
  while (curr->next != source.head_) {
    curr = curr->next;
    this->InsertInOrder(curr->data);
  }
  return *this;
}

template <typename T>
CircularLinkedList<T>::~CircularLinkedList() {
  if (head_ == nullptr) return;
  tail_->next = nullptr;
  while (head_->next != nullptr) {
    Node<T>* next = head_->next;
    delete head_;
    head_ = next;
  }
  delete head_;
  head_ = nullptr;
  tail_ = nullptr;
}

template <typename T>
void CircularLinkedList<T>::InsertInOrder(const T& data) {
  Node<T>* curr = head_;
  Node<T>* to_add = new Node(data);
  if (head_ == nullptr) {
    head_ = to_add;
    tail_ = to_add;
    head_->next = tail_;
    return;
  }
  if (node_order_ == Order::kASC) {
    if (data <= head_->data) {
      to_add->next = head_;
      head_ = to_add;
      tail_->next = head_;
      return;
    }
    while (curr->next->data < data) {
      if (curr == tail_) break;
      curr = curr->next;
    }
    to_add->next = curr->next;
    curr->next = to_add;
    if (curr == tail_) tail_ = to_add;
  }
  if (node_order_ == Order::kDESC) {
    if (data >= head_->data) {
      to_add->next = head_;
      head_ = to_add;
      tail_->next = head_;
      return;
    }
    while (curr->next->data > data) {
      if (curr == tail_) break;
      curr = curr->next;
    }
    to_add->next = curr->next;
    curr->next = to_add;
    if (curr == tail_) tail_ = to_add;
  }
}

template <typename T>
void CircularLinkedList<T>::Reverse() {
  if (node_order_ == Order::kASC) {
    node_order_ = Order::kDESC;
  } else if (node_order_ == Order::kDESC) {
    node_order_ = Order::kASC;
  }
  if (head_ == nullptr) return;
  Node<T>* next = head_->next;
  Node<T>* curr = head_;
  Node<T>* prev = tail_;
  curr->next = prev;
  prev = curr;
  curr = next;
  while (curr != head_) {
    next = curr->next;
    curr->next = prev;
    prev = curr;
    curr = next;
  }
  head_ = prev;
  tail_ = curr;
}

template <typename T>
std::ostream& operator<<(std::ostream& os, const CircularLinkedList<T>& cll) {
  Node<T>* iter = cll.head_;
  // empty list condition
  if (iter == nullptr) {
    os << "Empty list";
    return os;
  }
  // non-empty list condition
  do {
    int test = iter->data;
    test++;
    os << iter->data << '\t';
    iter = iter->next;
  } while (iter != cll.head_);

  return os;
}

#endif
