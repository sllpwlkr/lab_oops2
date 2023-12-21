#pragma once

#include <iostream>
#include <vector>
#include <iostream>
#include <memory>
#include <list>
#include <utility>
#include <map>
#include "allocator.h"

template <typename T, size_t BlockSize, typename Allocator = MyAllocator<T, BlockSize>>
class MyQueue {
private:
    //структура, представляющая узел очереди
    struct Node {
        T data;
        Node* next;
        Node(const T& d, Node* n = nullptr) : data(d), next(n) {}
    };

public:
    // Реализация итератора
    class Iterator {
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = T;
        using pointer = T*;
        using reference = T&;
        using difference_type = std::ptrdiff_t;

        Iterator(Node* p) : ptr(p) {}

        //получение значения
        reference operator*() const {
            return ptr->data;
        }

        pointer operator->() const {
            return &(ptr->data);
        }

        //перемещение итератора
        Iterator& operator++() {
            ptr = ptr->next;
            return *this;
        }

        Iterator operator++(int) {
            Iterator temp = *this;
            ++(*this);
            return temp;
        }

        //сравнение итераторов
        bool operator==(const Iterator& rhs) const {
            return ptr == rhs.ptr;
        }

        bool operator!=(const Iterator& rhs) const {
            return !(*this == rhs);
        }

    private:
        Node* ptr;
    };

    using iterator = Iterator;
    using const_iterator = Iterator;
    using allocator_type = Allocator;

    MyQueue() : head(nullptr), tail(nullptr) {}
    //добавляет новый элемент в конец очереди.
    void enqueue(const T& value) {
        Node* newNode = new Node(value);
        if (empty()) {
            head = newNode;
            tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
    }

   //удаляет элемент из начала очереди.
    void dequeue() {
        if (empty()) {
            throw std::runtime_error("Queue is empty");
        }
        Node* temp = head;
        head = head->next;
        if (head == nullptr) {
            tail = nullptr;
        }
        destroyNode(temp);
    }

    //возвращает ссылку на первый элемент очереди.
    T& front() {
        if (empty()) {
            throw std::runtime_error("Queue is empty");
        }
        return head->data;
    }

    const T& front() const {
        if (empty()) {
            throw std::runtime_error("Queue is empty");
        }
        return head->data;
    }
    //проверяет, пуста ли очередь.
    bool empty() const {
        return head == nullptr;
    }
    //возвращает количество элементов в очереди.
    size_t size() const {
        size_t count = 0;
        Node* current = head;
        while (current != nullptr) {
    
            current = current->next;
            ++count;
        }
        return count;
    }
    //возвращают итераторы в начало
    iterator begin() {
        return iterator(head);
    }
    

    const_iterator begin() const {
        return const_iterator(head);
    }

    //возвращают итераторы в конец
    iterator end() {
        return iterator(nullptr);
    }

    const_iterator end() const {
        return const_iterator(nullptr);
    }

private:
    //вызов деструктора и освобождение памяти
    void destroyNode(Node* node) {
        node->data.~T();
        int* ptr = allocator.allocate(node->data);
        allocator.deallocate(ptr, 1);
    }

    Node* head;
    Node* tail;
    allocator_type allocator;
};