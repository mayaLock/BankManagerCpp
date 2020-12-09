/*
	A simple bank management system	in C++ std-17.

	Author:		Dipayan Sarker
	Date:		December 09, 2020
	file:		bankmanagerapp.h

	Version:	2.0.0.1
*/

#pragma once

#include <string_view>

#include "bankmanager.h"
#include "displayui.h"

class BankManagerApp final
{
public:
	BankManagerApp() = delete;
	explicit BankManagerApp(void(*clearFunc)());
	BankManagerApp(const BankManagerApp& src) = delete;
	BankManagerApp(BankManagerApp&& src) noexcept = delete;
	BankManagerApp& operator=(const BankManagerApp& other) = delete;
	BankManagerApp& operator=(BankManagerApp&& other) noexcept = delete;
	~BankManagerApp();
public:
	void run();
private:
	void createNewAccount();
	void updateBalance(const unsigned long& acNum, std::string_view name, bool deposit=true);
	void showAccountStatus(const unsigned long& acNum) const;
	void showAllAccounts() const;
	void updateAccountInfo(const unsigned long& acNum, std::string_view name);
	void deleteAccount(const unsigned long& acNum, std::string_view name);
	void getAccoutInfo(unsigned long& acNum, std::string& name) const;
private:
	BankManager* m_ptrBM;
	DisplayUI* m_ptrDisUI;
};

