#include <cctype>
#include <vector>
#include <utility>
#include <string>
#include <iostream>

#include "bankmanagerapp.h"
#include "defines.h"

BankManagerApp::BankManagerApp(void(*clearFunc)())
    : m_ptrBM(new BankManager()), m_ptrDisUI(new DisplayUI(clearFunc))
{
    // this may throw std::bad_alloc
    // how to overcome this without checking if these two
    // pointers are nullptr or not for each function call?
}

BankManagerApp::~BankManagerApp()
{
	delete this->m_ptrBM;
	delete this->m_ptrDisUI;
}

void BankManagerApp::run()
{
    this->m_ptrDisUI->coverMenu();
    bool continueProgram = true;
    while (continueProgram)
    {
        char userChoice = this->m_ptrDisUI->mainMenu();
        unsigned long acNum = 0UL;
        std::string name;
        switch (userChoice)
        {
        case '1':
            this->createNewAccount();
            break;
        case '2':
            this->getAccoutInfo(acNum, name);
            if (acNum != 0UL)
            {
                this->updateBalance(acNum, name.c_str());                
            }
            break;
        case '3':
            this->getAccoutInfo(acNum, name);
            if (acNum != 0UL)
            {
                this->updateBalance(acNum, name.c_str(), false);
            }
            break;
        case '4':
            this->getAccoutInfo(acNum, name);
            if (acNum != 0UL)
            {
                this->showAccountStatus(acNum);
                std::cin.ignore();
            }
            break;
        case '5':
            this->showAllAccounts();
            std::cin.ignore();
            break;
        case '6':
            this->getAccoutInfo(acNum, name);
            if (acNum != 0UL)
            {
                this->deleteAccount(acNum, name.c_str());
            }
            break;
        case '7':
            this->getAccoutInfo(acNum, name);
            if (acNum != 0UL)
            {
                this->updateAccountInfo(acNum, name.c_str());
            }
            break;
        case '8':
            continueProgram = false;
            this->m_ptrBM->store(); // we store any everything at the end of program; since a CLI app shouldn't be closed using 'X' button, we don't
            break;                  // need to store the data after each transaction or modification of the user data
        }                           // however, this is "not" a good idea since program can terminate for other reasons, so we won't get any unsaved data
    }                               // nonetheless, for this simple app I think it is okay
}

void BankManagerApp::createNewAccount()
{
	sleepFor(500);
	this->m_ptrDisUI->clearScreen();
	std::vector<std::string> accountInfo{};
	std::string temp;

	std::cout << CARRIAGE_RETURN << DOUBLE_NEWLINE << DOUBLE_NEWLINE
		<< DOUBLE_TAB << this->m_ptrDisUI->getHeadingMenuString("Register New Account", '*', 5UL, temp);
    do
    {
        std::cout << NEWLINE << DOUBLE_TAB 
            << "Enter the Name of the Account Holder:" << DOUBLE_TAB;
        std::getline(std::cin, temp); // account name
        if (this->m_ptrBM->accountExists(temp.c_str()))
        {
            std::cout << NEWLINE << DOUBLE_TAB
                << "The person already has account!" << NEWLINE;
            sleepFor(1000);
            this->m_ptrDisUI->clearScreen();
        }
    } while (temp.compare("") == 0 || this->m_ptrBM->accountExists(temp.c_str()));
    accountInfo.push_back(std::move(temp));
    do
    {
        std::cout << NEWLINE << DOUBLE_TAB 
            << "Enter the Type <C/S/F>:" << DOUBLE_TAB << DOUBLE_TAB;
        std::getline(std::cin, temp); // account type
        if (temp[0] == 'C' || temp[0] == 'S' || temp[0] == 'F')
        {
            break;
        }
    } while (true);
    accountInfo.push_back(std::move(temp));
    do
    {
        std::cout << NEWLINE << DOUBLE_TAB 
            << "Enter the Amount:" << DOUBLE_TAB << DOUBLE_TAB;
        std::getline(std::cin, temp); // balance
    } while (temp.compare("") == 0 || !isFloat(temp));
    accountInfo.push_back(std::move(temp));
    if (!this->m_ptrBM->createNewAccount(
        accountInfo.at(0).c_str(),
        charToAccountType(accountInfo.at(1)[0]),
        std::stold(accountInfo.at(2))))
    {
        std::cout << "couldn't create account\n";
    }
    else
    {
        std::cout << DOUBLE_NEWLINE << TRIPPLE_TAB << "Record Updated!!!";
    }
}

void BankManagerApp::updateBalance(const unsigned long& acNum, const char* name, bool deposit)
{
    sleepFor(500);
    this->m_ptrDisUI->clearScreen();
    std::string temp;
    const char* msg = deposit ? "Deposit to Account" : "Withdraw from Account";
    long double balance = 0.0L;
    std::cout << TRIPPLE_NEWLINE << DOUBLE_TAB
        << this->m_ptrDisUI->getHeadingMenuString(msg, '*', 5UL, temp);
    const BankData& clientData = this->m_ptrBM->getBankData(acNum);
    temp = std::move(static_cast<std::string>(clientData));
    this->m_ptrDisUI->accountStatusMenu(temp);
    do
    {
        this->m_ptrDisUI->printTransectionHeader(deposit ? "DEPOSIT" : "WITHDRAW");
        std::getline(std::cin, temp);
    } while (temp.compare("") == 0 || !isFloat(temp));
    balance = std::stold(temp);
    if (!deposit)
    {
        balance *= -1L; // to make negative // balance -= balance * 2 -> make positive
    }
    if (!this->m_ptrBM->updateBalance(acNum, name, balance))
    {
        std::cout << "couldn't update balance\n";
    }
    else
    {
        std::cout << DOUBLE_NEWLINE << TRIPPLE_TAB << "Record Updated!!!";
    }
}

void BankManagerApp::showAccountStatus(const unsigned long& acNum) const
{
    sleepFor(500);
    this->m_ptrDisUI->clearScreen();
    const BankData& clientData = this->m_ptrBM->getBankData(acNum);
    std::string temp(std::move(static_cast<std::string>(clientData)));
    this->m_ptrDisUI->accountStatusMenu(temp);
}

void BankManagerApp::showAllAccounts() const
{
    sleepFor(500);
    this->m_ptrDisUI->clearScreen();
    std::string temp(std::move(this->m_ptrBM->to_string()));
    this->m_ptrDisUI->allAccountMenu(temp);
}

void BankManagerApp::updateAccountInfo(const unsigned long& acNum, const char* name)
{
    sleepFor(500);
    this->m_ptrDisUI->clearScreen();
    std::string temp;
    const char* options[2] = { "Account holder's name", "Account type" };
    std::cout << TRIPPLE_NEWLINE << DOUBLE_TAB
        << this->m_ptrDisUI->getHeadingMenuString("Modify An Account Information", '*', 5UL, temp);
    for (int i = 0; i < 2; i++)
    {
        std::cout << DOUBLE_NEWLINE << DOUBLE_TAB
            << "Please press " << i + 1 << " to edit "
            << options[i] << NEWLINE;
    }
    int userChoice = 0;
    do
    {
        std::cout << DOUBLE_NEWLINE << DOUBLE_TAB << ROOT_SYMBOL;
        std::getline(std::cin, temp);
        if (temp[0] == '1' || temp[0] == '2')
        {
            break;
        }
    } while (true);
    userChoice = temp[0] - '0';
    switch (userChoice)
    {
    case 1:
        {
            do
            {
                std::cout << DOUBLE_NEWLINE << DOUBLE_TAB
                    << "Please enter new name:" << TAB;
                std::getline(std::cin, temp);
            } while (temp.compare("") == 0);
        }
        break;
    case 2:
        {
            do
            {
                std::cout << DOUBLE_NEWLINE << DOUBLE_TAB
                    << "Enter enter new account type <C/S/F>:" << DOUBLE_TAB << DOUBLE_TAB;
                std::getline(std::cin, temp);
                if (temp[0] == 'C' || temp[0] == 'S' || temp[0] == 'F')
                {
                    break;
                }
            } while (true);
        }
        break;
    default:
        return;
    }
    std::cout << DOUBLE_NEWLINE << DOUBLE_TAB
        << "Press \"M\" to modify again" << NEWLINE << DOUBLE_TAB
        << "Press \"S\" save and exit" << NEWLINE << DOUBLE_TAB
        << "Press \"N\" to exit without saving"; 
    char userResponse = '\0';
    std::string temp2; // is there a way to avoid this? since I can't use 'temp' here which is holding value we need later
    do
    {
        std::cout << NEWLINE << DOUBLE_TAB << ROOT_SYMBOL;
        std::getline(std::cin, temp2);
        if (temp2[0] == 'M' || temp2[0] == 'S' || temp2[0] == 'N')
        {
            break;
        }

    } while (true);
    userResponse = temp2[0];
    switch (userResponse)
    {
    case 'M':
        this->updateAccountInfo(acNum, name);
        break;
    case 'S':
        {
            bool res = userChoice == 1
                ? this->m_ptrBM->updateAccountInfo(acNum, name, temp.c_str())
                : this->m_ptrBM->updateAccountInfo(acNum, name, charToAccountType(temp[0]));
            if (!res)
            {
                std::cout << "couldn't update account information\n";
            }
            else
            {
                std::cout << DOUBLE_NEWLINE << TRIPPLE_TAB << "Record Updated!!!";
            }
        }
        break;
    default:
        return;
    }
}

void BankManagerApp::deleteAccount(const unsigned long& acNum, const char* name)
{
    sleepFor(500);
    this->m_ptrDisUI->clearScreen();
    if (!this->m_ptrBM->deleteAccount(acNum, name))
    {
        std::cout << "couldn't delete account\n";
    }
    else
    {
        std::cout << DOUBLE_NEWLINE << TRIPPLE_TAB << "Record Updated!!!";
    }
}

void BankManagerApp::getAccoutInfo(unsigned long& acNum, std::string& name) const
{
    sleepFor(500);
    this->m_ptrDisUI->clearScreen();
    std::string tmp;
    do
    {
        std::cout << DOUBLE_NEWLINE << DOUBLE_TAB
            << "Please enter the account number:" << DOUBLE_TAB;
        std::getline(std::cin, tmp);
    } while (tmp.compare("") == 0 || !isDigit(tmp));
    acNum = std::stoul(tmp);
    do
    {
        std::cout << DOUBLE_NEWLINE << DOUBLE_TAB
            << "Please enter the account holder's name:" << DOUBLE_TAB;
        std::getline(std::cin, name);
    } while (name.compare("") == 0);
    if (!this->m_ptrBM->isEmpty())
    {
        if (!this->m_ptrBM->accountExists(acNum) || !this->m_ptrBM->accountExists(name.c_str()))
        {
            acNum = 0UL;
            name.clear();
            std::cout << NEWLINE << DOUBLE_TAB
                << "Not found!" << NEWLINE;
            sleepFor(1000);
        }
    }
    else
    {
        acNum = 0UL;
        name.clear();
        std::cout << NEWLINE << DOUBLE_TAB
            << "No account has been created!\n";
        sleepFor(1000);
    }
}
