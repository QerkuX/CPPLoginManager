#include <iostream>
#include <fstream>
#include <cstdio>
using namespace std;

void fileExist(string file){
    ifstream exist(file);
    if (!exist.good()){
        ofstream NewFile("data.txt");
        NewFile.close();
    }
}

int main(){
    fileExist("data.txt");

    ifstream DataFile("data.txt");
    string txt;
    int dataAmmount = 0;
    while (getline (DataFile, txt)) {
        dataAmmount++;
    }
    DataFile.close();
    DataFile.open("data.txt");
    string data[255][2];
    int colCounter = 0;
    dataAmmount = 0;
    while (getline (DataFile, txt)) {
        data[dataAmmount][colCounter] = txt;
        if (colCounter == 0){
            colCounter++;
        }
        else{
            dataAmmount++;
            colCounter = 0;
        }
    }

    DataFile.close();

    int option;
    string username, password;
    bool valid;

    while (true){
        cout << "Hello in my Account Manager" << endl;
        cout << "1.Login\n2.Register" << endl;
        cin >> option;

        switch(option){
            case 1:
                while (true){
                    cout << "Insert your username: ";
                    cin >> username;
                    cout << "Insert your password: ";
                    cin >> password;
                    for (int i = 0; i < dataAmmount+1; i++){
                        if (data[i][0] == username){
                            if (data[i][1] == password){
                                valid = true;
                                break;
                            }
                        }
                    }

                    system("cls");

                    if (!valid){
                        cout << "Your username or password is unvalid\n\n" << endl;
                        continue;
                    }

                    cout << "Successfully logged to: " << username << "\n\n" << endl;
                    string oldUsername = username;
                    while (true){
                        cout << "1.Change username\n2.Delete account" << endl;
                        cin >> option;
                        switch (option){
                            case 1:
                                while (true){
                                    cout << "Insert your new username: ";
                                    cin >> username;

                                    valid = true;

                                    for (int i = 0; i < dataAmmount; i++){
                                        if (data[i][0] == username){
                                            valid = false;
                                            break;
                                        }
                                    }

                                    system("cls");

                                    if (!valid){
                                        cout << "Account with that username already exist\n\n" << endl;
                                        continue;
                                    }

                                    cout << "Successfully changed your username" << endl;
                                    break;
                                }

                                for (int i = 0; i < dataAmmount+1; i++){
                                    if (data[i][0] == oldUsername){
                                        data[i][0] = username;
                                    }
                                }
                                break;
                            case 2:
                                for (int i = 0; i < dataAmmount+1; i++){
                                    if (data[i][0] == username){
                                        data[i][0] = "";
                                        data[i][1] = "";

                                        system("cls");
                                        cout << "Successfully deleted your account" << endl;
                                        break;
                                    }
                                }
                                break;
                            default:
                                system("cls");
                                cout << "This option doesn't exist!\n\n" << endl;
                                continue;
                                break;
                        }

                        break;
                    }
                    break;
                }
                break;
            case 2:
                while (true){
                    cout << "Insert new username: ";
                    cin >> username;
                    cout << "Insert new password: ";
                    cin >> password;

                    valid = true;

                    for (int i = 0; i < dataAmmount; i++){
                        if (data[i][0] == username){
                            valid = false;
                            break;
                        }
                    }

                    system("cls");

                    if (!valid){
                        cout << "Account with that username already exist\n\n" << endl;
                        continue;
                    }

                    data[dataAmmount][0] = username;
                    data[dataAmmount][1] = password;


                    cout << "Account was succesfully created!" << endl;
                    break;

                }
                break;
            default:
                system("cls");
                cout << "This option doesn't exist!\n\n" << endl;
                continue;
                break;
        }
        break;
    }
    remove("data.txt");

    ofstream NewAccount("data.txt");
    for (int i = 0; i < dataAmmount+1; i++){
        NewAccount << data[i][0] << "\n";
        NewAccount << data[i][1] << "\n";
    }

    NewAccount.close();
    return 0;
}
