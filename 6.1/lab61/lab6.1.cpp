// 6.1. Счастливые билеты (8).
// Номера автобусных билетов состоят из 2N цифр,
// включая незначащие нули (1 ≤ N ≤ 500). Минимальный возможный номер состоит
// из 2N нулей, а максимальный - из 2N девяток. Студент Вася ездит в университет
// на автобусе и коллекционирует счастливые билеты, в которых сумма первых N цифр
// совпадает с суммой последних N цифр. Как и всякий настоящий коллекционер,
// Вася готов пойти на все для пополнения своей коллекции.
// Вместе с тем ему пока приходится учитывать свои финансовые возможности.
// Каждый раз после приобретения билета Вася определяет, какое минимальное
// количество билетов нужно купить еще, чтобы среди них обязательно оказался
// счастливый билет. Если у него оказывается достаточно денег, он тут же покупает
// необходимое число билетов. Иногда он не успевает закончить расчеты, проезжает
// свою остановку и опаздывает на занятия. Помогите Васе.
// Ввод из файла INPUT.TXT. В первой строке находится число N. Во второй строке
// задан номер первого билета Васи из 2N цифр.
// Вывод в файл OUTPUT.TXT. В единственной строке вывести минимальное число
// следующих билетов, необходимое для гарантированного получения счастливого билета.

//Visual Studio Code

//Гусев Сергей ПС-22

#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

// Функция для подсчета суммы цифр в строке
int sumDigits(const string& number) {
    int sum = 0;
    for (char digit : number) {
        sum += digit - '0';
    }
    return sum;
}

// Функция для получения всех возможных последовательностей чисел с заданной суммой
void generateSequences(unordered_map<int, vector<string>>& sequences, int N, bool reverse) {
    for (int i = 0; i <= 9 * N; ++i) {
        sequences[i] = {};
    }

    int limit = 1;
    for (int i = 0; i < N; ++i) {
        limit *= 10;
    }

    for (int num = 0; num < limit; ++num) {
        string numStr = to_string(num);
        numStr = string(N - numStr.length(), '0') + numStr; // Добавляем ведущие нули
        int s = sumDigits(numStr);
        sequences[s].push_back(numStr);
    }
}

// Функция проверки счастливого билета
bool isLucky(const string& number, int N) {
    string firstHalf = number.substr(0, N);
    string secondHalf = number.substr(N, N);
    return sumDigits(firstHalf) == sumDigits(secondHalf);
}

int main() {
    ifstream inFile("input7.txt");
    ofstream outFile("OUTPUT.TXT");

    int N;
    string ticket;
    inFile >> N >> ticket;

    unordered_map<int, vector<string>> firstPartSequences, secondPartSequences;
    generateSequences(firstPartSequences, N, false);
    generateSequences(secondPartSequences, N, true);

    int minTickets = 0;
    bool found = false;

    // Начнем поиск счастливого билета
    while (!found) {
        if (isLucky(ticket, N)) {
            found = true;
            break;
        }
        // Инкремент номера билета
        int pos = 2 * N - 1;
        while (pos >= 0 && ticket[pos] == '9') {
            ticket[pos] = '0';
            --pos;
        }
        if (pos >= 0) {
            ticket[pos]++;
        }
        minTickets++;
    }

    outFile << minTickets << endl;

    inFile.close();
    outFile.close();

    return 0;
}
