#pragma once

#include <chrono>
#include <thread>
#include <cctype>
#include <regex>
#include <fstream>

constexpr size_t MAX_STR_LEN = 30UL;
constexpr size_t MENU_HEADER_ARRAY_LEN = 8UL;
constexpr const char* DOUBLE_NEWLINE = "\n\n";
constexpr char NEWLINE = '\n';
constexpr char TAB = '\t';
constexpr const char* TEN_NEWLINE = "\n\n\n\n\n\n\n\n\n\n";
constexpr const char* TRIPPLE_NEWLINE = "\n\n\n";
constexpr const char* DOUBLE_TAB = "\t\t";
constexpr const char* TRIPPLE_TAB = "\t\t\t";
constexpr char CARRIAGE_RETURN = '\r';
constexpr const char* ROOT_SYMBOL = ">>> ";

enum class AccountType
{
	CURRENT,
	SAVINGS,
	FIXED
};

static void sleepFor(unsigned long milSec)
{
	std::this_thread::sleep_for(std::chrono::milliseconds(milSec));
}

static AccountType charToAccountType(char c)
{
	return c == 'C' ? AccountType::CURRENT
		: c == 'S' ? AccountType::SAVINGS
		: AccountType::FIXED;
}

static char accountTypeToChar(const AccountType& accType)
{
	return accType == AccountType::CURRENT ? 'C' 
		: accType == AccountType::SAVINGS ? 'S'
		: 'F';
}

static const char* accountTypeToString(const AccountType& accType)
{
	return accType == AccountType::CURRENT ? "CURRENT"
		: accType == AccountType::SAVINGS ? "SAVINGS"
		: "FIXED";
}

static bool isDigit(const std::string& str)
{
	std::string::const_iterator cit = str.cbegin();
	while (cit != str.end() && std::isdigit(*cit))
	{
		++cit;
	}
	return !str.empty() && cit == str.end();
}

static bool isFloat(const std::string& str)
{
	std::regex pattern("[0-9]*\\.?[0-9]+$");
	return std::regex_match(str, pattern);
}

static bool existsFile(const char* name)
{
	std::ifstream ifs(name);
	return ifs.good();
}
