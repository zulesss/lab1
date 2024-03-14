#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

struct Settlement 
{
    string type;
    string name;
    string region;
    int population;

    void displayInfo() 
    {
        cout << "Type: " << type << endl;
        cout << "Name: " << name << endl;
        cout << "Region: " << region << endl;
        cout << "Population: " << population << endl;
    }
};

vector<Settlement> settlements; 

void logAction(const string& action) {
    ofstream logFile("log.txt", ios::app);
    if (logFile.is_open()) 
    {
        logFile << action << endl;
        logFile.close();
    }
    else
        cout << "Unable to open log file." << endl;
}

void readData(const string& fileName) 
{
    ifstream inFile(fileName, ios::binary);
    if (inFile.is_open()) 
    {
        settlements.clear(); 
        Settlement temp;
        while (inFile.read(reinterpret_cast<char*>(&temp), sizeof(Settlement))) 
        {
            settlements.push_back(temp);
        }
        inFile.close();
        cout << "Data read successfully." << endl;
        logAction("Read data from file.");
    }
    else
        cout << "Unable to open file." << endl;
}

void saveData(const string& fileName) 
{
    ofstream outFile(fileName, ios::binary);
    if (outFile.is_open()) 
    {
        for (const auto& settlement : settlements)
        {
            outFile.write(reinterpret_cast<const char*>(&settlement), sizeof(Settlement));
        }
        outFile.close();
        cout << "Data saved successfully." << endl;
        logAction("Saved data to file.");
    }
    else
        cout << "Unable to open file." << endl;
}

void addSettlement() {
    Settlement newSettlement;
    cout << "Enter type: ";
    cin >> newSettlement.type;
    cout << "Enter name: ";
    cin >> newSettlement.name;
    cout << "Enter region: ";
    cin >> newSettlement.region;
    cout << "Enter population: ";
    cin >> newSettlement.population;
    settlements.push_back(newSettlement);
    cout << "New settlement added successfully." << endl;
    logAction("Added new settlement.");
}

void deleteSettlement(const string& name) {
    auto it = find_if(settlements.begin(), settlements.end(), [&name](const Settlement& s) {
        return s.name == name;
        });
    if (it != settlements.end()) 
    {
        settlements.erase(it);
        cout << "Settlement '" << name << "' deleted successfully." << endl;
        logAction("Deleted settlement '" + name + "'.");
    }
    else
        cout << "Settlement '" << name << "' not found." << endl;
}

void sortSettlementsByName() 
{
    sort(settlements.begin(), settlements.end(), [](const Settlement& a, const Settlement& b) {
        return a.name < b.name;
        });
    cout << "Settlements sorted by name." << endl;
    logAction("Sorted settlements by name.");
}

int main()
{
    int choice;
    string fileName = "settlements.dat";

    while (true)
    {
        cout << "\nMenu:\n";
        cout << "1. Read data from file\n";
        cout << "2. Save data to file\n";
        cout << "3. Add new settlement\n";
        cout << "4. Delete settlement by name\n";
        cout << "5. Sort settlements by name\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) 
        {
        case 1:
            readData(fileName);
            break;
        case 2:
            saveData(fileName);
            break;
        case 3:
            addSettlement();
            break;
        case 4: {
            string nameToDelete;
            cout << "Enter name of settlement to delete: ";
            cin >> nameToDelete;
            deleteSettlement(nameToDelete);
            break;
        }
        case 5:
            sortSettlementsByName();
            break;
        case 6:
            return 0;
        default:
            cout << "Invalid choice. Please enter a number between 1 and 6." << endl;
        }
    }

    return 0;
}