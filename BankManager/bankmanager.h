/*
	A simple bank management system	in C++ std-17.

	Author:		Dipayan Sarker
	Date:		December 09, 2020
	file:		bankmanager.h

	Version:	2.0.0.1
*/

#pragma once

#include <vector>
#include <string>
#include <utility>
#include <string_view>

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
	template <typename ...Args>
	void createNewAccount(Args&& ...args);
	bool deleteAccount(const unsigned long& acNum, std::string_view name);
	bool updateBalance(const unsigned long& acNum, std::string_view name, const long double& balance);
	bool updateAccountInfo(const unsigned long& acNum, std::string_view name, std::string_view newName);
	bool updateAccountInfo(const unsigned long& acNum, std::string_view name, const AccountType& acType);
	bool updateAccountInfo(const unsigned long& acNum, std::string_view name, std::string_view* newName, const AccountType* acType);
	bool accountExists(const unsigned long& acNum) const;
	bool accountExists(std::string_view name) const;
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

template<typename ...Args>
inline void BankManager::createNewAccount(Args&& ...args) // universail reference
{
	this->m_bankInfo.emplace_back(std::forward<Args>(args)...);
}
