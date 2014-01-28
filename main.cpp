#include<iostream>
#include<fstream>
#include<cstdlib>
#include<string>

using namespace std;
string rawInputCode, inputCode;

#define GRID_LENGTH 30000

long long terminatingBracket(unsigned long long curPos);
long long beginBracket(unsigned long long curPos);

int main(int argc, char *argv[]){

    char grid[GRID_LENGTH];
    char *pointer =grid;

    for (long j = 0; j <GRID_LENGTH; j++){
        grid[j]=0;
    }

    //read file, tests for ability to open
    ifstream readCode;
    readCode.open(argv[1]);
    if (!readCode.is_open()){
        cout << "FILE READ ERROR" << endl;
        system("PAUSE");
        exit(EXIT_FAILURE);
    }
    rawInputCode.assign((std::istreambuf_iterator<char>(readCode)),(std::istreambuf_iterator<char>()));//reads all of readCode into RawInput
    readCode.close();
    for (long long j = 0; j < rawInputCode.length(); j++){
        inputCode = inputCode + rawInputCode[j];
    }
    for (unsigned long long i = 0; i < inputCode.length(); i++){
        switch (inputCode[i]) {
            case '>':
                if(pointer + 1 < grid + GRID_LENGTH){
                    ++pointer;
                } else {
                    cout << endl << "Pointer out of upper range exception on char: " << i << endl;
                    cout << endl << i << " " << inputCode[i] << " " << int(pointer) << " " << *pointer << " " << int(*pointer) << endl;
                    system("PAUSE");
                    exit(EXIT_FAILURE);
                }
                break;
            case '<':
                if(pointer - 1 >= grid){
                    --pointer;
                } else {
                    cout << endl << "Pointer out of lower range exception on char: " << i << endl;
                    cout << endl << i << " " << inputCode[i] << " " << int(pointer) << " " << *pointer << " " << int(*pointer) << endl;
                    system("PAUSE");
                    exit(EXIT_FAILURE);
                }
                break;
            case '+':
                ++*pointer;
                break;
            case '-':
                --*pointer;
                break;
            case '.':
                putchar(*pointer);
                break;
            case ',':
                *pointer = getchar();
                break;
            case '[':
                if(*pointer == 0){
                   if(terminatingBracket(i) >= 0){
                       i = terminatingBracket(i);
                   } else if (terminatingBracket(i) == -1){
                          cout << endl << "Unmatched '['! Char: " << i << endl;
                          cout << endl << i << " " << inputCode[i] << " " << int(pointer) << " " << *pointer << " " << int(*pointer) << endl;
                          system("PAUSE");
                          exit(EXIT_FAILURE);
                          }
                }
                break;
            case ']':
                if(*pointer != 0){
                   if(beginBracket(i) >= 0){
                       i = beginBracket(i);
                   } else if (beginBracket(i) == -1){
                          cout << endl << "Unmatched ']'! Char: " << i << endl;
                          cout << endl << i << " " << inputCode[i] << " " << int(pointer) << " " << *pointer << " " << int(*pointer) << endl;
                          system("PAUSE");
                          exit(EXIT_FAILURE);
                          }
                }
                break;
            case '#':
                cout << endl << i << " " << inputCode[i] << " " << int(pointer) << " " << *pointer << " " << int(*pointer) << endl;
                break;
            default:
                break;

        }
    }
    cout << endl;
    system("PAUSE");
}

long long terminatingBracket(unsigned long long curPos){
    long lCount = 1, rCount = 0;
    unsigned long long k;
    for (k = curPos + 1; lCount != rCount && k < inputCode.length(); k++){
        switch (inputCode[k]){
            case '[':
                lCount++;
                break;
            case ']':
                rCount++;
                break;
        }
    }
    if (lCount == rCount){
           return (k -2);
    } else {
           return(-1);
    }
}
long long beginBracket(unsigned long long curPos){
    long lCount = 0, rCount = 1;
        unsigned long long k;
    for (k = curPos - 1; lCount != rCount && k >= 0; k--){
        switch (inputCode[k]){
            case '[':
                lCount++;
                break;
            case ']':
                rCount++;
                break;
        }
    }
    if (lCount == rCount){
           return (k);
    } else {
           return(-1);
    }
}
bool isCommand(char c){
    if (c == '>' || c == '<' || c == '+' || c == '-' || c == '.' || c == ',' || c == '[' || c == ']' || c == '#'){
        return true;
    } else {
        return false;
    }
}
