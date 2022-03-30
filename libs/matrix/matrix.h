#ifndef INC_MATRIX_H
#define INC_MATRIX_H

#include <iostream>
#include <vector>

template<typename T>
class matrix;

///Чтение матрицы
template <typename T>
std::istream& operator >> (std::istream& in, matrix<T>& a);
//Вывод матрицы
template <typename T>
std::ostream& operator << (std::ostream& out, matrix<T> a);

template <typename T>
bool operator == (matrix<T> &a, matrix<T> &b);
template <typename T>
bool operator != (matrix<T> &a, matrix<T> &b);

template <typename T>
class matrix {
protected:
    long long n, m; ///< Переменные размерности матрицы
    std::vector <std::vector<T>> mas; ///< Матрица

public:

    /**
     * \brief Конструктор пустой матрицы.
     */
    matrix(void);
    ~matrix();
    /**
     * \brief Конструктор квадратной матрицы.
     * \param[in] m Размер квадратной матрицы
     */
    matrix(long long m);
    /**
     * \brief Конструктор произвольной матрицы.
     * \param[in] m Число строк матрицы.
     * \param[in] n Число столбцов матрицы.
     */
    matrix(long long m, long long n);
    ///Изменить размер матрицы на m и n
    void resize(long long m, long long n);
    /**
     * \brief Метод чтение матрицы со стандартного потока.
     */
    void read_matr();

    inline std::vector<std::vector<T>> &matr(void);

    //Работа с полями
    ///\brief Метод, возвращающий число строк в матрице.
    inline long long lines(void);
    ///\brief Метод, возвращающий число столбцов в матрице.
    inline long long columns(void);
    ///\brief Метод, устанавливающий число строк в матрице.
    inline void set_lines(long long m);
    ///\brief Метод, устанавливающий число столбцов в матрице.
    inline void set_columns(long long n);
    ///\brief Метод получения элемента матрицы по индексам i и j.
    inline long double at(long long i, long long j);
    matrix transpose(void); // Транспонирование
    matrix turn_90(); // Поворот матрицы на 90 градусов
    matrix inverse_columns(); // Инверсия матрицы по горизонтали
    matrix inverse_lines(); // Инверсия матрицы по горизонтали

    /// <summary>
    /// Вывод матрицы
    /// </summary>
    /// <param name="out"></param>
    /// <param name="a"></param>
    /// <returns>Поток вывода</returns>
    friend std::ostream& operator << <T>(std::ostream& out, matrix a);

    ///Чтение матрицы
    friend std::istream& operator >> <T>(std::istream& in, matrix& a);

    ///Сравнение матриц
    friend bool operator == <T>(matrix& a, matrix& b);
    friend bool operator != <T>(matrix& a, matrix& b);

//Перегруженный операторы
///Возвращает строку матрицы
    std::vector <T> &operator [] (size_t i);

    /// Возвращает значение истинна, если j столбец заполнен el
    bool element_column(int j, T el);

    /// Возвращает значение истинна, если i строка заполнена el
    bool element_line(int i, T el);

    /// Копирует столбец source в des
    void column_cpy(int des, int source);
};

#endif //INC_MATRIX_H