#ifndef VALUEPROCESSOR_H
#define VALUEPROCESSOR_H

#include <vector>
#include <numeric>

/**
 * @brief Szablon klasy do prostego przetwarzania danych.
 *
 * Umożliwia dodawanie wartości i obliczanie średniej.
 * Może być użyty do analizy danych z czujników.
 */
template <typename T>
class ValueProcessor {
public:
    void addValue(T value) {
        values.push_back(value);
    }

    T average() const {
        if (values.empty()) return T();
        T sum = std::accumulate(values.begin(), values.end(), T());
        return sum / static_cast<T>(values.size());
    }

    void clear() {
        values.clear();
    }

    std::size_t count() const {
        return values.size();
    }

private:
    std::vector<T> values;
};

#endif // VALUEPROCESSOR_H
