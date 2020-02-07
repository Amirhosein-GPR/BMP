/*
-----------------------------------------------------------------
A word from developer :
Hi how are you my friend :D I know it's
not typical to speak like this so i apoligise (:
This program took me a long time to develope. I really don't know
exactly but i'm pretty sure that i spent hours & hours on it.
I also wanted to say that i didn't use any database like sql and
wrote a simple specific algorithm to write & read & search in
files. I mean the algorithm to work with files not something like
fstream header file :D

Well now it's finished !
So i hope you enjoy this program. yours faithfully, Amirhosein.
-----------------------------------------------------------------
A word from developer to the master assistant :D :
I gained a lot of expireince from this & the other university
project. I really apreciate you for it. I also asks you to note
that some of the students are new to coding & making algorithm &
projects. So PLESAE IF it isn't wrong take it easy with them.
THANK YOU :D
-----------------------------------------------------------------
Weclome to the source code of BMP (The Bank Manager Program)
-----------------------------------------------------------------
Version : 0.9.0
-----------------------------------------------------------------
Status : Beta
-----------------------------------------------------------------
Target platform : Gnu/Linux (I think it'll work on windows too)
-----------------------------------------------------------------
This program is coded & developed by : Amirhosein_GPR
-----------------------------------------------------------------
Telegram ID : Amirhosein_GPR
-----------------------------------------------------------------
*/
#include <iostream>
#include <fstream>
#include <string.h>
#include <time.h>

using namespace std;

void welcome(bool);
int identify();
void ceoDesk(bool = 1);
void empDesk(bool = 1);
void cliDesk(bool = 1, char * = NULL);
void empInfo();
void cliInfo();
void transInfo();
void totalBalance();
void clientBalance();
void searchBy(int);
void printSearch(ifstream &, int = 0, char * = NULL, bool = 1);
void addRemoveEmp();
void addEmp(fstream &);
void removeEmp(fstream &, char *);
void searchInTransaction();
void backToMenu(int, char * = NULL);
void printReport(ifstream &, int * = NULL);
void printLine(char *);
void withdrawDeposit(bool);
void loan();
void transfer();
void addRemoveCli();
void addCli(fstream &);
void removeCli(fstream &, char *);
void Credit(char *);
void cliTransactions(char *);
void buyCharge(char *);

int foundIndex[100];

//Our program starts right down here :D

int main(){
    int key = 0;
    bool retry = false;
    do{
        welcome(retry);
        key = identify();
        switch(key){
            case -1:
                cout << "Can't open the file!";
            break;
            case 0:
                retry = true;
                continue;
            break;
            case 1:
                ceoDesk();
            break;
            case 2:
                empDesk();
            break;
            default:
                string str = to_string(key);
                char *chKey = new char[11];
                strcpy(chKey , str.c_str());
                cliDesk(1, chKey);
            break;
        }
    }while (!key);
}

//This function prints a welcome and login page.

void welcome(bool retry){
    std::system("clear");
    time_t t = time(NULL);
    if (retry)
        cout << "Your username or password or both of them are incorrect!\n\nGoing back to login page.....\n\n--------------------------------------------------------\n\nPlease tell me you want to login as :\n\n1) CEO\n2) Employee\n3) Client\n\nwhich one ? (Enter only the number!) : ";
    else
        cout << "Welcome to BMP! (The Bank Manager Program) ^^^ Gnu/Linux edition! ^^^\n\nCurrent time : "<< ctime(&t) <<"\nFirst please tell me you want to login as :\n\n\n1) CEO\n\n2) Employee\n\n3) Client\n\n\nwhich one ? (Enter only the number!) : ";
}

int i;
int flag = 0;

//This function checks whether user has entered the right username and password or not.

int identify(){
    int user;
    bool wrong = 0;
    do{
        if (wrong)
            cout << "Please enter a number from 1 to 3 : ";
        cin >> user;
        wrong = 1;
    }while (user < 1 || user > 3);
    char *adrs;
    int returnValue;
    switch (user){
        case 1:
            adrs = (char *) "./data/user/ceo.bat";
            returnValue = 1;
        break;
        case 2:
            adrs = (char *) "./data/user/emp.bat";
            returnValue = 2;
        break;
        case 3:
            adrs = (char *) "./data/user/cli.bat";
            returnValue = 3;
        break;
        default :
            cout << "\nError! (You entered a wrong number/character! only numbers from 1 to 3 are allowed)\n\n";
            exit(0);
    }
    std::system("clear");
    char *accountNumber = new char[11];
    cout << "Excellent! now please enter your account number & password (From 3 to 30 characters are allowed for each one!) \n\nAccount number : ";
    wrong = 0;
    do{
        if (wrong)
            cout << "\nThe length of the account number you've entered is out of range (Only from 3 to 10 characters are allowed)\n\nAccount number : ";
        cin >> accountNumber;
        for (i=0; accountNumber[i]; i++);
        wrong = 1;
    }while(i< 3 || i > 30);
    char *password = new char[31];
    cout << "\nPassword : ";
    wrong = 0;
    do{
        if (wrong)
            cout << "\nThe length of the password you've entered is out of range (Only from 3 to 30 characters are allowed)\n\nPassword : ";
        cin >> password;
        for (i=0; password[i]; i++);
        wrong = 1;
    }while(i< 3 || i > 30);
    ifstream read(adrs);
    if (!read){
        cout << "\nError! (couldn't open the file)\n";
        return -1;
    }
    char *accountNumber2 = new char [11];
    char *password2 = new char [31];
    i = 0;
    int i2 = 0;
    char ch;
    while (!read.eof()){
        read.get(ch);
        if (ch != '|'){
            if (flag)
                password2[i++] = ch;
            else if (ch != '/')
                accountNumber2[i2++] = ch;
            else
                flag = 1;
        }else{
            flag = 0;
            accountNumber2[i2] = '\0';
            password2[i] = '\0';
            i = 0;
            if (!strcmp(accountNumber, accountNumber2))
                if (!strcmp(password, password2)){
                    flag = 1;
                    break;
                }
        }
    }
    read.close();
    delete [] password;
    delete [] accountNumber2;
    if (returnValue != 2)
        delete [] password2;
    if (!flag)
        return 0;
    std::system("clear");
    if (user == 3)
        returnValue = atoi(accountNumber);
    delete [] accountNumber;
    return returnValue;
}

//This function prints saved texts in the program files with a specific algorithm.

void printReport(ifstream &read, int * foundParts){
    i = 0;
    flag = 0;
    int num = 20;
    int fpi = 0;
    char ch;
    while (!read.eof()){
        read.get(ch);
        if (ch != '|'){
            if (ch != '/'){
                cout << ch;
                i++;
            }else{
                if (flag == 4){
                    num = 33;
                }
                else
                    num = 20;
                for (int j=0; j<num-i; j++)
                    cout << " ";
                i = 0;
                flag++;
                continue;
            }
        }else{
            i = 0;
            flag = 0;
            cout << "\n";
        }
    }
}

//This function gets a string and if the function finds it in the that file we've given to it, then it prints saved texts that file with a specific algorithm.

void printSearch(ifstream &read, int pos, char *needle, bool print){
    char ch;
    int round = 1;
    int part = 1;
    char *file = new char[20];
    int i = 0;
    int indexArray[100];
    indexArray[0] = -1;
    foundIndex[0] = -1;
    int index = 0;
    while (!read.eof()){
        read.get(ch);
        if (ch != '|'){
            if (ch != '/'){
                if (part == pos)
                    file[i++] = ch;
            }else{
                if (part == pos)
                    file[i] = '\0';
                part++;
            }
        }else{
            if (part == pos)
                file[i] = '\0';
            if (!read.eof()){
                indexArray[round-1] = read.tellg();
                if (!strcmp(needle, file)){
                    if (round != 1){
                        foundIndex[index] = indexArray[round - 2];
                    }else{
                        foundIndex[index] = 0;
                    }
                    index++;
                    foundIndex[index] = -1;
                }
                i = 0;
                part = 1;
                round++;
            }
        }
    }
    delete [] file;
    read.clear();
    if (print){
        i = 0;
        flag = 0;
        int num = 20;
        int fii = 0;
        bool first = true;
        while (true){
            if (first)
                if (foundIndex[fii] != -1){
                    read.seekg(foundIndex[fii++]);
                    first = false;
                }else{
                    break;
                }
            read.get(ch);
            if (ch != '|'){
                if (ch != '/'){
                    cout << ch;
                    i++;
                }else{
                    if (flag == 4){
                        num = 33;
                    }
                    else
                        num = 20;
                    for (int j=0; j<num-i; j++)
                        cout << " ";
                    i = 0;
                    flag++;
                    continue;
                }
            }else{
                i = 0;
                flag = 0;
                cout << "\n";
                if (foundIndex[fii] != -1){
                    read.seekg(foundIndex[fii++]);
                }else{
                    break;
                }
            }
        }
    }
}

//This function prints a graphical rectangle with a string which we've given it to the function.

void printLine(const char *str){
    for (int i=0; i<54; i++)
        cout << '-';
    cout << '\n';
    cout << '|';
    int k;
    for (k=0; k<52; k++)
        cout << " ";
    cout << '|';
    cout << '\n';
    int j;
    for (j=0; str[j]; j++);
    int num = ((54 - j) / 2) - 1;
    for (k=0; k<num; k++){
        if (k == 0)
            cout << '|';
        else
            cout << '-';
    }
    cout << str;
    for (k=num; k<54 - j; k++){
        if (k == 54-j -1)
            cout << '|';
        else
            cout << '-';
    }
    cout << '\n';
    cout << '|';
    for (k=0; k<52; k++)
        cout << " ";
    cout << '|';
    cout << '\n';
    for (int i=0; i<54; i++)
        cout << '-';
    cout << "\n\n";
}

//This function prints the CEO Desktop :D

void ceoDesk(bool first){
    if (first){
        cout << "You've successfully logged in as a 'CEO'!\n\n";
        for (int i=0; i<37; i++)
            cout << '*';
        cout << "\n\n";
    }
    cout << "Please choose a number from the following list : \n\n";
    printLine("See & Report");
    cout << "1) Employees info \t 2) Clients info \t 3) Transactions \n\n4) Total bank balance \t 5) Clients' balance\n\n";
    printLine("Search");
    cout << "6) Employees' info \t 7) Transactions\n\n";
    printLine("Add or Remove");
    cout << "8) Employees\n\n";
    cout << "Enter number : ";
    int num;
    cin >> num;
    switch (num){
        case 1:
            empInfo();
        break;
        case 2:
            cliInfo();
        break;
        case 3:
            transInfo();
        break;
        case 4:
            totalBalance();
        break;
        case 5:
            clientBalance();
        break;
        case 6:
            std::system("clear");
            cout << "Search by :\n\n1) Account number\t\t2) Personl code\n\nEnter number : ";
            {
                bool repeat = 0;
                do{
                    if (repeat)
                        cout << "\nWrong number! Please enter a number from 1 to 2 : ";
                    cin >> num;
                    repeat = 1;
                }while(num < 1 || num > 2);
            }
            searchBy(num);
        break;
        case 7:
            searchInTransaction();
        break;
        case 8:
            addRemoveEmp();
        break;
    }
}

//This function prints the Employee Desktop :D

void empDesk(bool first){
    if (first){
        cout << "You've successfully logged in as an 'Employee'!\n\n";
        for (int i=0; i<37; i++)
            cout << '*';
        cout << "\n\n";
    }
    cout << "Please choose a number from the following list : \n\n";
    printLine("Account operations");
    cout << "1) Widthdraw \t 2) Deposit \t 3) Loan\n\n4) Transfer\n\n";
    printLine("Search");
    cout << "5) Clients' info\n\n";
    printLine("Add or Remove");
    cout << "6) Client\n\n";
    cout << "Enter number : ";
    int num;
    cin >> num;
    switch (num){
        case 1:
            withdrawDeposit(1);
        break;
        case 2:
            withdrawDeposit(0);
        break;
        case 3:
            loan();
        break;
        case 4:
            transfer();
        break;
        case 5:
            std::system("clear");
            cout << "Search by :\n\n1) Account number\t\t2) National code\n\nEnter number : ";
            {
                bool repeat = 0;
                do{
                    if (repeat)
                        cout << "\nWrong number! Please enter a number from 1 to 2 : ";
                    cin >> num;
                    repeat = 1;
                }while(num < 1 || num > 2);
            }
            if (num == 1)
                num = 3;
            else
                num = 4;
            searchBy(num);
        break;
        case 6:
            addRemoveCli();
        break;
    }
}

//This function prints the Client Desktop :D

void cliDesk(bool first, char *accountNumber){
    if (first){
        cout << "You've successfully logged in as an 'client'!\n\n";
        for (int i=0; i<37; i++)
            cout << '*';
        cout << "\n\n";
    }
    cout << "Please choose a number from the following list : \n\n";
    printLine("See & Report");
    cout << "1) Credit \t 2) Client's transactions\n\n";
    printLine("Operations");
    cout << "3)Buy charge (For SIM Card)\n\n";
    cout << "Enter number : ";
    int num;
    cin >> num;
    switch (num){
        case 1:
            Credit(accountNumber);
        break;
        case 2:
            cliTransactions(accountNumber);
        break;
        case 3:
            buyCharge(accountNumber);
        break;
    }
}

//This function prints the employee's info.

void empInfo(){
    std::system("clear");
    ifstream read("./data/report/emp/emp-info.bat");
    if (!read){
        cout << "\nError! (couldn't open the file)\n";
        exit(0);
    }
    printLine("Employees");
    cout << "First name\t    Last name\t\tAccount number\t    Personal code\n\n";
    printReport(read);
    read.close();
    backToMenu(0);
}

//This function prints the Client's info.

void cliInfo(){
    std::system("clear");
    ifstream read("./data/report/cli/cli-info.bat");
    if (!read){
        cout << "\nError! (couldn't open the file)\n";
        exit(0);
    }
    printLine("Clients");
    cout << "First name\t    Last name\t\tAccount number\t    National code\tAddress\t\t\t\t Phone number\t     Email\t         Birth date\n\n";
    printReport(read);
    read.close();
    backToMenu(0);
}

//This function prints the transactions info.

void transInfo(){
    std::system("clear");
    ifstream read("./data/report/bank/transaction.bat");
    if (!read){
        cout << "\nError! (couldn't open the file)\n";
        exit(0);
    }
    printLine("Transactions");
    cout << "From\t\t    To\t\t\tAmount (Toman)\t    Date\n\n";
    printReport(read);
    backToMenu(0);
}

//This function prints total balance of the bank.

void totalBalance(){
    std::system("clear");
    printLine("Total bank balance");
    cout << "Amount (Toman)\n\n";
    ifstream read("./data/credit/cli-credit.bat");
    if (!read){
        cout << "\nError! (couldn't open the file)\n";
        exit(0);
    }
    char ch;
    int part = 1;
    i = 0;
    int sum = 0;
    char *credit = new char[20];
    while(!read.eof()){
        read.get(ch);
        if (ch != '|'){
            if (ch != '/'){
                if (part == 4){
                    credit[i] = ch;
                    i++;
                }
            }else{
                part++;
            }
        }else{
            credit[i] = '\0';
            sum += atoi(credit);
            i = 0;
            part = 1;
        }
    }
    cout << sum;
    backToMenu(0);
}

//This function prints clients' balance.

void clientBalance(){
    std::system("clear");
    ifstream read("./data/credit/cli-credit.bat");
    if (!read){
        cout << "\nError! (couldn't open the file)\n";
        exit(0);
    }
    printLine("Clients' balance");
    cout << "Name\t\t    Last name\t\tAccount number\t    Balance (Toman)\n\n";
    printReport(read);
    backToMenu(0);
}

/*
This function prints employees or clients info.(function's paramter is important.
The function algorithm depends on its parameter).
*/

void searchBy(int num){
    std::system("clear");
    ifstream read;
    char *needle = new char[20];
    int pos;
    int menu;
    const char *title = new char[120];
    switch (num){
        case 1:
            pos = 3;
            menu = 0;
            title = "First name\t    Last name\t\tAcoount number\t    Personal code\n\n";
            read.open("./data/report/emp/emp-info.bat");
            printLine("Search in employees' info (Acoount number)");
            cout << "Please enter account number : ";
            cin >> needle;
        break;
        case 2:
            pos = 4;
            menu = 0;
            title = "First name\t    Last name\t\tAcoount number\t    Personal code\n\n";
            read.open("./data/report/emp/emp-info.bat");
            printLine("Search in employees' info (Personal code)");
            cout << "Please enter personal code : ";
            cin >> needle;
        break;
        case 3:
            pos = 3;
            menu = 1;
            title = "First name\t    Last name\t\tAccount number\t    National number\tAddress\t\t\t\t Phone number\t     Email\t         Birth date\n\n";
            read.open("./data/report/cli/cli-info.bat");
            printLine("Search in clients' info (Acoount number)");
            cout << "Please enter Account number : ";
            cin >> needle;
        break;
        case 4:
            pos = 4;
            menu = 1;
            title = "First name\t    Last name\t\tAccount number\t    National number\tAddress\t\t\t\t Phone number\t     Email\t         Birth date\n\n";
            read.open("./data/report/cli/cli-info.bat");
            printLine("Search in clients' info (National code)");
            cout << "Please enter Account number : ";
            cin >> needle;
        break;
    }
    cout << '\n';
    if (!read){
        cout << "\nError! (couldn't open the file)\n";
        exit(0);
    }
    cout << title;
    printSearch(read, pos, needle);
    if (foundIndex[0] != -1)
        cout << "\nFound !";
    else
        cout << "\nNothing found !";
    delete [] needle;
    //delete [] title; ??? I don't know why but if i delete this pointer the programs will get some issue :D ???
    backToMenu(menu);
}

//This function decides to remove or to add an employee.

void addRemoveEmp(){
    std::system("clear");
    ifstream ifs("./data/report/emp/emp-info.bat");
    if (!ifs){
        cout << "\nError! (couldn't open the file)\n";
        exit(0);
    }
    printLine("Add or Remove : Employee");
    cout<< "Please enter employees' account number : ";
    char *needle = new char[20];
    cin >> needle;
    cout << "\nFirst name\t    Last name\t\tAccount number\t    Personal code\n\n";
    printSearch(ifs, 3, needle);
    ifs.close();
    fstream io("./data/report/emp/emp-info.bat", ios::in | ios::out);
    if (!io){
        cout << "\nError! (couldn't open the file)\n";
        exit(0);
    }
    if (foundIndex[0] == -1){
        for (int i=0; i<74; i++)
            cout << "-";
        cout << "\n\nNothing was found.\n\nDo you want to add this employee ? (Y/N) : ";
    }else{
        cout << '\n';
        for (int i=0; i<74; i++)
            cout << "-";
        cout << "\n\nEmployee was found successfully !\n\nDo you want to remove this employee ? (Y/N) : ";
    }
    char ch;
    cin >> ch;
    switch (ch){
        case 'Y':
        case 'y':
            std::system("clear");
            if (foundIndex[0] == -1)
                addEmp(io);
            else{
                removeEmp(io, needle);
                delete [] needle;
            }
        break;
        case 'N':
        case 'n':
            exit(0);
        break;
    }
}

//This function adds an employee and saves his or her info in 2 files.

void addEmp(fstream &io){
    char *str = new char[30];
    int turn = 0;
    io.seekp(0,io.end);
    char *firstName = new char[20];
    char *lastName = new char[20];
    char *accountNumber = new char[9];
    char *personalCode = new char[20];
    cin.ignore(1, '\n');
    while (true){
        switch (turn){
            case 0:
                cout << "OK ! Now please enter employee's info\n\n1 - First name : ";
            break;
            case 1:
                cout << "\n2 - Last name : ";
            break;
            case 2:
                cout << "\n3 - Account number : ";
            break;
            case 3:
                cout << "\n4 - Personal code : ";
            break;
        }
        turn++;
        cin.getline(str, 50);
        io.write(str, strlen(str));
        if (turn == 1){
            i = 0;
            while (str[i]){
                firstName[i] = str[i];
                i++;
            }
            firstName[i] = '\0';
        }
        if (turn == 2){
            i = 0;
            while (str[i]){
                lastName[i] = str[i];
                i++;
            }
            lastName[i] = '\0';
        }
        if (turn == 3){
            i = 0;
            while (str[i]){
                accountNumber[i] = str[i];
                i++;
            }
            accountNumber[i] = '\0';
        }
        if (turn == 4){
            i = 0;
            while (str[i]){
                personalCode[i] = str[i];
                i++;
            }
            personalCode[i] = '\0';
            io.put('|');
            break;
        }else
            io.put('/');
    }
    io.close();
    //-----
    io.open("./data/user/emp.bat");
    if (!io){
        cout << "\nError! (couldn't open the file)\n";
        exit(0);
    }
    io.seekp(0, io.end);
    io.write(firstName, strlen(firstName));
    io.flush();
    io.put('/');
    io.write(lastName, strlen(lastName));
    io.flush();
    io.put('/');
    io.write(accountNumber, strlen(accountNumber));
    io.flush();
    io.put('/');
    io.write(personalCode, strlen(personalCode));
    io.flush();
    io.put('|');
    io.close();
    delete [] firstName;
    delete [] lastName;
    delete [] accountNumber;
    delete [] personalCode;
    delete [] str;
    cout << "\nEmployee was added successfully !";
    backToMenu(0);
}

//This function removes an employee and deletes his or her info in 2 files.

void removeEmp(fstream &io, char *needle){
    char ch;
    int fii = 0;
    int p;
    char *copyStr = new char[500];
    int c = 0;
    while (!io.eof()){
        io.get(ch);
        if (foundIndex[fii] + 1 != io.tellg() && io.tellg() != -1){
            copyStr[c++] = ch;
        }else{
            io.get(ch);
            while(ch != '|'){
                io.get(ch);
            }
            fii++;
        }
    }
    copyStr[c] = '\0';
    io.close();
    ofstream ofs("./data/report/emp/emp-info.bat", ios::trunc);
    ofs.write(copyStr, strlen(copyStr));
    ofs.close();
    //-----
    ifstream ifs("./data/user/emp.bat");
    if (!ifs){
        cout << "\nError! (couldn't open the file)\n";
        exit(0);
    }
    cout << "\nFirst name\t    Last name\t\tPersonal code\n\n";
    printSearch(ifs, 1, needle);
    fii = 0;
    c = 0;
    while (!ifs.eof()){
        ifs.get(ch);
        if (foundIndex[fii] + 1 != ifs.tellg() && ifs.tellg() != -1){
            copyStr[c++] = ch;
        }else{
            ifs.get(ch);
            while(ch != '|'){
                ifs.get(ch);
            }
            fii++;
        }
    }
    copyStr[c] = '\0';
    ifs.close();
    ofs.open("./data/user/emp.bat", ios::trunc);
    ofs.write(copyStr, strlen(copyStr));
    ofs.close();
    cout << "\nEmployee was removed successfully !";
    backToMenu(0);
}

/*
This function searches in transactions file by account number and 
will print related information IF it finds the same account number in it (the file).
*/

void searchInTransaction(){
    std::system("clear");
    char *needle = new char[20];
    ifstream read("./data/report/bank/transaction.bat");
    printLine("Search in transactions");
    cout << "Please enter account number : ";
    cin >> needle;
    cout << '\n';
    if (!read){
        cout << "\nError! (couldn't open the file)\n";
        exit(0);
    }
    cout << "From\t\t    To\t\t\tAmount (Toman)\t    Date\n\n";
    printSearch(read, 1, needle);
    read.seekg(read.beg);
    for (i=0; i<84; i++)
        cout << '-';
    cout << "\n\n";
    printSearch(read, 2, needle);
    if (foundIndex[0] != -1)
        cout << "\nFound !";
    else
        cout << "\nNothing found !";
    delete [] needle;
    backToMenu(0);
}

/*
This function prints a back to menu message and asks the user to enter "Y" or "N" character.
If the user enters Y the function calls the menu function and
if the user enters N the function exits the program.
*/

void backToMenu(int menu, char *cliAN){
    cout << "\n\nBack to main menu ? (Y/N) : ";
    char ch;
    cin >> ch;
    switch (ch){
        case 'Y':
        case 'y':
            std::system("clear");
            switch (menu){
                case 0:
                    ceoDesk(0);
                break;
                case 1:
                    empDesk(0);
                break;
                case 2:
                if (cliAN != NULL)
                    cliDesk(0, cliAN);
                else
                    cout << "Error ! (check backToMenu function!)";
                break;
            }
        break;
        case 'N':
        case 'n':
            exit(0);
        break;
    }
}

/*
This function searches for the client and if it the function finds it,
the function decides to withdraw some credits from it or deposit some to it.
(it does some more things too like printing... . But i'm bored to write them :D).
*/

void withdrawDeposit(bool isWithdraw){
    std::system("clear");
    if (isWithdraw)
        printLine("Withdraw");
    else
        printLine("Deposit");
    cout << "Please enter clients' Account number : ";
    char *needle = new char[20];
    cin >> needle;
    ifstream read("./data/credit/cli-credit.bat");
    cout << "\nFirst name\t    Last name\t\tAccount number\t    Credit (Toman)\n\n";
    printSearch(read, 3, needle);
    if (foundIndex[0] == -1){
        cout << "\nNothing found!";
        backToMenu(1);
        exit(0);
    }else{
        cout << "\nClient was found successfully!\n\n";
    }
    ifstream ifs("./data/credit/cli-credit.bat");
    if (!ifs){
        cout << "\nError! (couldn't open the file)\n";
        exit(0);
    }
    char ch;
    int fii = 0;
    char *copyStr = new char[500];
    char *removed = new char[80];
    int c = 0;
    int c2 = 0;
    int part = 1;
    i = 0;
    char *creditMoney = new char[12];
    while (!ifs.eof()){
        ifs.get(ch);
        if (foundIndex[fii] + 1 != ifs.tellg() && ifs.tellg() != -1){
            copyStr[c++] = ch;
        }else{
            while (ch != '|'){
                if (part != 4){
                    removed[c2++] = ch;
                }else{
                    creditMoney[i++] = ch;
                }
                if (ch == '/')
                    part++;
                ifs.get(ch);
            }
            fii++;
        }
    }
    ifs.close();
    creditMoney[i] = '\0';
    if (isWithdraw)
        cout << "Please enter the amount of money for withdrawing : ";
    else
        cout << "Please enter the amount of money for depositing : ";
    char *inputMoney = new char[12];
    cin >> inputMoney;
    i = 0;
    int im = atoi(inputMoney);
    int cm = atoi(creditMoney);
    if (isWithdraw)
        cm -= im;
    else
        cm += im;
    if (isWithdraw)
        if (cm < 10000){
            cout << "\nError ! Client's credit reaches under 10000";
            backToMenu(1);
            exit(0);
        }
    string str = to_string(cm);
    strcpy(creditMoney, str.c_str());
    while (creditMoney[i]){
        removed[c2++] = creditMoney[i++];
    }
    removed[c2++] = '|';
    removed[c2] = '\0';
    c2 = 0;
    while (removed[c2]){
        copyStr[c++] = removed[c2++];
    }
    copyStr[c] = '\0';
    ofstream ofs("./data/credit/cli-credit.bat", ios::trunc);
    ofs.write(copyStr, strlen(copyStr));
    ofs.close();
    if (isWithdraw)
        cout << "\nWithdraw was done successfully!\n\nRemaining credit is : \"" << creditMoney << "\" Toman";
    else
        cout << "\nDeposit was done successfully!\n\nRemaining credit is : \"" << creditMoney << "\" Toman";
    backToMenu(1);
}

// This function does the loan proccess (For clients).

void loan(){
    std::system("clear");
    printLine("Loan");
    cout << "Please enter clients' Account number : ";
    char *needle = new char[20];
    cin >> needle;
    ifstream ifs("./data/credit/cli-credit.bat");
    cout << "\nFirst name\t    Last name\t\tAccount number\t    Credit (Toman)\n\n";
    printSearch(ifs, 3, needle);
    ifs.close();
    int *ic = new int;
    *ic = foundIndex[0];
    ifs.open("./data/credit/cli-loan.bat");
    cout << "\nFirst name\t    Last name\t\tAccount number\t    Loan (Toman)\n\n";
    printSearch(ifs, 3, needle);
    int *il = new int;
    *il = foundIndex[0];
    foundIndex[0] = *ic;
    ifs.close();
    if (foundIndex[0] == -1){
        cout << "\nNothing found!";
        backToMenu(1);
        exit(0);
    }else{
        cout << "\nClient was found successfully!\n\n";
    }
    ifs.open("./data/credit/cli-credit.bat");
    if (!ifs){
        cout << "\nError! (couldn't open the file)\n";
        exit(0);
    }
    char ch;
    int fii = 0;
    int c2 = 0;
    int part = 1;
    i = 0;
    char *creditMoney = new char[12];
    while (!ifs.eof()){
        ifs.get(ch);
        if (foundIndex[fii] + 1 == ifs.tellg() || ifs.tellg() == -1){
            while (ch != '|'){
            if (part == 4)
                creditMoney[i++] = ch;
                if (ch == '/')
                    part++;
                ifs.get(ch);
            }
            fii++;
        }
    }
    creditMoney[i] = '\0';
    ifs.close();

    foundIndex[0] = *il;
    delete il;
    ifs.open("./data/credit/cli-loan.bat");    
    int cm = atoi(creditMoney);
    cm /= 2;
    int bankRate = 0.15 * cm;
    int totalPay = bankRate + cm;
    int installment = totalPay / 12;

    cout << "= = = 1 year (12 months) = = =";
    cout << "\n\n----- Loan (50% of credit) is : " << cm << " Toman -----";
    cout << "\n\n- - - Bank rate is : " << bankRate << " Toman - - -";
    cout << "\n\n----- Total pay is : " << totalPay << " Toman -----";
    cout << "\n\n- - - Installment for every month is : " << installment << " Toman - - -";

    cout << "\n\nAre you sure ? (Y/N) : ";
    cin >> ch;
    switch (ch){
        case 'Y':
        case 'y':{
            int fii = 0;
            char *copyStr = new char[500];
            char *removed = new char[80];
            int c = 0;
            int c2 = 0;
            int part = 1;
            i = 0;
            char *loanMoney = new char[12];
            while (!ifs.eof()){
                ifs.get(ch);
                if (foundIndex[fii] + 1 != ifs.tellg() && ifs.tellg() != -1){
                    copyStr[c++] = ch;
                }else{
                    while (ch != '|'){
                        if (part != 4){
                            removed[c2++] = ch;
                        }
                        if (ch == '/')
                            part++;
                        ifs.get(ch);
                    }
                    fii++;
                }
            }
            ifs.close();
            i = 0;
            string str = to_string(totalPay);
            strcpy(loanMoney, str.c_str());
            while (loanMoney[i]){
                removed[c2++] = loanMoney[i++];
            }
            removed[c2++] = '|';
            removed[c2] = '\0';
            c2 = 0;
            while (removed[c2]){
                copyStr[c++] = removed[c2++];
            }
            copyStr[c] = '\0';
            ofstream ofs("./data/credit/cli-loan.bat", ios::trunc);
            ofs.write(copyStr, strlen(copyStr));
            ofs.close();
            cout << "\nLoan was given successfully!\n\nCurrent client's loan is : \"" << loanMoney << "\"";
            //------
            foundIndex[0] = *ic;
            delete ic;
            ifs.open("./data/credit/cli-credit.bat");
            fii = 0;
            c = 0;
            c2 = 0;
            part = 1;
            i = 0;
            while (!ifs.eof()){
                ifs.get(ch);
                if (foundIndex[fii] + 1 != ifs.tellg() && ifs.tellg() != -1){
                    copyStr[c++] = ch;
                }else{
                    while (ch != '|'){
                        if (part != 4){
                            removed[c2++] = ch;
                        }else{
                            loanMoney[i++] = ch;
                        }
                        if (ch == '/')
                            part++;
                        ifs.get(ch);
                    }
                    fii++;
                }
            }
            ifs.close();
            loanMoney[i] = '\0';
            int lm = atoi(loanMoney);
            lm += cm;
            i = 0;
            str = to_string(lm);
            strcpy(loanMoney, str.c_str());
            while (loanMoney[i]){
                removed[c2++] = loanMoney[i++];
            }
            removed[c2++] = '|';
            removed[c2] = '\0';
            c2 = 0;
            while (removed[c2]){
                copyStr[c++] = removed[c2++];
            }
            copyStr[c] = '\0';
            ofs.open("./data/credit/cli-credit.bat", ios::trunc);
            ofs.write(copyStr, strlen(copyStr));
            ofs.close();
            backToMenu(1);
        }
        break;
        case 'N':
        case 'n':
            backToMenu(1);
        break;
    }
}

// This function decides to call the addCli function or the removeCli function.

void addRemoveCli(){
    std::system("clear");
    ifstream ifs("./data/report/cli/cli-info.bat");
    if (!ifs){
        cout << "\nError! (couldn't open the file)\n";
        exit(0);
    }
    printLine("Add or Remove : Client");
    cout<< "Please enter clients' Account number : ";
    char *needle = new char[20];
    cin >> needle;
    cout << "\nFirst name\t    Last name\t\tAccount number\t    National number\tAddress\t\t\t\t Phone number\t     Email\t         Birth date\n\n";
    printSearch(ifs, 3, needle);
    ifs.close();
    fstream io("./data/report/cli/cli-info.bat", ios::in | ios::out);
    if (!io){
        cout << "\nError! (couldn't open the file)\n";
        exit(0);
    }
    if (foundIndex[0] == -1){
        for (int i=0; i<74; i++)
            cout << "-";
        cout << "\n\nNothing was found.\n\nDo you want to add this client ? (Y/N) : ";
    }else{
        cout << '\n';
        for (int i=0; i<74; i++)
            cout << "-";
        cout << "\n\nClient was found successfully !\n\nDo you want to remove this client ? (Y/N) : ";
    }
    char ch;
    cin >> ch;
    switch (ch){
        case 'Y':
        case 'y':
            std::system("clear");
            if (foundIndex[0] == -1)
                addCli(io);
            else{
                cout << '\n';
                for (int i=0; i<74; i++)
                cout << "-";
                cout << "\n\nClient was found successfully !\n\nDo you want to remove this client ? (Y/N) : ";
                removeCli(io, needle);
            }
        break;
        case 'N':
        case 'n':
            backToMenu(1);
            exit(0);
        break;
    }
}

// This function adds a new client and saves his or her information to the realted file.

void addCli(fstream &io){
    std::system("clear");
    printLine("Add client");
    char *str = new char[51];
    int turn = 0;
    io.seekp(0,io.end);
    char *firstName = new char[20];
    char *lastName = new char[20];
    char *accountNumber = new char[9];
    cin.ignore(1, '\n');
    while (true){
        switch (turn){
            case 0:
                cout << "OK ! Now please enter client's info\n\n1 - First name : ";
            break;
            case 1:
                cout << "\n2 - Last name : ";
            break;
            case 2:
                cout << "\n3 - Account number : ";
            break;
            case 3:
                cout << "\n4 - National code : ";
            break;
            case 4:
                cout << "\n5 - Address : ";
            break;
            case 5:
                cout << "\n6 - Phone number : ";
            break;
            case 6:
                cout << "\n7 - Email : ";
            break;
            case 7:
                cout << "\n8 - Birth date : ";
            break;
        }
        turn++;
        cin.getline(str, 50);
        io.write(str, strlen(str));
        if (turn == 1){
            i = 0;
            while (str[i]){
                firstName[i] = str[i];
                i++;
            }
            firstName[i] = '\0';
        }
        if (turn == 2){
            i = 0;
            while (str[i]){
                lastName[i] = str[i];
                i++;
            }
            lastName[i] = '\0';
        }
        if (turn == 3){
            i = 0;
            while (str[i]){
                accountNumber[i] = str[i];
                i++;
            }
            accountNumber[i] = '\0';
        }
        if (turn == 8){
            io.put('|');
            break;
        }else
            io.put('/');
    }
    io.close();
    io.open("./data/user/cli.bat");
    if (!io){
        cout << "\nError! (couldn't open the file)\n";
        exit(0);
    }
    io.seekp(0, io.end);
    io.write(accountNumber, strlen(accountNumber));
    io.flush();
    io.put('/');
    io.flush();
    cout << "\n\nExceleent ! Now please enter your password : ";
    cin >> str;
    io.write(str, strlen(str));
    delete [] str;
    io.flush();
    io.put('|');
    io.flush();
    io.close();
    //-----
    io.open("./data/credit/cli-credit.bat");
    if (!io){
        cout << "\nError! (couldn't open the file)\n";
        exit(0);
    }
    io.seekp(0, io.end);
    io.write(firstName, strlen(firstName));
    io.flush();
    io.put('/');
    io.write(lastName, strlen(lastName));
    io.flush();
    io.put('/');
    io.write(accountNumber, strlen(accountNumber));
    io.flush();
    io.put('/');
    io.write("10000", 5);
    io.flush();
    io.put('|');
    io.flush();
    io.close();
    //-----
    io.open("./data/credit/cli-loan.bat");
    if (!io){
        cout << "\nError! (couldn't open the file)\n";
        exit(0);
    }
    io.seekp(0, io.end);
    io.write(firstName, strlen(firstName));
    io.flush();
    io.put('/');
    io.write(lastName, strlen(lastName));
    io.flush();
    io.put('/');
    io.write(accountNumber, strlen(accountNumber));
    io.flush();
    io.put('/');
    io.write("0", 1);
    io.flush();
    io.put('|');
    io.flush();
    io.close();
    delete [] firstName;
    delete [] lastName;
    delete [] accountNumber;
    cout << "\nClient was added successfully !";
    backToMenu(1);
}

// This function removes a new client and deletes his or her information from the realted file.

void removeCli(fstream &io, char *needle){
    char ch;
    int fii = 0;
    int p;
    char *copyStr = new char[500];
    int c = 0;
    while (!io.eof()){
        io.get(ch);
        if (foundIndex[fii] + 1 != io.tellg() && io.tellg() != -1){
            copyStr[c++] = ch;
        }else{
            io.get(ch);
            while(ch != '|'){
                io.get(ch);
            }
            fii++;
        }
    }
    copyStr[c] = '\0';
    io.close();
    ofstream ofs("./data/report/cli/cli-info.bat", ios::trunc);
    ofs.write(copyStr, strlen(copyStr));
    ofs.close();
    //------
    ifstream ifs("./data/user/cli.bat");
    printSearch(ifs, 1, needle);
    fii = 0;
    c = 0;
    while (!ifs.eof()){
        ifs.get(ch);
        if (foundIndex[fii] + 1 != ifs.tellg() && ifs.tellg() != -1){
            copyStr[c++] = ch;
        }else{
            ifs.get(ch);
            while(ch != '|'){
                ifs.get(ch);
            }
            fii++;
        }
    }
    copyStr[c] = '\0';
    ifs.close();
    ofs.open("./data/user/cli.bat", ios::trunc);
    ofs.write(copyStr, strlen(copyStr));
    ofs.close();
    //-----
    ifs.open("./data/credit/cli-credit.bat");
    printSearch(ifs, 3, needle);
    fii = 0;
    c = 0;
    while (!ifs.eof()){
        ifs.get(ch);
        if (foundIndex[fii] + 1 != ifs.tellg() && ifs.tellg() != -1){
            copyStr[c++] = ch;
        }else{
            ifs.get(ch);
            while(ch != '|'){
                ifs.get(ch);
            }
            fii++;
        }
    }
    copyStr[c] = '\0';
    ifs.close();
    ofs.open("./data/credit/cli-credit.bat", ios::trunc);
    ofs.write(copyStr, strlen(copyStr));
    ofs.close();
    //-----
    ifs.open("./data/credit/cli-loan.bat");
    printSearch(ifs, 3, needle);
    delete [] needle;
    fii = 0;
    c = 0;
    while (!ifs.eof()){
        ifs.get(ch);
        if (foundIndex[fii] + 1 != ifs.tellg() && ifs.tellg() != -1){
            copyStr[c++] = ch;
        }else{
            ifs.get(ch);
            while(ch != '|'){
                ifs.get(ch);
            }
            fii++;
        }
    }
    copyStr[c] = '\0';
    ifs.close();
    ofs.open("./data/credit/cli-loan.bat", ios::trunc);
    ofs.write(copyStr, strlen(copyStr));
    ofs.close();
    std::system("clear");
    printLine("Client removed");
    cout << "Client was removed successfully !";
    backToMenu(1);
}

// This function do the money transfer proccess.

void transfer(){
    std::system("clear");
    printLine("Transfer");
    cout << "Please enter client's account number:\n\n1 - Withdraw from : ";
    char *accountNumber1 = new char[10];
    cin >> accountNumber1;
    cout << "\n2 - Deposit to : ";
    char *accountNumber2 = new char[10];
    cin >> accountNumber2;
    //-----
    ifstream ifs("./data/credit/cli-credit.bat");
    if (!ifs){
        cout << "\nError! (couldn't open the file)\n";
        exit(0);
    }
    cout << '\n';
    printLine("Withdraws from");
    cout << "\nFirst name\t    Last name\t\tAccount number\t    Credit (Toman)\n\n";
    printSearch(ifs, 3, accountNumber1);
    cout << "\n";
    if (foundIndex[0] == -1){
        cout << "No credits were found with acoount number : " << accountNumber1 << " (Withdraw from)";
        delete [] accountNumber1;
        delete [] accountNumber2;
        backToMenu(1);
        exit(0);
    }
    int partition1 = foundIndex[0];
    ifs.seekg(ifs.beg);
    printLine("Deposit to");
    cout << "\nFirst name\t    Last name\t\tAccount number\t    Credit (Toman)\n\n";
    printSearch(ifs, 3, accountNumber2);
    if (foundIndex[0] == -1){
        cout << "No credits were found with acoount number : " << accountNumber2 << " (Deposit to)";
        delete [] accountNumber1;
        delete [] accountNumber2;
        backToMenu(1);
        exit(0);
    }
    ifs.seekg(ifs.beg);
    char ch;
    int fii = 0;
    char *copyStr = new char[500];
    char *removed = new char[80];
    int c = 0;
    int c2 = 0;
    int part = 1;
    i = 0;
    char *creditMoney = new char[12];
    while (!ifs.eof()){
        ifs.get(ch);
        if (partition1 + 1 != ifs.tellg() && ifs.tellg() != -1){
            copyStr[c++] = ch;
        }else{
            while (ch != '|'){
                if (part != 4){
                    removed[c2++] = ch;
                }else{
                    creditMoney[i++] = ch;
                }
                if (ch == '/')
                    part++;
                ifs.get(ch);
            }
            fii++;
        }
    }
    ifs.close();
    creditMoney[i] = '\0';
    cout << '\n';
    for (i=0; i<84; i++)
        cout << '-';
    cout << '\n';
    cout << "\nPlease enter the amount of money you want to transfer : ";
    char *inputMoney = new char[12];
    cin >> inputMoney;
    i = 0;
    int im = atoi(inputMoney);
    int cm = atoi(creditMoney);
    cm -= im;
    if (cm < 10000){
        cout << "\nError ! Client's credit reaches under 10000";
        backToMenu(1);
        exit(0);
    }
    string str = to_string(cm);
    strcpy(creditMoney, str.c_str());
    while (creditMoney[i]){
        removed[c2++] = creditMoney[i++];
    }
    removed[c2++] = '|';
    removed[c2] = '\0';
    c2 = 0;
    while (removed[c2]){
        copyStr[c++] = removed[c2++];
    }
    copyStr[c] = '\0';
    ofstream ofs("./data/credit/cli-credit.bat", ios::trunc);
    ofs.write(copyStr, strlen(copyStr));
    ofs.close();
    ifs.close();
    //-----
    ifs.open("./data/credit/cli-credit.bat");
    printSearch(ifs, 3, accountNumber2, 0);
    if (foundIndex[0] == -1){
        cout << "No credits were found with acoount number : " << accountNumber2 << " (Deposit to)";
        delete [] accountNumber1;
        delete [] accountNumber2;
        backToMenu(1);
        exit(0);
    }
    ifs.seekg(ifs.beg);
    fii = 0;
    c = 0;
    c2 = 0;
    part = 1;
    i = 0;
    while (!ifs.eof()){
        ifs.get(ch);
        if (foundIndex[i] + 1 != ifs.tellg() && ifs.tellg() != -1){
            copyStr[c++] = ch;
        }else{
            while (ch != '|'){
                if (part != 4){
                    removed[c2++] = ch;
                }else{
                    creditMoney[i++] = ch;
                }
                if (ch == '/')
                    part++;
                ifs.get(ch);
            }
            fii++;
        }
    }
    ifs.close();
    creditMoney[i] = '\0';
    i = 0;
    im = atoi(inputMoney);
    cm = atoi(creditMoney);
    cm += im;
    str = to_string(cm);
    strcpy(creditMoney, str.c_str());
    while (creditMoney[i]){
        removed[c2++] = creditMoney[i++];
    }
    removed[c2++] = '|';
    removed[c2] = '\0';
    c2 = 0;
    while (removed[c2]){
        copyStr[c++] = removed[c2++];
    }
    copyStr[c] = '\0';
    ofs.open("./data/credit/cli-credit.bat", ios::trunc);
    ofs.write(copyStr, strlen(copyStr));
    ofs.close();
    delete [] copyStr;
    delete [] removed;
    delete [] creditMoney;
    //-----
    ofs.open("./data/report/bank/transaction.bat", ios::app);
    ofs.flush();
    ofs.write(accountNumber1, strlen(accountNumber1));
    ofs.put('/');
    ofs.flush();
    ofs.write(accountNumber2, strlen(accountNumber2));
    ofs.put('/');
    ofs.flush();
    ofs.write(inputMoney, strlen(inputMoney));
    ofs.put('/');
    ofs.flush();
    time_t t = time(NULL);
    ofs.write(ctime(&t), strlen(ctime(&t)));
    ofs.put('|');
    ofs.flush();
    delete [] inputMoney;
    cout << "\nTransfer was done successfully !\n\n";
    for (i=0; i<84; i++)
        cout << '-';
    cout << '\n';
    ifs.open("./data/credit/cli-credit.bat");
    if (!ifs){
        cout << "\n\nError! (couldn't open the file)\n";
        exit(0);
    }
    printLine("Withdrawed from");
    cout << "\nFirst name\t    Last name\t\tAccount number\t    Credit (Toman)\n\n";
    printSearch(ifs, 3, accountNumber1);
    cout << '\n';
    ifs.seekg(ifs.beg);
    printLine("Deposited to");
    cout << "\nFirst name\t    Last name\t\tAccount number\t    Credit (Toman)\n\n";
    printSearch(ifs, 3, accountNumber2);
    ifs.close();
    delete [] accountNumber1;
    delete [] accountNumber2;
    backToMenu(1);
}

// This function prints the client's credit (For the user who is entered as a client).

void Credit(char *accountNumber){
    std::system("clear");
    printLine("Credit");
    ifstream ifs("./data/credit/cli-credit.bat");
    if (!ifs){
        cout << "\nError! (couldn't open the file)\n";
        exit(0);
    }
    cout << "\nFirst name\t    Last name\t\tAccount number\t    Credit (Toman)\n\n";
    printSearch(ifs, 3, accountNumber);
    backToMenu(2, accountNumber);
    delete [] accountNumber;
}

// This function prints the client's transcations (For the user who is entered as a client).

void cliTransactions(char *accountNumber){
    std::system("clear");
    printLine("Client's transactions");
    i = 0;
    cout << "Warning ! This operation costs 100 Toman. Do you want to continue ?\n\n1 - It's none of your buisiness ! :D (Yes)\n\n2 - No\n\nEnter only the number : ";
    cin >> i;
    if (i != 1){
        backToMenu(2, accountNumber);
        exit(0);
    }
    ifstream ifs("./data/credit/cli-credit.bat");
    if (!ifs){
        cout << "\nError! (couldn't open the file)\n";
        exit(0);
    }
    printSearch(ifs, 3, accountNumber, 0);
    ifs.close();
    ifs.open("./data/credit/cli-credit.bat");
    if (!ifs){
        cout << "\nError! (couldn't open the file)\n";
        exit(0);
    }
    char ch;
    int fii = 0;
    char *copyStr = new char[500];
    char *removed = new char[80];
    int c = 0;
    int c2 = 0;
    int part = 1;
    i = 0;
    char *creditMoney = new char[12];
    while (!ifs.eof()){
        ifs.get(ch);
        if (foundIndex[fii] + 1 != ifs.tellg() && ifs.tellg() != -1){
            copyStr[c++] = ch;
        }else{
            while (ch != '|'){
                if (part != 4){
                    removed[c2++] = ch;
                }else{
                    creditMoney[i++] = ch;
                }
                if (ch == '/')
                    part++;
                ifs.get(ch);
            }
            fii++;
        }
    }
    ifs.close();
    creditMoney[i] = '\0';
    i = 0;
    int cm = atoi(creditMoney);
    cm -= 100;
    if (cm < 10000){
        cout << "\nError ! Client's credit reaches under 10000";
        backToMenu(1);
        exit(0);
    }
    string str = to_string(cm);
    strcpy(creditMoney, str.c_str());
    while (creditMoney[i]){
        removed[c2++] = creditMoney[i++];
    }
    removed[c2++] = '|';
    removed[c2] = '\0';
    c2 = 0;
    while (removed[c2]){
        copyStr[c++] = removed[c2++];
    }
    copyStr[c] = '\0';
    ofstream ofs("./data/credit/cli-credit.bat", ios::trunc);
    ofs.write(copyStr, strlen(copyStr));
    ofs.close();
    //-----
    ifs.open("./data/report/bank/transaction.bat");
    if (!ifs){
        cout << "\nError! (couldn't open the file)\n";
        exit(0);
    }
    cout << "\nFrom\t\t    To\t\t\ttransfered (Toman)  Date\n\n";
    printSearch(ifs, 1, accountNumber);
    for (i=0; i<84; i++)
        cout << '-';
    cout << "\n\n";
    ifs.seekg(ifs.beg);
    printSearch(ifs, 2, accountNumber);
    if (foundIndex[0] != -1)
        cout << "\nFound ! (:\n\n";
    else
        cout << "\nNothing found ! ):\n\n";
    backToMenu(2, accountNumber);
    delete [] accountNumber;
}

// This function do the proccess of buying and printing a charge code. (For the user who is entered as a client).

void buyCharge(char *accountNumber){
    std::system("clear");
    printLine("Buy charge");
    cout << "\n\nWhich operator do you want to buy charge from ? :\n\n1 - Hamrahe aval\n\n2 - Irancell\n\n3 - Rightel\n\nEnter only the number : ";
    int opr;
    bool access = false;
    while (true){
        cin >> opr;
        switch (opr){
            case 1:
            case 2:
            case 3:
                access = true;
            break;
            default :
                std::system("clear");
                cout << "You entered a wrong number !\n\n1 - Hamrahe aval\n\n2 - Irancell\n\n3 - Rightel\n\nEnter the number again ! : ";
        }
        if (access)
            break;
    }
    std::system("clear");
    printLine("Buy charge");
    const char *charge = new char[16];
    cout << "OK ! (: Now please choose one of the following amounts :\n\n1 - 2000\t2 - 5000\n\n3 - 10000\t4 - 20000\n\nEnter only the number : ";
    int amount;
    while (true){
        cin >> amount;
        switch (amount){
            case 1:
                charge = "2000";
            break;
            case 2:
                charge = "5000";
            break;
            case 3:
                charge = "10000";
            break;
            case 4:
                charge = "20000";
            break;
            default :
                std::system("clear");
                cout << "\nYou entered a wrong number !\n\n1 - 2000\t2 - 5000\n\n3 - 10000\t4 - 20000\n\nEnter the number again ! : ";
                charge = NULL;
        }
        if (charge != NULL)
            break;
    }
    //-----
    ifstream ifs("./data/credit/cli-credit.bat");
    if (!ifs){
        cout << "\nError! (couldn't open the file)\n";
        exit(0);
    }
    printSearch(ifs, 3, accountNumber, 0);
    ifs.close();
    ifs.open("./data/credit/cli-credit.bat");
    if (!ifs){
        cout << "\nError! (couldn't open the file)\n";
        exit(0);
    }
    char ch;
    int fii = 0;
    char *copyStr = new char[500];
    char *removed = new char[80];
    int c = 0;
    int c2 = 0;
    int part = 1;
    i = 0;
    char *creditMoney = new char[12];
    while (!ifs.eof()){
        ifs.get(ch);
        if (foundIndex[fii] + 1 != ifs.tellg() && ifs.tellg() != -1){
            copyStr[c++] = ch;
        }else{
            while (ch != '|'){
                if (part != 4){
                    removed[c2++] = ch;
                }else{
                    creditMoney[i++] = ch;
                }
                if (ch == '/')
                    part++;
                ifs.get(ch);
            }
            fii++;
        }
    }
    ifs.close();
    creditMoney[i] = '\0';
    i = 0;
    int im = atoi(charge);
    int cm = atoi(creditMoney);
    cm -= im;
    if (cm < 10000){
        cout << "\nError ! Client's credit reaches under 10000";
        backToMenu(1);
        exit(0);
    }
    string str = to_string(cm);
    strcpy(creditMoney, str.c_str());
    while (creditMoney[i]){
        removed[c2++] = creditMoney[i++];
    }
    removed[c2++] = '|';
    removed[c2] = '\0';
    c2 = 0;
    while (removed[c2]){
        copyStr[c++] = removed[c2++];
    }
    copyStr[c] = '\0';
    ofstream ofs("./data/credit/cli-credit.bat", ios::trunc);
    ofs.write(copyStr, strlen(copyStr));
    ofs.close();

    switch (opr){
            case 1:
                charge = "115";
            break;
            case 2:
                charge = "337";
            break;
            case 3:
                charge = "885";
            break;
    }
    int randNum;
    cout << "\nCharge code was successfully purchased !\n\nCODE : \"" << charge;
    for (i=0; i<9; i++){
        srand(i);
        randNum = rand() % 10;
        cout << randNum;
    }
    cout << "\"";
    backToMenu(2, accountNumber);
}