#pragma once
#include "npc.hpp"

struct Wolf : public NPC
{
    Wolf(int x, int y); // Конструктор с параметрами x и y для установки координат волка
    Wolf(std::istream &is); // Конструктор для чтения данных из потока

    void print() override; // Переопределенный метод для вывода информации о волке
    void print(std::ostream &os) override; // Переопределенный метод для вывода информации о волке в указанный поток

    // Метод для взаимодействия с другими NPC
    bool accept(std::shared_ptr<NPC> other) override;

    // Метод для схватки с другими волками, грабителями и медведями
    bool fight(std::shared_ptr<Wolf> other) override;
    bool fight(std::shared_ptr<Robber> other) override;
    bool fight(std::shared_ptr<Bear> other) override;

    // Метод для сохранения данных о волке в поток
    void save(std::ostream &os) override;

    // Перегрузка оператора вывода для вывода информации о волке в поток
    friend std::ostream &operator<<(std::ostream &os, Wolf &wolf);
};
