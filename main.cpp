#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
using namespace std;

char choice;
bool Valid = true;
int Brackets = 0, SquareBrackets = 0, Q_marks = 0;
int lineNumberForChar[100000];

void showMenu() {
    cout << "Welcome to the JSON Parser!" << endl;
    cout << "Press 'o' to open JSON file." << endl;
    cout << "Press 'd' to validate JSON content." << endl;
}

string ClearRead(const string& fileName) {
    ifstream file(fileName);
    if (!file.is_open()) {
        cerr << "Błąd: Nie udało się otworzyć pliku " << fileName << endl;
        exit(1);
    }

    string result;
    char c;
    bool inString = false;
    int currentLine = 1;
    int index = 0;

    while (file.get(c)) {
        if (c == '\n') {
            currentLine++;
            continue;
        }

        if (c == '"') {
            result += c;
            lineNumberForChar[index++] = currentLine;
            inString = !inString;
        } else if (inString) {
            result += c;
            lineNumberForChar[index++] = currentLine;
        } else {
            if (!isspace(static_cast<unsigned char>(c))) {
                result += c;
                lineNumberForChar[index++] = currentLine;
            }
        }
    }

    return result;
}

void CounterForDualElements(const string& fileName, int& Brackets, int& SquareBrackets, int& Q_marks) {
    ifstream file(fileName);
    char ch;
    while (file.get(ch)) {
        if (ch == '{' || ch == '}') Brackets++;
        if (ch == '[' || ch == ']') SquareBrackets++;
        if (ch == '"') Q_marks++;
    }
}

bool MissingItems(int x) {
    return x % 2 == 0;
}

bool startsWithNumber(const string& json, int index) {
    while (index < json.length() && isspace(static_cast<unsigned char>(json[index]))) {
        index++;
    }

    if (index < json.length()) {
        char c = json[index];
        return isdigit(static_cast<unsigned char>(c)) || c == '-' || c == '+' || c == '.';
    }

    return false;
}

bool validateJsonContent(const string& json) {
    int doubleQuotes = 0;
    bool firstErrorReported = false;

    for (int i = 0; i < json.length(); i++) {
        char current = json[i];

        if (current == '"') {
            doubleQuotes++;

            if (doubleQuotes % 2 == 0 && i + 1 < json.length()) {
                char next = json[i + 1];

                if (next != ':' && next != ',' && next != ']' && next != '}') {
                    Valid = false;
                    if (!firstErrorReported) {
                        cout << "Błąd: Nieprawidłowy znak po cudzysłowie w linii: "
                             << lineNumberForChar[i + 1] << endl;
                        firstErrorReported = true;
                    }
                }
            }

            if (i + 1 < json.length() && json[i + 1] == '"') {
                Valid = false;
                if (!firstErrorReported) {
                    cout << "Błąd: Podwójny cudzysłów bez przecinka w linii: "
                         << lineNumberForChar[i + 1] << endl;
                    firstErrorReported = true;
                }
            }
        }
        if (current == '{' && startsWithNumber(json, i + 1)) {
            Valid = false;
            if (!firstErrorReported) {
                cout << "Błąd: Nie można zaczynać zawartości obiektu od liczby! Linia: "
                     << lineNumberForChar[i + 1] << endl;
                firstErrorReported = true;
            }
        }
        if (current == '{' && i + 1 < json.length() && json[i + 1] != '"' && json[i + 1] != ',') {
            Valid = false;
            if (!firstErrorReported) {
                cout << "Błąd: Oczekiwano cudzysłowu po '{' w linii: "
                     << lineNumberForChar[i + 1] << endl;
                firstErrorReported = true;
            }
        }
        if (current == '{' && i + 1 < json.length() && json[i + 1] == ',') {
            Valid = false;
            if (!firstErrorReported) {
                cout << "Błąd: Nieprawidłowy przecinek przy '{' w linii: "
                     << lineNumberForChar[i + 1] << endl;
                firstErrorReported = true;
            }

        }
        if (current == ',' && i + 1 < json.length() && json[i + 1] == '}') {
            Valid = false;
            if (!firstErrorReported) {
                cout << "Błąd: Nieprawidłowy przecinek przy '}' w linii: "
                     << lineNumberForChar[i + 1] << endl;
                firstErrorReported = true;
            }

        }
        if (current == '[' && i + 1 < json.length() && json[i + 1] == ',') {
            Valid = false;
            if (!firstErrorReported) {
                cout << "Błąd: Nieprawidłowy przecinek przy '[' w linii: "
                     << lineNumberForChar[i + 1] << endl;
                firstErrorReported = true;
            }

        }
        if (current == ',' && i + 1 < json.length() && json[i + 1] == ']') {
            Valid = false;
            if (!firstErrorReported) {
                cout << "Błąd: Nieprawidłowy przecinek przy ']' w linii: "
                     << lineNumberForChar[i + 1] << endl;
                firstErrorReported = true;
            }

        }
                    
    }

    return Valid;
}

void handleOpen() {
    string line;
    ifstream file("Json.txt");

    if (!file.is_open()) {
        cerr << "Błąd: Nie udało się otworzyć pliku!" << endl;
        return;
    }

    while (getline(file, line)) {
        cout << line << endl;
    }

    file.close();
}

void handleValidation() {
    string Clear_Read = ClearRead("Json.txt");
    validateJsonContent(Clear_Read);

    CounterForDualElements("Json.txt", Brackets, SquareBrackets, Q_marks);

    if (!MissingItems(Brackets)) {
        cout << "Brackets not paired!" << endl;
        Valid = false;
    }
    if (!MissingItems(SquareBrackets)) {
        cout << "Square brackets not paired!" << endl;
        Valid = false;
    }
    if (!MissingItems(Q_marks)) {
        cout << "Quotes not paired!" << endl;
        Valid = false;
    }

    cout << Clear_Read << endl;
    cout << "Final result: " << (Valid ? "VALID" : "INVALID") << endl;
}

int main() {
    showMenu();

    while (true) {
        cin >> choice;

        if (choice == 'o') {
            handleOpen();
        } else if (choice == 'd') {
            handleValidation();
            break;
        } else {
            cout << "Nieznana opcja! Wybierz 'o' lub 'd'." << endl;
        }
    }

    return 0;
}

