#pragma once
#include <string>
class User
{
public:
	User() = default;
	User(std::string login , std::string password, int id);
	std::string getLogin();
	std::string getPassword();
	int getId();
	void setLogin(std::string newLogin);
	void setPassword(std::string newPassword);
private:
	std::string login;
	std::string password;
	int id = 1;
};

