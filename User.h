#pragma once
#include <string>

class User {
private:
	std::string login_;
	std::string password_;
	std::string name_;
public:
	User() {
		login_ = "";
		password_ = "";
		name_ = "";
	}

	User(const std::string& login, const std::string& password, const std::string& name) :
		login_(login), password_(password), name_(name) {}

	User(const User& other) {
		login_ = other.login_;
		password_ = other.password_;
		name_ = other.name_;
	}

	User operator=(User other) {
		User newUser;
		newUser.login_ = other.login_;
		newUser.password_ = other.password_;
		newUser.name_ = other.name_;
		return newUser;
	}

	const std::string& getUserLogin() const { return login_; }

	const std::string& getUserPassword() const { return password_; }
	void setUserPassword(const std::string& password) { password_ = password; }

	const std::string& getUserName() const { return name_; }
	void setUserName(const std::string& name) { name_ = name; }

	void show() {
		std::cout << "login: " << getUserLogin() << "\npassword: " << getUserPassword() << "\nname: " << getUserName();
	}

	friend std::ostream& operator<<(std::ostream& output, User& other);
};

std::ostream& operator<<(std::ostream& output, User& other) {
	output << other.getUserLogin() << " " << other.getUserPassword() << " " << other.getUserName();
	return output;
}