#include <iostream>



//У наведеному вище прикладі ми використовуємо патерн Facade в класі Facade.
//Цей клас надає метод Operation(), який виконує операції з підсистемами Subsystem1 та Subsystem2.
//Клієнтський код використовує інтерфейс Facade для виконання цих операцій, не звертаючись безпосередньо до підсистем.
//Таким чином, ми можемо змінювати підсистеми без зміни клієнтського коду.
//
//Переваги використання патерну Facade :
//
//Він пропонує простий інтерфейс до складної системи.
//Він розділяє клієнтів від компонентів підсистеми, що полегшує розробку та тестування.
//Недоліки використання патерну Facade :
//
//Клієнт може мати обмежений доступ до складних підсистем.
//Програма може стати складнішою, якщо ви використовуєте декілька фасадів.

class Subsystem1 {
public:
    std::string operation1() const {
        return "Subsystem1: Ready!\n";
    }
    std::string operationN() const {
        return "Subsystem1: Go!\n";
    }
};

class Subsystem2 {
public:
    std::string operation1() const {
        return "Subsystem2: Get ready!\n";
    }
    std::string operationZ() const {
        return "Subsystem2: Fire!\n";
    }
};

class Facade {
protected:
    Subsystem1* subsystem1_;
    Subsystem2* subsystem2_;
public:
    Facade(
        Subsystem1* subsystem1 = nullptr,
        Subsystem2* subsystem2 = nullptr) {
        this->subsystem1_ = subsystem1 ? : new Subsystem1;
        this->subsystem2_ = subsystem2 ? : new Subsystem2;
    }
    ~Facade() {
        delete subsystem1_;
        delete subsystem2_;
    }
    std::string Operation() {
        std::string result = "Facade initializes subsystems:\n";
        result += this->subsystem1_->operation1();
        result += this->subsystem2_->operation1();
        result += "Facade orders subsystems to perform the action:\n";
        result += this->subsystem1_->operationN();
        result += this->subsystem2_->operationZ();
        return result;
    }
};

void ClientCode(Facade* facade) {
    std::cout << facade->Operation();
}

int main() {
    Subsystem1* subsystem1 = new Subsystem1;
    Subsystem2* subsystem2 = new Subsystem2;
    Facade* facade = new Facade(subsystem1, subsystem2);
    ClientCode(facade);

    delete facade;

    return 0;
}
