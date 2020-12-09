/*
	A simple bank management system	in C++ std-17.

	Author:		Dipayan Sarker
	Date:		December 09, 2020
	file:		BankData.cc

	Version:	2.0.0.1
*/

#include <sstream>
#include <utility>

#include "bankdata.h"

unsigned long BankData::sm_acNum = 0UL;

BankData::BankData(std::string&&name, const AccountType& acType, const long double& balance)
	: m_name(std::move(name)), m_acType(acType), m_balance(balance)
{
	++BankData::sm_acNum;
	this->m_acNum = BankData::sm_acNum;
}

BankData::BankData(const unsigned long& acNum, std::string&& name, const AccountType& acType, const long double& balance)
	: m_acNum(acNum), m_name(std::move(name)), m_acType(acType), m_balance(balance)
{
}

bool BankData::operator==(const unsigned long& acNum) const
{
	return this->m_acNum == acNum;
}

bool BankData::operator==(std::string_view name) const
{
	return (this->m_name.compare(name) == 0);
}

BankData::operator std::string() const
{
	std::ostringstream oss;
	oss << "Account Number:" << TAB << this->m_acNum << NEWLINE << DOUBLE_TAB
		<< "Account Holder:" << TAB << this->m_name << NEWLINE << DOUBLE_TAB
		<< "Account Type:" << TAB << accountTypeToString(this->m_acType) << NEWLINE << DOUBLE_TAB
		<< "Account Balance" << TAB << this->m_balance;
	return oss.str();
}

std::string_view BankData::getName() const
{
	return this->m_name;
}

void BankData::setName(std::string_view name)
{
	this->m_name = name;
}

AccountType BankData::getAcType() const
{
	return this->m_acType;
}

void BankData::setAcType(const AccountType& acType)
{
	this->m_acType = acType;
}

long double BankData::getBalance() const
{
	return this->m_balance;
}

void BankData::setBalace(const long double& balace)
{
	this->m_balance = balace;
}

unsigned long BankData::getAcNum() const
{
	return this->m_acNum;
}

std::ostream& BankData::prepareForStore(std::ostream& ofs) const // serialization
{
	ofs << this->m_acNum << ';' << this->m_name << '\0' << accountTypeToChar(this->m_acType)
		<< ';' << this->m_balance;
	return ofs;
}

unsigned long BankData::getAccountCount()
{
	return BankData::sm_acNum;
}

void BankData::setAccountCount(const unsigned long& count)
{
	BankData::sm_acNum = count;
}
