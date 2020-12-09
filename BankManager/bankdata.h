/*
	A simple bank management system	in C++ std-17.

	Author:		Dipayan Sarker
	Date:		December 09, 2020
	file:		bankdata.h

	Version:	2.0.0.1
*/

#pragma once

#include <string>
#include <ostream>
#include <string_view>

#include "defines.h"

class BankData
{
public:
	BankData() = delete;
	BankData(std::string&& name, const AccountType& acType, const long double& balance);
	BankData(const unsigned long& acNum, std::string&& name, const AccountType& acType, const long double& balance);
	BankData(const BankData& src) = default;
	BankData(BankData&& src) noexcept = default;
	BankData& operator=(const BankData& other) = default;
	BankData& operator=(BankData&& other) noexcept = default;
	~BankData() = default;
	bool operator==(const unsigned long& acNum) const;
	bool operator==(std::string_view name) const;
	operator std::string() const;	
public:
	std::string_view getName() const;
	void setName(std::string_view name);
	AccountType getAcType() const;
	void setAcType(const AccountType& acType);
	long double getBalance() const;
	void setBalace(const long double& balace);
	unsigned long getAcNum() const;
	std::ostream& prepareForStore(std::ostream& os) const;
public:
	static unsigned long getAccountCount();
	static void setAccountCount(const unsigned long& count);
private:
	std::string m_name;
	AccountType m_acType;
	long double m_balance;
	unsigned long m_acNum;
private:
	static unsigned long sm_acNum;
};
