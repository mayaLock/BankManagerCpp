#include <cstring>
#include <conio.h> // _getch()
#include <iomanip>
#include <sstream>
#include <utility>

#include "displayui.h"
#include "defines.h"

char DisplayUI::mainMenu() const
{
	sleepFor(300);
	this->clearScreen();
	char options[] = "12345678";
	char ret = '\0';
	const char* menuHeaders[MENU_HEADER_ARRAY_LEN] = { "CREATE AN ACCOUNT", "DIPOSIT AMOUNT", "WITHDRAW AMOUNT", "BALANCE ENQUIRE", "VIEW LIST OF ALL ACCOUNT HOLDERS", "CLOSE AN ACCOUNT", "MODIFY AN ACCOUNT", "EXIT" };
	std::cout << CARRIAGE_RETURN << DOUBLE_NEWLINE << DOUBLE_TAB << "MAIN MENU" << DOUBLE_NEWLINE;
	for (size_t i = 0UL; i < MENU_HEADER_ARRAY_LEN; i++)
	{
		std::cout << DOUBLE_TAB << '0' << i + 1 << "  " << menuHeaders[i] << DOUBLE_NEWLINE;
	}
	do
	{
		std::cout << DOUBLE_NEWLINE << DOUBLE_TAB 
			<< "Please select <1-8> to operate:" << DOUBLE_TAB;
		ret = _getch();
		size_t optionsLen = std::strlen(options);
		for (size_t i = 0UL; i < optionsLen; i++)
		{
			if (options[i] == ret)
			{
				return ret;
			}
		}
	} while (true);
}

void DisplayUI::coverMenu() const
{
	std::cout << TEN_NEWLINE << TRIPPLE_TAB
		<< "Welcome to BankManager v2.0: A Banking Management System by Alex"
		<< DOUBLE_NEWLINE << TRIPPLE_TAB << "Please Press 'Enter' To Continue..."
		<< TRIPPLE_NEWLINE << TRIPPLE_TAB;
	std::cin.get();
	sleepFor(2000);
	this->clearScreen();
}

void DisplayUI::accountStatusMenu(const std::string& accFormatStr) const
{
	std::string temp;
	std::cout << CARRIAGE_RETURN << DOUBLE_NEWLINE << DOUBLE_NEWLINE
		<< DOUBLE_TAB << this->getHeadingMenuString("ACCOUNT STATUS", '-', 5UL, temp)
		<< TRIPPLE_NEWLINE << DOUBLE_TAB << accFormatStr << NEWLINE;
}

void DisplayUI::allAccountMenu(const std::string& accListFormatStr) const
{
	char heading[] = "List of All the Account Holders";
	size_t headingLen = std::strlen(heading);
	std::string space(headingLen * 3, '-');
	std::cout << TRIPPLE_NEWLINE << std::setw(headingLen * 2)
		<< heading << std::setw(headingLen * 2) << DOUBLE_NEWLINE
		<< space << NEWLINE << "Ac No." << std::setw(20) << "Name"
		<< std::setw(30) << "Type" << std::setw(38) << "Amount"
		<< NEWLINE << space << NEWLINE << accListFormatStr << space << NEWLINE;
}

void DisplayUI::clearScreen() const
{
	this->m_clear();
}

void DisplayUI::printTransectionHeader(const char* str) const
{
	std::cout << DOUBLE_NEWLINE << DOUBLE_TAB
		<< "Enter the amount to " << str << ':' << TAB;
}

DisplayUI::DisplayUI(void(*clearFunc)()) : m_clear(clearFunc)
{
}

std::string& DisplayUI::getHeadingMenuString(const char* menuName, char character, size_t len, std::string& out) const
{
	std::ostringstream oss;
	oss << std::move(std::string(len, character)) << menuName << std::move(std::string(len, character));
	out = std::move(oss.str());
	return out;
}
