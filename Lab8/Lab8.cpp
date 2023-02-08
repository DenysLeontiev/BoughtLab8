#include<iostream>
#include<fstream>
using namespace std;
bool ShowFileContent(const char*);
bool AreFilesDifferent(const char*, const char*);

int main() {
    const char* firstFile = "f1.txt";
    const char* secondFile = "f2.txt";
    if (!ShowFileContent(firstFile)) 
    {
        cout << "\nApplication is stopped\n"; return 1;
    }
    if (!ShowFileContent(secondFile)) 
    {
        cout << "\nApplication is stopped\n"; return 1;
    }
    if (!AreFilesDifferent(firstFile, secondFile)) 
    {
        cout << "\nApplication is stopped\n"; return 1;
    }
    return 0;
}

bool ShowFileContent(const char* fn) {
    ifstream fileIn(fn);
    if (!fileIn) 
    {
        cout << "\nFile called" << fn << " is not found.\n"; 
        return false;
    }
    fileIn.seekg(0, 2);  // sets pointer to particular positions
    int currentPos = (int)fileIn.tellg(); // eturns the current “get” position of the pointer in the stream
    fileIn.seekg(0, 0); 
    char* data = new char[currentPos + 1];
    cout << "\n\t\t\t File" << fn << "content :\n";
    while (!fileIn.eof()) 
    {
        fileIn.getline(data, currentPos);
        cout << data << endl;
    }
    fileIn.close();
    return true;
}

bool AreFilesDifferent(const char* firstFileIn, const char* secondFileIn) 
{
    ifstream firstFile(firstFileIn); ifstream secondFile(secondFileIn);
    if (!firstFile) 
    {
        cout << "\nFile " << firstFileIn << " not found.\n"; return false;
    }
    if (!secondFile) 
    {
        cout << "\nFile " << secondFileIn << " not found.\n"; return false;
    }
    firstFile.seekg(0, 2); 
    int firstFileCurrPos = (int)firstFile.tellg();
    firstFile.seekg(0);
    secondFile.seekg(0, 2); 
    int secondFileCurrPos = (int)secondFile.tellg();
    secondFile.seekg(0);
    int counter = 0; 
    int position = 0; 
    char character;
    bool isInFile = true;
    while ((firstFileCurrPos > secondFileCurrPos) ? !firstFile.eof() : !secondFile.eof()) 
    {
        if ((character = firstFile.get()) != secondFile.get()) {
            cout << "\nFirst difference is at " << counter + 1 << " row and at" << position + 1 << " line";
            isInFile = false;
            break;
        }
        else 
        {
            position++;
            if (character == '\n') 
            {
                counter++; position = 0;
            }
        }
    }
    if ((firstFileCurrPos < secondFileCurrPos || secondFileCurrPos < firstFileCurrPos) && isInFile) cout << "\nContent of " << ((firstFileCurrPos < secondFileCurrPos) ? firstFileIn : secondFileIn) << " is inside " << ((firstFileCurrPos > secondFileCurrPos) ? firstFileIn : secondFileIn);
    else if (isInFile) cout << "\nFiles are equal";
    firstFile.close(); secondFile.close();
    return true;
}