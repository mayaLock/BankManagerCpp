/*
	A simple bank management system	in C++ std-17.

	Author:		Dipayan Sarker
	Date:		December 09, 2020
	file:		BankManager.cc

	Version:	2.0.0.1
*/

#include <algorithm>
#include <sstream>
#include <iomanip>
#include <fstream>
#include <cstdlib>

#include "bankmanager.h"
#include "defines.h"

static std::string_view storeFileName = "v8.dat";

bool BankManager::deleteAccount(const unsigned long& acNum, std::string_view name)
{
	if (!this->accountExists(acNum) || !this->accountExists(name))
	{
		return false;
	}
	this->m_bankInfo.erase(this->m_bankInfo.begin() + this->indexOf(acNum));
	return true;
}

bool BankManager::updateBalance(const unsigned long& acNum, std::string_view name, const long double& balance)
{
	if (!this->accountExists(acNum) || !this->accountExists(name))
	{
		return false;
	}
	BankData& clientData = this->getBankData(acNum);
	long double curBalance = clientData.getBalance();
	curBalance += balance;
	clientData.setBalace(curBalance);
	return true;
}

bool BankManager::accountExists(std::string_view name) const
{
	return std::find(this->m_bankInfo.begin(), this->m_bankInfo.end(), name) != this->m_bankInfo.end();
}

size_t BankManager::indexOf(const unsigned long& acNum) const
{
	return std::find(this->m_bankInfo.begin(), this->m_bankInfo.end(), acNum) - this->m_bankInfo.begin();
}

BankData& BankManager::getBankData(const unsigned long& acNum)
{
	size_t pos = this->indexOf(acNum);
	return this->m_bankInfo.at(pos);
}

bool BankManager::isEmpty() const
{
	return this->m_bankInfo.empty();
}

std::string BankManager::to_string() const
{
	return this->operator std::string();
}

bool BankManager::store() const // serialization
{
	std::ofstream ofs(storeFileName.data(), std::ios::binary | std::ios::out); // not a good approach since we may have big chunk of data so we create file each time we invoke store()
	if (!ofs.good() || !ofs.is_open())									// what would be a better option?
	{
		return false;
	}
	ofs << this->m_bankInfo.size() << '*' << BankData::getAccountCount() << '*';
	for (const BankData& b : this->m_bankInfo)
	{
		b.prepareForStore(ofs) << '*';
	}
	ofs.close();
	return true;
}

bool BankManager::load() // deserialization; only call once at app initialization
{
	std::ifstream ifs(storeFileName.data(), std::ios::in | std::ios::binary);
	if (!ifs.good() || !ifs.is_open())
	{
		return false;
	}
	std::string tmp, name;
	unsigned long acNum, acCount;
	AccountType acType;
	long double balance;
	std::getline(ifs, tmp, '*'); // vSize
	size_t vSize = std::stoull(tmp);
	std::getline(ifs, tmp, '*'); // count
	acCount = std::stoul(tmp);
	BankData::setAccountCount(acCount);
	for (size_t i = 0UL; i < vSize; i++)
	{
		std::getline(ifs, tmp, ';');
		acNum = std::stoul(tmp); // acNum
		std::getline(ifs, tmp, '\0'); // name
		name = std::move(tmp);
		std::getline(ifs, tmp, ';'); // acType
		acType = charToAccountType(tmp[0]);
		std::getline(ifs, tmp, '*'); // balance
		balance = std::stold(tmp);
		this->createNewAccount(acNum, std::move(name), acType, balance);
	}
	ifs.close();
	return true;
}

const BankData& BankManager::getBankData(const unsigned long& acNum) const
{
	//return const_cast<const BankData&>(this->getBankData(acNum)); // won't work since it's gonna cause overflow // return a const version of BankData&
	size_t pos = this->indexOf(acNum);
	return this->m_bankInfo.at(pos);
}

bool BankManager::updateAccountInfo(const unsigned long& acNum, std::string_view name, const AccountType& acType)
{
	return this->updateAccountInfo(acNum, name, nullptr, &acType);
}

bool BankManager::updateAccountInfo(const unsigned long& acNum, std::string_view name, std::string_view newName)
{
	return this->updateAccountInfo(acNum, name, &newName, nullptr);
}

bool BankManager::updateAccountInfo(const unsigned long& acNum, std::string_view name, std::string_view* newName, const AccountType* acType)
{
	if (name.empty() && acType == nullptr)
	{
		return false;
	}
	if (!this->accountExists(acNum) || !this->accountExists(name))
	{
		return false;
	}
	BankData& clientData = this->getBankData(acNum);
	if (newName != nullptr)
	{
		clientData.setName(*newName);
	}
	if (acType != nullptr)
	{
		clientData.setAcType(*acType);
	}
	return true;
}

bool BankManager::accountExists(const unsigned long& acNum) const
{
	return std::find(this->m_bankInfo.begin(), this->m_bankInfo.end(), acNum) != this->m_bankInfo.end();
}

BankManager::BankManager()
{
	if (existsFile(storeFileName.data()))
	{
		if (!this->load())
		{
			std::exit(EXIT_FAILURE);
		}
	}
}

BankManager::operator std::string() const
{
	std::ostringstream oss;
	for (size_t i = 0UL; i < this->m_bankInfo.size(); i++)
	{
		oss << this->m_bankInfo.at(i).getAcNum() << std::setw(28)
			<< this->m_bankInfo.at(i).getName() << std::setw(25)
			<< accountTypeToChar(this->m_bankInfo.at(i).getAcType()) << std::setw(39)
			<< this->m_bankInfo.at(i).getBalance() << '\n';
	}
	return oss.str();
}
