#pragma once

using namespace std;

class Data {
private:
  int day, month, year;

public:
  Data(int day=1, int month=1, int year=2023) {
    this->day = day;
    this->month = month;
    this->year = year;
  }

  int getDay() {
    return this->day;
  }
  int getMonth() {
    return this->month;
  }
  int getYear() {
    return this->year;
  }
};