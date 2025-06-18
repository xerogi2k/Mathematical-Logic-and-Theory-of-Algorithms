#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

// Функция для генерации начального списка участников
void generatePairs(int start, int end, vector<int>& result) {
    if (start > end) return;
    if (start == end) {
        result.push_back(start);
        return;
    }
    result.push_back(start);
    result.push_back(end);
    generatePairs(start + 1, end - 1, result);
}

// Функция для симуляции турнира и определения победителя
void simulateTournament(vector<int>& players, ofstream& outputFile) {
    int round = 1;
    while (players.size() > 1) {
        outputFile << "Round " << round << ":";
        for (size_t i = 0; i < players.size(); ++i) {
            if (i > 0) outputFile << " ";
            outputFile << players[i];
        }
        outputFile << endl;

        vector<int> nextRound;
        for (size_t i = 0; i < players.size(); i += 2) {
            nextRound.push_back(players[i]);  // Более высокий рейтинг побеждает
        }
        players = nextRound;
        round++;
    }

    // Последний раунд
    outputFile << "Round " << round << ": " << players[0] << endl;
}

int main() {
    ifstream inputFile("input.txt");
    ofstream outputFile("output.txt");

    if (!inputFile.is_open() || !outputFile.is_open()) {
        cerr << "Error opening file!" << endl;
        return 1;
    }

    int n;
    inputFile >> n;
    int totalPlayers = 1 << n; // 2^n игроков
    vector<int> result;

    generatePairs(1, totalPlayers, result);

    // Запись начального списка в файл
    outputFile << "Initial list: ";
    for (int i = 0; i < totalPlayers; ++i) {
        if (i > 0) outputFile << " ";
        outputFile << result[i];
    }
    outputFile << endl;

    // Симуляция турнира и вывод каждого раунда
    simulateTournament(result, outputFile);

    inputFile.close();
    outputFile.close();

    return 0;
}
