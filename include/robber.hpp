#pragma once
#include "npc.hpp"


struct Robber : public NPC
{
    Robber(int x, int y); // Конструктор с параметрами x и y для установки координат грабителя
    Robber(std::istream &is); // Конструктор для чтения данных из потока

    void print() override; // Переопределенный метод для вывода информации о грабителе
    void print(std::ostream &os) override; // Переопределенный метод для вывода информации о грабителе в указанный поток

    // Метод для взаимодействия с посетителями
    bool accept(std::shared_ptr<NPC> visitor) override;

    // Метод для схватки с другими грабителями, волками и медведями
    bool fight(std::shared_ptr<Robber> other) override;
    bool fight(std::shared_ptr<Wolf> other) override;
    bool fight(std::shared_ptr<Bear> other) override;

    // Метод для сохранения данных о грабителе в поток
    void save(std::ostream &os) override;

    // Перегрузка оператора вывода для вывода информации о грабителе в поток
    friend std::ostream &operator<<(std::ostream &os, Robber &robber);
};
