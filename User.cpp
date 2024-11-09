#include "User.h"

User::User(std::string login, std::string password, int id):login(login), password(password), id(id) {}

std::string User::getLogin()
{
	return login;
}

std::string User::getPassword()
{
	return password;
}

int User::getId()
{
	return id;
}

void User::setLogin(std::string newLogin)
{
	login = newLogin;
}

void User::setPassword(std::string newPassword)
{
	password=newPassword;
}

