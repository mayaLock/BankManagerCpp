#include <cstring>
#include <sstream>

#include "bankdata.h"

unsigned long BankData::sm_acNum = 0UL;

BankData::BankData() 
	: m_acNum(0UL), m_name(""), m_acType(AccountType::CURRENT), m_balance(0.0L)
{
}

BankData::BankData(const char* name, const AccountType& acType, const long double& balance)
	: m_acType(acType), m_balance(balance)
{
	++BankData::sm_acNum;
	this->m_acNum = BankData::sm_acNum;
	strcpy_s(this->m_name, MAX_STR_LEN, name);
}

bool BankData::operator==(const unsigned long& acNum) const
{
	return this->m_acNum == acNum;
}

bool BankData::operator==(const char* name) const
{
	return std::strcmp(this->m_name, name) == 0;
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

const char* BankData::getName() const
{
	return this->m_name;
}

void BankData::setName(const char* name)
{
	strcpy_s(this->m_name, MAX_STR_LEN, name);
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

void BankData::setAcNum(const unsigned long& acNum)
{
	this->m_acNum = acNum;
}

std::ofstream& BankData::prepareForStore(std::ofstream& ofs) const // serialization
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
