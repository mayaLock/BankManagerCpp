#pragma once

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
	void updateBalance(const unsigned long& acNum, const char* name, bool deposit=true);
	void showAccountStatus(const unsigned long& acNum) const;
	void showAllAccounts() const;
	void updateAccountInfo(const unsigned long& acNum, const char* name);
	void deleteAccount(const unsigned long& acNum, const char* name);
	void getAccoutInfo(unsigned long& acNum, std::string& name) const;
private:
	BankManager* m_ptrBM;
	DisplayUI* m_ptrDisUI;
};

