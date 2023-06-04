#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cmath>

// Class time
// ===================================================================

struct Time {
    int hours;
    int minutes;
    bool operator< (const Time& second_time) const;
    bool operator== (const Time& second_time) const;
    bool operator<= (const Time& second_time) const;
};

bool Time::operator<(const Time& second_time) const {
    if (hours < second_time.hours)
        return true;
    if (hours == second_time.hours)
        return minutes < second_time.minutes;

    return false;
}

bool Time::operator==(const Time& second_time) const {
    return (hours == second_time.hours) && (minutes == second_time.minutes);
}

bool Time::operator<=(const Time& second_time) const {
    return (*this < second_time) || (*this == second_time);
}

std::ostream& operator<< (std::ostream& out, const Time& time) {
    out << time.hours;
    if (time.minutes) {
        out << '.' << time.minutes;
    }

    return out;
}

int str_to_int(const std::string& str) {
    int res = 0;
    int power = 0;
    for (int i = str.length() - 1; i >= 0; --i) {
        res += (str[i] - '0') * std::pow(10, power);
        power++;
    }

    return res;
}

std::istream& operator>> (std::istream& in, Time& time) {
    std::string time_str;
    in >> time_str;
    std::string hours_str, minutes_str;
    int i = 0;
    for (i; i < time_str.length(); ++i) {
        if (time_str[i] == '.') {
            break;
        } else {
            hours_str += time_str[i];
        }
    }
    i = i + 1;
    for (i; i < time_str.length(); ++i) {
        minutes_str += time_str[i];
    }

    time.hours = str_to_int(hours_str);
    time.minutes = str_to_int(minutes_str);

    return in;
}

// ======================================================================

// Class event
// ======================================================================

struct Event {
    Time begin;
    Time end;
    bool operator<(const Event& second_event) const;
};

bool Event::operator<(const Event& second_event) const {
    if (end < second_event.end)
        return true;
    if (end == second_event.end)
        if (begin < second_event.begin)
            return true;
        
    return false;
}

// =======================================================================

auto make_best_timetable(std::vector<Event>& timetable) {
    std::sort(timetable.begin(), timetable.end());
    
    std::vector<Event> best_timetable;
    Time cur_time = {0,0};
    for (const auto& event : timetable) {
        if (cur_time <= event.begin) {
            best_timetable.push_back(event);
            cur_time = event.end;
        }
    }

    return best_timetable;
}

int main() {
    std::ifstream in;
    std::ofstream out;

    in.open("input.txt");
    out.open("output.txt");

    int n;
    in >> n;

    std::vector<Event> timetable (n);
    for (auto& event : timetable) {
        in >> event.begin >> event.end;
    }

    auto best_timetable = make_best_timetable(timetable);

    out << best_timetable.size() << std::endl;
    for (const auto& event : best_timetable) {
        out << event.begin << " " << event.end << std::endl;
    }

    in.close();
    out.close();
}