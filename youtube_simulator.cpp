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


int main() {

    Database database;
    read_database(database);
    
    
   

    return 0;
}