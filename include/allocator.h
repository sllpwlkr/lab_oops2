#pragma once

#include <iostream>
#include <vector>
#include <iostream>
#include <memory>
#include <list>
#include <utility>
#include <map>

template <typename T, size_t BlockSize>
class MyAllocator {
public:
    using value_type = T; // Тип значения
    using pointer = T*; // Тип указателя
    using size_type = size_t; // Тип размера

    // Шаблонная структура rebind, которая позволяет переиспользовать аллокатор для другого типа
    template <typename U>
    struct rebind {
        using other = MyAllocator<U, BlockSize>;
    };

    MyAllocator() noexcept {}
    // Конструктор копирования для переиспользования аллокатора для другого типа
    template <typename U>
    MyAllocator(const MyAllocator<U, BlockSize>&) noexcept {}
    
    // Функция выделения памяти
    pointer allocate(size_type n) {
        if (n != 1)
            throw std::bad_alloc();
        if (position_ == nullptr || end_ - position_ < n) {
            data_.push_back(new value_type[BlockSize]);
            position_ = data_.back();
            end_ = position_ + BlockSize;
        }
        auto p = position_;
        position_ += n;
        return p;
    }

    // Функция освобождения памяти
    void deallocate(pointer p, size_type n) {
        if (n != 1) return;
        if (p == position_ - n) {
            position_ -= n;
            return;
        }
        for (auto it = data_.begin(); it != data_.end(); ++it) {
            if ((*it) == p) {
                delete[] (*it);
                data_.erase(it);
                break;
            }
        }
    }

private:
    std::vector<pointer> data_; // Вектор указателей на блоки памяти
    pointer position_ = nullptr; // Указатель на текущую позицию в блоке памяти
    pointer end_ = nullptr; // Указатель на конец блока памяти
};