#include "libs/task/fairy_tail.hpp"
#include "libs/solver/solve.h"

#include <windows.h>
#include <fstream>
const char f_output_name[] = "output.txt";

void write_file(matrix<char> &tmp, int final_type, int steps, std::ostream &out) {
    if (final_type == THEY_FIND) {
        out << "Герои нашли друг-друга\n";
        out << "Карта полученная одним из героев в ходе поиска:\n";
        out << tmp;

    } else if (final_type == THEY_CANT_FIND) {
        out << "Герои не могут найти друг-друга из-за препятствий\n";
        out << "Карта полученная одним из героев в ходе поиска:\n";
        out << tmp;
    } else if (final_type == LIMIT_EXCEEDED) {
        out << "Ходы истекли. Герои не нашли друг-друга и не проверили все клетки\n";
        out << "Карта полученная одним из героев в ходе поиска:\n";
        out << tmp;
    }

    out << "Число ходов потраченных на поиск\n";
    out << steps << '\n';
}

int main()
{
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    int steps, final_type;

    matrix<char> tmp = solve(steps, final_type);


    write_file(tmp, final_type, steps, std::cout);

    std::cout << "Произвожу записть результата решения в файл\n";

    write_file(tmp, final_type, steps, std::cout);

    std::fstream f(f_output_name, std::ios::out);

    write_file(tmp, final_type, steps, f);

    f.close();

    getchar();
    return 0;
}
