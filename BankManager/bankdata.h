#pragma once

#include <string>
#include <fstream>

#include "defines.h"

class BankData
{
public:
	BankData();
	BankData(const char* name, const AccountType& acType, const long double& balance);
	BankData(const BankData& src) = default;
	BankData(BankData&& src) noexcept = default;
	BankData& operator=(const BankData& other) = default;
	BankData& operator=(BankData&& other) noexcept = default;
	~BankData() = default;
	bool operator==(const unsigned long& acNum) const;
	bool operator==(const char* name) const;
	operator std::string() const;	
public:
	const char* getName() const;
	void setName(const char* name);
	AccountType getAcType() const;
	void setAcType(const AccountType& acType);
	long double getBalance() const;
	void setBalace(const long double& balace);
	unsigned long getAcNum() const;
	void setAcNum(const unsigned long& acNum);
	std::ofstream& prepareForStore(std::ofstream& ofs) const;
public:
	static unsigned long getAccountCount();
	static void setAccountCount(const unsigned long& count);
private:
	char m_name[MAX_STR_LEN];	
	AccountType m_acType;
	long double m_balance;
	unsigned long m_acNum;
private:
	static unsigned long sm_acNum;
};
