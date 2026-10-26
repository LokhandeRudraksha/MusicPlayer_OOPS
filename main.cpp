#include <iostream>
#include <string>
#include "MusicPlayer.h"

int main() {
    MusicPlayer player;
    int choice;

    std::string folderPath;
    std::cout << "Enter path to your songs folder\n[Press Enter to use default C:\\Users\\Vansh\\Downloads\\songsfolder]: ";
    std::getline(std::cin, folderPath);
    if (folderPath.empty()) {
        folderPath = "C:\\Users\\Rudraksha Lokhande\\OneDrive\\Documents\\MusicPlayer\\Music";
    }

    player.loadSongsFromFolder(folderPath);

    do {
        std::cout << "\n=====================================\n";
        std::cout << "       OOP TERMINAL MUSIC PLAYER     \n";
        std::cout << "=====================================\n";
        std::cout << "1. View Song Library\n";
        std::cout << "2. Search Song\n";
        std::cout << "3. Add Song to Queue\n";
        std::cout << "4. View Current Queue\n";
        std::cout << "5. Play / Start Queue\n";
        std::cout << "6. Pause Song\n";
        std::cout << "7. Resume Song\n";
        std::cout << "8. Next Song\n";
        std::cout << "9. Previous Song\n";
        std::cout << "10. Volume Up (+10%)\n";
        std::cout << "11. Volume Down (-10%)\n";
        std::cout << "0. Exit\n";
        std::cout << "=====================================\n";
        std::cout << "Enter your choice: ";
        
        if (!(std::cin >> choice)) {
            std::cout << "Invalid input. Please enter a number.\n";
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            continue;
        }

        switch (choice) {
            case 1:
                player.displayLibrary();
                break;
            case 2: {
                std::string query;
                std::cout << "Enter search keyword: ";
                std::cin >> query;
                player.searchSong(query);
                break;
            }
            case 3: {
                int index;
                std::cout << "Enter song number from library to add to queue: ";
                std::cin >> index;
                player.addSongToQueue(index);
                break;
            }
            case 4:
                player.showQueue();
                break;
            case 5:
                player.startPlayback();
                break;
            case 6:
                player.pauseSong();
                break;
            case 7:
                player.resumeSong();
                break;
            case 8:
                player.next();
                break;
            case 9:
                player.previous();
                break;
            case 10:
                player.volumeUp();
                break;
            case 11:
                player.volumeDown();
                break;
            case 0:
                std::cout << "Exiting Music Player. Goodbye!\n";
                break;
            default:
                std::cout << "Invalid choice! Please choose a valid option from the menu.\n";
        }
    } while (choice != 0);

    return 0;
}