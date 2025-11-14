#include <iostream>
#include <vector>
#include <tuple>
using namespace std;

int main() {
    // Step 1: Store days of the week
    vector<string> days = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"};

    // Step 2: Store temperatures for each day
    vector<double> temps = {12.5, 8.3, 15.0, 21.5, 18.0, 25.7, 9.8};

    // Step 3: Track the warmest day using a tuple
    tuple<string, double> warmestDay = make_tuple(days[0], temps[0]);

    cout << "=== Weekly Weather Report ===\n";

    // Step 4: Loop through all days & print details
    for (int i = 0; i < days.size(); i++) {
        cout << days[i] << ": " << temps[i] << "°C - ";

        // Classification
        if (temps[i] < 10)
            cout << "Cold";
        else if (temps[i] <= 20)
            cout << "Ok";
        else
            cout << "Warm";

        cout << endl;

        // Update warmest day
        if (temps[i] > get<1>(warmestDay)) {
            warmestDay = make_tuple(days[i], temps[i]);
        }
    }

    // Step 5: Print the warmest day (from tuple)
    cout << "\nWarmest Day: " 
         << get<0>(warmestDay) << " (" 
         << get<1>(warmestDay) << "°C)\n";

    return 0;
}
