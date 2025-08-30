#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cctype>
#include <unordered_map>

using namespace std;

vector<int> lineForChar;
bool isValid = true;

string readJsonFile(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: Failed to open file " << filename << endl;
        exit(1);
    }

    string result;
    char c;
    bool inString = false;
    int currentLine = 1;

    while (file.get(c)) {
        if (c == '\n') {
            currentLine++;
            continue;
        }

        if (inString || !isspace(static_cast<unsigned char>(c))) {
            result += c;
            lineForChar.push_back(currentLine);
        }

        if (c == '"') {
            inString = !inString;
        }
    }

    return result;
}

bool checkBalanced(const string& json, char open, char close, const string& name) {
    int count = 0;
    for (char c : json) {
        if (c == open) count++;
        else if (c == close) count--;
    }
    if (count != 0) {
        cout << "Error: Unmatched number of characters " << open << "/" << close << "!" << endl;
        isValid = false;
        return false;
    }
    return true;
}

bool isUnquotedWord(const string& json, int index) {
    while (index < static_cast<int>(json.length()) &&
           isspace(static_cast<unsigned char>(json[index]))) {
        index++;
    }

    if (index >= static_cast<int>(json.length()) ||
        json[index] == '"' || json[index] == '{' || json[index] == '[') {
        return false;
    }

    // number
    if (isdigit(static_cast<unsigned char>(json[index])) ||
        json[index] == '-' || json[index] == '+') {
        return false;
    }

    // special words: true, false, null
    string word;
    while (index < static_cast<int>(json.length()) &&
           (isalnum(static_cast<unsigned char>(json[index])) || json[index] == '_')) {
        word += json[index++];
    }

    return !(word == "true" || word == "false" || word == "null");
}

static inline bool isEscaped(const string& s, size_t i) {
    // returns true if s[i] is preceded by an odd number of backslashes
    size_t cnt = 0;
    size_t k = i;
    while (k > 0 && s[--k] == '\\') ++cnt;
    return (cnt % 2) == 1;
}

void validateJson(const string& json) {
    int quoteCount = 0;
    bool insideString = false;

    for (size_t i = 0; i < json.length(); ++i) {
        char c = json[i];

        // Toggle only on unescaped quotes
        if (c == '"' && !isEscaped(json, i)) {
            insideString = !insideString;
            quoteCount++;
            // Empty string "" is valid, so no extra check here.
        }

        if (!insideString) {
            // Guard next char
            char next = (i + 1 < json.size() ? json[i + 1] : '\0');

            if ((c == '{' || c == ',' || c == ':') &&
                (i + 1 < json.size()) && isUnquotedWord(json, static_cast<int>(i + 1))) {
                cout << "Error: Unquoted word at line " << lineForChar[i + 1] << endl;
                isValid = false;
                return;
            }

            if ((c == ',' && (next == '}' || next == ']')) ||
                ((c == '{' || c == '[') && next == ',')) {
                cout << "Error: Invalid comma at line " << lineForChar[i] << endl;
                isValid = false;
                return;
            }
        }
    }

    if (quoteCount % 2 != 0) {
        cout << "Error: Odd number of quotation marks!" << endl;
        isValid = false;
    }

    checkBalanced(json, '{', '}', "brackets");
    checkBalanced(json, '[', ']', "square brackets");
}

void handleOpen(const string& filename) {
    ifstream file(filename);
    string line;
    while (getline(file, line)) {
        cout << line << endl;
    }
}

int main() {
    char choice;
    const string filename = "Json.txt";

    cout << "Welcome to the JSON Parser!" << endl;
    cout << "Press 'o' to open JSON file." << endl;
    cout << "Press 'd' to validate JSON content." << endl;

    while (cin >> choice) {
        if (choice == 'o') {
            handleOpen(filename);
        } else if (choice == 'd') {
            string json = readJsonFile(filename);
            validateJson(json);
            cout << json << endl;
            cout << "Final result: " << (isValid ? "VALID" : "INVALID") << endl;
            break;
        } else {
            cout << "Unknown option! Choose 'o' or 'd'." << endl;
        }
    }

    return 0;
}
