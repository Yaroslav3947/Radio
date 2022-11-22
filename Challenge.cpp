#include <list>
#include <limits>
#include <iomanip>
#include <iostream>
#include <algorithm>

const short MINRATE = 1;
const short MAXRATE = 5;

enum Selection {
    PLAYFIRST = 'F',
    PLAYNEXT = 'N',
    PLAYPRVIOUS = 'P',
    ADD = 'A',
    LISTPLAYLIST = 'L',
    QUIT = 'Q'
};
class Song {
    friend std::ostream &operator <<(std::ostream &os, const Song &obj);
    std::string name;
    std::string artist;
    int rating;
public:
    Song() = default;
    ~Song() = default;
    Song(std::string name, std::string artist, int rating)
        :name{name},artist{artist},rating{rating}{}
    std::string get_name() {
        return name;
    }
    std::string get_artist() {
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

std::ostream &operator <<(std::ostream &os, const Song &obj) {
    os << std::setw(20) << std::left << obj.name
       << std::setw(30) << std::left << obj.artist
       << std::setw(2)  << std::left << obj.rating;
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

void play_current_song(const std::list<Song>::iterator &current_song) {
    std::cout << "Playing:\n" << *current_song << std::endl;
}

void display_playlist(const std::list<Song> &playlist, std::list<Song>::iterator &current_song) {
    for(const auto &song : playlist) {
        std::cout << song << std::endl;
    }
    play_current_song(current_song);
}

void play_first_song(const std::list<Song> &playlist) {
    auto first_song_in_playlist = playlist.cbegin();
    std::cout << "Playing:\n" << *first_song_in_playlist << std::endl;
}

void play_next_song(std::list<Song> &playlist, std::list<Song>::iterator &current_song) {
    current_song++;
    if(current_song == playlist.end()) {
        current_song = playlist.begin();
    }
    play_current_song(current_song);
}

void play_previous_song(std::list<Song> &playlist, std::list<Song>::iterator &current_song_it) {
    if(current_song_it == playlist.begin()) {
        current_song_it = playlist.end();
    }
    current_song_it--;
    play_current_song(current_song_it);
}

bool IsRight(const int &val) {
    return (val >= MINRATE && val <= MAXRATE);
}
void add_and_play_new_song(std::list<Song> &playlist, auto &current_song) {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
    std::cout << "Adding and playing new song" << std::endl;
    std::string song_name;
    std::string song_artist;
    int song_rating;
    std::cout << "Enter song name:";
    getline(std::cin, song_name);

    std::cout << "Enter song artist:";
    getline(std::cin, song_artist);
    do {
        std::cout << "Enter your rating (1-5):";
        std::cin >> song_rating;
    } while(!IsRight(song_rating));
    
    playlist.insert(current_song, Song{song_name,song_artist,song_rating});
    current_song--;
    
}

char get_selection() {
    char selection;
    std::cin >> selection;
    selection = toupper(selection);
    return selection;
}
int main() {

    std::list<Song> playlist{
            {"God's Plan",        "Drake",                     5},
            {"Never Be The Same", "Camila Cabello",            5},
            {"Pray For Me",       "The Weekend and K. Lamar",  4},
            {"The Middle",        "Zedd, Maren Morris & Grey", 5},
            {"Wait",              "Maroone 5",                 4},
            {"Whatever It Takes", "Imagine Dragons",           3}          
    };

    auto current_song = playlist.begin();

    display_playlist(playlist,current_song);
    char selection{};
    do {
        display_menu();
        selection = get_selection();
        switch(selection) {
            case PLAYFIRST: 
                play_first_song(playlist);
                break;

            case PLAYNEXT:  
                play_next_song(playlist, current_song);
                break;

            case PLAYPRVIOUS: 
                play_previous_song(playlist, current_song);
                break;

            case ADD:  
                add_and_play_new_song(playlist, current_song);
                break;

            case LISTPLAYLIST: 
                display_playlist(playlist, current_song);
                break;

            case QUIT: 
                break;;

            default : 
                std::cout << "You did smth wrong, try again!" << std::endl;
                break;
        }
    } while (selection != QUIT);
    
    std::cout << "Thanks for listening!" << std::endl;

    return 0;
}




