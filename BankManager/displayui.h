#pragma once

#include <iostream>
#include <vector>
#include <string>

class DisplayUI final
{
public:
	DisplayUI() = delete;
	explicit DisplayUI(void(*clearFunc)());
	DisplayUI(const DisplayUI& src) = delete;
	DisplayUI(DisplayUI&& src) noexcept = delete;
	DisplayUI& operator=(const DisplayUI& other) = delete;
	DisplayUI& operator=(DisplayUI&& other) noexcept = delete;
	~DisplayUI() = default;
public:
	char mainMenu() const;
	void coverMenu() const;
	void accountStatusMenu(const std::string& accFormatStr) const;
	void allAccountMenu(const std::string& accListFormatStr) const;
	void clearScreen() const;
	void printTransectionHeader(const char* str) const;
	std::string& getHeadingMenuString(const char* menuName, char character, size_t len, std::string& out) const;
private:
	void (*m_clear)();
};

