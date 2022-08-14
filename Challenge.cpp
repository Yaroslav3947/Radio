#include <list>
#include <limits>
#include <iomanip>
#include <iostream>
#include <algorithm>
using namespace std;

class Song {
    friend ostream &operator <<(ostream &os, const Song &obj);
    string name;
    string artist;
    int rating;
public:
    Song() = default;
    ~Song() = default;
    Song(string name, string artist, int rating)
        :name{name},artist{artist},rating{rating}{}
    string get_name() {
        return name;
    }
    string get_artist() {
        return artist;
    }
    int get_rating() {
        return rating;
    }
    bool operator <(const Song &rhs) const  {
        return this->name < rhs.name;
    }
    bool operator ==(const Song &rhs) const  {
        return this->name == rhs.name;
    }
};

ostream &operator <<(ostream &os, const Song &obj) {
    os << setw(20) << left << obj.name
       << setw(30) << left << obj.artist
       << setw(2)  << left << obj.rating;
    return os;
}

void display_menu() {
    std::cout << "\nF - Play First Song" << std::endl;
    std::cout << "N - Play Next song" << std::endl;
    std::cout << "P - Play Previous song" << std::endl;
    std::cout << "A - Add and play a new Song at current location" << std::endl;
    std::cout << "L - List the current playlist" << std::endl;
    std::cout << "===============================================" << std::endl;
    std::cout << "Enter a selection (Q to quit): ";
}

void play_current_song(const list<Song>::iterator &current_song) {
    cout << "Playing:\n" << *current_song << endl;
}

void display_playlist(const list<Song> &playlist, const Song &current_song) {
    for(const auto &song : playlist) {
        cout << song << endl;
    }

    cout << "Current song:\n" << current_song << endl;
}

void play_first_song(const list<Song> &playlist) {
    auto first_song_in_playlist = playlist.cbegin();
    cout << "Playing:\n" << *first_song_in_playlist << endl;
}

void play_next_song(list<Song> &playlist, list<Song>::iterator &current_song) {
    current_song++;
    if(current_song == playlist.end()) {
        current_song = playlist.begin();
    }
    play_current_song(current_song);
}

void play_previous_song(list<Song> &playlist, list<Song>::iterator& current_song) {
    if(current_song == playlist.begin()) {
        current_song = playlist.end();
    }
    current_song--;
    play_current_song(current_song);
}

bool IsRight(const int &val) {
    return (val >=1 && val <=5);
}
void add_and_play_new_song(list<Song> &playlist, auto &current_song) {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
    cout << "Adding and playing new song" << endl;
    string song_name, song_artist;
    int song_rating;
    cout << "Enter song name:";
    getline(cin, song_name);

    cout << "Enter song artist:";
    getline(cin, song_artist);
    do {
    cout << "Enter your rating (1-5):";
    cin >> song_rating;
    } while(!IsRight(song_rating));

    
    playlist.insert(current_song, Song{song_name,song_artist,song_rating});
    current_song--;
    
}


int main() {

    list<Song> playlist{
            {"God's Plan",        "Drake",                     5},
            {"Never Be The Same", "Camila Cabello",            5},
            {"Pray For Me",       "The Weekend and K. Lamar",  4},
            {"The Middle",        "Zedd, Maren Morris & Grey", 5},
            {"Wait",              "Maroone 5",                 4},
            {"Whatever It Takes", "Imagine Dragons",           3}          
    };

    auto current_song = playlist.begin();

    display_playlist(playlist,*current_song);
    char selection{};
    do {
        display_menu();
        cin >> selection;
        switch(selection) {
            case 'f': {
            case 'F': 
                play_first_song(playlist);
                break;
            }

            case 'n': {
            case 'N': 
                play_next_song(playlist, current_song);
                break;
            }

            case 'p': {
            case 'P': 
                play_previous_song(playlist, current_song);
                break;
            }

            case 'a': {
            case 'A': 
                add_and_play_new_song(playlist, current_song);
                break;
            }

            case 'l': {
            case 'L': 
                display_playlist(playlist, *current_song);
                break;
            }

            case 'q': {
            case 'Q': 
                continue;
            }

            default : {
                cout << "You did smth wrong, try again!" << endl;
                break;
            }
            
        }
    } while (selection != 'q' && selection != 'Q');
    

    cout << "Thanks for listening!" << endl;


    return 0;
}


