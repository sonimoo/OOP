#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class Airport {
private:
    string airportName;
    int yearConstruction;
    string cityName;
    int flightCount;

public:
    Airport() {
        airportName = " ";
        yearConstruction = 0;
        cityName = " ";
        flightCount = 0;
    }

    Airport(string airportName, int yearConstruction, string cityName, int flightCount) {
        this->airportName = airportName;
        this->yearConstruction = yearConstruction;
        this->cityName = cityName;
        this->flightCount = flightCount;
    }

    ~Airport() {}

    string getAirportName() const {
        return airportName;
    }

    int getBuildDate() const {
        return yearConstruction;
    }

    string getCityName() const {
        return cityName;
    }

    int getFlightCount() const {
        return flightCount;
    }

    void show_info() const {
        cout << "Airport name: " << airportName << endl;
        cout << "Date of construction: " << yearConstruction << endl;
        cout << "City name: " << cityName << endl;
        cout << "Count of flights: " << flightCount << endl;
        cout << "================" << endl << endl;
    }

    void inputData() {
        cout << "Enter name of airport: ";
        cin >> airportName;
        cout << "Enter date of construction: ";
        cin >> yearConstruction;
        cout << "Enter name of the city: ";
        cin >> cityName;
        cout << "Enter count of flights: ";
        cin >> flightCount;
    }

    bool hasCity() const {
        return !cityName.empty();
    }

    void writeToStream(ostream& out) const {
        out << airportName << " " << yearConstruction << " " << cityName << " " << flightCount << endl;
    }

    void readFromStream(istream& in) {
        in >> airportName >> yearConstruction >> cityName >> flightCount;
    }
};

void bubbleSort(vector<Airport>& airports) {
    int n = airports.size();
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (airports[j].getFlightCount() > airports[j + 1].getFlightCount()) {
                swap(airports[j], airports[j + 1]);
            }
        }
    }
}

// Функция для записи данных массива в файл
void writeToFile(const vector<Airport>& airports, const string& filename) {
    ofstream outputFile(filename);

    if (!outputFile) {
        cerr << "Unable to open the file for writing." << endl;
        return;
    }

    for (const Airport& airport : airports) {
        airport.writeToStream(outputFile);
    }

    cout << "Data written to file successfully." << endl;
    outputFile.close();
}

// Функция для чтения данных из файла и вывода первых N элементов на экран
void displayFirstNFromFile(const string& filename, int N) {
    ifstream inputFile(filename);

    if (!inputFile) {
        cerr << "Unable to open the file for reading." << endl;
        return;
    }

    int count = 0;
    while (count < N && inputFile >> ws && !inputFile.eof()) {
        Airport airport;
        airport.readFromStream(inputFile);
        airport.show_info();
        ++count;
    }

    inputFile.close();
}

int main() {
    vector<Airport> airports;
    int choice;

    do {
        cout << "Menu:" << endl;
        cout << "1. Display airports " << endl;
        cout << "2. Create a new airport" << endl;
        cout << "3. Sort by flight count" << endl;
        cout << "4. Display airports with known city" << endl;
        cout << "5. Add new element at position K" << endl;
        cout << "6. Remove element by build date" << endl;
        cout << "7. Write airports data to file" << endl;
        cout << "8. Display first N airports from file" << endl;
        cout << "0. Exit" << endl;
        cout << " Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Display airports data" << endl;
            for (int i = 0; i < airports.size(); i++) {
                airports[i].show_info();
            }
            break;

        case 2: {
            cout << "Create new airport" << endl;
            Airport newAirport;
            newAirport.inputData();
            airports.push_back(newAirport);
            break;
        }

        case 3: {
            cout << "Sorting by flight count using Bubble Sort..." << endl;
            bubbleSort(airports);

            cout << "Sorted by Flight Count:\n";
            for (int i = 0; i < airports.size(); i++) {
                airports[i].show_info();
            }
            break;
        }
        case 4: {
            cout << "Displaying airports with known city:" << endl;
            for (Airport airport : airports) {
                if (airport.hasCity()) {
                    airport.show_info();
                }
            }
            break;
        }
        case 5: {
            cout << "Add new element at position K" << endl;
            int positionK;
            cout << "Enter position K: ";
            cin >> positionK;

            if (positionK >= 0 && positionK <= airports.size()) {
                Airport newAirport;
                newAirport.inputData();
                // Вставляем новый элемент на позицию K
                airports.insert(airports.begin() + positionK, newAirport);
            }
            else {
                cout << "Invalid position. Position should be between 0 and " << airports.size() << endl;
            }
            break;
        }
        case 6: {
            cout << "Remove element by build date" << endl;
            int buildDateToRemove;
            cout << "Enter build date to remove: ";
            cin >> buildDateToRemove;

            auto it = find_if(airports.begin(), airports.end(), [buildDateToRemove](const Airport& airport) {
                return airport.getBuildDate() == buildDateToRemove;
                });

            if (it != airports.end()) {
                airports.erase(it);
                cout << "Element removed successfully." << endl;
            }
            else {
                cout << "No element found with the specified build date." << endl;
            }
            break;
        }
        case 7: {
            cout << "Write airports data to file" << endl;
            string filename;
            cout << "Enter the filename: ";
            cin >> filename;

            writeToFile(airports, filename);
            break;
        }

        case 8: {
            cout << "Display first N airports from file" << endl;
            int N;
            string filename;
            cout << "Enter N: ";
            cin >> N;

            cout << "Enter the filename: ";
            cin >> filename;

            displayFirstNFromFile(filename, N);
            break;
        }


        case 0:
            cout << "Exit" << endl;
            break;
        }
    } while (choice != 0);

    return 0;
}
