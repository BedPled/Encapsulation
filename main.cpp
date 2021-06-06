#include <iostream>
#include <stdexcept>

using namespace std;
//1. Продемонстрировать различные уровни инкапсуляции данных (указать комментарием):
//    + a. Отсутствие инкапсуляции (public свойства)
//    + b. Инкапсуляция с помощью set/get
//    + c. Инкапсуляция с помощью специализированных протоколов/методов
//    + d. Инкапсуляция за счёт абстракций
//
//p.s. использовать механизмы исключений, если нарушается инвариант или не соблюдаются пост/пред-условия
//
//2. Продемонстрировать различные варианты инкапсуляции поведения
//      + a. За счёт позднего связывания
//      + b. Замена поведения (тут тоже используется позднее связывание)
//      + c. Расширения поведения (тут тоже используется позднее связывание)

class data_a { /* a. Отсутствие инкапсуляции (public свойства) */
public:
    int day;
    int month;
    int year;
};

class data_b { /* b. Инкапсуляция с помощью set/get */
private:
    int day;
    int month;
    int year;
public:
    int getDay() const {
        return day;
    }

    int getMonth() const {
        return month;
    }

    int getYear() const {
        return year;
    }

    void setDay(int day) {
        if (day <= 0 || day > 31) {
            throw logic_error("Некорректный день");
        }
        this->day = day;
    }

    void setMonth(int month) {
        if (day <= 0 || day > 12) {
            throw logic_error("Некорректный месяц");
        }
        this->month = month;
    }

    void setYear(int year) {
        if ( year <= 0 ) {
            throw logic_error("Отрицательный год");
        }
        this->year = year;
    }
};

class data_c { /* c. Инкапсуляция с помощью специализированных протоколов/методов */
private:
    int day = 0;
    int month = 0;
    int year = 0;

public:
    void incData () {
        day++;
        if (day > 30) {
            day = 0;
            month++;
            if (month > 12) {
                month = 0;
                year++;
            }
        }
    }

    void getData () {
        cout << "Насчитано " << day << " дней " << month << " месяцев "  << year << " лет "  << endl;
    };
};


/* d. Инкапсуляция за счёт абстракций */
class IClock {
protected:
    int hour;
    int minute;
public:
    virtual void time () = 0;

    void setHour(int hour) {
        IClock::hour = hour;
    }

    void setMinute(int minute) {
        IClock::minute = minute;
    }
};

// a. За счёт позднего связывания
void printTime (IClock *p) {
    p->time();
    cout << endl;
}

class clock24 : public IClock {
public:
    virtual void time () {
        if (minute < 10) {
            cout << hour << ":0" << minute;
        } else {
            cout << hour << ":" << minute;
        }
    }
};

class clock12 : public IClock {
public:
    bool midday;
    virtual void time () { // c. Расширения поведения
         if (midday) {
             if (minute < 10) {
                cout << hour << ":0" << minute << " AM";
             } else {
                 cout << hour << ":" << minute << " AM";
             }
         } else {
             if (minute < 10) {
                 cout << hour << ":0" << minute << " PM";
             } else {
                 cout << hour << ":" << minute << " PM";
             }
         }
    }
};

class timerClock : public IClock { // b. Замена поведения
public:
    virtual void time () {
        minute++;
        if (minute >= 60) {
            minute = 0;
            hour++;
        }
        if (minute < 10) {
            cout << hour << ":0" << minute;
        } else {
            cout << hour << ":" << minute;
        }
    }

};




int main() {

    data_a a;
    /* a. Отсутствие инкапсуляции (public свойства) */
    a.day = 32;
    a.month = 13;
    a.year = -1;

    data_b b;
    /* b. Инкапсуляция с помощью set/get */
    try {
        b.setDay(32);
    } catch (logic_error err) {
        cout << err.what() << endl;
    }

    try {
        b.setMonth(13);
    } catch (logic_error err) {
        cout << err.what() << endl;
    }

    try {
        b.setYear(-2);
    } catch (logic_error err) {
        cout << err.what() << endl;
    }

    /* c. Инкапсуляция с помощью специализированных протоколов/методов */
    data_c c;
    for (int i = 0; i < 1000; ++i) {
        c.incData();
    }
    c.getData();


    clock12 a12;
    a12.midday = false;
    a12.setHour(11);
    a12.setMinute(24);

    clock24 a24;
    a24.setHour(23);
    a24.setMinute(24);

    printTime(&a12);
    printTime(&a24);


    //b. Замена поведения
    timerClock abc;
    abc.setMinute(0);
    abc.setHour(0);

    printTime(&abc);


    return 0;
}



