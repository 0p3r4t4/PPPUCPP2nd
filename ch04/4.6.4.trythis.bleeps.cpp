#include "std_lib_facilities.h"

int main()
{
    const vector<string> dislikes {"Broccoli", "Weed", "Funeral"};

    for (string word; cin >> word; ){
        bool disliked {false};
        for (string dislike: dislikes)
            if (word==dislike)
                disliked = true;
        if (disliked)
            cout << "BLEEP!\n";
        else
            cout << word << '\n';
    }
    
    return 0;
}
