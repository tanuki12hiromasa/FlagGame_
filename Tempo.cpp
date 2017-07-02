#include "Tempo.h"
#include <chrono>
using namespace std::chrono_literals;

Tempo::Tempo()
{
    bpm = 80;
    std::chrono::milliseconds time_per_beat = (60000ms / bpm);
    std::chrono::milliseconds time_per_bar = time_per_beat * 4;
    int_time_per_beat = time_per_beat.count();
    int_time_per_ber = time_per_bar.count();
    time_base = std::chrono::system_clock::now();
}

Tempo::~Tempo()
{
}

void Tempo::start() {
    time_base = std::chrono::system_clock::now();
}

void Tempo::set_tempo(int _bpm, int _beat) {
    bpm = _bpm;
    std::chrono::milliseconds time_per_beat = (60000ms / bpm);
    std::chrono::milliseconds time_per_bar = time_per_beat * _beat;
    int_time_per_beat = time_per_beat.count();
    int_time_per_ber = time_per_bar.count();
	start();
}

double Tempo::get_current() {
    std::chrono::system_clock::time_point now = system_clock::now();
    system_clock::duration diff = now - time_base;
    std::chrono::milliseconds m_diff = std::chrono::duration_cast<std::chrono::milliseconds>(diff);
    long long int_m_diff = m_diff.count();
    return (double)(int_m_diff % int_time_per_ber) / int_time_per_beat;
}

int Tempo::get_ber_current() {
	std::chrono::system_clock::time_point now = system_clock::now();
	system_clock::duration diff = now - time_base;
	std::chrono::milliseconds m_diff = std::chrono::duration_cast<std::chrono::milliseconds>(diff);
	long long int_m_diff = m_diff.count();
	return (int)(int_m_diff / int_time_per_ber);
}