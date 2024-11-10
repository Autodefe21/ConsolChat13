#include "Chat.h"
#include "User.h"
#include <stdexcept>
//#include <cstdlib>
Chat::Chat() : lastUserId(0) {}


void Chat::addUser(std::string& login, std::string& password)
{
    lastUserId++;
    User newUser(login, password, lastUserId); 
   
    users.push_back(newUser); 
}

void Chat::showUsers()
{
    std::cout << "Список пользователей:" << std::endl;

    for ( User& user : users) {
        std::cout << user.getLogin() << " (id: " << user.getId() << ")";
        std::cout << std::endl; 
    }

    std::cout << "Всего пользователей: " << users.size() << std::endl;
}

bool Chat::registerUser()
{
    std::string login, password;
    std::cout << "Введите логин: ";
    std::cin >> login;
    std::cout << "Введите пароль: ";
    std::cin >> password;
    for ( User& user : users) {
        if (user.getLogin() == login) {
            std::cout << "Такой логин уже есть" << std::endl;
            return false; 
        }
    }
    addUser(login, password);
   
    std::cout << "Пользователь зарегистрирован с логином: " << login << " и ID: " << lastUserId << std::endl;
    return true;
}

void Chat::menu() {
    int choice;
    User user;

    while (true) {
        
        std::cout << "Добро пожаловать в чат!" << std::endl;
        std::cout << "Выберите действие:" << std::endl;
        std::cout << "1. Регистрация нового пользователя" << std::endl;
        std::cout << "2. Вход в аккаунт" << std::endl;
        std::cout << "0. Выйти из программы" << std::endl;

        std::cout << "Введите номер выбранного действия: ";
        std::string input;
        std::cin >> input;

        try {
            choice = std::stoi(input); 
            switch (choice) {
            case 1:
                registerUser();
                std::cout << "Регистрация прошла успешно!";
                break; 
            case 2:
                logIn();
                break;
            case 0:
                return; 
            default:
                std::cout << "Некорректный выбор. Пожалуйста, выберите 1, 2 или 0." << std::endl;
                break;
            }
        }
        catch (const std::invalid_argument&) {
            std::cout << "Пожалуйста, введите число." << std::endl;
        }
        catch (const std::out_of_range&) {
            std::cout << "Число вне допустимого диапазона." << std::endl;
        }

       
    }
}

void Chat::menu2(User& user) {
    std::string message;
    int choice;

    while (true) {
        std::cout << "----Главное меню-----" << std::endl;
        std::cout << "1. Отправить сообщение всем пользователям" << std::endl;
        std::cout << "2. Отправить сообщение конкретному пользователю" << std::endl;
        std::cout << "3. Просмотр полученных сообщений" << std::endl;
        std::cout << "4. Просмотр всех пользователей чата" << std::endl;
        std::cout << "5. Просмотр своего логина и пароля" << std::endl;
        std::cout << "6. Изменить логин и пароль" << std::endl;
        std::cout << "7. Выход из аккаунта" << std::endl;

        std::cout << "Введите номер выбранного действия: ";

        
        while (true) {
            std::string input;
            std::cin >> input;

            try {
                choice = std::stoi(input); 
                break; 
            }
            catch (const std::invalid_argument&) {
                std::cout << "Введите число." << std::endl;
            }
            catch (const std::out_of_range&) {
                std::cout << "Число вне допустимого диапазона." << std::endl;
            }
        }

        switch (choice) {
        case 1:
            std::cout << "Введите сообщение для всех пользователей: ";
            std::cin.ignore();
            std::getline(std::cin, message);
            sendMessageToAll(message);
            break;
        case 2:
            int userId;
            std::cout << "Введите ID пользователя для отправки сообщения: ";
            showUsers();
            while (true) {
                std::string userIdInput;
                std::cin >> userIdInput;
                try {
                    userId = std::stoi(userIdInput);
                    break;
                }
                catch (const std::invalid_argument&) {
                    std::cout << " Введите корректный ID." << std::endl;
                }
                catch (const std::out_of_range&) {
                    std::cout << "ID вне допустимого диапазона." << std::endl;
                }
            }
            std::cout << "Введите сообщение: ";
            std::cin.ignore();
            std::getline(std::cin, message);
            sendMessageToUser(userId, message);
            break;
        case 3:
            printMessage();
            break;
        case 4:
            showUsers();
            break;
        case 5:
            printLog();
            break;
        case 6:
            changeUser();
            break;
        case 7:
            logOut();
            return;
        default:
            std::cout << "Неверный выбор. Пожалуйста, попробуйте снова." << std::endl;
            break;
        }
    }
}

void Chat::logIn()
{
    if (users.empty()) {
        std::cout << "Нет зарегистрированных пользователей. Пожалуйста, зарегистрируйтесь." << std::endl;
       //menu();
        return; 
    }

    std::string login, password;
        std::cout << "Введите логин: ";
        std::cin >> login;
        std::cout << "Введите пароль: ";
        std::cin >> password;

        for (auto& user : users)
        {
            if (user.getLogin() == login && user.getPassword() == password)
            {
                currentUser = &user; // Устанавливаем текущего пользователя
                std::cout << "Успешный вход в аккаунт. Логин: " << login << ", ID: " << user.getId() << std::endl;
                menu2(user);
                return; 
            }
        }
        std::cout << "Ошибка: неверный логин или пароль." << std::endl;
}

void Chat::logOut()
{
    currentUser = nullptr;
    std::cout << "Вы вышли из аккаунта" << std::endl;
}

void Chat::sendMessageToAll(std::string& messageContent)
{

    for ( User& user : users) {
        if (user.getId() != currentUser->getId()) {
            Message newMessage(messageContent, user.getLogin(), currentUser->getLogin());
            messages.push_back(newMessage);
            //std::cout << "Сообщение отправлено пользователю: " << user.getLogin() << std::endl;
        }
    }
    std::cout << "Сообщение было отправлено всем пользователям" << std::endl;
}

void Chat::printVector()
{
    std::cout << "Количество элемнтов " << messages.size() << std::endl;
}

void Chat::printMessage()
{
    //std::cout << "Сообщения для пользователя " << currentUser->getLogin() << ":\n";
    bool hasMessages = false;

    for ( Message& message : messages) {
        if (message.getRecipient() == currentUser->getLogin()) {
            hasMessages = true;
            std::cout << "От: " << message.getSender() << " " << "Сообщение: " << message.getMessage() << std::endl;
        }
    }

    if (!hasMessages) {
        std::cout << "Нет новых сообщений." << std::endl;
    }
}

void Chat::sendMessageToUser(int userId, std::string& messageContent)
{

    for (User& user : users) {
        if (user.getId() == userId) {
            Message newMessage(messageContent, user.getLogin(), currentUser->getLogin());
            messages.push_back(newMessage);
            std::cout << "Сообщение отправлено пользователю: " << user.getLogin() << std::endl;
            return;
        }
    }

    std::cout << "Ошибка: Пользователь с ID " << userId << " не найден." << std::endl;
}

void Chat::changeUser()
{
    std::string newLogin, newPassword;
   std:: cout << "Введите новый логин: ";
   std:: cin >> newLogin;
   currentUser->setLogin(newLogin);
   std:: cout << "Введите новый пароль: ";
   std:: cin >> newPassword;
   currentUser->setPassword(newPassword);
   std:: cout << "Данные пользователя успешно изменены!" <<std:: endl;
}

void Chat::printLog()
{
    std::cout << "Логин: " << currentUser->getLogin() << std::endl;
     std::cout   << "Пароль: " << currentUser->getPassword() << std::endl;
}

/* void Chat::clearConsole()
{
#ifdef _WIN32 
    system("cls");//
#endif
}
*/


