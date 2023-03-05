#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e5 + 5;

ifstream read_user("Database/users.txt");

struct Date {
    int day;
    int month;
    int year;
};

struct Location {
    string country;
    string city;
};

struct User {

    string name;
    string surname;
    string username;
    string email;
    Date birthday;
    Location location;
    string password;

};

struct Database {
    vector<User> users;
};

Date date_transform(string value) {
    Date result;
    result = {0, 0, 0};
    int pos1 = -1, pos2 = -1;
    for(int i=0; i < value.size(); ++i) {
        if(value[i] =='.' &&pos1==-1){
            pos1=i;
            continue;
        }
        if(value[i]=='.'&&pos1!=-1){
            pos2=i;
            break;
        }
    }
    for(int i=0; i<pos1; i++){
        result.day = result.day * 10 + (value[i] - '0');
    }
    for(int i=pos1+1; i<pos2; i++){
        result.month= result.month*10+(value[i]-'0');
    }
    for(int i=pos2+1; i<value.size(); i++){
        result.year= result.year*10+(value[i]-'0');
    }

    return result;
}

Location location_transform(string value) {
    Location result;
    result = {"", ""};
    int pos=-1;
    for(int i=0; i<value.size(); i++){
        if(value[i]==','){
            pos=i;
            break;
        }
    }

    for(int i=0; i<pos; i++){
        result.country += value[i];
    }

    for(int i=pos+2; i<value.size(); i++){
        result.city+=value[i];
    }
    

    return result;
}

void read_users(Database &database) {
    int nr_users;
    read_user >> nr_users;
    for (int i = 1; i <= nr_users; ++i) {
        User user;
        read_user >> user.name >> user.surname >> user.username >> user.email;
        string date;
        read_user >> date;
        user.birthday = date_transform(date);
        string location;
        getline(read_user, location);
        getline(read_user, location);
        user.location = location_transform(location);
        read_user >> user.password;
        database.users.push_back(user);
    }
}

void read_database(Database &database) {
    read_users(database);
}

bool check_login(Database database, string username, string password){
    for (auto user : database.users) {
        if ((user.username == username || (user.email == username)) && user.password == password) {
            return true;
        }
    }
    return false;
}

User get_user(Database database, string username, string password) {
    User found_user;
    for (auto user : database.users) {
        if ((user.username == username || (user.email == username)) && user.password == password) {
            found_user = user;
            return found_user;
        }
    }
    return found_user;
}

void user_login(Database &database, User user) {







    exit(0);
}

void user_register(Database &database) {
    User user;

    cout<<"\nPlease enter your name: ";
    cin>>user.name;
    cout <<"\nPlease enter your surname: ";
    cin >> user.surname;
    cout<<"\nPlease enter your email: ";
    cin>>user.email;
    cout<<"\nPlease enter your username: ";
    cin>>user.username;
    cout<<"\nPlease enter your password: ";
    cin>>user.password;
    cout<<"\nPlease enter your birthday: \n";
    cout <<"\n          Day: ";
    cin >> user.birthday.day;
    cout <<"\n          Month: ";
    cin >> user.birthday.month;
    cout <<"\n          Year: ";
    cin >> user.birthday.year;
    cout <<"\nPlease enter your coutry: ";
    string country;
    cin >> country;
    user.location.country = country;
    cout << "\nPlease enter your city: ";
    string city;
    cin >> city;
    user.location.city = city;
    database.users.push_back(user);
    cout<<"\n\nWelcome to Youtube!\n";
    user_login(database, user);
}


int main() {

    Database database;
    read_database(database);
    
    cout << "########## Welcome to Youtube ##########\n\n";
    cout << "Please Log In or Register!\n";
    cout << "1) Login\n";
    cout << "2) Register\n";
    cout << "3) Exit\n";
    while (true) {
        string value;
        cout << "Please choose your option:... ";
        cin >> value;
        if (value == "3") {
            exit(0);
        }
        if(value != "1" && value!="2"){
            cout<< "Sorry, wrong option, please try again\n";
            continue;
        }
        if (value == "1") {
            while (true) {
                cout<<"Username/email: ";
                string username;
                cin >> username;
                cout<<"Password: ";
                string password;
                cin >> password;
                if (check_login(database, username, password)) {
                    cout << "Logged In Succesfully!\n";
                    user_login(database, get_user(database, username, password));
                }
                else {
                    cout << "Sorry, wrong credentials, please try again!\n";
                }
            }
        }
        if(value=="2"){
            user_register(database);
        }
        
    }
    

    
   

    return 0;
}