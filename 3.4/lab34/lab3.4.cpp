//3.4 Суперсчастливые билеты(9)
//Известно, что «счастливым» билетом называется билет,
//в номере которого сумма цифр первой половины номера равна
//сумме цифр второй половины номера. А «суперсчастливым»
//называется билет, у которого кроме упомянутого условия
//каждая цифра отличается от соседней не более чем на 1
//(например, 323233). Номер может начинаться с 0. Найти количество
//«суперсчастливых» номеров среди всех 2N-значных билетов (1 ≤ N ≤ 30).
//Ввод. Единственная строка содержит значение N.
//Вывод. Единственная строка содержит количество номеров.

//CLion

//Гусев Сергей ПС-22

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

const int MAX_N = 30;

vector<vector<vector<unsigned long long>>> dp;

int main() {
    ifstream inFile("INPUT.TXT");
    ofstream outFile("OUTPUT.TXT");

    int N;
    inFile >> N;

    int maxPos = 2 * N;
    int offset = MAX_N * 9;

    dp.resize(maxPos + 1, vector<vector<unsigned long long>>(10, vector<unsigned long long>(2 * offset + 1, 0)));

    for (int d = 0; d <= 9; d++) {
        dp[1][d][offset + d] = 1;
    }

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

    unsigned long long result = 0;
    for (int last = 0; last <= 9; last++) {
        result += dp[maxPos][last][offset];
    }

    outFile << result << endl;

    inFile.close();
    outFile.close();

    return 0;
}