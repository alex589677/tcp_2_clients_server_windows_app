#pragma once
#include <iostream>
#include <string>
#include <map>
#include <cstdlib>
#include "MyContainers.h"
#include "User.h"
#include "Utilites.h"

void callHandleFunction(bool& myFlag) {
	// call function callHandleFunction()
	User currentUser = Handler1(myFlag);		// call handler file in Utilites.h
	std::cout << currentUser << std::endl;
	int client_counter{ 0 };
	bool isFlag{ true };
	// exit out on menu 1 if (message == "")!
	if (currentUser.getUserName() == "")
		isFlag = false;
	while (isFlag) {
		std::cout << "Menu2: \n"
			<< "1-write text to user\n"
			<< "2-go previous menu\n"
			<< "3-show chat\n"
			<< "4-exit\n";
		std::cin >> client_counter;
		if (client_counter == 4) {
			isFlag = false;
			break;
		}
		if (client_counter == 1) {
			// write message
			std::cout << "Input login from write message: \n";
			std::string loginSource;
			std::cin >> loginSource;
			std::cout << "Input login to write message: \n";
			std::string loginTarget;
			std::cin >> loginTarget;
			std::cout << "Write your message and input '@' to end you message, and click Enter: \n";
			std::string str1;
			// input message
			std::getline(std::cin, str1, '@');

			// type message and login to anothe client
			send(connection, &str1[0], sizeof(str1), 0);
			send(connection, &loginTarget[0], sizeof(loginTarget), 0); 

			Message message1(loginSource, loginTarget, str1);
			std::cout << "[" << loginTarget << "]: " << message1.getText() << std::endl;
			allContainers.insert(make_pair(loginTarget, message1.getText()));
		}
		if (client_counter == 2) {
			// go to previous menu
			Handler1(myFlag);
		}
		if (client_counter == 3) {
			// show clients messages
			std::cout << "--------Chat------------\n";
			// multimap<string, string>::iterator item == auto
			for (auto& item : allContainers) {
				std::cout << "login: " << item.first << std::endl;
				std::cout << "message: " << item.second << std::endl;
			}
			std::cout << "--------------\n";
		}
	}
}