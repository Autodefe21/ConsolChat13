#include "Chat.h"
#include "User.h"
#include <stdexcept>
#include <cstdlib>
Chat::Chat() : lastUserId(0) {}


void Chat::addUser(std::string& login, std::string& password)
{
    lastUserId++;
    User newUser(login, password, lastUserId); 
   
    users.push_back(newUser); 
}

void Chat::showUsers()
{
    std::cout << "������ �������������:" << std::endl;

    for ( User& user : users) {
        std::cout << user.getLogin() << " (id: " << user.getId() << ")";
        std::cout << std::endl; 
    }

    std::cout << "����� �������������: " << users.size() << std::endl;
}

bool Chat::registerUser()
{
    std::string login, password;
    std::cout << "������� �����: ";
    std::cin >> login;
    std::cout << "������� ������: ";
    std::cin >> password;
    for ( User& user : users) {
        if (user.getLogin() == login) {
            std::cout << "����� ����� ��� ����" << std::endl;
            return false; 
        }
    }
    addUser(login, password);
   
    std::cout << "������������ ��������������� � �������: " << login << " � ID: " << lastUserId << std::endl;
    return true;
}

void Chat::menu()
{
    int choice;
    User user;

    while (true) {
        std::cout << "����� ���������� � ���!" << std::endl;
        std::cout << "�������� ��������:" << std::endl;
        std::cout << "1. ����������� ������ ������������" << std::endl;
        std::cout << "2. ���� � �������" << std::endl;
        std::cout << "0. ����� �� ���������" << std::endl;

        std::cout << "������� ����� ���������� ��������: ";
        std::cin >> choice;

        switch (choice) {
        case 1:
            registerUser();
            
            break;
        case 2:
            logIn();
            menu2(user);
            
            break;
        case 0:
            std::cout << "����� �� ���������." << std::endl;
            return;
        default:
            std::cout << "������������ �����." << std::endl;
            break;
        }
    }
}

void Chat::menu2(User& user) {
    std::string message;
    int choice;

    while (true) {
        std::cout << "----������� ����-----" << std::endl;
        std::cout << "1. ��������� ��������� ���� �������������" << std::endl;
        std::cout << "2. ��������� ��������� ����������� ������������" << std::endl;
        std::cout << "3. �������� ���������� ���������" << std::endl;
        std::cout << "4. �������� ���� ������������� ����" << std::endl;
        std::cout << "5. �������� ������ ������ � ������" << std::endl;
        std::cout << "6. �������� ����� � ������" << std::endl;
        std::cout << "7. ����� �� ��������" << std::endl;

        std::cout << "������� ����� ���������� ��������: ";

        
        while (true) {
            std::string input;
            std::cin >> input;

            try {
                choice = std::stoi(input); 
                break; 
            }
            catch (const std::invalid_argument&) {
                std::cout << "����������, ������� �����." << std::endl;
            }
            catch (const std::out_of_range&) {
                std::cout << "����� ��� ����������� ���������." << std::endl;
            }
        }

        switch (choice) {
        case 1:
            std::cout << "������� ��������� ��� ���� �������������: ";
            std::cin.ignore();
            std::getline(std::cin, message);
            sendMessageToAll(message);
            break;
        case 2:
            int userId;
            std::cout << "������� ID ������������ ��� �������� ���������: ";
            showUsers();
            while (true) {
                std::string userIdInput;
                std::cin >> userIdInput;
                try {
                    userId = std::stoi(userIdInput);
                    break;
                }
                catch (const std::invalid_argument&) {
                    std::cout << "����������, ������� ���������� ID." << std::endl;
                }
                catch (const std::out_of_range&) {
                    std::cout << "ID ��� ����������� ���������." << std::endl;
                }
            }
            std::cout << "������� ���������: ";
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
            std::cout << "�������� �����. ����������, ���������� �����." << std::endl;
            break;
        }
    }
}

void Chat::logIn()
{
    if (users.empty()) {
        std::cout << "��� ������������������ �������������. ����������, �����������������." << std::endl;
        menu();
        return; 
    }

    std::string login, password;
        std::cout << "������� �����: ";
        std::cin >> login;
        std::cout << "������� ������: ";
        std::cin >> password;

        for (auto& user : users)
        {
            if (user.getLogin() == login && user.getPassword() == password)
            {
                currentUser = &user; // ������������� �������� ������������
                std::cout << "�������� ���� � �������. �����: " << login << ", ID: " << user.getId() << std::endl;
                return; 
            }
        }
        std::cout << "������: �������� ����� ��� ������." << std::endl;
}

void Chat::logOut()
{
    currentUser = nullptr;
    std::cout << "�� ����� �� ��������" << std::endl;
}

void Chat::sendMessageToAll(std::string& messageContent)
{

    for ( User& user : users) {
        if (user.getId() != currentUser->getId()) {
            Message newMessage(messageContent, user.getLogin(), currentUser->getLogin());
            messages.push_back(newMessage);
            //std::cout << "��������� ���������� ������������: " << user.getLogin() << std::endl;
        }
    }
    std::cout << "��������� ���� ���������� ���� �������������" << std::endl;
}

void Chat::printVector()
{
    std::cout << "���������� �������� " << messages.size() << std::endl;
}

void Chat::printMessage()
{
    std::cout << "��������� ��� ������������ " << currentUser->getLogin() << ":\n";
    bool hasMessages = false;

    for ( Message& message : messages) {
        if (message.getRecipient() == currentUser->getLogin()) {
            hasMessages = true;
            std::cout << "��: " << message.getSender()
                << "\n���������: " << message.getMessage();
               
        }
    }

    if (!hasMessages) {
        std::cout << "��� ����� ���������." << std::endl;
    }
}

void Chat::sendMessageToUser(int userId, std::string& messageContent)
{

    for (User& user : users) {
        if (user.getId() == userId) {
            Message newMessage(messageContent, user.getLogin(), currentUser->getLogin());
            messages.push_back(newMessage);
            std::cout << "��������� ���������� ������������: " << user.getLogin() << std::endl;
            return;
        }
    }

    std::cout << "������: ������������ � ID " << userId << " �� ������." << std::endl;
}

void Chat::changeUser()
{
    std::string newLogin, newPassword;
   std:: cout << "������� ����� �����: ";
   std:: cin >> newLogin;
   currentUser->setLogin(newLogin);
   std:: cout << "������� ����� ������: ";
   std:: cin >> newPassword;
   currentUser->setPassword(newPassword);
   std:: cout << "������ ������������ ������� ��������!" <<std:: endl;
}

void Chat::printLog()
{
    std::cout << "�����: " << currentUser->getLogin() << std::endl;
     std::cout   << "������: " << currentUser->getPassword() << std::endl;
}



