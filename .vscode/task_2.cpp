#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <stdexcept>
#include <iomanip> // for std::setprecision

using namespace std;

// Template function for average calculation
template <typename T>
T calculateAverage(T* arr, int size) {
    if (size == 0) throw runtime_error("Division by zero: No readings available.");
    T sum = 0;
    for (int i = 0; i < size; ++i)
        sum += arr[i];
    return sum / size;
}

class WeatherStation {
private:
    string location;
    float* readings;
    int capacity;
    int count;

    void resize() {
        int newCapacity = capacity * 2;
        float* newReadings = new float[newCapacity];
        for (int i = 0; i < count; ++i)
            newReadings[i] = readings[i];
        delete[] readings;
        readings = newReadings;
        capacity = newCapacity;
    }

public:
    WeatherStation(string loc, int initialCapacity = 5)
        : location(loc), capacity(initialCapacity), count(0) {
        readings = new float[capacity];
    }

    ~WeatherStation() {
        delete[] readings;
    }

    void addReading(float value) {
        if (count == capacity)
            resize();
        readings[count++] = value;
    }

    void printReadings() {
        cout << "Location: " << location << endl;
        cout << "Readings: ";
        for (int i = 0; i < count; ++i)
            cout << readings[i] << " ";
        cout << endl;
        try {
            float avg = calculateAverage(readings, count);
            cout << "Average: " << fixed << setprecision(2) << avg << endl;
        } catch (runtime_error& e) {
            cout << e.what() << endl;
        }

        // Count readings above 25°C using STL
        int aboveThreshold = count_if(readings, readings + count, [](float r){ return r > 25.0; });
        cout << "Readings above 25°C: " << aboveThreshold << endl;
    }

    void saveToFile(string filename) {
        try {
            ofstream outFile(filename);
            if (!outFile) throw runtime_error("Error opening file for writing.");
            outFile << location << endl;
            for (int i = 0; i < count; ++i)
                outFile << readings[i] << " ";
            outFile.close();
            cout << "Saved to file: " << filename << endl;
        } catch (runtime_error& e) {
            cerr << e.what() << endl;
        }
    }

    // Static function to load from a file
    static WeatherStation loadFromFile(string filename) {
        try {
            ifstream inFile(filename);
            if (!inFile) throw runtime_error("Error opening file for reading.");
            string loc;
            getline(inFile, loc);

            WeatherStation ws(loc);
            float value;
            while (inFile >> value)
                ws.addReading(value);

            inFile.close();
            return ws;
        } catch (runtime_error& e) {
            cerr << e.what() << endl;
            throw;
        }
    }

    void sortReadings() {
        sort(readings, readings + count);
    }
};

int main() {
    WeatherStation lahti("Lahti");

    // Add some readings
    lahti.addReading(22.5);
    lahti.addReading(24.0);
    lahti.addReading(26.3);
    lahti.addReading(21.8);
    lahti.addReading(25.7);

    lahti.sortReadings();
    lahti.printReadings();
    lahti.saveToFile("lahti_readings.txt");

    cout << "\nLoading readings from file...\n";
    WeatherStation newLahti = WeatherStation::loadFromFile("lahti_readings.txt");
    newLahti.printReadings();

    return 0;
}
