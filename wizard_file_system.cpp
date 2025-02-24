/*
Author: Lauren Bell
Description: file accessing program for users to login, sort given spellbooks and spells by effect and success rate, 
	and save information to file or terminal. 
*/

#include <iostream>
#include <fstream>
#include <string>

struct spell {
	std::string name;
	float success_rate;
	std::string effect;
};

struct spellbook {
	std::string title;
	std::string author;
	int num_pages;
	int edition;
	int num_spells;
	float avg_success_rate;
	spell *spells;
};

//a struct to hold info of a wizard
struct wizard {
	std::string name;
	int id; // Used for logging in
	std::string password; // Used for logging in
	std::string position_title; // Used to restrict poison and death spells
	float beard_length;
};

/*
 * Function: create_spells
 * Description: Allocates a dynamic array of spells of the requested size and
 * 		returns a pointer that points to it
 * Parameters:
 * 		size (int): Size of dynamic array of spells to create
 * Returns: Pointer that points to dynamically allocated array of spells
 */
spell* create_spells(int size) {
	
	spell* spell_array = new spell[size];
	return spell_array;
}

/*
 * Function: read_spell_data
 * Description: Reads all of the information associated with a single spell
 * 		structure from the given spellbooks text file and returns a created
 * 		spell structure containing that information.
 * Parameters:
 * 		file (std::ifstream&): A reference to an std::ifstream that is open on
 * 		the input spellbooks text file and prepared to read information about
 * 		the next spell in a spellbook.
 * Returns: The created spell structure containing the information of the
 * 		next spell in the input file
 *
 * Hint: “std::ifstream& file” is a reference to a filestream object. You will
 * need to create one, open it up to read from the spellbooks text file, read
 * the information up to (but not including) the first spell, and then pass it
 * into this function to start reading spell data. Remember that information in
 * an input file must generally be read by your program in the order that it’s
 * presented in the file.
 */
spell read_spell_data(std::ifstream& file) {
	spell s;
	file >> s.name >> s.success_rate >> s.effect;
	return s;
}

/*
 * Function: create_spellbooks
 * Description: Allocates a dynamic array of spellbooks of the requested size
 * 		and returns a pointer that points to it.
 * Parameters:
 * 		size (int): Size of dynamic array of spellbooks to create
 * Returns: Pointer that points to dynamically allocated array of spellbooks
 */
spellbook* create_spellbooks(int size) {
	return new spellbook[size];
}

/*
 * Function: read_spellbook_data
 * Description: Reads all of the information associated with a single spellbook
 * 		structure from the given spellbooks text file and returns a created
 * 		spellbook structure containing that information. Note that the
 * 		avg_success_rate member variable of the returned spellbook structure is
 * 		not contained in the text file, but rather will need to be computed as
 * 		the average (mean) success rate of all spells in the spellbook (i.e.,
 * 		add up the success rates of all spells in the spellbook, then divide by
 * 		the number of spells in the spellbook).
 * Parameters:
 * 		file (std::ifstream&): A reference to an std::ifstream that is open on
 * 		the input spellbooks text file and prepared to read information about
 * 		the next spellbook.
 * Returns: The created spellbook structure containing the information of the
 * 		next spellbook in the file
 *
 * Hint: This function will need to call the read_spell_data() function several
 * times in order to read all of the data associated with all of the spells in
 * the given spellbook.
 */
spellbook read_spellbook_data(std::ifstream& file) {
	spellbook sb;
	file >> sb.title >> sb.author >> sb.num_pages >> sb.edition >> sb.num_spells;
	
	sb.spells = create_spells(sb.num_spells);
	
	for (int i = 0; i < sb.num_spells; i++)
		sb.spells[i] = read_spell_data(file);
	
	double mean = 0;
	for (int i = 0; i < sb.num_spells; i++) {
		mean += sb.spells[i].success_rate;
	}
	sb.avg_success_rate = mean/sb.num_spells;
	return sb;
}

/*
 * Function: delete_spells
 * Description: Deletes a given dynamic array of spells and updates its pointer
 * 		to be nullptr.
 * Parameters:
 * 		spells (spell*&): A reference to the pointer that points to the dynamic
 * 			array of spells to be deleted.
 * Post-conditions: 1. Dynamic array of spells should be deleted. 2. spells
 * 		pointer parameter should be set to nullptr. Since this parameter is
 * 		passed by reference, the corresponding argument will be set to nullptr
 * 		as well.
 *
 * Hint: A dynamic array of spells is normally represented with a pointer of
 * type spell* pointing to the array’s base address, but here it’s spell*&.
 * That is, it’s a reference to a spell pointer. This is because the function
 * needs to be able to delete the array that the pointer points to AND modify
 * the pointer itself to be nullptr. In order to be able to modify the pointer
 * itself (which is an argument), the pointer needs to be passed by reference
 * (or passed by pointer---here we use a reference for simplicity).
 */
void delete_spells(spell*& spells) {
	delete[] spells;
	spells = nullptr;}

/*
 * Function: delete_spellbooks
 * Description: Deletes all of the dynamic memory associated with the given
 * 		array of spellbooks, including the arrays of spells inside each
 * 		spellbook. The size parameter indicates the size of the array of
 * 		spellbooks.
 * Parameters:
 * 		spellbooks (spellbook*&): A reference to the pointer that points to the
 * 			dynamic array of spellbooks to be deleted
 * Post-conditions: 1. Dynamic arrays of spells within each spellbook should
 * 		be deleted (see hint). 2. Dynamic array of spellbooks should be deleted.
 * 		3. spellbooks pointer parameter should be set to nullptr. Since this
 * 		parameter is passed by reference, the corresponding argument will be set
 * 		to nullptr as well.
 *
 * Hint: This function should call the delete_spells() function several
 * times---once for each spellbook’s array of spells---and then proceed to
 * delete the array of spellbooks itself. spellbooks is passed by reference for
 * the same reason as in the delete_spells() function.
 */
void delete_spellbooks(spellbook*& spellbooks, int size) {
	for (int i = 0; i < size; i++) {
        delete_spells(spellbooks[i].spells);
    }
    delete[] spellbooks;
    spellbooks = nullptr;
}


/*
Function: create_wizards
Description: allocates a dynamic array of wizardss of the requested size
 * 		and returns a pointer that points to it.
Parameters: size (int): Size of dynamic array of wizards to create
Returns: Pointer that points to dynamically allocated array of wizards
*/
wizard* create_wizards(int size) {
	return new wizard[size];
}

/*
Function: read_wizard_data
Description: reads in wizard data from the user-given file and creates a wizards
 * 		data structure with each line 
Parameters: user given file
Returns: the newly-made wizard object 
*/
wizard read_wizard_data(std::ifstream &file) {
	wizard w;
	file >> w.name >> w.id >> w.password >> w.position_title >> w.beard_length;
	return w;
}

/*
Function: delete_wizards
Description: deletes all of the dynamic memory associated with the given
 * 		array of wizards. The size parameter indicates the size of the array of
 * 		wizards.
Parameters: wizard (wizards*&): A reference to the pointer that points to the dynamic
 * 			array of wizards to be deleted.
*/
void delete_wizards(wizard*& wizards) {
	delete[] wizards;
	wizards = nullptr;
}

/*
Function: login_verification
Description: iterates through the user-given wizards file to see if the user login matches
Parameters: const wizard* wizards: pointer to the wizards dynamic array
			int num_wizards: number of wizards found in the user given wizards file
			int id: user given id 
			const std::string &password: user given password
			wizard& current_user: reference to the wizard object currently logged in
Returns: a boolean value (true if the match is found, false if not)
*/
bool login_verification(const wizard* wizards, int num_wizards, int id, const std::string &password, wizard& current_user) {
	for (int i = 0; i < num_wizards; i++) {
		if ((wizards[i].id == id) && (wizards[i].password == password)) {
			current_user = wizards[i];
			return true;
		}
	}
	return false;
}

/*
Function: display_spellbook_info
Description: pretty self explanatory, displays all the attributes of a spellbook to the terminal. filters
	out 'death' and 'poison' spells if the logged-in user is a student
Parameters: const spellbook &sb: refernce to the spellbook object being printed
			bool is_student: true if the user's wizard.position_title is student, and false if not
*/
void display_spellbook_info(const spellbook &sb, bool is_student) {
	std::cout << "Spellbook: " << sb.title << std::endl;
	std::cout << "Author: " << sb.author << std::endl;
	std::cout << "Pages: " << sb.num_pages << std::endl;
	std::cout << "Edition: " << sb.edition << std::endl;
	std::cout << "Average Success Rate: " << sb.avg_success_rate << std::endl;
	
	std::cout << "Spells: " << std::endl;
	for (int i = 0; i < sb.num_spells; i++) {
		if (is_student && (sb.spells[i].effect == "death" || sb.spells[i].effect == "poison"))
			//don't print poison or death spells if the user is a student
			continue;
		
		std::cout << sb.spells[i].name << " " << sb.spells[i].success_rate << " " << sb.spells[i].effect << std::endl;
	}
}

/*
Function: spellbook_to_file
Description: saves the spellbook data to file, similar to the previous function. filters out 'death'
	and 'poison' spells if the logged in user is a student
Parameters: std::ofstream &outfile: user given name of the file to save information to
			const spellbook &sb: refernce to the current spellbook object
			bool is_student: boolean value, true if the logged in user is a student and false if not
*/
void spellbook_to_file(std::ofstream &outfile, const spellbook &sb, bool is_student) {
	outfile << "Spellbook: " << sb.title << std::endl;
	outfile << "Author: " << sb.author << std::endl;
	outfile << "Pages: " << sb.num_pages << std::endl;
	outfile << "Edition: " << sb.edition << std::endl;
	outfile << "Average Success Rate: " << sb.avg_success_rate << std::endl;
	
	outfile << "Spells: " << std::endl;
	for (int i = 0; i < sb.num_spells; i++) {
		if (is_student && (sb.spells[i].effect == "death" || sb.spells[i].effect == "poison"))
			continue;
		
		outfile << sb.spells[i].name << " " << sb.spells[i].success_rate << " " << sb.spells[i].effect << std::endl;
	}
}

/* for the poor TA who ends up having to grade this, could I have could I have combined the previous two functions 
and just treated the locaion as another argument? like, have put 'location' as a parameter and the input options are 
'std::cout' or 'std::ofstream &outfile"? Having two seperate functions felt like an okay way to implement it, especially
since I'm not sure how it would work with different data types, but lmk if that is a possible strat for next time. */


/*
Function: input_files
Description: 
Parameters: std::string &wizard_file: reference to the user given file with wizard info
			std::string &spellbook_file: reference to the user given spellbook info file
Returns: a boolean value, true if the file uploads works, false if not
*/
bool input_files(std::string &wizard_file, std::string &spellbook_file) {
	std::cout << "Enter the wizard info file name: ";
    if (not (std::cin >> wizard_file)) return false;
    
    std::cout << "Enter the spellbook info file name: ";
    if (not (std::cin >> spellbook_file)) return false;
    
    return true;
}

/*
Function: open_files
Description: opens the user given files and saves them to a reference variable
Parameters: const std::string &wizard_file: reference to the user given wizard info file
			const std::string &spellbook_file: reference to the user given spellbook info file
			std::ifstream &wizard_in: variable holding the wizard input file
			std::ifstream &spellbook_in: variable holding the wpellbook input file
REturns: a boolean value, true if the file accessing works, false if not
*/
bool open_files(const std::string &wizard_file, const std::string &spellbook_file, 
				std::ifstream &wizard_in, std::ifstream &spellbook_in) {
	wizard_in.open(wizard_file);
	spellbook_in.open(spellbook_file);
	
	if (not wizard_in || not spellbook_in) {
		std::cout << "Error: file names not found or accessing error." << std::endl;
		return false;
	}
	return true;
}

/*
Function: read_in_data
Description: reads in spellbook and wizards data from the user given files and creates a pointer to 
	the respective dynamic arrays created. 
Parameters: std::ifstream& wizard_in: reference to the user given wizard file
			std::ifstream& spellbook_in: reference to the user given spellbook file 
			wizard*& wizards: pointer to the created wizards object
			spellbook*& spellbooks: pointer to the created spellbook object
			int& num_wizards: integer found in the beginning of the file with the number of wizards 
			int& num_spellbooks: integer found in the beginning of the file with the number of spellbooks 
Returns: a boolean value depending on if the reading was a success
*/
bool read_in_data(std::ifstream& wizard_in, std::ifstream& spellbook_in, wizard*& wizards, 
					spellbook*& spellbooks, int& num_wizards, int& num_spellbooks){
	wizard_in >> num_wizards;
	wizards = create_wizards(num_wizards);
	for (int i = 0; i < num_wizards; i++) {
		wizards[i] = read_wizard_data(wizard_in);
	}

	spellbook_in >> num_spellbooks; 
	spellbooks = create_spellbooks(num_spellbooks);
	for (int i = 0; i < num_spellbooks; i++) {
		spellbooks[i] = read_spellbook_data(spellbook_in);
	}
	return true;
}

/*
Function: user_login
Description: takes the uder given ID and password, sends them to login_verification() to find a match, and 
	prints the information of the logged in user to the terminal
Parameters: const wizard* wizards: pointer for the wizards dynamic array
			int num_wizards: read in from the first line of the user given wizards file
			wizard& current_user: reference to the wizard currently logged in
*/
bool user_login(const wizard* wizards, int num_wizards, wizard& current_user) {
    int login_attempts = 0;
    bool logged_in = false;
    
	//let the user try to login three times
    while (not logged_in && login_attempts < 3) {
        int id;
        std::string password;
        std::cout << "Please enter your ID: ";
        std::cin >> id;
        std::cout << "Please enter your password: ";
        std::cin >> password;
        
		//if verification returns true, print info to terminal
        if (login_verification(wizards, num_wizards, id, password, current_user)) {
            logged_in = true;
            std::cout << "Welcome, " << current_user.name << "!" << std::endl;
        	std::cout << "ID: " << current_user.id  << std::endl;
            std::cout << "Status: " << current_user.position_title << std::endl;
            std::cout << "Beard Length: " << current_user.beard_length << std::endl;
			return true;
		} else {
			//let the user try to login again if verification returns false
            login_attempts++;
			std::cout << "Incorrect id or password. Attempts remaining: " << login_attempts << std::endl;
        }
    }
	//end program when theres more than three attempts
	std::cout << "Too many failed login attempts." << std::endl;
	return false;
}

/*
Function: display_selection_effect
Description: search and display function for 'search by effect', filtering 'death' and 'poison' out for students. 
	saves to file or prints to screen depending on user input 
Parameters: spellbook* spellbooks: pointer to the spellbook dynamic array
			int num_spellbooks: # of spellbooks from user given file
			std::string effect: effect to search for 
			bool is_student: true if student, false if not
*/
void display_selection_effect(spellbook* spellbooks, int num_spellbooks, std::string effect, bool is_student) {
    int display_choice;
    do {
        std::cout << "How would you like the information displayed?" << std::endl;
        std::cout << "1. Print to screen" << std::endl;
        std::cout << "2. Print to file" << std::endl;
        std::cout << "Your Choice: ";
        std::cin >> display_choice;
    } while (display_choice != 1 && display_choice != 2);

    // print spells with the user-chosen effect
    if (display_choice == 1) {
        // print to screen
        for (int i = 0; i < num_spellbooks; i++) {
            for (int j = 0; j < spellbooks[i].num_spells; j++) {
                if (spellbooks[i].spells[j].effect == effect) {
                    if (!(is_student && (effect == "death" || effect == "poison"))) {
                        std::cout << "Spellbook: " << spellbooks[i].title << std::endl;
                        std::cout << "Spell: " << spellbooks[i].spells[j].name 
                                  << " " << spellbooks[i].spells[j].success_rate 
                                  << " " << spellbooks[i].spells[j].effect 
                                  << std::endl;
                    }
                }
            }
        }
    } else {
        // save to user given file
        std::string filename;
        std::cout << "Please enter filename: ";
        std::cin >> filename;
        
        std::ofstream outfile(filename);
        for (int i = 0; i < num_spellbooks; i++) {
            for (int j = 0; j < spellbooks[i].num_spells; j++) {
                if (spellbooks[i].spells[j].effect == effect) {
                    if (!(is_student && (effect == "death" || effect == "poison"))) {
                        outfile << "Spellbook: " << spellbooks[i].title << std::endl;
                        outfile << "Spell: " << spellbooks[i].spells[j].name 
                                << " " << spellbooks[i].spells[j].success_rate 
                                << " " << spellbooks[i].spells[j].effect 
                                << std::endl;
                    }
                }
            }
        }
        outfile.close();
        std::cout << "Saved to file!" << std::endl;
    }
}

/*
Function: display_selection_avg_success
Description: sorts spells and either prints it to terminal or saves to user given file
Parameters: spellbook* spellbooks: pointer to the spellbook dynamic array
			int num_spellbooks: from user given spellbooks file
			bool is_student: true if the user is a student, false if not
*/
void display_selection_avg_success(spellbook* spellbooks, int num_spellbooks, bool is_student) {
    int total_spells = 0;

    // count total spells
    for (int i = 0; i < num_spellbooks; i++) {
        total_spells += spellbooks[i].num_spells;
    }

    // allocate dynamic array for all spells
    spell* all_spells = new spell[total_spells];

    // copy all spells into the array
    int index = 0;
    for (int i = 0; i < num_spellbooks; i++) {
        for (int j = 0; j < spellbooks[i].num_spells; j++) {
            if (not (is_student && (spellbooks[i].spells[j].effect == "death" || spellbooks[i].spells[j].effect == "poison"))) {
                all_spells[index++] = spellbooks[i].spells[j];
            }
        }
    }

    // sort spells in descending order of success rate using bubble sort!!
    for (int i = 0; i < index - 1; i++) {
        for (int j = 0; j < index - i - 1; j++) {
            if (all_spells[j].success_rate < all_spells[j + 1].success_rate) {
                std::swap(all_spells[j], all_spells[j + 1]);
            }
        }
    }

    // print sorted spells
    for (int i = 0; i < index; i++) {
        std::cout << all_spells[i].name << " " << all_spells[i].success_rate << " " << all_spells[i].effect << std::endl;
    }
	//cleanup
    delete[] all_spells;  
}


/*
Function: main_menu
Description: gives main menu options to user and using their input, lets them do various things as outlined in the interface 
	for the main menu. 
Parameters: spellbook* spellbooks: pointer to spellbook dynamic array
			int num_spellbooks: number of spellbooks as outlined by user given file
			const wizard& current_user: reference to the current logged in wiazrd object
*/
void main_menu(spellbook* spellbooks, int num_spellbooks, const wizard& current_user) {
    bool is_student = (current_user.position_title == "Student");
    int choice;
    
    do {
        //user interface for main menu
		std::cout << "Which option would you like to choose?" << std::endl;
        std::cout << "1. Display all" << std::endl;
        std::cout << "2. Search spellbook by its name" << std::endl;
        std::cout << "3. Search spells by their effect" << std::endl;
        std::cout << "4. Sort spellbooks by average success rate" << std::endl;
        std::cout << "5. Quit" << std::endl;
        
        std::cout << "Your Choice: ";
        std::cin >> choice;
        
        switch (choice) {
            case 1: { 
                //display all 
                for (int i = 0; i < num_spellbooks; i++) {
                    display_spellbook_info(spellbooks[i], is_student);
                }
                break;
            }
            case 2: { 
                //search by name
                std::string book_name;
                std::cout << "Enter spellbook name: ";
                std::cin >> book_name;
                
				//iterate through spellbooks and print the info to the terminal
                bool found = false;
                for (int i = 0; i < num_spellbooks; i++) {
                    if (spellbooks[i].title == book_name) {
                        display_spellbook_info(spellbooks[i], is_student);
                        found = true;
                        break;
                    }
                }
                //error handling for incorrect user input
				if (not found) {
					std::cout << "No spellbook found with that name." << std::endl;
                }
                break;
            }
            case 3: {
                //search by effect
                std::string effect;
                bool valid_effect;
                do {
                    std::cout << "Enter the spell effect: ";
                    std::cin >> effect;
                    
					//making sure students can't access 'death' and 'poison')
                    valid_effect = effect == "fire" || effect == "bubble" || effect == "memory_loss" || effect == "healing" ||
                                 (not is_student && (effect == "death" || effect == "poison"));
                    
                    if (not valid_effect) {
                        std::cout << "Error: Invalid spell effect" << std::endl;
                    }
                } while (not valid_effect);
                
				//print spell info to terminal OR append to file
                display_selection_effect(spellbooks, num_spellbooks, effect, is_student);
                break;
            }
            case 4: {
				//sort by average success rate !!
				//print spell info to terminal OR append to file
                display_selection_avg_success(spellbooks, num_spellbooks, is_student);
                break;
            }
            case 5: {
                //exit the program
				std::cout << "Goodbye!" << std::endl;
                break;
            }
            default:
                //error handling for choice != 1-5
				std::cout << "Invalid choice. Please try again." << std::endl;
        }
    } while (choice != 5);
}

/*
Function: main
Description: main function for program, reads in data, does error handling for file mishaps, and
	passes info the various functions for the login and main menu processes
Parameters: none
*/
int main () {
	
	//initialize all the needed variables
	std::string wizard_file;
	std::string spellbook_file;
	std::ifstream wizard_in;
	std::ifstream spellbook_in;
	wizard* wizards = nullptr;
	spellbook* spellbooks = nullptr;
	int num_wizards = 0; 
	int num_spellbooks = 0;
	wizard current_user;

	//error handling for file accessing
	if (not input_files(wizard_file, spellbook_file)) {
		std::cout << "Error: file names incorrect or missing." << std::endl;
		return 0;
	}
	if (not open_files(wizard_file, spellbook_file, wizard_in, spellbook_in)) {
		return 0;
	}

	//error handling for reading in the data
	if (not read_in_data(wizard_in, spellbook_in, wizards, spellbooks, num_wizards, num_spellbooks)) {
		delete_wizards(wizards);
		delete_spellbooks(spellbooks, num_spellbooks);
		wizard_in.close();
		spellbook_in.close();
		return 0;
	}
	wizard_in.close();
	spellbook_in.close();

	//error handling for logging in
	if (not user_login(wizards, num_wizards, current_user)) {
		delete_wizards(wizards);
		delete_spellbooks(spellbooks, num_spellbooks);
		return 0;
	}

	//run the actual user-selection part of the program
	main_menu(spellbooks, num_spellbooks, current_user);

	//cleaning up after the user decides to exit
	delete_wizards(wizards);
	delete_spellbooks(spellbooks, num_spellbooks);

	return 0;

}
