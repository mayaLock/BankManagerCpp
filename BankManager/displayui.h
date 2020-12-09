/*
	A simple bank management system	in C++ std-17.

	Author:		Dipayan Sarker
	Date:		December 09, 2020
	file:		displayui.h

	Version:	2.0.0.1
*/

#pragma once

#include <string>
#include <string_view>

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
	void accountStatusMenu(std::string_view accFormatStr) const;
	void allAccountMenu(std::string_view accListFormatStr) const;
	void clearScreen() const;
	void printTransectionHeader(std::string_view str) const;
	std::string& getHeadingMenuString(std::string_view menuName, char character, size_t len, std::string& out) const;
private:
	void (*m_clear)();
};

