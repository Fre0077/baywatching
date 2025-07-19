#ifndef MENU_HPP
	#define MENU_HPP

	#include <iostream>
	#include <cstdlib>
	#include <string>
	#include <iomanip>
	#include "Random.hpp"

	class Random;

class Menu {
private:
	Random	*list = NULL;
	void	random();
	void	clearScreen();
	void	printManual();
	void	handleManual();
	void	printMainMenu();
	void	handleAddUser();
	void	handleAddUsedto();
	void	printGitHubBasics();
	void	handleGroupCreation();
	void	printGitHubCollaborators();
	void	printByColumns(const std::vector<std::vector<std::string> >& data);
	bool	equalsIgnoreCase(const std::string& a, const std::string& b);

	std::string	trim_space(const std::string& s);
	std::string	trim_non_alpha(const std::string& s);

public:
	void	run();
};

#endif