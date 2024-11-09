#pragma once
#include <vector>
#include <iostream>
#include <string>
#include "User.h"
#include "Message.h"
class Chat
{
public:
	Chat();
	void addUser( std::string& login, std::string& password);
	void showUsers();
	bool registerUser();
	void menu();
	void menu2(User& user);
	void logIn();
	void logOut();
	void sendMessageToAll(std::string& messageContent);
	void printVector();
	void printMessage();
	void sendMessageToUser(int userId, std::string& messageContent);
	void changeUser();
	void printLog();
	//void clearConsole();
private:
	std::vector<Message> messages;
	User* currentUser = nullptr;
	std::vector<User> users;
	int lastUserId;
};

