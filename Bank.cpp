#include <iostream>
#include <fstream>
#include <string.h>
#include <time.h>

using namespace std;

void welcome(bool);
int identify();
void ceoDesk(bool = 1);
void empInfo();
void cliInfo();
void transInfo();
void totalBalance();
void clientBalance();
void searchBy(int);
void printSearch(ifstream &, int = 0, char * = NULL);
void addRemoveEmp();
void addEmp(fstream &);
void removeEmp(fstream &);
void searchInTransaction();
void empDesk(bool = 1);
void cliDesk(bool = 1);
void backToMenu(int);
void printReport(ifstream &, int * = NULL);
void printLine(char *);


int foundIndex[100];

int main(){
    int key = 0;
    bool retry = false;
    do{
        welcome(retry);
        key = identify();
        switch(key){
            case 0:
                retry = true;
                continue;
            break;
            case 1:
                ceoDesk();
                break;
            break;
            case 2:
                empDesk();
                break;
            break;
            case 3:
                cliDesk();
                break;
            break;
            default :
                cout << "Can't open the file! aaaaaaa";
        }
    }while (!key);
}

void welcome(bool retry){
    std::system("clear");
    time_t t = time(NULL);
    if (retry)
        cout << "Your username or password or both of them are incorrect!\n\nGoing back to login page.....\n\n--------------------------------------------------------\n\nPlease tell me you want to login as :\n\n1) CEO\n2) Employee\n3) Client\n\nwhich one ? (Enter only the number!) : ";
    else
        cout << "Welcome to BMA! (The Bank Manager App) ^^^ Gnu/Linux edition! ^^^\n\nCurrent time : "<< ctime(&t) <<"\nFirst please tell me you want to login as :\n\n1) CEO\n2) Employee\n3) Client\n\nwhich one ? (Enter only the number!) : ";
}

int i;
int flag = 0;

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
            adrs = (char *) "/home/amirhosein/Documents/Dev/c++/Bank/data/user/ceo.bat";
            returnValue = 1;
        break;
        case 2:
            adrs = (char *) "/home/amirhosein/Documents/Dev/c++/Bank/data/user/emp.bat";
            returnValue = 2;
        break;
        case 3:
            adrs = (char *) "/home/amirhosein/Documents/Dev/c++/Bank/data/user/cli.bat";
            returnValue = 3;
        break;
        default :
            cout << "\nError! (You entered a wrong number/character! only numbers from 1 to 3 are allowed)\n\n";
            exit(0);
    }
    std::system("clear");
    char *username = new char[31];
    cout << "Excellent! now please enter your username & password (From 3 to 30 characters are allowed for each one!) \n\nUsername : ";
    wrong = 0;
    do{
        if (wrong)
            cout << "\nThe length of the username you've entered is out of range (Only from 3 to 30 characters are allowed)\n\nUsername : ";
        cin >> username;
        for (i=0; username[i]; i++);
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
    char *username2 = new char [31];
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
                username2[i2++] = ch;
            else
                flag = 1;
        }else{
            flag = 0;
            username2[i2] = '\0';
            password2[i] = '\0';
            i = 0;
            if (!strcmp(username, username2))
                if (!strcmp(password, password2)){
                    flag = 1;
                    break;
                }
        }
    }
    read.close();
    delete [] username;
    delete [] password;
    delete [] username2;
    delete [] password2;
    if (!flag)
        return 0;
    std::system("clear");
    return returnValue;
}

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

void printSearch(ifstream &read, int pos, char *needle){
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

void ceoDesk(bool first){
    if (first){
        cout << "You've successfully logged in as CEO!\n\n";
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
            cout << "Search by :\n\n1) Personl code\t\t2) Account number\n\nEnter number : ";
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

void empInfo(){
    std::system("clear");
    ifstream read("/home/amirhosein/Documents/Dev/c++/Bank/data/report/emp/emp-info.bat");
    if (!read){
        cout << "\nError! (couldn't open the file)\n";
        exit(0);
    }
    printLine("Employees");
    cout << "First name\t    Last name\t\tPersonal code\t    Account number\n\n";
    printReport(read);
    read.close();
    backToMenu(0);
}

void cliInfo(){
    std::system("clear");
    ifstream read("/home/amirhosein/Documents/Dev/c++/Bank/data/report/cli/cli-info.bat");
    if (!read){
        cout << "\nError! (couldn't open the file)\n";
        exit(0);
    }
    printLine("Clients");
    cout << "First name\t    Last name\t\tAccount number\t    National number\tAddress\t\t\t\t Phone number\t     Email\t         Birth date\n\n";
    printReport(read);
    read.close();
    backToMenu(0);
}

void transInfo(){
    std::system("clear");
    ifstream read("/home/amirhosein/Documents/Dev/c++/Bank/data/report/bank/transaction.bat");
    if (!read){
        cout << "\nError! (couldn't open the file)\n";
        exit(0);
    }
    printLine("Transactions");
    cout << "From\t\t    To\t\t\tAmount (Toman)\t    Transaction number\tDate\n\n";
    printReport(read);
    backToMenu(0);
}

void totalBalance(){
    std::system("clear");
    ifstream read("/home/amirhosein/Documents/Dev/c++/Bank/data/report/bank/balance.bat");
    if (!read){
        cout << "\nError! (couldn't open the file)\n";
        exit(0);
    }
    printLine("Total bank balance");
    cout << "Amount (Toman)\n\n";
    printReport(read);
    backToMenu(0);
}

void clientBalance(){
    std::system("clear");
    ifstream read("/home/amirhosein/Documents/Dev/c++/Bank/data/credit/cli-credit.bat");
    if (!read){
        cout << "\nError! (couldn't open the file)\n";
        exit(0);
    }
    printLine("Clients' balance");
    cout << "Name\t\t    Last name\t\tAccount number\t    Balance (Toman)\n\n";
    printReport(read);
    backToMenu(0);
}

void searchBy(int num){
    std::system("clear");
    ifstream read;
    char *needle = new char[20];
    int pos;
    switch (num){
        case 1:
            pos = 3;
            read.open("/home/amirhosein/Documents/Dev/c++/Bank/data/report/emp/emp-info.bat");
            printLine("Search in employees' info (Personal code)");
            cout << "Please enter personal code : ";
            cin >> needle;
        break;
        case 2:
            pos = 4;
            read.open("/home/amirhosein/Documents/Dev/c++/Bank/data/report/emp/emp-info.bat");
            printLine("Search in employees' info (Acoount number)");
            cout << "Please enter Account number : ";
            cin >> needle;
        break;
    }
    cout << '\n';
    if (!read){
        cout << "\nError! (couldn't open the file)\n";
        exit(0);
    }
    cout << "First name\t    Last name\t\tPersonal code\t    Account number\n\n";
    printSearch(read, pos, needle);
    delete [] needle;
    backToMenu(0);
}

void addRemoveEmp(){
    std::system("clear");
    ifstream ifs("/home/amirhosein/Documents/Dev/c++/Bank/data/report/emp/emp-info.bat");
    if (!ifs){
        cout << "\nError! (couldn't open the file)\n";
        exit(0);
    }
    printLine("Add or Remove : Employee");
    cout<< "Please enter employees' personal code : ";
    char *needle = new char[20];
    cin >> needle;
    cout << "\nFirst name\t    Last name\t\tPersonal code\t    Account number\n\n";
    printSearch(ifs, 3, needle);
    delete [] needle;
    ifs.close();
    fstream io("/home/amirhosein/Documents/Dev/c++/Bank/data/report/emp/emp-info.bat", ios::in | ios::out);
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
            else
                removeEmp(io);
        break;
        case 'N':
        case 'n':
            exit(0);
        break;
    }
}

void addEmp(fstream &io){
    char *str = new char[30];
    int turn = 0;
    io.seekp(0,io.end);
    while (true){
        switch (turn){
            case 0:
                cout << "OK ! Now please enter employee's info\n\n1 - First name : ";
            break;
            case 1:
                cout << "\n2 - Last name : ";
            break;
            case 2:
                cout << "\n3 - Personal code : ";
            break;
            case 3:
                cout << "\n4 - Account number : ";
            break;
        }
        turn++;
        cin >> str;
        io.write(str, strlen(str));
        if (turn == 4){
            io.put('|');
            break;
        }else
            io.put('/');
    }
    delete [] str;
    io.close();
    cout << "\nEmployee was added successfully !";
    backToMenu(0);
}

void removeEmp(fstream &io){
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
    ofstream ofs("/home/amirhosein/Documents/Dev/c++/Bank/data/report/emp/emp-info.bat", ios::trunc);
    ofs.write(copyStr, strlen(copyStr));
    ofs.close();
    cout << "Employee was removed successfully !";
    backToMenu(0);
}

void searchInTransaction(){
    std::system("clear");
    int pos = 4;
    char *needle = new char[20];
    ifstream read("/home/amirhosein/Documents/Dev/c++/Bank/data/report/bank/transaction.bat");
    printLine("Search in transactions");
    cout << "Please enter transaction number : ";
    cin >> needle;
    cout << '\n';
    if (!read){
        cout << "\nError! (couldn't open the file)\n";
        exit(0);
    }
    cout << "From\t\t    To\t\t\tAmount (Toman)\t    Transaction number\tDate\n\n";
    printSearch(read, pos, needle);
    delete [] needle;
    backToMenu(0);
}

void empDesk(bool again){

}

void cliDesk(bool again){
    
}

void backToMenu(int menu){
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
                    cliDesk(0);
                break;
            }
        break;
        case 'N':
        case 'n':
            exit(0);
        break;
    }
}