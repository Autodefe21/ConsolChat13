# Консольный чат с использованием std::vector.
Список функций класса Chat.
```C++
Chat();
void addUser( std::string& login, std::string& password); //Функция добавления пользователя в вектор.
void showUsers(); // Вывести список пользователей.
bool registerUser(); // Регистрация пользователей.
void menu(); // Меню регистрации и входа.
void menu2(User& user); // Главное меню.
void logIn(); // Функция входа в аккаунт.
void logOut(); // Функция выхода из аккаунта.
void sendMessageToAll(std::string& messageContent); // Отправить сообщение всем пользователям чата 
void printVector();
void printMessage(); // Показать полученные сообщения.
void sendMessageToUser(int userId, std::string& messageContent); // Отправить сообщение конкретному пользователю.
void changeUser(); // Функция изменения данных пользователя.
void printLog(); // Показать данные пользователя (Логин, Пароль).
```
