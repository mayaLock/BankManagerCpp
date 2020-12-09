#pragma once

#include <vector>
#include <string>

#include "bankdata.h"
#include "defines.h"

class BankManager final
{
public:
	BankManager();
	BankManager(const BankManager& src) = delete;
	BankManager(BankManager&& src) noexcept = delete;
	BankManager& operator=(const BankManager& other) = delete;
	BankManager& operator=(BankManager&& other) noexcept = delete;
	~BankManager() = default;
	operator std::string() const;
public:
	bool createNewAccount(const char* name, const AccountType& acType, const long double& balance);
	bool deleteAccount(const unsigned long& acNum, const char* name);
	bool updateBalance(const unsigned long& acNum, const char* name, const long double& balance);
	bool updateAccountInfo(const unsigned long& acNum, const char* name, const char* newName);
	bool updateAccountInfo(const unsigned long& acNum, const char* name, const AccountType& acType);
	bool updateAccountInfo(const unsigned long& acNum, const char* name, const char* newName, const AccountType* acType);
	bool accountExists(const unsigned long& acNum) const;
	bool accountExists(const char* name) const;
	const BankData& getBankData(const unsigned long& acNum) const;	
	BankData& getBankData(const unsigned long& acNum);
	bool isEmpty() const;
	std::string to_string() const;
	bool store() const;
	bool load();
private:	
	size_t indexOf(const unsigned long& acNum) const;
private:
	std::vector<BankData> m_bankInfo{};
};
