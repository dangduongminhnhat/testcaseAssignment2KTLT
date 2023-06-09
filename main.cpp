#include "C:\Users\GAMING\Desktop\A2_initial\knight2.h"
#include<time.h>
#include<vector>
#include<windows.h>

#define NUMBER_OF_KNIGHTS_AND_EVENTS 30
#define NUMBER_OF_TESTCASE 1000

string input = "input\\";
string output = "output\\";

string runSourceCode(string file_armyknights, string file_events) {
    std::stringstream buffer; // chuỗi để lưu thông tin được redirect từ console
    std::streambuf* oldCoutStreamBuf = std::cout.rdbuf(); // lưu lại địa chỉ stream buffer của cout
    std::cout.rdbuf(buffer.rdbuf()); // redirect cout sang buffer

    KnightAdventure * knightAdventure = new KnightAdventure();
    knightAdventure->loadArmyKnights(file_armyknights);
    knightAdventure->loadEvents(file_events);
    knightAdventure->run();

    delete knightAdventure;

    std::cout.rdbuf(oldCoutStreamBuf); // phục hồi cout sang stream buffer ban đầu
    std::string consoleOutput = buffer.str(); // lấy thông tin được lưu trong chuỗi buffer
    return consoleOutput;
}

void createTestCase() {
    vector<int> events = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 112, 113, 114};
    vector<int> paladinKnights, lancelotKnights, dragonKnights, normalKnights;
    vector<KnightType> chooseKnight = {PALADIN, LANCELOT, DRAGON, NORMAL};
    for(int i = 1; i < 1000; i ++) {
        if(checkPrime(i)) paladinKnights.push_back(i);
        else if(i == 888) lancelotKnights.push_back(i);
        else if(checkPythagoras(i)) dragonKnights.push_back(i);
        else normalKnights.push_back(i);
    }
    for(int i = 301; i <= NUMBER_OF_TESTCASE; i ++) {
        srand( (unsigned)time(NULL) );
        vector<int> mustHave = {95, 96, 97, 98};

        string file_armyknights = input + "tc" + to_string(i) + "_armyknights";
        ofstream file;
        file.open(file_armyknights);
        int numKnights = rand() % NUMBER_OF_KNIGHTS_AND_EVENTS + 1;
        file << numKnights << endl;
        for(int i = 0; i < numKnights; i ++) {
            int hp, level = rand() % 10 + 1, phoenixDownI = rand() % 6, gil = rand() % 999 + 1, antidote = rand() % 6;
            int choose = rand() % 4;
            if(chooseKnight[choose] == PALADIN) {
                int pal = rand() % paladinKnights.size();
                hp = paladinKnights[pal];
                paladinKnights.erase(paladinKnights.begin() + pal);
                paladinKnights.push_back(hp);
            } else if(chooseKnight[choose] == LANCELOT) {
                int lan = rand() % lancelotKnights.size();
                hp = lancelotKnights[lan];
                lancelotKnights.erase(lancelotKnights.begin() + lan);
                lancelotKnights.push_back(hp);
            } else if(chooseKnight[choose] == DRAGON) {
                int dra = rand() % dragonKnights.size();
                hp = dragonKnights[dra];
                dragonKnights.erase(dragonKnights.begin() + dra);
                dragonKnights.push_back(hp);
            } else {
                int nor = rand() % normalKnights.size();
                hp = normalKnights[nor];
                normalKnights.erase(normalKnights.begin() + nor);
                normalKnights.push_back(hp);
            }
            KnightType typeChoose = chooseKnight[choose];
            chooseKnight.erase(chooseKnight.begin() + choose);
            chooseKnight.push_back(typeChoose);
            file << hp << " " << level << " " << phoenixDownI << " " << gil << " " << antidote;
            if(i < numKnights - 1) file << endl;
        }
        file.close();

        string file_events = input + "tc" + to_string(i) + "_events";
        file.open(file_events);
        int numEvents = rand() % NUMBER_OF_KNIGHTS_AND_EVENTS + 5;
        file << numEvents << endl;
        for(int i = 0; i < numEvents - 5; i ++) {
            if(mustHave.size() > 0) {
                int write = rand() % 2;
                if(write == 1) {
                    int choose = rand() % mustHave.size();
                    file << mustHave[choose] << " ";
                    mustHave.erase(mustHave.begin() + choose);
                } 
            }
            int event = rand() % events.size();
            file << events[event] << " ";
            int temp = events[event];
            events.erase(events.begin() + event);
            events.push_back(temp);
        }
        while(mustHave.size() > 0) {
            int choose = rand() % mustHave.size();
            file << mustHave[choose] << " ";
            mustHave.erase(mustHave.begin() + choose);
        }
        file << 99;
        file.close();

        string saveString = runSourceCode(file_armyknights, file_events);

        string file_output = output + "tc" + to_string(i) + "_output";
        file.open(file_output);
        file << saveString;
        file.close();

        Sleep(1000);
        cout << "testcase " << i << " is created\n";
    }
    cout << "Testcases were created!\n";
}

void checkTestCase() {
    for(int i = 1; i <= NUMBER_OF_TESTCASE; i ++) {
        string file_armyknights = input + "tc" + to_string(i) + "_armyknights", 
            file_events = input + "tc" + to_string(i) + "_events",
            file_output = output + "tc" + to_string(i) + "_output";
        
        string your_answer = runSourceCode(file_armyknights, file_events);
        
        ifstream file;
        file.open(file_output);
        string my_answer = "", read;
        while(getline(file, read)) my_answer += read + "\n";
        file.close();

        if(my_answer == your_answer) cout << "You have passed testcase " + to_string(i) << endl;
        else {
            cout << "You are a chicken\n" 
                << "my answer is:\n"
                << my_answer << endl
                << "your answer is:\n"
                << your_answer << endl;
                break;
        }
    }
}

void runTestcaseI(int i) {
    string file_armyknights = input + "tc" + to_string(i) + "_armyknights", file_events = input + "tc" + to_string(i) + "_events";
    KnightAdventure * knightAdventure = new KnightAdventure();
    knightAdventure->loadArmyKnights(file_armyknights);
    knightAdventure->loadEvents(file_events);
    knightAdventure->run();

    delete knightAdventure;
}

void updateOutput() {
    for(int i = 1; i <= NUMBER_OF_TESTCASE; i ++) {
        string file_armyknights = input + "tc" + to_string(i) + "_armyknights", 
            file_events = input + "tc" + to_string(i) + "_events",
            file_output = output + "tc" + to_string(i) + "_output";

        string saveString = runSourceCode(file_armyknights, file_events);

        ofstream file;
        file.open(file_output);
        file << saveString;
        file.close();
        cout << "testcase " << i << " is updated\n";
    }
    cout << "Testcases were updated!\n";
}

int main(int argc, char ** argv) {
    //  g++ -g -o main main.cpp C:\Users\GAMING\Desktop\A2_initial\knight2.cpp -I . -std=c++11 -DDEBUG

    checkTestCase();

    return 0;
}