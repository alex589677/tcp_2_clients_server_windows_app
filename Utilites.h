#pragma once
#include <iostream>
#include <map>
#include "User.h"

std::map<int, User> users;

User Handler1(bool& myFlag) {
	bool isExit{ true };
	char myChoice;
	int counterUsers{ 0 };
	while (isExit) {
		std::cout << "\nMenu1:"
				  << "\n1-Registrations Users"
				  << "\n2-Create message by login"
				  << "\n3-ShowAllUsers"
				  << "\n4-exit\n";
		std::cin >> myChoice;
		switch (myChoice) {
			case '4': {			// quick exit
				isExit = false;
				break;
			}
			case '1': {
				// registration user
				std::cout << "Create you login: \n";
				std::string myLogin;
				std::cin >> myLogin;
				std::cout << "Create you password: \n";
				std::string myPassword;
				std::cin >> myPassword;
				std::cout << "Enter your name: \n";
				std::string myName;
				std::cin >> myName;

				User user(myLogin, myPassword, myName);
				users.insert({ counterUsers++, user });
				user.show();
				break;
			}
			case '2': {
				int index{ 0 };
				static User currentUser = users[index++];
				std::cout << "new current user selected " << currentUser;
				std::cout << "\nAuthorization user\n";
				std::cout << "Input your login: \n";
				std::string login;
				std::cin >> login;
				std::cout << "Input your password: \n";
				std::string password;
				std::cin >> password;
				if (login == currentUser.getUserLogin() && password == currentUser.getUserPassword()) {
					std::cout << "well done\n";
					return currentUser;
				}
				else {
					std::cout << "Wrong login or Password!!!\nTry input data for authorizatioan...\n";
				}
				break;
			}
			case '3': {
				// map<int, User>::iterator it == auto
				for (auto it = users.begin(); it != users.end(); it++) {
					std::cout << "id: " << it->first
						<< " login: " << it->second.getUserLogin()
						<< " password: " << it->second.getUserPassword()
						<< " name: " << it->second.getUserName() 
						<< "\n------------\n";
				}
				break;
			}
			default: {
				std::cout << "Wrong input in menu1\n";
			}
		}
	}
	return User();
}