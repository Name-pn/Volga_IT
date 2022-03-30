#include <iostream>
#include <vector>
#include <iomanip>
#include "matrix.h"

const int MATR_OUTPUT_CHARS = 1;

/*
 * \brief Класс матрица, над которой определены алгебраические операции
 *
 * \details Данный класс поддерживает такие операции как: сумма матриц, разность, произведение матрицы на матрицу и число, а также вычисление определителя
 * квадратной матрицы и получение обратной матрицы. Часть методов и перегрузок операторов в классе выполняют одно и тоже действие.
 */

template <typename T>
matrix<T>::matrix(void) {
    n = 0;
    m = 0;
}

template <typename T>
matrix<T>::~matrix() {;}

template <typename T>
matrix<T>::matrix(long long m) {
    try {
        if (m < 1)
            throw "Ошибка данных. Попытка определения некорректного размера матрицы\n";
    }
    catch (std::exception a) {
        std::cout << a.what();
        exit(-1);
    }
    this->m = m;
    this->n = m;
    mas.resize(m);
    for (size_t i = 0; i < m; i++) {
        mas[i].resize(n);
    }
}

template<class T>
matrix<T>::matrix(long long m, long long n) {
    try {
        if (m < 1 || n < 1)
            throw "Ошибка данных. Попытка определения некорректного размера матрицы\n";
    }
    catch (std::exception a) {
        std::cout << a.what();
        exit(-1);
    }
    this->m = m;
    this->n = n;
    mas.resize(m);
    for (size_t i = 0; i < m; i++) {
        mas[i].resize(n);
    }
}

template <typename T>
void matrix<T>::read_matr (void){
    for (size_t i = 0; i < this->lines(); i++) {
        for (size_t j = 0; j < this->n; j++) {
            std::cin >> (*this)[i][j];
        }
    }
}

template <typename T>
inline long long matrix<T>::lines(void) {
    return(m);
}

template <typename T>
inline void matrix<T>::set_lines(long long m) {
    try {
        if (m < 0)
            throw "Ошибка данных. Попытка определения некорректного размера матрицы\n";
    }
    catch (char const * a) {
        std::cout << a;
        exit(-1);
    }
    this -> m = m;
    this->mas.resize(m);
    for (size_t i = 0; i < this->m; i++) {
        this->mas[i].resize(this->n);
    }

}

template <typename T>
inline long long matrix<T>::columns(void) {
    return(n);
}

template <typename T>
inline void matrix<T>::set_columns(long long n) {
    try {
        if (n < 0)
            throw "Ошибка данных. Попытка определения некорректного размера матрицы\n";
    }
    catch (std::exception a) {
        std::cout << a.what();
        exit(-1);
    }
    this->n = n;
    for (size_t i = 0; i < this->m; i++) {
        this->mas[i].resize(this->n);
    }
}

template <typename T>
inline long double matrix<T>::at(long long i, long long j) {
    try {
        if (i < 0 || i > this->m-1 || j < 0 || j > this->n-1)
            throw "Логическая ошибка. Попытка обращения по некорректному индексу\n";
    }
    catch (char const * a) {
        std::cout << a;
        exit(-1);
    }
    return(mas[i][j]);
}

template <typename T>
matrix<T> matrix<T>::transpose(void) {
    matrix b(n, m);
    for (size_t i = 0; i < m; i++) {
        for (size_t j = 0; j < n; j++) {
            b.mas[j][i] = mas[i][j];
        }
    }
    return (b);
}

template <typename T>
matrix<T> matrix<T>::turn_90() {
    matrix b(n, m);
    b = (*this);
    b = b.transpose();
    b = b.inverse_columns();
    return (b);
}

template <typename T>
matrix<T> matrix<T>::inverse_columns() {
    matrix b(m, n);
    for (size_t i = 0; i < m; i++) {
        for (size_t j = 0; j < n; j++) {
            b.mas[i][j] = mas[i][b.n - j - 1];
        }
    }
    return (b);
}

template <typename T>
matrix<T> matrix<T>::inverse_lines() {
    matrix b(m, n);
    for (size_t i = 0; i < m; i++) {
        for (size_t j = 0; j < n; j++) {
            b.mas[i][j] = mas[b.m-i-1][j];
        }
    }
    return (b);
}

template <typename T>
std::vector <T> & matrix<T>::operator [] (size_t i) {
    try {
        if (i < 0 || i > this->m - 1)
            throw "Логическая ошибка. Попытка обращения по некорректному индексу\n";
    }
    catch (char const* s) {
        std::cout << s;
        exit(-1);
    }
    return(mas[i]);
}

template<typename T>
std::istream& operator >> (std::istream& in, matrix<T>& a) {
    if (a.m == 0 || a.n == 0) {
        in >> a.m >> a.n;
        a.mas.resize(a.m);
        for (size_t i = 0; i < a.m; i++) {
            a.mas[i].resize(a.n);
        }
    }
    for (size_t i = 0; i < a.m; i++) {
        for (size_t j = 0; j < a.n; j++) {
            in >> a.mas[i][j];
        }
    }
    return(in);
}

template <typename T>
inline std::vector<std::vector<T>> &matrix<T>::matr(void) {
    return this->mas;
}

template <typename T>
std::ostream& operator << (std::ostream& out, matrix<T> a) {
    std::string top = "";
    int ind = a.columns() * MATR_OUTPUT_CHARS + a.columns() - 1;
    for (int i = 0; i < ind; ++i) {
        top += "";
    }
    top += "";
    std::cout << top;
    for (size_t i = 0; i < a.m; i++) {
        std::cout << "";
        for (size_t j = 0; j < a.n; j++) {
            out << std::setw(MATR_OUTPUT_CHARS) << a.mas[i][j] << "";
        }
        out << "\n";
    }
    std::string bottom = "";
    for (int i = 0; i < ind; ++i) {
        bottom += "";
    }
    bottom += "";
    std::cout << bottom;
    return(out);
}

template<typename T>
bool operator == (matrix<T>& a, matrix<T>& b) {
    if (a.columns() != b.columns() || a.lines() != b.lines())
        return false;
    for (int i = 0; i < a.lines(); ++i) {
        for (int j = 0; j < a.columns(); ++j) {
            if (a[i][j] != b[i][j])
                return false;
        }
    }
    return true;
}

template<typename T>
bool operator != (matrix<T>& a, matrix<T>& b) {
    return !(a == b);
}

template <typename T>
void matrix<T>::resize(long long m, long long n) {
    this->set_lines(m);
    this->set_columns(n);
}

template <typename T>
bool matrix<T>::element_column(int j, T el) {
    for (int i = 0; i < this->lines(); ++i) {
        if ((*this)[i][j] != el)
            return false;
    }
    return true;
}

template <typename T>
bool matrix<T>::element_line(int i, T el) {
    for (int j = 0; j < this->columns(); ++j) {
        if ((*this)[i][j] != el)
            return false;
    }
    return true;
}

template <typename T>
void matrix<T>::column_cpy(int des, int source) {
    for (int i = 0; i < this->lines(); ++i) {
        (*this)[i][des] = (*this)[i][source];
    }
}

// Истанцирование
template class matrix<char>;
template std::ostream& operator << (std::ostream& out, matrix<char> a);
template std::istream& operator >> (std::istream& in, matrix<char>& a);
