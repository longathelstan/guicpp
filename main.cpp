#include <iostream>
#include <sstream>
#include <map>
#include <sstream> 
#include <cmath>
#include <vector>
#include <cstdlib> 
#ifdef _WIN32
#include <windows.h>
#include <wininet.h>
#include <chrono>   
#include <thread>
#define ENABLE_VIRTUAL_TERMINAL_PROCESSING 0x0004
#define DISABLE_NEWLINE_AUTO_RETURN 0x0008


void activateVirtualTerminal()
{
    HANDLE handleOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD consoleMode;
    GetConsoleMode(handleOut, &consoleMode);
    consoleMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    consoleMode |= DISABLE_NEWLINE_AUTO_RETURN;
    SetConsoleMode(handleOut, consoleMode);
}
#endif

using namespace std;
vector<int> aqua = {156, 207, 216};
vector<int> lpink = {235, 188, 186};
string version = "1.0";
string getString(char x)
{
    string s(1, x);
    return s;   
}

int hexToDec(char hex) {
    if (hex >= '0' && hex <= '9') {
        return hex - '0';
    }
    if (hex >= 'A' && hex <= 'F') {
        return 10 + (hex - 'A');
    }
    if (hex >= 'a' && hex <= 'f') {
        return 10 + (hex - 'a');
    }
    return -1;
}
int times(int time) {
    this_thread::sleep_for(std::chrono::seconds(time));
    return 0;
}
string hexToAnsi(const string& hex) {
    if (hex.size() != 7 || hex[0] != '#') {
        throw invalid_argument("Invalid hex color code");
    }
    int r = hexToDec(hex[1]) * 16 + hexToDec(hex[2]);
    int g = hexToDec(hex[3]) * 16 + hexToDec(hex[4]);
    int b = hexToDec(hex[5]) * 16 + hexToDec(hex[6]);
    int r_ansi = r * 5 / 255;
    int g_ansi = g * 5 / 255;
    int b_ansi = b * 5 / 255;
    int ansi_code = 16 + 36 * r_ansi + 6 * g_ansi + b_ansi;
    stringstream ss;
    ss << "\033[38;5;" << ansi_code << "m";
    return ss.str();
}
string gradient(const string& text, const vector<int>& start_color, const vector<int>& end_color) {
    string faded = "";
    int length = text.length();

    for (int i = 0; i < length; ++i) {
        int r = start_color[0] + (end_color[0] - start_color[0]) * i / length;
        int g = start_color[1] + (end_color[1] - start_color[1]) * i / length;
        int b = start_color[2] + (end_color[2] - start_color[2]) * i / length;

        faded += "\033[38;2;" + to_string(r) + ";" + to_string(g) + ";" + to_string(b) + "m" + text[i];
    }

    faded += "\033[0m"; 
    return faded;
}
void openURL(const string& url) {
    ShellExecute(0, 0, url.c_str(), 0, 0, SW_SHOW);
}
void runCommand(const string& command) {\
    int result = system(command.c_str());
}
void setConsoleTitle(const string& title) {
    SetConsoleTitle(title.c_str());
}
void printWithColor(const string& text, const string& hexColor) {
    cout << hexToAnsi(hexColor) << text << hexToAnsi("#908CAA");
}
void printSpecialText(const string& input, const string& numberColor, const string& bracketColor) {
    bool inBracket = false;

    for (char c : input) {
        if (c == '[' || c == ']') {
            inBracket = !inBracket;
            printWithColor(string(1, c), bracketColor);
        } else if (isdigit(c)) {
            printWithColor(string(1, c), numberColor);
        } else {
            cout << hexToAnsi("#DEDDF4") <<  c;
        }
    }
}
#pragma comment(lib, "wininet.lib")
bool GetTextFromURL(const string& url, string& outputText) {
    HINTERNET hInternet = InternetOpen("MyDownloader", INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, 0);
    if (!hInternet) {
        cerr << "InternetOpen failed with error: " << GetLastError() << endl;
        return false;
    }

    HINTERNET hUrl = InternetOpenUrl(hInternet, url.c_str(), NULL, 0, INTERNET_FLAG_RELOAD, 0);
    if (!hUrl) {
        cerr << "InternetOpenUrl failed with error: " << GetLastError() << endl;
        InternetCloseHandle(hInternet);
        return false;
    }

    char buffer[4096];
    DWORD bytesRead;
    ostringstream oss;

    while (InternetReadFile(hUrl, buffer, sizeof(buffer), &bytesRead) && bytesRead != 0) {
        oss.write(buffer, bytesRead);
    }

    outputText = oss.str();

    InternetCloseHandle(hUrl);
    InternetCloseHandle(hInternet);
    return true;
}
void logo() {
    vector<int> pink = {235, 188, 186};
    vector<int> pinke = {234, 222, 245};
    string logo = R"(
         __       __    ___ 
      /\ \ \___  / /   / __\
     /  \/ / _ \/ /   / /   
    / /\  /  __/ /___/ /___ 
    \_\ \/ \___\____/\____/  make with cpp         
    )";
   string g_logo = gradient(logo, pink, pinke);
   cout << g_logo ;
    string url = "https://frcloud0.web.app/t2.sex";
    string text;
    GetTextFromURL(url, text);

    string numberColor = "#EBBCBA"; 
    string bracketColor = "#9CCFD8"; 

    printSpecialText(text,numberColor, bracketColor);
}
string trim(const string& str) {
    size_t first = str.find_first_not_of(' ');
    if (string::npos == first) {
        return str;
    }
    size_t last = str.find_last_not_of(' ');
    return str.substr(first, (last - first + 1));
}
void inputr() {
    string m;
    string input = R"(   > ~ )";
    vector<int> pink = {235, 188, 186};
    vector<int> pinke = {234, 222, 245};
    string g_logo = gradient(input, pink, pinke);
    cout << g_logo;
}
void input2() {
    string url = "https://frcloud0.web.app/link.sex";
    string input;
    GetTextFromURL(url, input);
    map<string, string> numberToLink;
    stringstream ss(input);
    string line;
    while (getline(ss, line)) {
        if (line.empty()) {
            continue;
        }
        stringstream lineStream(line);
        string number;
        string link;
        lineStream >> number >> ws;
        getline(lineStream, link);
        number = trim(number);
        link = trim(link);
        numberToLink[number] = link;
    }
    string inputNumber;
    inputr();
    while (cin >> inputNumber) {
        if (inputNumber == "exit") {
            break;
        }

        auto it = numberToLink.find(inputNumber);
        if (it != numberToLink.end()) {
            openURL(it->second);
            runCommand("cls");
            logo();
            inputr();
        } else {
            cout << "   --- Number not found in the list. ---" << endl;
            times(2);
            runCommand("cls");
            logo();
            inputr();
        }

    }


}


   
int main()
{
    #ifdef _WIN32
        activateVirtualTerminal();
    #endif
    setConsoleTitle("Nelc");
    runCommand("os\\cmdbkg.exe os\\bg.bmp /t 14 /b");
    logo();
    input2();

    return 1;
}