#include "Menu.hpp"

void Menu::run() {
	bool running = true;
	printMainMenu();
	while (running) {
		std::string choice;
		std::cout << "> ";
		if (!std::getline(std::cin, choice)) {
			std::cout << "\n[EOF rilevato. Uscita dal programma.]\n";
			if (list)
				delete list;
			break;
		}

		if (equalsIgnoreCase(trim_space(choice), "1"))
			handleGroupCreation();
		else if (equalsIgnoreCase(trim_space(choice), "2"))
			handleAddUser();
		else if (equalsIgnoreCase(trim_space(choice), "3"))
			handleAddUsedto();
		else if (equalsIgnoreCase(trim_space(choice), "it"))
			handleManual();
		else if (equalsIgnoreCase(trim_space(choice), "en"))
			showGitHubGuide();
		else if (equalsIgnoreCase(trim_space(choice), "task"))
			taskList();
		else if (equalsIgnoreCase(trim_space(choice), "random"))
			random();
		else if (equalsIgnoreCase(trim_space(choice), "EXIT")) {
			running = false;
			if (list)
				delete list;
		} else
			std::cout << "input non valido...\n" << std::endl;
	}

	std::cout << "Programma terminato.\n";
}

void	Menu::printMainMenu() {
	clearScreen();
	std::cout << "========= MENU PRINCIPALE =========" << std::endl;
	std::cout << "1.      Crea gruppo di utenti" << std::endl;
	std::cout << "2.      Aggiungi uno user" << std::endl;
	std::cout << "3.      Aggiungi uno usedto" << std::endl;
	std::cout << "it.     Per una breve guida a gitHUB" << std::endl;
	std::cout << "en.     For a fast guide at gitHUB" << std::endl;
	std::cout << "task.   task per la giornata" << std::endl;
	std::cout << "random. Aggiungi uno usedto" << std::endl;
	std::cout << "EXIT. per uscire" << std::endl;
}

void	Menu::handleGroupCreation() {
	clearScreen();
	std::cout << "========= CREAZIONE GRUPPO UTENTI =========" << std::endl;
	std::cout << "(EXIT per tornare al Menu)" << std::endl;
	std::cout << "Inserisci lista degli user per creare il gruppo" << std::endl;
	std::string input;
	while (true) {
		std::cout << "> ";
		if (!std::getline(std::cin, input)) {
			std::cout << "\n[EOF rilevato. Ritorno al Menu principale.]\n";
			std::cin.clear();
			break;
		}
		if (equalsIgnoreCase(trim_space(input), "EXIT")) {
			break;
		} else if (trim_space(input) != "") {
			if (list)
				delete list;
			list = new Random(input); 
			std::cout << "Hai creato un nuvo gruppo!!\n" << std::endl;
		} else 
			std::cout << "inserire membri per il gruppo\n" << std::endl;
	}
	printMainMenu();
}

void	Menu::handleAddUser() {
	clearScreen();
	std::cout << "========= AGGIUNTA DI UN USER =========" << std::endl;
	std::cout << "(EXIT per tornare al Menu)" << std::endl;
	std::cout << "inserisci nuovo user da aggiungere al gruppo" << std::endl;
	std::string input;
	while (true) {
		std::cout << "> ";
		if (!std::getline(std::cin, input)) {
			std::cout << "\n[EOF rilevato. Ritorno al Menu principale.]\n";
			std::cin.clear();
			break;
		}
		if (equalsIgnoreCase(trim_space(input), "EXIT"))
			break;
		if (list) {
			if (list->addUser(input)) {
				std::cout << "Hai aggiunto l'utente: " << input << "\n" << std::endl;
			} else if (trim_space(input) == "") {
				std::cout << "Fornire un utente da aggiungere\n" << std::endl;
			} else
				std::cout << "L'utente è già presente nel gruppo\n" << std::endl;
		} else
			std::cout << "nessuna lista esistente\n" << std::endl;
	}
	printMainMenu();
}

void	Menu::handleAddUsedto() {
	clearScreen();
	std::cout << "========= AGGIUNTA DI UNO USEDTO =========" << std::endl;
	std::cout << "(EXIT per tornare al Menu)" << std::endl;
	std::cout << "Lo usedTo è chi conosce già github" << std::endl;
	std::string input;
	while (true) {
		std::cout << "> ";
		if (!std::getline(std::cin, input)) {
			std::cout << "\n[EOF rilevato. Ritorno al Menu principale.]\n";
			std::cin.clear();
			break;
		}
		if (equalsIgnoreCase(trim_space(input), "EXIT"))
			break;
		if (list) {
			list->addUsedTo(input);
			if (list->addUser(input)) {
				std::cout << "Hai aggiunto lo usedto: " << input << "\n" << std::endl;
			} else if (trim_space(input) == "") {
				std::cout << "Fornire uno usedTo da aggiungere\n" << std::endl;
			} else
				std::cout << "Lo usedTo è già presente nel gruppo\n" << std::endl;
		} else
			std::cout << "nessuna lista esistente\n" << std::endl;
	}
	printMainMenu();
}

void	Menu::random() {
	clearScreen();
	if (!list)
		return ;
	std::string input;
	std::cout << "========= RANDOMIZER =========" << std::endl;
	std::cout << "(EXIT per tornare al Menu)" << std::endl;
	std::cout << "random. per avere gli utenti randomizzati" << std::endl;
	while (true) {
		std::cout << "> ";
		if (!std::getline(std::cin, input)) {
			std::cout << "\n[EOF rilevato. Ritorno al Menu principale.]\n";
			std::cin.clear();
			break;
		}
		if (equalsIgnoreCase(trim_space(input), "EXIT")) {
			break;
		} else if (equalsIgnoreCase(trim_space(input), "random")){
			std::cout << "scrumbling in corso, attendere...\n";
			list->randomize();
			printByColumns(list->getFinal());
		} else
			std::cout << "input non valido...\n" << std::endl;
	}
	printMainMenu();
}

std::string	Menu::trim_non_alpha(const std::string& s) {
	size_t start = 0;
	size_t end = s.length();

	while (start < end && !std::isalpha(s[start]))
		++start;
	while (end > start && !std::isalpha(s[end - 1]))
		--end;
	return s.substr(start, end - start);
}

std::string	Menu::trim_space(const std::string& s) {
	size_t start = 0;
	size_t end = s.length();

	while (start < end && s[start] == ' ')
		++start;
	while (end > start && s[end - 1] == ' ')
		--end;
	return s.substr(start, end - start);
}

void	Menu::printByColumns(const std::vector<std::vector<std::string> > &data) {
	if (data.empty())
		return;

	std::vector<size_t> columnWidths(data.size(), 0);
	for (size_t col = 0; col < data.size(); ++col) {
		for (size_t row = 0; row < data[col].size(); ++row) {
			if (data[col][row].length() > columnWidths[col])
				columnWidths[col] = data[col][row].length();
		}
	}

	for (size_t row = 0; row < data[0].size(); ++row) {
		for (size_t col = 0; col < data.size(); ++col) {
			std::cout << std::left << std::setw(columnWidths[col] + 4) << data[col][row];
		}
		std::cout << std::endl;
	}
}

bool	Menu::equalsIgnoreCase(const std::string& a, const std::string& b) {
	if (a.size() != b.size())
		return false;
	for (size_t i = 0; i < a.size(); ++i)
		if (tolower(a[i]) != tolower(b[i]))
			return false;
	return true;
}

void	Menu::clearScreen() {
#ifdef _WIN32
    std::system("cls");
#else
    std::system("clear");
#endif
}


void	Menu::handleManual() {
	clearScreen();
	printManual();

	std::string input;
	while (true) {
		std::cout << "> ";
		if (!std::getline(std::cin, input)) {
			std::cout << "\n[EOF rilevato. Ritorno al Menu principale.]\n";
			std::cin.clear();
			break;
		}
		input = trim_space(input);

		if (equalsIgnoreCase(input, "EXIT"))
			break;
		else if (equalsIgnoreCase(input, "1"))
			printGitHubBasics();
		else if (equalsIgnoreCase(input, "2"))
			printGitHubCollaborators();
		else
			std::cout << "Selezione non valida.\n" << std::endl;
	}
	printMainMenu();
}

void	Menu::printManual() {
	std::cout << "========= MANUALE GITHUB =========" << std::endl;
	std::cout << "1. Uso base di GitHub" << std::endl;
	std::cout << "2. Aggiungere collaboratori a una repository" << std::endl;
	std::cout << "EXIT. Torna al menu principale" << std::endl;
}

void	Menu::printGitHubBasics() {
	clearScreen();
	std::cout << "========= MANUALE DI SOPPRAVIVENZA PER GITHUB =========" << std::endl;
	std::cout << "1. Crea un account su https://github.com:" << std::endl;
	std::cout << "   utilizza per l'account l'email che preferisci" << std::endl;
	std::cout << "   e come nome utente metti il tuo nome intra." << std::endl;
	std::cout << std::endl;
	std::cout << "2. Una volta nella home premi il tasto \"NEW\"" << std::endl;
	std::cout << "   per creare una nuova repository, decidi" << std::endl;
	std::cout << "   il nome delal repository e mettila come" << std::endl;
	std::cout << "   \"Public\", ricordati che questo è solo" << std::endl;
	std::cout << "   una guida! Va dare un'occhiata a che" << std::endl;
	std::cout << "   differenza c'è tra public e private." << std::endl;
	std::cout << std::endl;
	std::cout << "3. aggiungi la tua chiave ssh andando nei settings." << std::endl;
	std::cout << "   Dopo shell00 dovreste essere abbastanza pratici" << std::endl;
	std::cout << "   quindi no starò a spiegarvi come si fa ;)." << std::endl;
	std::cout << std::endl;
	std::cout << "4. Clona il repository sul tuo computer:" << std::endl;
	std::cout << "   git clone \"link alla tua repositori\"..." << std::endl;
	std::cout << "   il link si trova della pagina della repository" << std::endl;
	std::cout << "   premento il pulsante \"code <>\"." << std::endl;
	std::cout << std::endl;
	std::cout << "5. Aggiungi I file alla cartella clonata e pushali" << std::endl;
	std::cout << "   sulla repository." << std::endl;
	std::cout << "   git add . (guardate che cosa fa)" << std::endl;
	std::cout << "   git commit -m \"messaggio generico\"" << std::endl;
	std::cout << "   git push" << std::endl;
	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << "Premi INVIO per tornare al manuale...";
	std::string dummy;
	std::getline(std::cin, dummy);
	clearScreen();
	printManual();
}

void	Menu::printGitHubCollaborators() {
	clearScreen();
	std::cout << "========= AGGIUNGERE COLLABORATORI =========" << std::endl;
	std::cout << "1. Vai alla repository su GitHub." << std::endl;
	std::cout << std::endl;
	std::cout << "2. Clicca su 'Settings' del repository" << std::endl;
	std::cout << std::endl;
	std::cout << "3. Nel menu a sinistra, seleziona 'Collaborators'" << std::endl;
	std::cout << std::endl;
	std::cout << "4. Clicca 'Add people' e inserisci il nome utente GitHub" << std::endl;
	std::cout << std::endl;
	std::cout << "5. Il collaboratore riceverà un invito che dovrà accettare" << std::endl;
	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << "Premi INVIO per tornare al manuale...";
	std::string dummy;
	std::getline(std::cin, dummy);
	clearScreen();
	printManual();
}

void	Menu::showGitHubGuide() {
	clearScreen();
	printGuideIndex();

	std::string input;
	while (true) {
		std::cout << "> ";
		if (!std::getline(std::cin, input)) {
			std::cout << "\n[EOF detected. Returning to main menu.]\n";
			std::cin.clear();
			break;
		}
		input = trim_space(input);

		if (equalsIgnoreCase(input, "EXIT"))
			break;
		else if (equalsIgnoreCase(input, "1"))
			showBasicGitHubUsage();
		else if (equalsIgnoreCase(input, "2"))
			showAddingCollaborators();
		else
			std::cout << "Invalid selection.\n" << std::endl;
	}
	printMainMenu();
}

void	Menu::printGuideIndex() {
	std::cout << "========= GITHUB USER GUIDE =========" << std::endl;
	std::cout << "1. Basic GitHub usage" << std::endl;
	std::cout << "2. Adding collaborators to a repository" << std::endl;
	std::cout << "EXIT. Return to main menu" << std::endl;
}

void	Menu::showBasicGitHubUsage() {
	clearScreen();
	std::cout << "========= BASIC GITHUB USAGE =========" << std::endl;
	std::cout << "1. Create an account at https://github.com" << std::endl;
	std::cout << "   You can use any email you like." << std::endl;
	std::cout << "   For your username, use your Intra username." << std::endl;
	std::cout << std::endl;
	std::cout << "2. Once on your dashboard, click \"NEW\"" << std::endl;
	std::cout << "   to create a new repository. Choose a name" << std::endl;
	std::cout << "   and set it as 'Public' for now." << std::endl;
	std::cout << "   (Tip: Learn the difference between public and private repos!)" << std::endl;
	std::cout << std::endl;
	std::cout << "3. Add your SSH key by going into your GitHub settings." << std::endl;
	std::cout << "   After completing shell00, you should be familiar enough" << std::endl;
	std::cout << "   with it, so I won't bother explaining how to do it ;)." << std::endl;
	std::cout << std::endl;
	std::cout << "4. Clone the repository to your computer:" << std::endl;
	std::cout << "   git clone <your repository link>" << std::endl;
	std::cout << "   You can find the link by clicking the green \"Code <>\" button." << std::endl;
	std::cout << std::endl;
	std::cout << "5. Add files to the cloned folder and push them:" << std::endl;
	std::cout << "   git add . (go search what it do)" << std::endl;
	std::cout << "   git commit -m \"your message here\"" << std::endl;
	std::cout << "   git push" << std::endl;
	std::cout << std::endl;
	std::cout << "Press ENTER to return to the guide...";
	std::string dummy;
	std::getline(std::cin, dummy);
	clearScreen();
	printGuideIndex();
}

void	Menu::showAddingCollaborators() {
	clearScreen();
	std::cout << "========= ADDING COLLABORATORS =========" << std::endl;
	std::cout << "1. Go to your repository on GitHub." << std::endl;
	std::cout << std::endl;
	std::cout << "2. Click on 'Settings' at the top of the repository page." << std::endl;
	std::cout << std::endl;
	std::cout << "3. In the left sidebar, choose 'Collaborators'." << std::endl;
	std::cout << std::endl;
	std::cout << "4. Click 'Add people' and enter the GitHub username." << std::endl;
	std::cout << std::endl;
	std::cout << "5. The person will receive an invitation they must accept." << std::endl;
	std::cout << std::endl;
	std::cout << "Press ENTER to return to the guide...";
	std::string dummy;
	std::getline(std::cin, dummy);
	clearScreen();
	printGuideIndex();
}

void	Menu::taskList() {
	clearScreen();
	printTask();

	std::string input;
	while (true) {
		std::cout << "> ";
		if (!std::getline(std::cin, input)) {
			std::cout << "\n[EOF detected. Returning to main menu.]\n";
			std::cin.clear();
			break;
		}
		input = trim_space(input);

		if (equalsIgnoreCase(input, "EXIT"))
			break;
		else if (equalsIgnoreCase(input, "1"))
			mandatory();
		else if (equalsIgnoreCase(input, "2"))
			bonus();
		else
			std::cout << "input non valido\n" << std::endl;
	}
	printMainMenu();
}

void	Menu::printTask() {
	std::cout << "========= TASK LIST =========" << std::endl;
	std::cout << "1. Mandatory task" << std::endl;
	std::cout << "2. Bonus" << std::endl;
	std::cout << "EXIT. Return to main menu" << std::endl;
}

void	Menu::mandatory() {
	clearScreen();
	std::cout << "========= MANDATORY =========" << std::endl;
	std::cout << "   E' il momento di imparare ad usare git hub e lasicare in pace" << std::endl;
	std::cout << "   questi poveri baywatcher. per prima cosa dovrete creare una" << std::endl;
	std::cout << "   vostra repository su gitHUB, per poi scrivere l'inizio di una" << std::endl;
	std::cout << "   storia da voi inventata. " << std::endl;
	std::cout << std::endl;
	std::cout << "Press ENTER to return to the task list...";
	std::string dummy;
	std::getline(std::cin, dummy);
	clearScreen();
	printGuideIndex();
}

void	Menu::bonus() {
	clearScreen();
	std::cout << "========= BONUS =========" << std::endl;
	std::cout << "1. Go to your repository on GitHub." << std::endl;
	std::cout << std::endl;
	std::cout << "2. Click on 'Settings' at the top of the repository page." << std::endl;
	std::cout << std::endl;
	std::cout << "3. In the left sidebar, choose 'Collaborators'." << std::endl;
	std::cout << std::endl;
	std::cout << "4. Click 'Add people' and enter the GitHub username." << std::endl;
	std::cout << std::endl;
	std::cout << "5. The person will receive an invitation they must accept." << std::endl;
	std::cout << std::endl;
	std::cout << "Press ENTER to return to the task list...";
	std::string dummy;
	std::getline(std::cin, dummy);
	clearScreen();
	printGuideIndex();
}