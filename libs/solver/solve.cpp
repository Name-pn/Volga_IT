#include "solve.h"

const int MAP_SIZE = 10;

// Размерность матрицы на которой будет рисоваться путь Ивана
const int PROGRAM_MAP_SIZE = 30;

// Изначальное положение Ивана на большой карте
const int START_X = PROGRAM_MAP_SIZE / 2 - 1;
const int START_Y = PROGRAM_MAP_SIZE / 2 - 1;

// Пределы ходов
const int ELENA_LIM = 50;
const int IVAN_LIM = 1000;

// Точка на карте задается двумя координатами x и Y. x - столбец, y - строка
struct point {
    int x, y;

    point(int x = START_X, int y = START_Y) {
        this->x = x;
        this->y = y;
    }

    bool operator == (point b) {
        return this->x == b.x && this->y == b.y;
    }

    bool operator != (point b) {
        return !((*this) == b);
    }
};

// from пройденная ячейка, to ячейка доступная для прохождения и еще не пройденная
struct from_to_label {
    point from, to;
};

// Возвращает расстояние между двумя ячейками
long double distance(point a, point b) {
    point c;
    c.x = abs(a.x - b.x);
    c.y = abs(a.y - b.y);

    long double res = sqrt(c.x*c.x+c.y*c.y);
    return res;
}

// Возвращает направление от from к to
Direction say_dir(point from, point to) {
    int dif1 = from.x - to.x;
    int dif2 = from.y - to.y;
    int sum = abs(dif1) + abs(dif2);

    if (sum > 1 || sum < 1 || sum == 0) {
        std::cerr << "Ошибка определения направления, функция " << __FUNCTION__ << std::endl;
        exit(-1);
    }
    if (dif1 == 1)
        return Direction::Left;
    else if (dif1 == -1)
        return Direction::Right;
    else if (dif2 == 1)
        return Direction::Down;
    else if (dif2 == -1)
        return Direction::Up;
}

// Возвращает значение истинна, если new_p есть в way размера I
bool find(std::vector<point> &way, point new_p, int i) {
    for (int j = 0; j < i; ++j) {
        if (way[j] == new_p)
            return true;
    }
    return false;
}

bool is_movable_char(char c) {
    return c == '.' || c == '@' || c == '&';
}

// Возвращает ближайшую непосещенную точку
int near_point(std::vector<from_to_label> &vp, point &p) {
    long double min = distance(vp[0].from, p);
    int imin = 0;
    for (int i = 1; i < vp.size(); ++i) {
        if (min > distance(vp[i].from, p)) {
            min = distance(vp[i].from, p);
            imin = i;
        }
    }
    return imin;
}

// Возвращает ближайшую непосещенную точку
int near_point_to(std::vector<from_to_label> &vp, point &p) {
    long double min = distance(vp[0].to, p);
    int imin = 0;
    for (int i = 1; i < vp.size(); ++i) {
        if (min > distance(vp[i].to, p)) {
            min = distance(vp[i].to, p);
            imin = i;
        }
    }
    return imin;
}

template <typename T>
void vect_del(T &v, int i) {
    swap(v[i], v[v.size()-1]);
    v.resize(v.size()-1);
}

void vect_del_el(std::vector<from_to_label> &v, point a) {
    for (int i = 0; i < v.size(); ++i) {
        if (v[i].to == a)
            vect_del(v, i);
    }
}

// Возвращает путь из a в b по map. Пройденные точки записывает в way их число в i.
// Метод поиска с возращением
bool sup_find_way(point &a, point &b, matrix<char> &map, std::vector<point> &way, int &i) {
    bool finish = false;

    if (a == b)
        return true;
    else {
        std::vector<from_to_label> can_get(4);
        point new_p(a.x, a.y);
        can_get[3].from = can_get[2].from = can_get[1].from  =can_get[0].from = a;

        new_p.x = a.x-1;
        can_get[0].to = new_p;
        new_p.x += 2;
        can_get[1].to = new_p;
        new_p.x -= 1;
        new_p.y += 1;
        can_get[2].to = new_p;
        new_p.y -= 2;
        can_get[3].to = new_p;

        while (can_get.size()) {
            int k = near_point_to(can_get, b);

            new_p = can_get[k].to;

            if (is_movable_char(map[new_p.y][new_p.x]) && !(find(way, new_p, i))) {
                way[i] = new_p;
                ++i;
                finish = sup_find_way(new_p, b, map, way, i);
                if (finish)
                    return finish;
                --i;
            }
            vect_del_el(can_get, can_get[k].to);
        }


    }
    return finish;
}

// Возвращает путь из a в b по пройденным ячейкам map
std::vector <point> find_way(point &a, point &b, matrix<char> &map) {
    std::vector <point> way(1000);

    int i = 0;
    sup_find_way(a, b, map, way, i);
    way.resize(i);

    return way;
}

// Заменяет '\0' в map на '?'
void set_quation_sign(matrix<char> & map) {
    for (int i = 0; i < map.lines(); ++i) {
        for (int j = 0; j < map.columns(); ++j) {
            if (map[i][j] == '\0')
                map[i][j] = '?';
        }
    }
}

// Приводит матрицу к удобному для чтения виду
void matr_to_final_form(matrix<char> &map) {
    int i = 0;
    while (map.element_line(i, '\0')) {
        for (int j = 0; j < map.lines() - 1; ++j) {
            map[j] = map[j+1];
        }
        map.resize(map.lines()-1, map.columns());
    }

    while (map.element_column(i, '\0')) {
        for (int j = 0; j < map.columns() - 1; ++j) {
            map.column_cpy(j, j + 1);
        }
        map.resize(map.lines(), map.columns()-1);
    }

    i = map.lines() - 1;
    while (map.element_line(i, '\0')) {
        map.resize(map.lines() - 1, map.columns());
        i = map.lines() - 1;
    }

    i = map.columns() - 1;
    while (map.element_column(i, '\0')) {
        map.resize(map.lines(), map.columns()-1);
        i = map.columns() - 1;
    }

    if (map.columns() < 10 || map.lines() < 10)
        map.resize(10, 10);

    set_quation_sign(map);
    map = map.inverse_lines();
}

template <typename T>
void swap(T&a, T&b) {
    T tmp = a;
    a = b;
    b = tmp;
}

// Добавляет в a метки на неизвестные клетки из p
void add_new_points(point p, std::vector<from_to_label> &a, Direction dir, matrix<char> mx) {
    from_to_label tmp;
    tmp.from = p;
    if (dir == Direction::Left) {
        tmp.to.x = tmp.from.x -1;
        tmp.to.y = tmp.from.y;
        if (mx[tmp.to.y][tmp.to.x] == '\0')
            a.push_back(tmp);

        tmp.to.x = tmp.from.x;
        tmp.to.y = tmp.from.y-1;
        if (mx[tmp.to.y][tmp.to.x] == '\0')
            a.push_back(tmp);

        tmp.to.x = tmp.from.x;
        tmp.to.y = tmp.from.y+1;
        if (mx[tmp.to.y][tmp.to.x] == '\0')
            a.push_back(tmp);
    } else if (dir == Direction::Right) {
        tmp.to.x = tmp.from.x+1;
        tmp.to.y = tmp.from.y;
        if (mx[tmp.to.y][tmp.to.x] == '\0')
            a.push_back(tmp);

        tmp.to.x = tmp.from.x;
        tmp.to.y = tmp.from.y-1;
        if (mx[tmp.to.y][tmp.to.x] == '\0')
            a.push_back(tmp);

        tmp.to.x = tmp.from.x;
        tmp.to.y = tmp.from.y+1;
        if (mx[tmp.to.y][tmp.to.x] == '\0')
            a.push_back(tmp);
    } else if (dir == Direction::Up) {
        tmp.to.x = tmp.from.x+1;
        tmp.to.y = tmp.from.y;
        if (mx[tmp.to.y][tmp.to.x] == '\0')
            a.push_back(tmp);

        tmp.to.x = tmp.from.x - 1;
        tmp.to.y = tmp.from.y;
        if (mx[tmp.to.y][tmp.to.x] == '\0')
            a.push_back(tmp);

        tmp.to.x = tmp.from.x;
        tmp.to.y = tmp.from.y+1;
        if (mx[tmp.to.y][tmp.to.x] == '\0')
            a.push_back(tmp);
    } else if (dir == Direction::Down) {
        tmp.to.x = tmp.from.x+1;
        tmp.to.y = tmp.from.y;
        if (mx[tmp.to.y][tmp.to.x] == '\0')
            a.push_back(tmp);

        tmp.to.x = tmp.from.x - 1;
        tmp.to.y = tmp.from.y;
        if (mx[tmp.to.y][tmp.to.x] == '\0')
            a.push_back(tmp);

        tmp.to.x = tmp.from.x;
        tmp.to.y = tmp.from.y-1;
        if (mx[tmp.to.y][tmp.to.x] == '\0')
            a.push_back(tmp);
    }
    return;
}

class hero {
private:
    struct point p_h; // Клетка, где находится герой
    std::vector<from_to_label> possible_p; // Клетки доступные для посещения, но неизвестные
    matrix <char> map; // Карта
    Character name;
public:
    hero(Character name) {
        // Автоматическая инициализация p_h конструктором point
        map.resize(PROGRAM_MAP_SIZE, PROGRAM_MAP_SIZE);
        if (name == Character::Ivan)
            map[START_X][START_Y] = '@';
        else
            map[START_X][START_Y] = '&';
        from_to_label label;
        this->name = name;

        // Добавление клеток для посещения
        label.from = point();

        label.to = point(START_X-1, START_Y);
        possible_p.push_back(label);

        label.to = point(START_X+1, START_Y);
        possible_p.push_back(label);

        label.to = point(START_X, START_Y-1);
        possible_p.push_back(label);

        label.to = point(START_X, START_Y+1);
        possible_p.push_back(label);
    }

    // Перемещает героя в точку goal (goal уже посещенная точка)
    bool move_hero(point goal, Fairyland &fl) {
        std::vector <point> way = find_way(this->p_h, goal, this->map);

        for (int i = 0; i < way.size(); ++i) {
            Direction dir = say_dir(this->p_h, way[i]);
            if (this->name == Character::Ivan)
                fl.go(dir, Direction::Pass);
            else
                fl.go(Direction::Pass, dir);
            this->p_h = way[i];
        }
    }

    void set_wall(point &p, Fairyland &fl) {
        bool f = fl.canGo(name, Direction::Down);
        if (!f) {
            map[p.y-1][p.x] = '#';
            vect_del_el(this->possible_p, point(p.x, p.y-1));
        }

        f = fl.canGo(name, Direction::Left);
        if (!f) {
            map[p.y][p.x-1] = '#';
            vect_del_el(this->possible_p, point(p.x-1, p.y));
        }

        f = fl.canGo(name, Direction::Right);
        if (!f) {
            map[p.y][p.x + 1] = '#';
            vect_del_el(this->possible_p, point(p.x+1, p.y));
        }

        f = fl.canGo(name, Direction::Up);
        if (!f) {
            map[p.y+1][p.x] = '#';
            vect_del_el(this->possible_p, point(p.x, p.y+1));
        }
    }

    // Посещает одну неизвестную клетку, возвращает значение 1, если герои встретились, иначе возвращает 0
    bool explore_one(Fairyland &fl, bool &havent_vars, bool &lim_final, int limit) {
        bool meet = false;
        //std::cout << fl.getTurnCount() << std::endl; //для отладки
        if (fl.getTurnCount() < limit) {
            if (!this->possible_p.size()) {
                havent_vars = true;
                return false;
            }

            int unknow_point = near_point(this->possible_p, this->p_h);
            while (this->map[this->possible_p[unknow_point].to.y][this->possible_p[unknow_point].to.x] != '\0' && unknow_point < this->possible_p.size()) {
                vect_del_el(this->possible_p, this->possible_p[unknow_point].to);
                unknow_point = near_point(this->possible_p, this->p_h);
            }
            // Удалили точку, а на ее месте нет другой
            if (unknow_point >= this->possible_p.size()) {
                return false;
            }

            if (this->p_h != this->possible_p[unknow_point].from) {
                this->move_hero(this->possible_p[unknow_point].from, fl);
            }

            Direction dir = say_dir(this->p_h, this->possible_p[unknow_point].to);
            if (fl.canGo(this->name, dir)) {
                map[this->possible_p[unknow_point].to.y][this->possible_p[unknow_point].to.x] = '.';
                this->p_h = this->possible_p[unknow_point].to;
                if (this->name == Character::Ivan)
                    meet = fl.go(dir, Direction::Pass);
                else
                    meet = fl.go(Direction::Pass, dir);
                add_new_points(this->possible_p[unknow_point].to, this->possible_p, dir, map);
            } else {
                map[this->possible_p[unknow_point].to.y][this->possible_p[unknow_point].to.x] = '#';
            }
            vect_del_el(this->possible_p, this->possible_p[unknow_point].to);
            set_wall(this->p_h, fl);
            if (meet && this->name == Character::Ivan)
                map[this->p_h.y][this->p_h.x] = '&';
            if (meet && this->name == Character::Elena)
                map[this->p_h.y][this->p_h.x] = '@';

            //std::cout << map << std::endl; //для отладки
            return meet;
        } else {
            lim_final = true;
            return meet;
        }
    }

    inline matrix<char>& get_map() {
        return this->map;
    }
};

// Возвращает карту полученную героем в процессе поиска, записывает тип конца в final_type
// а числе понадобившихся шагов в steps
matrix<char> solve(int &steps, int& final_type) {
    Fairyland world;

    hero hero_two(Character::Ivan);
    matrix<char> map;

    bool good_finish = false;
    bool bad_finish = false;
    bool limit_finish = false;

    while (!good_finish && !bad_finish && !limit_finish) {
        good_finish = hero_two.explore_one(world, bad_finish, limit_finish, IVAN_LIM);
    }

    matr_to_final_form(hero_two.get_map());

    steps = world.getTurnCount();

    if (good_finish) {
        final_type = THEY_FIND;
        return hero_two.get_map();
    }
    else if (bad_finish) {
        final_type = THEY_CANT_FIND;
        return hero_two.get_map();
    } else if (limit_finish) {
        final_type = LIMIT_EXCEEDED;
        return hero_two.get_map();
    }

    return hero_two.get_map();

}