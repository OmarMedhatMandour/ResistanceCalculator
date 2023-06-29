#include <iostream>
#include <string>

using namespace std;
// define constants for circuit types
const char SERIES = 'S';
const char PARALLEL = 'P';
// function prototypes
double calculateResistance(string circuitDescription, char circuitType);
bool validateCircuit(string circuitDescription);
double branchResistance(string circuitDescription);

int main() {
    string circuitDescription;
    float voltage, resistance, current;
    bool wrongCircuit = false;

    cout << "Circuit description: ";
    getline(cin, circuitDescription);

    cout << "Voltage applied: ";
    cin >> voltage;
    cin.ignore(); // Ignore the newline character left in the input stream

    if (validateCircuit(circuitDescription)) {
        cout << "Wrong Circuit Description." << endl;
        return 0;
    }
    // get the circuit type from the first character of the description
    char circuitType = circuitDescription[0];
    // calculate the total resistance of the circuit
    resistance = calculateResistance(circuitDescription, circuitType);
    cout << "Total resistance: " << resistance << endl;
    // calculate the current flowing through the circuit using Ohm's law
    current = voltage / resistance;
    cout << "Current flowing through the circuit: " << current << endl;
    return 0;
}
// function to validate the format of the circuit description
bool validateCircuit(string circuitDescription) {
    for (int i = 0; i < circuitDescription.length(); i++) {
        switch (circuitDescription[i]) {
        case SERIES:
        case PARALLEL:
        case '0'...'9':
        case 'E':
        case '.':
        case 'e':
        case ' ':
            break;
        default:
            return true; // invalid character found
        }
    }
    //return true;
}
// function to calculate the total resistance of a circuit
double calculateResistance(string circuitDescription, char circuitType) {
    bool branch = false;
    double resistorValue = 0.0, totalResistorValue = 0.0;
    string carry;
    int digit = 0;
    int i = 2;
    while (i < circuitDescription.length()) {
        if (circuitDescription[i] == SERIES || circuitDescription[i] == PARALLEL) {
            branch = true; // start of a branch
        }
        if (!branch) {
            if (circuitDescription[i] == ' ') { // end of a resistor value
                resistorValue = stod(circuitDescription.substr(i - digit, digit));
                digit = -1; // reset the digit counter
                switch (circuitType) {
                case SERIES:
                    totalResistorValue += resistorValue; // add resistor values in
                    //series
                    break;
                case PARALLEL:
                    totalResistorValue += 1 / resistorValue; // add inverse of
                    //resistor values in parallel
                    break;
                }
            }
            digit++; // increment the digit counter
        }
        if (branch) {
            carry += circuitDescription[i]; // append the character to the carry string
            if (circuitDescription[i] == 'e') { // end of a branch
                branch = false;
                resistorValue = branchResistance(carry); // call the new function to
                //calculate the resistance of a branch
                switch (circuitType) {
                case SERIES:
                    totalResistorValue += resistorValue; // add branch resistance in
                    //series
                    break;
                case PARALLEL:
                    totalResistorValue += 1 / resistorValue; // add inverse of branch
                    //resistance in parallel
                    break;
                }
                carry = ""; // clear the carry string
                i += 1; // skip the next space character
            }
        }
        i++;
    }
    // return the total resistance depending on the circuit type
    return (circuitType == SERIES) ? totalResistorValue : 1 / totalResistorValue;
}

double branchResistance(string circuitDescription) {
    char connectionType = circuitDescription[0];
    double resistance = 0.0, totalResistance = 0.0;
    string carry;
    int digit = 0;

    for (int i = 2; i < circuitDescription.length(); i++) {
        if (circuitDescription[i] == ' ') {
            resistance = stod(circuitDescription.substr(i - digit, digit));
            digit = -1;
            switch (connectionType) {
            case 'S':
                totalResistance += resistance;
                break;
            case 'P':
                totalResistance += 1 / resistance;
                break;
            }
        }
        digit++;
    }
    return (connectionType == 'S') ? totalResistance : 1 / totalResistance;
}
