#include <iostream>
#include <vector>
#include <cstring>
#include <fstream> // Библиотека для работы с файлами

using namespace std;

const int MAX_N = 30;
long long dp[MAX_N * 2 + 1][10][2 * MAX_N * 9 + 1]; // Позиция, последняя цифра, смещённая разница сумм

int main() {
    ifstream inFile("input.txt"); // Поток для чтения из файла
    ofstream outFile("output.txt"); // Поток для записи в файл

    int N;
    inFile >> N; // Считывание из файла

    memset(dp, 0, sizeof(dp));
    int maxPos = 2 * N;
    int offset = MAX_N * 9; // Смещение для разницы сумм
    
    // Инициализация для первой цифры
    for (int d = 0; d <= 9; d++) {
        dp[1][d][offset + d] = 1;
    }
    
    // Заполнение таблицы ДП
    for (int pos = 1; pos < maxPos; pos++) {
        for (int last = 0; last <= 9; last++) {
            for (int diff = -pos * 9; diff <= pos * 9; diff++) {
                int realDiff = offset + diff;
                if (dp[pos][last][realDiff] == 0) continue;
                
                for (int next = max(0, last - 1); next <= min(9, last + 1); next++) {
                    int nextDiff = diff + (pos < N ? next : -next);
                    if (nextDiff >= -maxPos * 9 && nextDiff <= maxPos * 9) {
                        dp[pos + 1][next][offset + nextDiff] += dp[pos][last][realDiff];
                    }
                }
            }
        }
    }
    
    // Подсчёт результата
    long long result = 0;
    for (int last = 0; last <= 9; last++) {
        result += dp[maxPos][last][offset];
    }
    
    outFile << result << endl; // Запись результата в файл

    inFile.close(); // Закрытие файла ввода
    outFile.close(); // Закрытие файла вывода

    return 0;
}
