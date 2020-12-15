/*
    This is just an attempt at figuring out how to read and write from external files
    The goal is to figure out how to create a new file to write to, write to an existing
    file, wipe a file so it's completely blank, to delete a file, to copy a file, to
    encrypt and decrypt a line of text, and to carry over text from one run of a program
    to another

    I will make a class for all IO interactions just to get a feel for it

    I also plan on having a class specifically for encrypting and decrypting my text
*/

#include <iostream>
#include <string>
#include <array>
#include <vector>
#include <fstream>
#include <filesystem>


bool exitProgram(bool _willExit)
{
    // function will return true or false depending on parameter received
    bool willExit = _willExit;
    return willExit;
}

bool checkExit(std::string _usrInput)
{
    // will check to see what user input was used as a parameter
    // the program will exit depending on the output
    bool closeProgram = false;
    std::string usrInput = _usrInput;

    if (usrInput == "Exit" || usrInput == "exit" || usrInput == "EXIT")
    {
        // will close the program
        closeProgram = true;
        return exitProgram(closeProgram);
    }
    else if (usrInput == "Yes" || usrInput == "yes" || usrInput == "YES")
    {
        // will close the program
        closeProgram = true;
        return exitProgram(closeProgram);
    }
    else if (usrInput == "No" || usrInput == "no" || usrInput == "NO")
    {
        // program remains open
        closeProgram = false;
        return exitProgram(closeProgram);
    }
    
}

std::string chooseFile()
{
    std::string usrFile;
    //std::cout << "Please enter a file name: ";
    std::cin >> usrFile;
    return usrFile;
}

std::string inputText()
{
    // gets input from the user
    // this is mostly used to determine file names and the action the user
    // wants to perform
    std::string usrText;
    std::cin.ignore();
    std::getline(std::cin, usrText);
    return usrText;
}

// this funtion will create a new file to write to
std::string newFile(std::string _fileName)
{
    std::string fileName = _fileName;
    //std::string inputText = _inputText;

    std::ofstream os(fileName);
    //if (os.is_open()) {
    //    os << inputText << std::endl;
    //}
    os.close();
    return "Success";
}

// this function will read a file
std::string readFile(std::string _fileName)
{
    std::string fileName = _fileName;

    // checks to see if fileName opens successfully
    // if open() is successful, it will print the contents out into the terminal
    std::ifstream f(fileName);
    if (f.is_open())
        std::cout << f.rdbuf();
    return "Success";
}

// this function will append text to the end of the file
std::string appendFile(std::string _fileName, std::string _inputText)
{
    std::string inputText = _inputText;
    std::string fileName = _fileName;

    // assigns fstream and ifstream to variables to be used later in the function
    std::fstream f;
    std::ifstream is;

    // opens fileName in append mode, if the file is open, adds the text to the
    // bottom of the file
    std::ofstream os(fileName, std::ios::app);
    if (os.is_open()) {
        os << inputText << std::endl;
    }
    os.close();

    std::string output = inputText + " : has been added to the end of the file";

    return output;
}

// this will delete a file and all its contents
std::string deleteFile(std::string _fileName)
{
    std::string fileName = _fileName;
    std::string willDelete;

    // prompts the user with a warning to verify that they wish to attempt to delete
    // the selected file
    std::cout << "WARNING: Are you sure you wish to delete the file?" << std::endl
        << "This is a permanent action. Do you wish to delete? " << std::endl
        << "Please choose 'Yes' or 'No': ";
    std::cin >> willDelete;

    if (willDelete == "Yes" || willDelete == "yes" || willDelete == "YES")
    {
        if (remove(fileName.c_str()) != 0)
            perror("Error deleting file");
        else
            puts("File successfully deleted");
    }
    else
    {
        std::cout << "File not deleted" << std::endl;
    }
    
    return "";
}

// this will open a file in the desired location
std::string openFile(std::string _fileName)
{
    std::string fileName = _fileName;
    std::fstream iofs(fileName);
    return "";
}

// this will make a new copy of the file
std::string copyFile(std::string _fileName, std::string _copiedFile)
{
    std::string sourceFileName = _fileName;
    std::string copiedFileName = _copiedFile;
    std::filesystem::copy_file(sourceFileName, copiedFileName);
    return " ";
}

// this will wipe the entire file by deleting it, then recreating it as a blank file
std::string wipeFile(std::string _fileName)
{
    std::string fileName = _fileName;
    std::string willWipe;

    std::cout << "WARNING: This will permenantly wipe all the contents of the file"
        << std::endl << "Are you sure you wish to proceed?" << std::endl <<
        "Please choose 'Yes' or 'No': ";
    std::cin >> willWipe;

    if (willWipe == "Yes" || willWipe == "yes" || willWipe == "YES")
    {
        std::ofstream os(fileName);

        // opens up the file, and replaces the text with an empty string
        if (os.is_open()) {
            os << "";
        }
        os.close();
        return "File successfully wiped";
    }
    else
    {
        return "No file wiped.";
    }
}

std::string userAction()
{
    // holds a string designating what option the user wishes to take
    std::string usrChoice;

    std::cout << "What action would you like to perform?" << std::endl;
    std::cout << "'New' file" << std::endl << "'Read' file" << std::endl
        << "'Write' file" << std::endl << "'Delete' file" << std::endl
        << "'Copy' file" << std::endl << "'Wipe' file" << std::endl
        << "'Exit' program" << std::endl;

    std::cin >> usrChoice;
    std::cout << std::endl;
    
    // if-else statements that determines what action gets called
    if (usrChoice == "New" || usrChoice == "new" || usrChoice == "READ")
    {
        std::string addText;

        std::cout << "Please enter a file name: ";
        std::string chosenFile = chooseFile();
        
        std::cout << "Would you like to add text to the file? ";
        std::cin >> addText;
        if (addText == "Yes" || addText == "yes" || addText == "YES")
        {
            std::cout << "Please enter the text you want to input: " << std::endl;
            std::string usrText = inputText();
            return appendFile(chosenFile, usrText);
            
        }
        else if (addText == "No" || addText == "no" || addText == "NO")
        {
            return newFile(chosenFile);
        }
        else
        {
            std::cout << "Invalid input. No text added" << std::endl;
        }
        
    }
    else if (usrChoice == "Read" || usrChoice == "read" || usrChoice == "READ")
    {
        std::cout << "Please enter a file name: ";
        std::string chosenFile = chooseFile();
        std::cout << std::endl;
        return readFile(chosenFile);
    }
    else if (usrChoice == "Write" || usrChoice == "write" || usrChoice == "WRITE")
    {
        std::cout << "Please enter a file name: ";
        std::string chosenFile = chooseFile();

        std::cout << "Please enter the text you want to input: " << std::endl;
        std::string usrText = inputText();

        return appendFile(chosenFile, usrText);
    }
    else if (usrChoice == "Delete" || usrChoice == "delete" || usrChoice == "DELETE")
    {
        std::cout << "Please enter a file name: ";
        std::string chosenFile = chooseFile();
        std::cout << std::endl;
        return deleteFile(chosenFile);
    }
    else if (usrChoice == "Open" || usrChoice == "open" || usrChoice == "OPEN")
    {
        std::cout << "Please enter a file name: ";
        std::string chosenFile = chooseFile();
        return openFile(chosenFile);
    }
    else if (usrChoice == "Copy" || usrChoice == "copy" || usrChoice == "COPY")
    {
        std::cout << "Choose original file: ";
        std::string chosenFile = chooseFile();
        std::cout << std::endl;

        std::cout << "Choose copied file name: ";
        std::string newFile = chooseFile();
        std::cout << std::endl;

        return copyFile(chosenFile, newFile);
    }
    else if (usrChoice == "Wipe" || usrChoice == "wipe" || usrChoice == "WIPE")
    {
        std::cout << "Please enter a file name: ";
        std::string chosenFile = chooseFile();

        return wipeFile(chosenFile);
    }
    else if (usrChoice == "Exit" || usrChoice == "exit" || usrChoice == "EXIT")
    {
        std::cout << "Exiting program" << std::endl;
        exitProgram(true);
        return "EXIT";
    }
    else
    {
        std::cout << "Invalid output. Please select a valid option: " << std::endl;
        std::cout << std::endl;
        return userAction();
    }
    
    return "";
}

int main()
{
    std::string contProgram;
    bool contProgBool;

    do
    {

        bool willExit = checkExit(userAction());
        std::cout << std::endl;

        if (willExit == true)
        {
            contProgBool = false;
            break;
        }
        else if (willExit != true)
        {
            std::cout << "Would you like to select another action?" << std::endl;
            std::cout << "'Yes' or 'No'? ";
            std::cin >> contProgram;

            if (contProgram == "Yes" || contProgram == "yes" || contProgram == "YES")
            {
                exitProgram(true);
                contProgBool = true;
                std::cout << std::endl;
            }
            else if (contProgram == "No" || contProgram == "no" || contProgram == "YES")
            {
                std::cout << "Exiting program" << std::endl;
                exitProgram(false);
                contProgBool = false;
                break;
            }
            else
            {
                std::cout << "Invalid input. Exiting program";
                exitProgram(false);
                contProgBool = false;
                break;
            }
        }
        

    } while (contProgBool != false);

}





