#pragma once

#include <iostream>
#include <memory>
#include <cstring>
#include <string>
#include <random>
#include <fstream>
#include <set>
#include <math.h>
#include <shared_mutex>

// Определение типов NPC и его наследников
struct NPC;
struct Robber;
struct Wolf;
struct Bear;
using set_t = std::set<std::shared_ptr<NPC>>;

// Перечисление типов NPC
enum NpcType
{
    Unknown = 0,
    RobberType = 1,
    WolfType = 2,
    BearType = 3
};

// Интерфейс наблюдателя за схватками
struct IFightObserver{
    virtual void on_fight(const std::shared_ptr<NPC> attacker,const std::shared_ptr<NPC> defender, bool win) = 0;
};

// Класс NPC
class NPC 
{
 
private: 

    std::mutex mtx; // Мьютекс для синхронизации доступа

    NpcType type; // Тип NPC
    int x{0}; // Координата x
    int y{0}; // Координата y
    bool alive{true}; // Флаг жив/мертв

    std::vector<std::shared_ptr<IFightObserver>> observers; // Вектор наблюдателей за схватками

public:

    NPC(NpcType t, int _x, int _y); // Конструктор с параметрами
    NPC(NpcType t, std::istream &is); // Конструктор для чтения данных из потока

    void subscribe(std::shared_ptr<IFightObserver>observer ); // Подписка на наблюдателя
    void fight_notify(const std::shared_ptr<NPC> defender, bool win); // Оповещение наблюдателей о схватке
    virtual bool is_close(const std::shared_ptr<NPC> &other, size_t distance); // Проверка на близость к другому NPC

    virtual bool accept(std::shared_ptr<NPC> visitor) = 0; // Метод взаимодействия с посетителем
    virtual bool fight(std::shared_ptr<Robber> other) = 0; // Метод для схватки с грабителем
    virtual bool fight(std::shared_ptr<Wolf> other) = 0; // Метод для схватки с волком
    virtual bool fight(std::shared_ptr<Bear> other) = 0; // Метод для схватки с медведем
    bool visit(std::shared_ptr<Robber> other);
    bool visit(std::shared_ptr<Wolf> other);
    bool visit(std::shared_ptr<Bear> other);

    std::pair<int, int> position(); // Получение координат NPC
    NpcType get_type(); // Получение типа NPC
    
    virtual void print() = 0; // Вывод информации о NPC
    virtual void print(std::ostream &os) = 0; // Вывод информации о NPC в поток

    virtual void save(std::ostream &os); // Сохранение данных в поток

    friend std::ostream &operator<<(std::ostream &os, NPC &npc); // Перегрузка оператора вывода

    void move(int shift_x, int shift_y, int max_x, int max_y); // Перемещение NPC

    bool is_alive(); // Проверка на живучесть
    void must_die(); // Установка флага на "мертвый"
    
};
