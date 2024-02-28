//
//  main.cpp
//  PhoneBook
//
//  Created by Areş Mutemet on 28.02.2024.
//

#include <iostream>
#include <fstream>
using namespace std;

struct PhoneBook {
    
    // A struct to hold information about a person's contact information
    string name; string number; string birthday;
    
    // Pointer to the next entry in a linked list of PhoneBook entries
    PhoneBook* next = NULL;
    
};

// The number of contacts in the phonebook
int numberOfContacts = 0;

// Pointer to the first entry in the linked list of PhoneBook entries
PhoneBook* contactList = NULL;

// Array of pointers to PhoneBook entries, with each element representing a different letter of the alphabet
PhoneBook* alphabet[26] = {NULL};

// importContactList reads a list of contacts from a file and adds them to a linked list of phone book entries
void importContactList() {
    // open the file containing the list of contacts
    ifstream myFile; myFile.open("Phonebook.txt");
    
    // read the number of contacts in the file
    myFile >> numberOfContacts;
    
    // previous points to the last entry in the linked list of phone book entries // initially, it points to the head of the list (i.e. contactList)
    PhoneBook** previous = &contactList;
    
    // emptyLine is used to read and ignore empty lines in the file
    string emptyLine;
    getline(myFile, emptyLine);
    
    // read the list of contacts from the file and add them to the linked list
    for (int i = 0; i < numberOfContacts; i++)
    {
        // thisContact is the current contact being read from the file
        PhoneBook* thisContact = new PhoneBook;
        
        // read and ignore an empty line in the file
        getline(myFile, emptyLine);
        
        // read the name, number, and birth date of the current contact
        getline(myFile, thisContact -> name);
        getline(myFile, thisContact -> number);
        getline(myFile, thisContact -> birthday);
        
        // set the next pointer of the current contact to NULL
        thisContact -> next = NULL;
        
        // add the current contact to the linked list of phone book entries
        *previous = thisContact;
        previous = &thisContact -> next;
    }
    // close the file
    myFile.close();
}

// addContact allows the user to add a new contact to the phone book, and then saves.
void addContact() {
    // addNew is the new contact being added to the phone book
    PhoneBook* addNew = new PhoneBook;
    
    // read the name, number, and birth date of the new contact from the user
    cout << endl;
    cout << endl << "Contact Name : "; cin.ignore(); getline (cin, addNew -> name);
    cout << endl << "Contact Phone number : "; getline (cin, addNew -> number);
    cout << endl << "Contact Birtday(DD/MM/YYYY) : "; getline (cin, addNew -> birthday);
    
    // convert the name of the new contact to uppercase
    for (int i = 0; i<addNew -> name.length(); i++)
        addNew -> name[i] = toupper(addNew -> name[i]);
    
    // set the next pointer of the new contact to NULL
    addNew->next = NULL;
    
    // add the new contact to the linked list of phone book entries, in alphabetical order
    if(numberOfContacts == 0 || contactList -> name.compare(addNew -> name) > 0) {
        
        // if the list is empty, or if the new contact should be placed at the beginning of the list
        addNew -> next = contactList;
        contactList = addNew;
    }
    else {
        
        // otherwise, find contact's before and after elements in the list
        PhoneBook* before = contactList;
        PhoneBook* after = contactList -> next;
        
        while (after!=NULL) {
            if (addNew -> name.compare(after -> name) < 0) break; before = after;
            after = after -> next;
        }
        before -> next = addNew; addNew -> next = after;
    }
    
    // Increment the number of contacts
    numberOfContacts ++;
    
    // Update the phone book file with the updated list of contacts
    ofstream myFile;
    myFile.open("Phonebook.txt");
    
    myFile << numberOfContacts << endl;
    
    PhoneBook* thisContact = contactList;
    while(thisContact != NULL) {
        myFile << "===================" << endl;
        // write the name, number, and birth date to the text file
        myFile << thisContact -> name << endl;
        myFile << thisContact -> number << endl;
        myFile << thisContact -> birthday << endl;
        thisContact = thisContact -> next;
    }
    
    // close the file
    myFile.close();
    cout << endl << "New contact is saved successfully." << endl;
}

void showContact() {
    // Set a pointer to the head of the linked list representing the phonebook
    PhoneBook* allShow = contactList;
    // Set a flag variable to 0
    int flag = 0;
    // Print a separator line
    cout << "===============================" << endl;
    // Iterate through the linked list
    while (allShow != NULL) {
        // Print the contact's name, phone number, and birthday to the screen
        cout << "Contact Name : " << allShow->name << endl << endl;
        cout << "Contact Number : " << allShow->number << endl << endl;
        cout << "Contact Birthday (DD/MM/YYYY): " << allShow->birthday << endl << endl;
        // Print a separator line
        cout << "===============================" << endl;
        
        // Set the pointer to the next contact in the linked list
        allShow = allShow -> next;
        // Set the flag variable to 1 to indicate that at least one contact was found
        flag = 1;
    }
    
    // Check the value of the flag variable
    if(flag==0)
        // If the flag is still set to 0, this means that no contacts were found // Print a message to the user indicating that no contacts were found
        cout << "NO CONTACTS FOUND!" << endl;
}

// searchContact searches for a contact in the phone book and outputs the name, number, and birth date
void searchContact() {
    
    // input is the name of the contact to search for
    string input;
    cout << "Enter Name: "; cin.ignore(); getline (cin,input); cout << endl;
    // convert input to uppercase
    for (int i = 0; i < input.length(); i++)
        input[i] = toupper(input[i]);
    
    // searched points to the current entry in the linked list of phone book entries
    PhoneBook* searched = contactList;

    // flag indicates whether the contact was found (1) or not (0)
    int flag = 0;
    // search for the contact in the linked list of phone book entries
    while (searched!=NULL)
    {
        // if the contact is found, output its name, number, and birth date
        if (input.compare(searched -> name) == 0) {
            cout << "===============================" << endl;
            cout << "Contact Name: " << searched -> name << endl;
            cout << "Contact Number: " << searched -> number << endl;
            cout << "Contact Birthdate: "<< searched -> birthday << endl;
            cout << "===============================" << endl << endl;
            flag = 1;
            break;
        } else {
            // move to the next entry in the linked list
            searched = searched -> next;
        }
    }
    
    // if the contact was not found, output a message saying so
    if(flag == 0)
        cout << "Contact not found!" << endl;
}

void deleteContact() {
    
    // Prompt user to enter the name of the contact they want to delete
    string input;
    cout << "Enter Name : ";
    // Read the input and ignore any leading whitespace characters
    cin.ignore();
    getline(cin, input);
    // Convert the input string to uppercase
    for (int i = 0; i < input.length(); i++)
        input[i] = toupper(input[i]);
    
    // Search the phone book for the specified contact
    PhoneBook* searched = contactList;
    int flag = 0;
    while (searched!=NULL) {
        // If the contact is found
        if (input.compare(searched -> name) == 0) {
            // Display the contact's name, number, and birthday
            cout << "===============================" << endl;
            cout << "Contact Name : " << searched -> name << endl;
            cout << "Contact Number : " << searched -> number << endl;
            cout << "Contact Birthday(DD/MM/YYYY): " << searched -> birthday << endl;
            cout << "===============================" << endl << endl;
            
            // Delete the contact from the phone book
            if (searched == contactList) {
                // If the contact is at the beginning of the list, update the head of the list
                contactList = contactList -> next; } else {
                    // Otherwise, find the contact's previous element in the list
                    PhoneBook* previous = contactList;
                    while (previous -> next != searched) {
                        previous = previous -> next;
                    }
                    // Update the previous element to point to the contact's next element
                    previous -> next = searched -> next;
                }
            
            // Free the memory occupied by the contact
            delete searched;
            
            // Decrement the number of contacts
            numberOfContacts --;
            
            // Update the phone book file with the updated list of contacts
            ofstream myFile;
            myFile.open("Phonebook.txt");
            myFile << numberOfContacts << endl;
            PhoneBook* thisContact = contactList;
            
            while(thisContact != NULL) {
                // Export the contact's name, phone number, and birthday to the file
                myFile << "===================" << endl;
                myFile << thisContact->name << endl;
                myFile << thisContact->number << endl;
                myFile << thisContact->birthday << endl;
                thisContact = thisContact -> next;
            }
            // close the file
            myFile.close(); flag = 1;
            break;
            
        } else {
            // move to the next entry in the linked list
            searched = searched -> next;
        }
    }
    // if the contact was not found, output a message saying so
    if(flag == 0)
        cout << "Contact not found!" << endl;
    // if the contact was found, output a message saying so
    if(flag == 1)
        cout << "Contact is deleted" << endl;
}

int main() {
    
    // Import the existing contact list
    importContactList();
    
    // Declare a variable to store the user's menu choice
    int state;
    
    // Continuously present the menu and accept user input until the user chooses to exit
    do {
        
        cout << endl;
        cout << "EXIT----------------->0" << endl;
        cout << "ADD CONTACT---------->1" << endl;
        cout << "SHOW CONTACTS-------->2" << endl;
        cout << "SEARCH CONTACT------->3" << endl;
        cout << "DELETE CONTACT------->4" << endl << endl;
        cout << "Enter number : ";
        
        // Call the appropriate function based on the user's menu choice
        cin >> state;
        switch (state) {
            case 1: addContact(); break;
            case 2: showContact(); break;
            case 3: searchContact(); break;
            case 4: deleteContact(); break;
        }
    }
    while (state);
    
        // Return 0 to indicate successful program execution
        return 0;
}
