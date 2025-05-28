
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <ctime> // For time()
#include <string>
#include <stdexcept> // For exception handling
#include <chrono> // For time-based functions
#include <thread> // For sleeping
#include <sstream>
using namespace std;

// Forward declaration
class AnimalHospital;

// Base class for all animals
class Animal
{
protected:
    int health;
    int level;
    bool adoption_status;
    char gender;
    int groomingPts;
    string AnimalType;

public:
    Animal(int health = 0, int level = 0, bool adoption_status = false, char gender = 'M', string AnimalType = "unclear", int groomingPts = 0) {
        this->groomingPts = groomingPts;
        this->health = health;
        this->level = level;
        this->gender = gender;
        this->AnimalType = AnimalType;
        this->adoption_status = adoption_status;
    }

    template<typename T>
    T getGrommingpts()
    {
        return groomingPts;
    }

    int getHealth() const
    {
        return health;
    }

    bool isAdopted() const
    {
        return adoption_status;
    }

    void setAdoptionStatus(bool status)
    {
        adoption_status = status;
    }

    virtual void calculateGroomingPts() = 0;

    friend class AnimalHospital;

    // Method to perform feeding activity
    virtual void feed() = 0;

    // Method to perform grooming activity
    virtual void groom() = 0;

    virtual ~Animal() {}

};

// Derived classes for specific types of animals
class Bird : public Animal
{
public:
    int wing_span;
    bool can_talk;
    int beak_strength;

    Bird(int wing_span = 0, bool can_talk = false, int beak_strength = 0,
        int health = 0, int level = 0, bool adoption_status = false, char gender = 'F', string AnimalType = "Bird", int groomingPts = 0)
        : Animal(health, level, adoption_status, gender, AnimalType, groomingPts) {
        this->wing_span = wing_span;
        this->can_talk = can_talk;
        this->beak_strength = beak_strength;
        calculateGroomingPts();
    }

    void calculateGroomingPts() override {
        groomingPts = level + (wing_span * 0.5) + (can_talk * 0.8) + (beak_strength * 1.25);
    }

    void feed() override {
        health += 10; // Increase health by 10 when fed
        cout << "Bird fed. Health increased by 10." << endl;
        cout << "------------------Press Enter to continue------------------" << endl;
        cin.ignore();
    }

    void groom() override {
        groomingPts += 5; // Increase grooming points by 5 when groomed
        cout << "Bird groomed. Grooming points increased by 5." << endl;
        cout << "------------------Press Enter to continue------------------" << endl;
        cin.ignore();
    }
};

class Dog : public Animal
{
public:
    int tail_length;
    bool trained_status;
    int breed_size;

    Dog(int tail_length = 0, bool trained_status = false, int breed_size = 0,
        int health = 0, int level = 0, bool adoption_status = false, char gender = 'F', string AnimalType = "Dog", int groomingPts = 0)
        : Animal(health, level, adoption_status, gender, AnimalType, groomingPts) {
        this->tail_length = tail_length;
        this->trained_status = trained_status;
        this->breed_size = breed_size;
        calculateGroomingPts();
    }

    void calculateGroomingPts() override {
        groomingPts = level + (tail_length * 0.5) + (trained_status * 0.8) + (breed_size * 1.25);
    }

    void feed() override {
        health += 15; // Increase health by 15 when fed
        cout << "Dog fed. Health increased by 15." << endl;
        cout << "------------------Press Enter to continue------------------" << endl;
        cin.ignore();
    }

    void groom() override {
        groomingPts += 8; // Increase grooming points by 8 when groomed
        cout << "Dog groomed. Grooming points increased by 8." << endl;
        cout << "------------------Press Enter to continue------------------" << endl;
        cin.ignore();
    }
};

class Cat : public Animal
{
public:
    int claws_status;
    bool neuter_status;
    int coat_status;

    Cat(int claws_status = 0, bool neuter_status = false, int coat_status = 0,
        int health = 0, int level = 0, bool adoption_status = false, char gender = 'M', string AnimalType = "Cat", int groomingPts = 0)
        : Animal(health, level, adoption_status, gender, AnimalType, groomingPts),
        claws_status(claws_status),
        neuter_status(neuter_status),
        coat_status(coat_status) {
        calculateGroomingPts(); // Call the grooming points calculation method
    }

    void calculateGroomingPts() override
    {
        groomingPts = level + (claws_status * 0.5) + (neuter_status * 0.8) + (coat_status * 1.25);
    }

    void feed() override
    {
        health += 12; // Increase health by 12 when fed
        cout << "Cat fed. Health increased by 12." << endl;
        cout << "------------------Press Enter to continue------------------" << endl;
        cin.ignore();
    }

    void groom() override
    {
        groomingPts += 6; // Increase grooming points by 6 when groomed
        cout << "Cat groomed. Grooming points increased by 6." << endl;
        cout << "------------------Press Enter to continue------------------" << endl;
        cin.ignore();
    }
};

// Custom exception class for animal death
class AnimalDeathException : public std::exception
{
public:
    const char* what() const noexcept override
    {
        return "Sorry, the animal has died. It cannot be treated further.";
    }
};

// Class for the Animal Hospital
class AnimalHospital
{
public:
    vector<Animal*> animalsToTreat; // Animals that need treatment
    vector<Animal*> treatedAnimals; // Animals that have been treated
    int coins = 20;

public:
    void treatAnimal(int index, int& coins, int ch)
    {
        if (index >= 0 && index < animalsToTreat.size())
        {
            Animal* animal = animalsToTreat[index];
            if (animal->getHealth() > 0)
            {
                if (ch == 1)
                {
                    cout << "feeding............." << endl;
                    cin.ignore();
                    coins = coins + 10;
                    animal->feed(); // Feed the animal
                }
                else if (ch == 2)
                {
                    cout << "grooming............" << endl;
                    cin.ignore();
                    coins = coins + 5;
                    animal->groom(); // Groom the animal
                }
                else if (ch == 3)
                {
                    if (animal->groomingPts > 50)
                    {
                        cout << "Animal is being treated..........." << endl;
                        cin.ignore();
                        coins = coins + 15;
                        treatedAnimals.push_back(animal);
                        animalsToTreat.erase(animalsToTreat.begin() + index); // Remove the treated animal from animalsToTreat
                        coins += (animal->getGrommingpts<int>() + 5); // Award 10 coins for treating an animal
                    }
                    else
                    {
                        cout << "Animals grooming points are too low ";
                        cout << "Press Enter" << endl;
                        cin.ignore();
                        cin.ignore();
                    }
                }
                else if (ch == 4)
                {
                    int P;
                    cout << "Enter amount of grooming points to give: ";
                    cin >> P;
                    if (coins >= (P * 2))
                    {
                        animal->groomingPts += P;
                        coins -= (P * 2);
                    }
                    else
                    {
                        cout << "Insufficent coins......" << endl;
                        cout << "Press Enter to continue.................." << endl;
                        cin.ignore();
                    }
                }
            }
            else
            {
                throw AnimalDeathException(); // Throw the custom exception if the animal's health is 0
            }
        }
    }

    void addRandomAnimal()
    {
        srand(time(0)); // Seed for random number generation

        int choice = rand() % 3; // Randomly choose between Cat, Dog, or Bird
        int health = rand() % 80;
        int level = rand() % 50;
        int gen = rand() % 1 + 2;
        int ad = rand() % 1 + 2;
        bool adoption_status;
        char gend;;
        if (gen == 1)
        {
            gend = 'M';
        }
        else
        {
            gend = 'F';
        }
        if (ad == 1)
        {
            adoption_status = false;
        }
        else
        {
            adoption_status = true;
        }
        if (choice == 0)
        {
            // Generate attributes for a Cat
            int claws_status = rand() % 11; // Random claws status between 0 and 10
            bool neuter_status = rand() % 2; // Random neuter status (0 or 1)
            int coat_status = rand() % 11; // Random coat status between 0 and 10

            // Create and add the Cat object
            Animal* random = new Cat(claws_status, neuter_status, coat_status, health, level, adoption_status, gend, "Cat");
            animalsToTreat.push_back(random);
        }
        else if (choice == 1)
        {
            // Generate attributes for a Dog
            int tail_length = rand() % 21; // Random tail length between 0 and 20
            bool trained_status = rand() % 2; // Random trained status (0 or 1)
            int breed_size = rand() % 11; // Random breed size between 0 and 10

            // Create and add the Dog object
            Animal* random = new Dog(tail_length, trained_status, breed_size, health, level, adoption_status, gend, "Dog");
            animalsToTreat.push_back(random);
        }
        else
        {
            // Generate attributes for a Bird
            int wing_span = rand() % 21; // Random wing span between 0 and 20
            bool can_talk = rand() % 2; // Random can_talk status (0 or 1)
            int beak_strength = rand() % 11; // Random beak strength between 0 and 10

            // Create and add the Bird object
            Animal* random = new Bird(wing_span, can_talk, beak_strength, health, level, adoption_status, gend, "Bird");
            animalsToTreat.push_back(random);
        }
    }

    // Method to display the status of all animals in the hospital
    void displayAnimalStatus()
    {
        cout << "Animals to Treat:" << endl;
        for (int i = 0; i < animalsToTreat.size(); ++i)
        {
            cout << "Animal number - " << i + 1 << ": Type - " << animalsToTreat[i]->AnimalType << ": gender - " << animalsToTreat[i]->gender << ": Health - " << animalsToTreat[i]->health << ": Grooming Points - " << animalsToTreat[i]->groomingPts << endl;
        }

        cout << "\nTreated Animals:" << endl;
        for (int i = 0; i < treatedAnimals.size(); ++i)
        {
            cout << "Animal number - " << i + 1 << ": Type - " << treatedAnimals[i]->AnimalType << ": gender - " << treatedAnimals[i]->gender << ": Health - " << treatedAnimals[i]->health << ": coins earned - " << coins << endl;
        }
        cout << endl;
    }

    void saveGameState(const string& filename, const string& filename2)
    {
        ofstream outFile(filename);
        ofstream outFile2(filename2);
        if (!outFile.is_open() || !outFile2.is_open())
        {
            cerr << "Error: Unable to open file for writing." << endl;
            return;
        }

        // Save data to the first file
        outFile << animalsToTreat.size() << endl;
        for (int i = 0; i < animalsToTreat.size(); ++i)
        {
            outFile << animalsToTreat[i]->AnimalType[0] << "|" << animalsToTreat[i]->gender << "|"
                << animalsToTreat[i]->health << "|" << animalsToTreat[i]->level << "|"
                << animalsToTreat[i]->adoption_status << "|" << animalsToTreat[i]->groomingPts;

            // Saving specific characteristics of each animal type
            if (auto bird = dynamic_cast<Bird*>(animalsToTreat[i])) {
                outFile << "|" << bird->wing_span << "|" << bird->can_talk << "|" << bird->beak_strength;
            }
            else if (auto dog = dynamic_cast<Dog*>(animalsToTreat[i])) {
                outFile << "|" << dog->tail_length << "|" << dog->trained_status << "|" << dog->breed_size;
            }
            else if (auto cat = dynamic_cast<Cat*>(animalsToTreat[i])) {
                outFile << "|" << cat->claws_status << "|" << cat->neuter_status << "|" << cat->coat_status;
            }

            outFile << endl;
        }
        outFile.close();
        cout << "Data saved to file: " << filename << endl;

        // Save data to the second file
        outFile2 << treatedAnimals.size() << endl;
        for (int i = 0; i < treatedAnimals.size(); ++i)
        {
            outFile2 << treatedAnimals[i]->AnimalType[0] << "|" << treatedAnimals[i]->gender << "|"
                << treatedAnimals[i]->health << "|" << treatedAnimals[i]->level << "|"
                << treatedAnimals[i]->adoption_status << "|" << treatedAnimals[i]->groomingPts;

            // Saving specific characteristics of each animal type
            if (auto bird = dynamic_cast<Bird*>(treatedAnimals[i])) {
                outFile2 << "|" << bird->wing_span << "|" << bird->can_talk << "|" << bird->beak_strength;
            }
            else if (auto dog = dynamic_cast<Dog*>(treatedAnimals[i])) {
                outFile2 << "|" << dog->tail_length << "|" << dog->trained_status << "|" << dog->breed_size;
            }
            else if (auto cat = dynamic_cast<Cat*>(treatedAnimals[i])) {
                outFile2 << "|" << cat->claws_status << "|" << cat->neuter_status << "|" << cat->coat_status;
            }

            outFile2 << endl;
        }
        outFile2.close();
        cout << "Game state saved successfully." << endl;
    }

    void sendToAdoption(int index)
    {
        if (index >= 0 && index < treatedAnimals.size())
        {
            Animal* animal = treatedAnimals[index];
            if (animal->getHealth() > 0 && animal->groomingPts >= 50) {
                cout << "Animal sent to adoption successfully." << endl;

                treatedAnimals.erase(treatedAnimals.begin() + index);
                delete animal;
                cout << "------------------Press Enter to continue------------------" << endl;
                cin.ignore();
            }
            else {
                cout << "Animal not eligible for adoption." << endl;
                cout << "------------------Press Enter to continue------------------" << endl;
                cin.ignore();
            }
        }
    }

    void displayHUD(int& coins, int animalsToTreatSize, int treatedAnimalsSize)
    {
        system("cls");
        cout << "Coins: " << coins;
        cout << "\t\tAnimals to Treat: " << animalsToTreatSize;
        cout << "\tTreated Animals: " << treatedAnimalsSize << endl;
        cout << "----------------------------------------------------------" << endl;
    }

    bool confirmQuit()
    {
        char retry;
        cout << "Do you want to quit? (Y/N): ";
        cin >> retry;
        return retry == 'Y' || retry == 'y';
    }

    void clearFiles(const string& filename, const string& filename2)
    {
        ofstream ofs(filename);
        ofs << "";
        ofs.close();
        ofstream ofs2(filename2);
        ofs2 << "";
        ofs2.close();
    }

    void addRandomAnimalPeriodically() {
        while (true) {
            addRandomAnimal();
            this_thread::sleep_for(chrono::seconds(15));
        }
    }

    // Function to randomly adopt a treated animal periodically
    void adoptRandomAnimalPeriodically() {
        while (true) {
            if (!treatedAnimals.empty()) {
                int index = rand() % treatedAnimals.size();
                sendToAdoption(index);
                cout << "An animal has been adopted!" << endl;
            }
            this_thread::sleep_for(chrono::seconds(20));
        }
    }

    int main(AnimalHospital& hospital)
    {
        // Start threads for adding random animals and adopting treated animals periodically
        thread addAnimalThread(&AnimalHospital::addRandomAnimalPeriodically, &hospital);
        thread adoptAnimalThread(&AnimalHospital::adoptRandomAnimalPeriodically, &hospital);


        // Load game state from file or start a new game
        string filename = "TobeTreated.txt";
        string filename2 = "Treated.txt";
        int choice;
        char retry;

    menu_start: // Label to return to the main menu

        cout << "Welcome to the Game ^_^" << endl;
        cout << "---------------------------------------" << endl;
        cout << "1. Start Game " << endl;
        cout << "2. Instructions" << endl;
        cout << "3. Quit" << endl;

        // Loop until a valid choice is made
        while (true) {
            cout << "Enter your choice: ";
            cin >> choice;

            switch (choice)
            {
            case 1:
                cout << "Starting the game ." << endl;
                // Start a new game
                // Clear existing files
                //clearFiles(filename, filename2);
                hospital.animalsToTreat.clear();
                hospital.treatedAnimals.clear();
                coins = 20;
                // Add random animals to the hospital
                hospital.addRandomAnimal();
                break;
            case 2:
                instruct();
                //add instructions
                break;
            case 3:
                if (hospital.confirmQuit()) {
                    hospital.saveGameState("TobeTreated.txt", "Treated.txt");
                    cout << "Thank you for playing!" << endl;
                    exit(0);
                }
                break;
            default:
                cout << "Invalid choice. Please choose again." << endl;
                cin.clear(); // Clear error flags
                cout << "Retry? (Y/N): ";
                cin >> retry;
                if (retry == 'Y' || retry == 'y')
                    goto menu_start; // Return to the main menu
                else
                    break; // Exit the program if user chooses not to retry
            }

            // If we reach here, it means a valid choice was made, so we break out of the loop
            break;
        }

        // Game loop
        while (true)
        {
            hospital.displayHUD(hospital.coins, hospital.animalsToTreat.size(), hospital.treatedAnimals.size());
            hospital.displayAnimalStatus();

            int choice;
            cout << "Enter one of the following choices: " << endl;
            cout << "1. Interact with an animal" << endl;
            cout << "2. Shelter a new animal" << endl;
            cout << "3. Save Game" << endl;
            cout << "4. Quit" << endl;
            cin >> choice;

            switch (choice) {
            case 1: {
                int control;
                cout << "Enter the number of the animal you want to interact with: ";
                cin >> control;
                cout << "1. Feed the animal" << endl;
                cout << "2. Groom the animal" << endl;
                cout << "3. Treat the animal" << endl;
                cout << "4. Give Points (Consumes Double the amount of coins): " << endl;
                int interactionChoice;
                cout << "Enter your choice: ";
                cin >> interactionChoice;
                switch (interactionChoice) {
                case 1:
                    hospital.treatAnimal(control - 1, hospital.coins, 1);
                    break;
                case 2:
                    hospital.treatAnimal(control - 1, hospital.coins, 2);
                    break;
                case 3:
                    hospital.treatAnimal(control - 1, hospital.coins, 3);
                    break;
                case 4:
                    hospital.treatAnimal(control - 1, hospital.coins, 4);
                    break;
                default:
                    cout << "Invalid choice. Please choose again." << endl;
                    cout << "------------------Press Enter to continue------------------" << endl;
                    cin.ignore();
                    break;
                }
                break;
            }
            case 2:
                hospital.addRandomAnimal();
                break;
            case 3:
                hospital.saveGameState("TobeTreated.txt", "Treated.txt");
                break;
            case 4:
                if (hospital.confirmQuit()) {
                    //hospital.saveGameState("TobeTreated.txt", "Treated.txt");
                    cout << "Thank you for playing!" << endl;
                    // Join threads to ensure they finish before exiting
                    addAnimalThread.detach();
                    adoptAnimalThread.detach();
                    exit(0);
                }
                break;
            default:
                cout << "Invalid choice. Please choose again." << endl;
                cout << "------------------Press Enter to continue------------------" << endl;
                cin.ignore();
                break;
            }
        }
    }

    void instruct()
    {
        cout << "Welcome to Animal Hospital!" << endl;
        cout << "---------------------------------------" << endl;
        cout << "Press Enter to start the instructions..." << endl;
        cin.ignore();
        system("cls");
        cout << "In this game, you are the owner of an animal hospital." << endl;
        cout << "------------------Press Enter to continue------------------" << endl;
        cin.ignore();
        system("cls");
        cout << "Your goal is to treat sick animals and earn coins." << endl;
        cout << "------------------Press Enter to continue------------------" << endl;
        cin.ignore();
        system("cls");
        cout << "Here's how the game works:" << endl;
        cout << "------------------Press Enter to continue------------------" << endl;
        cin.ignore();
        system("cls");
        cout << "1. At the start of the game, you will be presented with a list of sick animals that need treatment." << endl;
        cout << "------------------Press Enter to continue------------------" << endl;
        cin.ignore();
        system("cls");
        cout << "2. To treat an animal, enter the number of the animal you want to treat." << endl;
        cout << "------------------Press Enter to continue------------------" << endl;
        cin.ignore();
        system("cls");
        cout << "3. The animal will be fed and groomed, increasing its health and grooming points." << endl;
        cout << "------------------Press Enter to continue------------------" << endl;
        cin.ignore();
        system("cls");
        cout << "4. You will earn coins for treating the animal." << endl;
        cout << "------------------Press Enter to continue------------------" << endl;
        cin.ignore();
        system("cls");
        cout << "5. Random animals will be added to the hospital every 15 seconds." << endl;
        cout << "------------------Press Enter to continue------------------" << endl;
        cin.ignore();
        system("cls");
        cout << "6. Treated animals will be adopted every 20 seconds, earning you more coins." << endl;
        cout << "------------------Press Enter to continue------------------" << endl;
        cin.ignore();
        system("cls");
        cout << "7. You can save and load the game state to continue your progress later." << endl;
        cout << "------------------Press Enter to continue------------------" << endl;
        cin.ignore();
        system("cls");
        cout << "8. To quit the game, enter -1 when prompted for the animal number." << endl;
        cout << "------------------Press Enter to continue------------------" << endl;
        cin.ignore();
        system("cls");
        cout << "---------------------------------------" << endl;
        cout << "Good luck, and have fun!" << endl;
        cout << "Press Enter to continue...";
        cin.ignore();
        system("cls");
    }
};

int main() {
    AnimalHospital hospital;
    hospital.main(hospital);
    return 0;
}