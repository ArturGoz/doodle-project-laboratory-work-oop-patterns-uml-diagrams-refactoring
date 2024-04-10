#include <iostream>
#include <string>

//Singleton - це патерн проектування, який гарантує, що клас має лише один екземпляр, і надає глобальний точку доступу до нього.
//Це досягається шляхом створення приватного конструктора і статичного методу, який контролює доступ до екземпляра цього класу.
//
//У цьому прикладі ми додаємо методи setSingletonData() та getSingletonData() до класу Singleton, щоб демонструвати, як можна використовувати Singleton для зберігання та отримання даних.
//Ми створюємо два посилання s1 та s2 на екземпляр Singleton, встановлюємо дані через s1 та отримуємо дані через s1 та s2.
//Як бачимо, дані, встановлені через s1, доступні через s2, що демонструє, що s1 та s2 посилаються на один і той же екземпляр Singleton.

//Переваги використання патерну Singleton :
//
//Він гарантує, що клас має лише один екземпляр.
//Він надає глобальний точку доступу до цього екземпляра.
//Він реалізує відкладену ініціалізацію для ексклюзивних ресурсів та сервісів.
//Недоліки використання патерну Singleton :
//
//Він порушує принцип єдиного обов’язку, оскільки клас контролює свою власну ініціалізацію та життєвий цикл.
//Він може призвести до проблем, якщо вам потрібно створити підклас.
//Він може приховати погані дизайнерські рішення, такі як розділення обов’язків класів.
//Він може створити проблеми з многопоточністю.
//Він може бути важко використовувати в юніт - тестуванні.

class Singleton
{
public:
    static Singleton& getInstance()
    {
        static Singleton instance;
        return instance;
    }

    void setSingletonData(const std::string& data)
    {
        singletonData = data;
    }

    std::string getSingletonData() const
    {
        return singletonData;
    }

private:
    Singleton() {}
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;

    std::string singletonData;
};

int main()
{
    Singleton& s1 = Singleton::getInstance();
    Singleton& s2 = Singleton::getInstance();

    s1.setSingletonData("Hello, Singleton!");

    std::cout << "s1: " << s1.getSingletonData() << std::endl;
    std::cout << "s2: " << s2.getSingletonData() << std::endl;

    return 0;
}
