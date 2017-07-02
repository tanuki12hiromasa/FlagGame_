#pragma once
#include<chrono>
using std::chrono::system_clock;
class Tempo
{
public:
    Tempo();
    ~Tempo();
    double get_current();
	int get_ber_current();
    void start();
    void set_tempo(int _bpm, int _beat);
private:
    int bpm;
    system_clock::time_point time_base;
    long long int_time_per_beat;
    long long int_time_per_ber;
};

