#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

using namespace std;

char choice;
int Brackets;
int  SquareBrackets;
int Q_marks;
bool Valid = true;

// Function to count the number of brackets, square brackets, and quotation marks 
void CounterForDualElements(const string& fileName, int& Brackets, int& SquareBrackets, int& Q_marks) {     
    fstream file("Json.txt");
    Brackets = 0;
    SquareBrackets = 0;
    Q_marks = 0;

    char characters;
    while(file.get(characters)) {
        if (characters == '{' || characters == '}') {
            Brackets++;
        } 
        else if (characters == '[' || characters == ']') {
            SquareBrackets++;
        } else if (characters == '"') {
            Q_marks++;
        }
    }
    
}
// Function to check if any bracket or quotation mark is missing
bool MissingItems(int MissedItem) {                                   
    return (MissedItem % 2 == 0);
}

//Delete space and enters so it easier to operate 
string ClearRead(const string& fileName){
    fstream file("Json.txt");
    string result;
    char c;
    bool inString = false;

    while (file.get(c)){
        if(c =='"'){
            result = result + c;
            inString = !inString; 
        }
        else if (inString) {
            result = result + c;
        }
        else{
            if(!isspace(c)) {
                result = result + c;
            }
        }
    }
    return result;
}



int main(){
    
    cout << "Welcome to the JSON Parser!"   << endl;
    cout << "----------------------------"  << endl;
    cout << "Select -o to open file: "      << endl;
    cout << "----------------------------"  << endl;
    cout << "Select -d to open file: "      << endl;
    while (true){
   
    cin >> choice;

        if (choice == 'o') {
            fstream file("Json.txt");
            if (file.is_open()) {
                cout << "File opened successfully!" << endl;
            
            } else {
            cout << "Error opening file!" << endl;
            }
        }
    
        if (choice == 'd') {
            string Clear_Read = ClearRead("Json.txt");
            for(int i = 0; i < Clear_Read.length(); i++) {
                
                char nextCharter = Clear_Read[i];
                int doubleQuotes = 0;
                if (nextCharter == '"'){
                    doubleQuotes++;
                    
                    if (doubleQuotes % 2 == 0){
                    nextCharter ++;
                    
                    if(nextCharter != ':' && nextCharter != ',' && nextCharter != ']' && nextCharter != '}'){
                        Valid = false;
                        }
                    }
                }
                
                
            }
            cout << Clear_Read;
            
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
            
            

            cout << "Final result: " << (Valid ? "VALID" : "INVALID") << endl;
            
            break;
        }
    
    }

}
