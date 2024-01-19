#include <iostream>

class Date
{
private:
    int year{1960};
    int month{1};
    int day{1};
    int hour{0};
    int minute{0};
    int seconds{0};
    bool isOurEra{true};

public:
    Date(int y, int m, int d, int h, int min, int sec, bool e) : year(y), month(m), day(d), hour(h), minute(min), seconds(sec), isOurEra(e)
    {
        if (!isOurEra)
            year = (year == 0) ? -1 : -year;
    }

    static bool isLeapYear(int year)
    {
        return (abs(year) % 4 == 0) && ((abs(year) % 100 != 0) || (abs(year) % 400 == 0));
    }

    static int DaysInMonth(int year, int month)
    {
        switch (month)
        {
        case 4:
        case 6:
        case 9:
        case 11:
            return 30;
        case 2:
            return (isLeapYear(year) ? 29 : 28);
        default:
            return 31;
        }
    }

    Date operator+(const Date &other) const
    {
        Date result = *this;
        result.seconds += other.seconds + 60 * (result.seconds >= 60);
        result.minute += other.minute + 60 * (result.minute >= 60);
        result.hour += other.hour + 24 * (result.hour >= 24);
        result.day += other.day;
        while (result.day > DaysInMonth(result.year, result.month))
        {
            result.day -= DaysInMonth(result.year, result.month);
            result.month++;
            if (result.month > 12)
                result.month = 1, result.year++;
        }
        result.month += other.month + 12 * (result.month > 12);
        result.year += other.year;
        result.isOurEra = (result.year >= 0);
        if (!result.isOurEra)
            result.year = -result.year;
        return result;
    }

    Date &operator+=(const Date &other)
    {
        *this = *this + other;
        return *this;
    }

    Date operator-(const Date &other) const
    {
        Date result = *this;
        result.seconds -= other.seconds - 60 * (result.seconds < 0);
        result.minute -= other.minute - 60 * (result.minute < 0);
        result.hour -= other.hour - 24 * (result.hour < 0);
        result.day -= other.day;
        while (result.day <= 0)
        {
            if (--result.month <= 0)
                result.month += 12, result.year--;
            result.day += DaysInMonth(result.year, result.month);
        }
        result.month -= other.month - 12 * (result.month > 12);
        result.year -= other.year;
        result.isOurEra = (result.year >= 0);
        if (!result.isOurEra)
            result.year = -result.year;
        return result;
    }

    Date &operator-=(const Date &other)
    {
        *this = *this - other;
        return *this;
    }

    Date &operator=(const Date &other)
    {
        year = other.year;
        month = other.month;
        day = other.day;
        hour = other.hour;
        minute = other.minute;
        seconds = other.seconds;
        isOurEra = other.isOurEra;

        return *this;
    }

    bool operator<(const Date &other) const
    {
        return std::tie(year, month, day, hour, minute, seconds) < std::tie(other.year, other.month, other.day, other.hour, other.minute, other.seconds);
    }

    bool operator>(const Date &other) const
    {
        return std::tie(year, month, day, hour, minute, seconds) > std::tie(other.year, other.month, other.day, other.hour, other.minute, other.seconds);
    }

    bool operator==(const Date &other) const
    {
        return std::tie(year, month, day, hour, minute, seconds, isOurEra) == std::tie(other.year, other.month, other.day, other.hour, other.minute, other.seconds, other.isOurEra);
    }

    friend std::ostream &operator<<(std::ostream &out, const Date &date)
    {
        out << "Год: " << date.year << ", Месяц: " << date.month << ", День: " << date.day
            << " Час: " << date.hour << ", Минута: " << date.minute << ", Секунда: " << date.seconds << (date.isOurEra ? " Наша эра" : " До нашей эры");
        return out;
    }

    Date add(unsigned y, unsigned short m, unsigned short d,
             unsigned short h, unsigned short min, unsigned short s, bool era)
    {
        return *this + Date(y, m, d, h, min, s, era);
    }

    Date subtract(unsigned y, unsigned short m, unsigned short d,
                  unsigned short h, unsigned short min, unsigned short s, bool era)
    {
        return *this - Date(y, m, d, h, min, s, era);
    }

    Date() = default;
};

int main()
{
    Date date1(2001, 2, 29, 0, 0, 0, 1);
    Date date2(4000, 0, 0, 0, 0, 0, 1);

    std::cout << date1 + date2 << std::endl;

    return 0;
}
