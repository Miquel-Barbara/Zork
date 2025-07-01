#include "Stat.h"



StatValue::StatValue(int base, int min, int max) {
	value = base;
	minValue = min;
	maxValue = max;
}

int StatValue::Get() {
	return value;
}

int StatValue::Clamp(int value) const {
	if (value < minValue) {
		return minValue;
	} else if (value > maxValue) {
		return maxValue;
	}
	return value;
}

void StatValue::Set(int value) {
	this->value = Clamp(value);
}

void StatValue::Increase(int amount) {
	value = Clamp(value + amount);
}

void StatValue::Decrease(int amount) {
	value = Clamp(value - amount);
}

