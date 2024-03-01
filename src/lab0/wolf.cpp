#include "wolf.hpp"
#include "bear.hpp"
#include "robber.hpp"

// Конструктор с параметрами для волка
Wolf::Wolf(int x, int y) : NPC(WolfType, x, y) {}

// Конструктор для чтения данных из потока для волка
Wolf::Wolf(std::istream &is) : NPC(WolfType, is) {}

// Вывод информации о волке
void Wolf::print()
{
    std::cout << *this;
}

// Вывод информации о волке в указанный поток
void Wolf::print(std::ostream &outfs) {
    outfs << *this;
}

// Метод для взаимодействия с другим NPC
bool Wolf::accept(std::shared_ptr<NPC> other) {
    return other->fight(std::shared_ptr<Wolf>(this,[](Wolf*){}));
}

// Сохранение данных о волке в поток
void Wolf::save(std::ostream &os)
{
    os << WolfType << std::endl;
    NPC::save(os);
}

// Метод для сражения с грабителем
bool Wolf::fight(std::shared_ptr<Robber> other)
{
    fight_notify(other, true);
    return true;
}

// Метод для сражения с другим волком
bool Wolf::fight(std::shared_ptr<Wolf> other)
{
    fight_notify(other, false);
    return false;
}

// Метод для сражения с медведем
bool Wolf::fight(std::shared_ptr<Bear> other)
{
    fight_notify(other, false);
    return false;
}

// Перегрузка оператора вывода для вывода информации о волке
std::ostream &operator<<(std::ostream &os, Wolf &wolf)
{
    os << "Wolf 🐺: " << *static_cast<NPC *>(&wolf) << std::endl;
    return os;
}
