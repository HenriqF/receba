#include <windows.h>
#include <bits/stdc++.h>

HANDLE inputH  = GetStdHandle(STD_INPUT_HANDLE);
HANDLE outputH = GetStdHandle(STD_OUTPUT_HANDLE);
CONSOLE_SCREEN_BUFFER_INFO csbi;

void eraseLine(std::string line){
    COORD cursorPos = csbi.dwCursorPosition;
    cursorPos.X = 0;
    SetConsoleCursorPosition(outputH, cursorPos);
    std::cout << std::string(line.length(), ' ');
    SetConsoleCursorPosition(outputH, cursorPos);
}


std::string editLine(std::string text){
    DWORD written;
    WriteConsoleA(outputH, text.c_str(), text.size(), &written, nullptr);

    GetConsoleScreenBufferInfo(outputH, &csbi);
    COORD cursorPos = csbi.dwCursorPosition;

    INPUT_RECORD ir;
    DWORD count;

    while (true){
        ReadConsoleInput(inputH, &ir, 1, &count);
        if (ir.EventType != KEY_EVENT || !ir.Event.KeyEvent.bKeyDown){
            continue;
        }
        switch (ir.Event.KeyEvent.wVirtualKeyCode){
            case VK_LEFT:
                if (cursorPos.X < 1) break;
                cursorPos.X--;
                SetConsoleCursorPosition(outputH, cursorPos);
                break;
            case VK_RIGHT:
                if (cursorPos.X == text.length()) break;
                cursorPos.X++;
                SetConsoleCursorPosition(outputH, cursorPos);
                break;
            case VK_ESCAPE:
                continue;
            default:
                break;
        }
        char c = ir.Event.KeyEvent.uChar.AsciiChar;

        if (c == '\r') break;
        else if (c == '\b' && !text.empty()){
            int index = cursorPos.X;
            eraseLine(text);
            if (index >= 1 && index <= text.size()){
                text.erase(index-1, 1);
                std::cout << text;
                cursorPos.X = index-1;
            }   
            else{
                std::cout << text;
            }
            SetConsoleCursorPosition(outputH, cursorPos);
        } 
        else if (c){
            std::string s(1, c);
            int size = 1;
            if (c == '\t'){
                s = "    ";
                size = 4;
            }

            int posMem = cursorPos.X;
            eraseLine(text);
            if (cursorPos.X == text.length()){
                text += s;
                std::cout << text;
                cursorPos.X = posMem+size;
            }
            else{   
                text.insert(cursorPos.X, s);
                std::cout << text;
                cursorPos.X = posMem+size;
                SetConsoleCursorPosition(outputH, cursorPos);
            }
        }
    }
    
    return text;
}


int main() {
    std::string currentline = "placeholder";
    while (1){
        currentline = editLine(currentline);
        std::cout << "\n'" << currentline << "'\n";
    }
}
