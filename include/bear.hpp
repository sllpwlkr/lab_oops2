#pragma once
#include "npc.hpp"

struct Bear : public NPC {
    Bear(int x, int y); // Конструктор с параметрами x и y
    Bear(std::istream &is); // Конструктор для чтения данных из потока

    void print() override; 
    void print(std::ostream &os) override; 
    bool accept(std::shared_ptr<NPC> visitor) override;

    bool fight(std::shared_ptr<Robber> other) override; 
    bool fight(std::shared_ptr<Wolf> other) override; 
    bool fight(std::shared_ptr<Bear> other) override; 

    void save(std::ostream &os) override; // Метод для сохранения данных в поток
    friend std::ostream &operator<<(std::ostream &os, Bear &bear); // Перегрузка оператора вывода
};
