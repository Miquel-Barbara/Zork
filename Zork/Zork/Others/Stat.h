#ifndef __Stat__
#define __Stat__

#include <string>

class StatValue {
public:
    StatValue(int base, int min = 0, int max = 100);

    int Get();
    void Set(int value);

    void Increase(int amount);
    void Decrease(int amount);

    int Clamp(int value) const;

private:
    int value;
	int minValue;
	int maxValue;
};


#endif

