// 15.5. Монеты(7)
// Однокопеечные монетки разложены в N стопок (1 ≤ N ≤ 100). В стопках может быть 
// различное количество монет, а стопки поставлены на столе в ряд слева направо. 
// Двое противников по очереди делают ходы. Ход состоит в том, что один из игроков 
// берет слева несколько стопок подряд, не меньше одной, но и не больше, чем перед 
// этим взял его соперник. Первый игрок своим первым ходом берет не более К стопок 
// (1 ≤ K ≤ 80). Игра заканчивается, когда стопок не остается.
// Требуется найти максимальное число монет, которое может получить первый участник 
// после окончания игры, если второй игрок тоже старается ходить так, чтобы получить 
// как можно больше монет.
// Ввод из файла INPUT.TXT. В первой строке находятся числа стопок N и К через пробел. 
// Во второй строке идут через пробел N чисел, задающих количество монет в стопках слева направо.
// Количество монет в каждой стопке не превышает 1000.
// Вывод в файл OUTPUT.TXT. Вывести одно число - максимальное количество монет, 
// которое заведомо может получить первый игрок, как бы ни играл второй.

//Visual Studio Code

//Гусев Сергей ПС-22

#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>

int count;
std::vector<int> stack;
std::vector<std::vector<int> > newStack;

int maxCoin(int j, int r, int i);

int sum(int i) {
    return (i >= count) ? 0 : stack[i] + sum(i + 1);
}

int takeMaxCoin(int k, int i) {
    if (newStack[k][i] == 0) {
        newStack[k][i] = maxCoin(std::min(k, count - i), 0, i);
    }
    return newStack[k][i];
}

int maxCoin(int j, int r, int i) {
    return j <= 0 ? r : maxCoin(j - 1, std::max(r, sum(i) - takeMaxCoin(j, i + j)), i);
}

int main() {
    std::ifstream inFile("input5.txt");
    std::ofstream outFile("OUTPUT.TXT");
    
    int firstStep;
    inFile >> count >> firstStep;
    
    stack.resize(count);
    newStack.resize(count + 1, std::vector<int>(count + 1, 0));

    for (int i = 0; i < count; ++i) {
        inFile >> stack[i];
    }
    outFile << takeMaxCoin(firstStep, 0) << std::endl;

    return 0;
}