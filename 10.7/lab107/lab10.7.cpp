// 10.7. Симпсон Гомер (10)
// Гомер Симпсон пожертвовал N долларов на распространение дисков с фильмами о себе.
// Имеется 3 вида дисков, которые продаются по ценам С1, С2 и С3 долларов. Требуется
// купить как можно больше дисков так, чтобы осталась неизрасходованной как можно меньшая сумма денег.
// Ввод из файла INPUT.TXT. В первой строке задается значение N (1 ≤ N ≤ 2×10^9).
// Во второй строке С1, С2 и С3 через пробел (1 ≤ C1, C2, C3 ≤ 2×10^9). Все числа целые.
// Вывод в файл OUTPUT.TXT. В первой строке вывести общее количество покупаемых дисков.
// Во второй строке выводится остаток средств. В третьей строке через пробел выводится
// число покупаемых дисков каждого вида соответственно.
// Рассмотреть случаи Min(C1, C2, C3) ≤ 10^6 и Min(C1, C2, C3) > 10^6
//CLion

//Гусев Сергей ПС-22

#include <iostream>
#include <fstream>
#include <algorithm>

void check_and_update(long long x, long long y, long long z, long long remaining_after_z,
                      long long& max_disks, long long& remaining_money,
                      long long& best_x, long long& best_y, long long& best_z) {
    long long total_disks = x + y + z;
    if (total_disks > max_disks || (total_disks == max_disks && remaining_after_z < remaining_money)) {
        max_disks = total_disks;
        remaining_money = remaining_after_z;
        best_x = x;
        best_y = y;
        best_z = z;
    }
}

int main() {
    std::ifstream in("INPUT.TXT");
    std::ofstream out("OUTPUT.TXT");

    long long N, C1, C2, C3;
    in >> N >> C1 >> C2 >> C3;

    long long max_disks = 0;
    long long remaining_money = N;
    long long best_x = 0;
    long long best_y = 0;
    long long best_z = 0;

    for (long long x = 0; x <= N / C1; ++x) {
        long long remaining_after_x = N - x * C1;

        for (long long y = 0; y <= remaining_after_x / C2; ++y) {
            long long remaining_after_y = remaining_after_x - y * C2;

            long long z = remaining_after_y / C3;
            long long remaining_after_z = remaining_after_y - z * C3;

            check_and_update(x, y, z, remaining_after_z, max_disks, remaining_money, best_x, best_y, best_z);

            if (y > 0) {
                y--;
                remaining_after_y += C2;
                z = remaining_after_y / C3;
                remaining_after_z = remaining_after_y - z * C3;

                check_and_update(x, y, z, remaining_after_z, max_disks, remaining_money, best_x, best_y, best_z);
            }
        }
    }

    out << max_disks << '\n' << remaining_money << '\n';
    out << best_x << ' ' << best_y << ' ' << best_z << '\n';

    return 0;
}
