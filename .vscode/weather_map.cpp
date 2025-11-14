#include <iostream>
#include <map>
using namespace std;

int main() {
    // Step 1: Using a map to store day → temperature
    map<string, double> weather = {
        {"Monday", 12.5},
        {"Tuesday", 8.3},
        {"Wednesday", 15.0},
        {"Thursday", 21.5},
        {"Friday", 18.0},
        {"Saturday", 25.7},
        {"Sunday", 9.8}
    };

    // Step 2: Add a char variable for general weather condition
    map<string, char> condition = {
        {"Monday", 'S'},
        {"Tuesday", 'R'},
        {"Wednesday", 'C'},
        {"Thursday", 'S'},
        {"Friday", 'C'},
        {"Saturday", 'S'},
        {"Sunday", 'R'}
    };

    cout << "=== Weekly Weather Report (Map Version) ===\n";

    double total = 0;
    int count = 0;

    // Step 3: Loop through the map to print and sum
    for (auto entry : weather) {
        string day = entry.first;
        double temp = entry.second;
        char cond = condition[day];

        cout << day << ": " << temp << "°C, Condition: " << cond << endl;

        total += temp;
        count++;
    }

    // Step 4: Calculate average
    double average = total / count;

    cout << "\nAverage Temperature: " << average << "°C\n";

    return 0;
}
