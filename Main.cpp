/* "LRU Music Library: Smart Song Management" */
#include <iostream>
#include <unordered_map>
using namespace std;

class MusicPlayer
{
private:
    class Song
    {
    public:
        string songName;
        string artist;
        Song* prev = nullptr;
        Song* next = nullptr;

        Song(string name, string artist)
        {
            songName = name;
            this->artist = artist;
        }
    };

    Song* head = new Song("", "");
    Song* tail = new Song("", "");
    int capacity;
    unordered_map<string, Song*> songMap;

public:
    MusicPlayer(int cap)
    {
        capacity = cap;
        head->next = tail;
        tail->prev = head;
    }

    string getSong(string songName)
    {
        if (songMap.find(songName) != songMap.end())
        {
            Song* current = songMap[songName];
            detach(current);
            attach(current);
            return current->artist;
        }
        return "Song not found.";
    }

    void addSong(string songName, string artist)
    {
        if (songMap.find(songName) != songMap.end())
        {
            Song* current = songMap[songName];
            detach(current);
            attach(current);
        }
        else
        {
            if (songMap.size() >= capacity)
            {
                Song* evictSong = tail->prev;
                detach(evictSong);
                songMap.erase(evictSong->songName);
                delete evictSong;
            }
            Song* newSong = new Song(songName, artist);
            songMap[songName] = newSong;
            attach(newSong);
        }
    }

    void printRecentSongs()
    {
        Song* current = head->next;
        cout << "Recently listened songs:" << endl;
        while (current != tail)
        {
            cout << "Song: " << current->songName << ", Artist: " << current->artist << endl;
            current = current->next;
        }
    }

private:
    void attach(Song* song)
    {
        song->next = head->next;
        head->next->prev = song;
        head->next = song;
        song->prev = head;
    }

    void detach(Song* song)
    {
        song->prev->next = song->next;
        song->next->prev = song->prev;
    }
};

int main()
{
    int capacity;
    cout << "Enter playlist capacity: ";
    cin >> capacity;

    MusicPlayer player(capacity);

    cout << "Enter the number of actions: ";
    int numActions;
    cin >> numActions;

    while (numActions--)
    {
        cout << "Choose action:" << endl;
        cout << "1. ADD" << endl;
        cout << "2. GET" << endl;
        cout << "3. RECENT" << endl;
        cout << "4. PRINT" << endl;

        int choice;
        cin >> choice;

        if (choice == 1)
        {
            string songName, artist;
            cout << "Enter song name: ";
            cin >> songName;
            cout << "Enter artist name: ";
            cin >> artist;
            player.addSong(songName, artist);
            cout << "Song added to playlist." << endl;
        }
        else if (choice == 2)
        {
            string songName;
            cout << "Enter song name: ";
            cin >> songName;
            string artist = player.getSong(songName);
            cout << "Artist: " << artist << endl;
        }
        else if (choice == 3)
        {
            player.printRecentSongs();
        }
        else if (choice == 4)
        {
            player.printRecentSongs();
        }
        else
        {
            cout << "Invalid choice." << endl;
        }
    }

    return 0;
}