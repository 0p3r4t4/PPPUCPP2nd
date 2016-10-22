#include "std_lib_facilities.h"

int main()
{
    cout << "Enter the name of the person you want to write to: ";
    string first_name {" "};
    cin >> first_name;

    cout << "Enter the age of this person: ";
    int age {0};
    cin >> age;
    if (age <= 0 || age >= 110)
        simple_error("you're kidding!");
    
    cout << "Enter the name of a mutual friend: ";
    string friend_name {" "};
    cin >> friend_name;

    cout << "Enter friend's sex (m for male, f for female): ";
    char friend_sex {0};
    cin >> friend_sex;

    cout << "\nDear " << first_name << ",\n\n";
    cout << "\tHow are you? I am fine. I miss you.\n"
            "I'm studying in I began to remember the good times\n"
            "at University.\n\n";

    cout << "Have you seen " << friend_name << " lately?\n";
    if (friend_sex == 'm')
        cout << "If you see " << friend_name << " please ask him to call me.\n";
    if (friend_sex == 'f')
        cout << "If you see " << friend_name << " please ask her to call me.\n";

    cout << "\nI hear you just had a birthday and you are " << age
        << " years old.";
    if (age < 12)
        cout << "\nNext year you will be " << age+1 << ".";
    else if (age == 17)
        cout << "\nNext year you will be able to vote.";
    else if (age > 70)
        cout << "\nI hope you are enjoying retirement.";

    cout << "\n\nYours sincerely,";
    cout << "\n\n\t\t\tDan\n\n";
}
