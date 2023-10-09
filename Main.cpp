/* "LRU Music Library: Smart Song Management" */
#include <iostream>
#include <unordered_map>
using namespace std;

class MusicPlayer
{
private:
    class Song //Linked List Class
    {
    public:
        string songName; // Name of Song
        string artist;   //Artist of song
        Song* prev = NULL;
        Song* next = NULL;

        Song(string name, string artist) //constructor
        {
            songName = name;
            this->artist = artist;
        }
    };

    Song* head = new Song("", "");
    Song* tail = new Song("", "");
    int capacity;                         //Song capacity of playlist
    unordered_map<string, Song*> songMap; //Mapping of song and Node

private:
    void attach(Song* song)  //Add song to Playlist
    {
        song->next = head->next;
        head->next->prev = song;
        head->next = song;
        song->prev = head;
    }

    void detach(Song* song) // remove song from playlist
    {
        song->prev->next = song->next;
        song->next->prev = song->prev;
    }
public:
    MusicPlayer(int cap) // constructor
    {
        capacity = cap;
        head->next = tail;
        tail->prev = head;
    }

    void getSong(string songName)  //search song in the playlist
    {
        if (songMap.find(songName) != songMap.end())
        {
            Song* current = songMap[songName];
            detach(current);
            attach(current);
            cout<<current->songName<<" Song is present"<<endl;
            cout<<"Artist: "<<current->artist<< endl;
        }
        else{
            cout<<"Song not found !!";
        }
    }

    void addSong(string songName, string artist) // Add song to the playlist
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
                Song* temp = tail->prev;
                detach(temp);
                songMap.erase(temp->songName);
                delete temp;
            }
            Song* newSong = new Song(songName, artist);
            songMap[songName] = newSong;
            attach(newSong);
        }
    }
    void printRecentSong(){     //print recently played song
        cout<<"songName : "<<head->next->songName<<" , Artist : "<<head->next->artist<<endl;
    }
    void printAllSongs()        //print all songs of playlist
    {
        Song* current = head->next;
        cout << "All songs: " << endl;
        while (current != tail)
        {
            cout << "Song: " << current->songName << " , Artist: " << current->artist << endl;
            current = current->next;
        }
    }


};

int main()
{
    int capacity;
    cout << "Enter playlist capacity: ";
    cin >> capacity;

    MusicPlayer player(capacity);
    
    int action = 1;
    while(action)
    {
        int choice;

        cout << "\nChoose action:" << endl;
        cout << "1. Add Song" << endl;
        cout << "2. Get Song" << endl;
        cout << "3. Recently played" << endl;
        cout << "4. Print All" << endl;

        string songName, artist;
        cin >> choice;
        switch (choice)
        {
        case 1:
            cout << "Enter song name: ";
            cin >> songName;
            cout << "Enter artist name: ";
            cin >> artist;
            player.addSong(songName, artist);
            cout << "Song added to playlist." << endl;
            break;

        case 2:
            cout << "Enter song name: ";
            cin >> songName;
            player.getSong(songName);
            break;

        case 3:
            player.printRecentSong();
            break;

        case 4:
            player.printAllSongs();
            break;
        
        default:
            cout << "Invalid choice." << endl;
            break;
        }
        
        cout<<"\nDo you want to continue \n 0 - Exit \n 1 - Continue"<<endl;
        cin>>action;
    }

    return 0;
}