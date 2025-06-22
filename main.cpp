#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

using namespace std;

char x;

bool is_number(const std::string& s)
{
    return !s.empty() && std::find_if(s.begin(),
        s.end(), [](unsigned char c) { return !std::isdigit(c); }) == s.end();
}


inline string& ltrim(std::string& s, const char* t = " \t\n\r\f\v")
{
    s.erase(0, s.find_first_not_of(t));
    return s;
}

inline string& rtrim(std::string& s, const char* t = " \t\n\r\f\v")
{
    s.erase(s.find_last_not_of(t) + 1);
    return s;
}


int main()
{
    cout << "---------------------" << endl;
    cout << "Helper: h" << endl;
    cout << "---------------------" << endl;
    fstream file;
    for (int i = 0; i < 100; i++)
    {
        cin >> x;

        if (x == 'h' || x == 'H')
        {
            cout << "---------------------" << endl;
            cout << "Jacek Or³owski" << endl;
            cout << "---------------------" << endl;
            cout << "Otworzenie pliku: o" << endl;
            cout << "---------------------" << endl;
            cout << "---------------------" << endl;
            cout << "Sprawdzenie pliku: c" << endl;
            cout << "---------------------" << endl;
            cout << "---------------------" << endl;
            cout << "sciezka dostepu pliku: p" << endl;
            cout << "---------------------" << endl;
        }

        if (x == 'o' || x == 'O')
        {
            file.open("NAZWA_PLIKU.txt", ios::in);
            if (file.is_open()) {
                cout << "Plik zostal otwarty" << endl;
            } 
            
            else {
                cout << "Blad: Nie mozna otworzyc pliku!" << endl;
            }

        }

        if (x == 'c' || x == 'C') {

            if (!file.is_open()) {
                cout << "Błąd: Plik nie został otwarty!" << endl;
                continue;
            }

            file.clear();      // Reset EOF i błędów
            file.seekg(0);     // Wróć na początek pliku
            
            string z;
            int counterBrackets = 0; // ++ { --}
            int counterSquareBrackets = 0; // ++ [ -- ]
            bool end = false;
            int line = 0;
            int errorLine = 0;
            bool checkBracket = false;
            while (!file.eof() && !end) {
                getline(file, z);
                if (checkBracket && ltrim(z) != "}") {
                    errorLine = line - 1;
                    end = true;
                    break;
                }
                if(checkBracket){
                    checkBracket = false;
                }

              /*  if (checkSquareBracket && ltrim(z) != "]") {
                    errorLine = line - 1;
                    end = true;
                    break;
                }
                if (checkSquareBracket) {
                    checkSquareBracket = false;
                }*/

                //if (z.find('[') || z.find(']')) {
                //    errorLine = line;
                //    end = true;
                //    break;
                //}
                string temp = ltrim(z);

                if (temp == "[") {
                    counterSquareBrackets++;
                }
                else if (temp == "]" || temp == "],") {
                    counterSquareBrackets--;
                }
                else if(temp == "{") {
                    counterBrackets++;
                }
                else if (temp == "}" || temp == "},") {
                    counterBrackets--;
                }
                else if(z.length() == 0){
                    continue;
                }
                else {
                    string left = z.substr(0, z.find(":")); // bierze lewą strone
                    left = ltrim(left);
                    if (left[0] == '\"' && left[left.length() - 1] == '\"') {
                        string name = left.erase(0, 1);
                        name.pop_back();
                        if (name.length() == 0) {
                            errorLine = line;
                            end = true;
                            break;
                        }
                    }
                    else {
                        errorLine = line;
                        end = true;
                        break;
                    }

                    size_t pos = z.find(":");
                    z.erase(0, pos + 1);
                    string rigth = z;// bierze prawą strone
                    rigth = rtrim(rigth);
                    rigth = ltrim(rigth);
                    if (rigth[rigth.length() - 1] == ',') {
                        rigth.pop_back();
                        rigth = rtrim(rigth);
                        if (rigth[0] == '\"' && rigth[rigth.length() - 1] == '\"') {
                            string name = rigth.erase(0, 1);
                            name.pop_back();
                            if (name.length() == 0) {
                                errorLine = line;
                                end = true;
                                break;
                            }
                        }
                        else {
                            if (!is_number(rigth)) {
                                errorLine = line;
                                end = true;
                                break;
                            }
                        }
                    }
                    else {
                        if (rigth == "{") {
                            counterBrackets++;
                        }
                        else if (rigth == "[") {
                            counterSquareBrackets++;
                        }
                        else {
                            rigth = rtrim(rigth);
                            if (rigth[0] == '\"' && rigth[rigth.length() - 1] == '\"') {
                                string name = rigth.erase(0, 1);
                                name.pop_back();
                                if (name.length() == 0) {
                                    errorLine = line;
                                    end = true;
                                    break;
                                }
                            }
                            else {
                                if (!is_number(rigth)) {
                                    errorLine = line;
                                    end = true;
                                    break;
                                }
                            }
                            checkBracket = true;
                        }     
                    }        
                }
                line++;
            }
            if (counterBrackets != 0) {
                errorLine = line;
            }
            string result = "GIT";
            if (errorLine != 0) {
                result = "!!! ERROR";
                cout << result << " " << errorLine;
            }
            else {
                cout << result;
            }
        }
        



    }

    return 0;


}


