// K-maps Project.cpp : This file contains the 'main' function. Program execution begins and ends there.
// Notes to self:
    //string str = bitset<3>(4).to_string();  I will use this to convert decimal to binary. 3 represents the number of digits that will be used to represent the number, and 4 is the number I want to convert. 

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <bitset>
#include <sstream>
#include <algorithm>

using namespace std; 

struct KMapMinterm {
    string binary;
    string minterm;
    bool check;
    string variableExpression; 
    KMapMinterm() {
        binary = "";
        minterm = "";
        check = false; 
        variableExpression = "";
    }
    KMapMinterm(string b, string m, bool ch) {
        binary = b; 
        minterm = m; 
        check = ch; 
        variableExpression = "";
    }
    void printMintermInfo() {
        cout << "Minterm in binary: " << binary << ", Minterm number: " << minterm << ", Check status: " << check << ", Variable expression: " << variableExpression << endl;
    }
};

// function to check if two strings differ by one bit 
bool isAdjacent(string m1, string m2) {
    int noOfDiffDigits = 0; 
    for (int i = 0; i < m1.size(); i++) {
        if (m1[i] != m2[i])
            noOfDiffDigits++;
    }
    if (noOfDiffDigits == 1)
        return true;
    else
        return false; 
}
// function to replace the differing digit between two minterms that differ by one digit
string replaceDiffBit(string m1, string m2) {
    string tmp = "";
    for (int i = 0; i < m1.size(); i++) {
        if (m1[i] != m2[i])
            tmp = tmp + "-";
        else
            tmp = tmp + m1[i];
    }
    return tmp; 
}
// function to compare each minterm in a vector with each minterm of another vector and returning a vector with the minterms that differ by just one bit
void compareVectors(vector<KMapMinterm>& v1, vector<KMapMinterm>& v2, vector<KMapMinterm>& adjMinterms) {
    for (int i = 0; i < v1.size(); i++) {
        for (int j = 0; j < v2.size(); j++) {
            bool isGrey = false; 
            isGrey = isAdjacent(v1.at(i).binary, v2.at(j).binary);
            if (isGrey) {
                KMapMinterm tmp1; 
                tmp1.binary = replaceDiffBit(v1.at(i).binary, v2.at(j).binary);
                tmp1.minterm = v1.at(i).minterm + ", " + v2.at(j).minterm;
                v1.at(i).check = true; 
                v2.at(j).check = true; 
                adjMinterms.push_back(tmp1);
            }
        }
    }
}
// function check if a PI is already in a vector and adds it if it is not
void addPrimeImplicant(KMapMinterm m, vector<KMapMinterm>& v) {
    bool isAlreadyInV = false; 
    if (m.check == false) {
        for (int i = 0; i < v.size(); i++) {
            if (v.at(i).binary == m.binary)
                isAlreadyInV = true; 
        }
        if (isAlreadyInV == false)
            v.push_back(m);
    }
}
// function to return a letter depending on the index of a char in the binary representation
string getLetter(char zeroOrOne, int index) {
    if (zeroOrOne == '0') {
        if (index == 0)
            return "A'";
        else if (index == 1)
            return "B'";
        else
            return "C'";
    }
    else if (zeroOrOne == '1') {
        if (index == 0)
            return "A";
        else if (index == 1)
            return "B";
        else
            return "C";
    }  
    else
        return "";
}
// function to convert binary expression to variables
string convertToVariables(string s) {
    string tmp = "";
    bool allDashes = true;
    for (int i = 0; i < s.size(); i++) {
        if (s.at(i) != '-') {
            allDashes = false; 
            tmp += getLetter(s.at(i), i);
        }
    }
    if (!allDashes)
        return tmp;
    else
        return "1";
}
// function to print the K-map
void printKMap(vector<string> toPrint, int noOfVariables, string outputFile) {
    ofstream outputStream1;
    outputStream1.open(outputFile, ios::app);
    if (outputStream1.fail()) {
        cout << "Problem in opening the output file\n";
        return; 
    }
    outputStream1 << "K-map = " << endl; 
    bool isInList = false; 
    if (noOfVariables == 2) {
        for (int i = 0; i < 2; i++) {
            outputStream1 << "    ";
            for (int j = 0; j < 2; j++) {
                isInList = false; 
                if (i == 0) {
                    for (int k = 0; k < toPrint.size(); k++) {
                        if (to_string(j) == toPrint.at(k))
                            isInList = true;
                    }
                }
                else {
                    for (int k = 0; k < toPrint.size(); k++) {
                        if (to_string(j + 2) == toPrint.at(k))
                            isInList = true;
                    }
                }
                if (isInList == true)
                    outputStream1 << "1 ";
                else
                    outputStream1 << "0 ";
            }
            if (i != 1)
                outputStream1 << endl;
        }
    }
    if (noOfVariables == 3) {
        for (int i = 0; i < 2; i++) {
            outputStream1 << "    ";
            for (int j = 0; j < 4; j++) {
                isInList = false;
                if (i == 0) {
                    if (j == 0 || j == 1) {
                        for (int k = 0; k < toPrint.size(); k++) {
                            if (to_string(j) == toPrint.at(k))
                                isInList = true;
                        }
                    }
                    else if (j == 2) {
                        for (int k = 0; k < toPrint.size(); k++) {
                            if (to_string(j + 1) == toPrint.at(k))
                                isInList = true;
                        }
                    }
                    else if (j == 3) {
                        for (int k = 0; k < toPrint.size(); k++) {
                            if (to_string(j - 1) == toPrint.at(k))
                                isInList = true;
                        }
                    }
                }
                else {
                    if (j == 0 || j == 1) {
                        for (int k = 0; k < toPrint.size(); k++) {
                            if (to_string(j + 4) == toPrint.at(k))
                                isInList = true;
                        }
                    }
                    else if (j == 2) {
                        for (int k = 0; k < toPrint.size(); k++) {
                            if (to_string(j + 5) == toPrint.at(k))
                                isInList = true;
                        }
                    }
                    else if (j == 3) {
                        for (int k = 0; k < toPrint.size(); k++) {
                            if (to_string(j + 3) == toPrint.at(k))
                                isInList = true;
                        }
                    }
                }
                if (isInList == true)
                    outputStream1 << "1 ";
                else
                    outputStream1 << "0 ";
            }
            if(i != 1)
                outputStream1 << endl;
        }
    }
}

int main()
{
    // asking the user to cin the input file directory 
    cout << "K-Map Boolean Simplifier" << endl << endl << "Please enter the input file directory: "; 
    string inputFileDirectory; // C:\\Users\\zeinn\\Desktop\\uni\\fall 2022\\digital design\\projects\\K-maps Project input and output files\\input.txt
    getline(cin, inputFileDirectory);

    // opening the file
    ifstream inputStream; 
    inputStream.open(inputFileDirectory);
    if (inputStream.fail()) {
        cout << "Problem in opening the file\n";
        return 1;
    }
    
    // creating the string that contains the file path to the output file
    string outputFileDirectory = inputFileDirectory;
    int pos = inputFileDirectory.find("input.txt");
    outputFileDirectory.erase(pos);
    outputFileDirectory += "output.txt";

    // loop to read each line in the file 
    bool firstLine = true; 
    string lineFromFile;
    int caseCounter = 0; 
    while (!inputStream.eof()) {
        getline(inputStream, lineFromFile);
        if (firstLine) {
            firstLine = false; // since I'm using .eof to read the file, I will ignore the first line in the input file
            caseCounter++;
        }
        else {
            // reading the line and storing its components
            istringstream X(lineFromFile);
            string variablesNumber;
            string mintermsNumber;
            string theMinterms;
            getline(X, variablesNumber, ' ');
            getline(X, mintermsNumber, ' ');
            getline(X, theMinterms);

            // opening the output file and creating an ofstream that will be used to write errors and the test case number
            ofstream outputStream4;
            outputStream4.open(outputFileDirectory, ios::app);
            if (outputStream4.fail()) {
                cout << "Problem in opening the output file\n";
            }

            // validating each line
            outputStream4 << caseCounter << endl; // printing the case number
            caseCounter++;
            if (stoi(variablesNumber) < 2 || stoi(variablesNumber) > 3) {
                outputStream4 << "Number of variables should be 2 or 3." << endl << endl;
                continue; 
            }
            int noOfMinterms = stoi(variablesNumber); // I meant noOfVariables, not noOfMinterms, but I already wrote the code so I'm just gonna leave it
            vector<KMapMinterm> KMinterms; // the minterms will all first be stored in this vector
            vector<string> mintermsToPrint; // I'll use this vector to print the map
            istringstream split(theMinterms); // splitting the string to get the individual minterms and storing the minterm numbers in the 'minterm' field of the KMinterms vector
            string token; int mintermsCounter = 0;
            while (getline(split, token, ' ')) {
                KMapMinterm M1;
                M1.minterm = token;
                KMinterms.push_back(M1);
                mintermsToPrint.push_back(token);
                mintermsCounter++;
            }
            bool isMintermValueValid = true; 
            if (stoi(variablesNumber) == 2) {
                if (stoi(mintermsNumber) < 0 || stoi(mintermsNumber) > 4) {
                    outputStream4 << "The number of minterms cannot be less than 0 or greater than 4 for 2 variable functions." << endl << endl;
                    continue; 
                }
                for (int i = 0; i < mintermsToPrint.size(); i++) {
                    if (stoi(mintermsToPrint.at(i)) < 0 || stoi(mintermsToPrint.at(i)) > 3) {
                        outputStream4 << "You cannot have a minterm value less than 0 or greater than 3 for 2 variable functions." << endl << endl;
                        isMintermValueValid = false; 
                        break; 
                    }
                }
                if (isMintermValueValid == false)
                    continue; 
            }
            bool isMintermValueValid2 = true; 
            if (stoi(variablesNumber) == 3) {
                if (stoi(mintermsNumber) < 0 || stoi(mintermsNumber) > 8) {
                    outputStream4 << "The number of minterms cannot be less than 0 or greater than 8 for 3 variable functions." << endl << endl;
                    continue;
                }
                for (int i = 0; i < mintermsToPrint.size(); i++) {
                    if (stoi(mintermsToPrint.at(i)) < 0 || stoi(mintermsToPrint.at(i)) > 7) {
                        outputStream4 << "You cannot have a minterm value less than 0 or greater than 7 for 3 variable functions." << endl << endl;
                        isMintermValueValid2 = false; 
                        break;
                    }
                }
                if (isMintermValueValid2 == false)
                    continue; 
            }
            if (mintermsCounter != stoi(mintermsNumber)) {
                outputStream4 << "The second number in the line does not match the number of minterms that follows." << endl << endl;
                continue;
            }
            
            // printing the kmap into the file 
            printKMap(mintermsToPrint, noOfMinterms, outputFileDirectory);

            // converting the strings to ints and then to binary and storing the binary number in the 'binary' field of the KMinterms vector
            string str;
            int tmpInt;
            for (int i = 0; i < KMinterms.size(); i++) {
                tmpInt = stoi(KMinterms.at(i).minterm);
                if (noOfMinterms == 3)
                    str = bitset<3>(tmpInt).to_string();
                else
                    str = bitset<2>(tmpInt).to_string();
                KMinterms.at(i).binary = str;
            }

            // sorting the KMinterms according to the number of ones in each minterm.
            vector<KMapMinterm> MintermsWithZeroOnes, MintermsWithOneOnes, MintermsWithTwoOnes, MintermsWithThreeOnes;
            int onesCount;
            char ch = '1';
            for (int i = 0; i < KMinterms.size(); i++) {
                onesCount = count(KMinterms.at(i).binary.begin(), KMinterms.at(i).binary.end(), ch);
                if (onesCount == 0) {
                    MintermsWithZeroOnes.push_back(KMinterms.at(i));
                }
                else if (onesCount == 1) {
                    MintermsWithOneOnes.push_back(KMinterms.at(i));
                }
                else if (onesCount == 2) {
                    MintermsWithTwoOnes.push_back(KMinterms.at(i));
                }
                else if (onesCount == 3) {
                    MintermsWithThreeOnes.push_back(KMinterms.at(i));
                }
            }

            // comparing each minterm in each vector with each minterm of the vectors of a higher number of ones and creating the new column
            int noOfDiffDigits, indexOfDiffChar;
            vector <KMapMinterm> colIZerosAndOnes, colIOnesAndTwos, colITwosAndThrees;
            compareVectors(MintermsWithZeroOnes, MintermsWithOneOnes, colIZerosAndOnes);
            compareVectors(MintermsWithOneOnes, MintermsWithTwoOnes, colIOnesAndTwos);
            if (noOfMinterms == 3)
                compareVectors(MintermsWithTwoOnes, MintermsWithThreeOnes, colITwosAndThrees);

            // creating the second column
            vector <KMapMinterm> colIIZerosOnesTwos, colIIOnesTwosThrees;
            compareVectors(colIZerosAndOnes, colIOnesAndTwos, colIIZerosOnesTwos);
            if (noOfMinterms == 3)
                compareVectors(colIOnesAndTwos, colITwosAndThrees, colIIOnesTwosThrees);

            // creating the third column if we have 3 minterms
            vector <KMapMinterm> colIII;
            if (noOfMinterms == 3) {
                compareVectors(colIIZerosOnesTwos, colIIOnesTwosThrees, colIII);
            }

            // creating the column with all prime implicants
            vector<KMapMinterm> primeImplicants;  // instead of creating this many loops, we could have collected all the kmapminterm vectors in a single vector and looped over that
            for (int i = 0; i < MintermsWithZeroOnes.size(); i++) {
                addPrimeImplicant(MintermsWithZeroOnes.at(i), primeImplicants);
            }
            for (int i = 0; i < MintermsWithOneOnes.size(); i++) {
                addPrimeImplicant(MintermsWithOneOnes.at(i), primeImplicants);
            }
            for (int i = 0; i < MintermsWithTwoOnes.size(); i++) {
                addPrimeImplicant(MintermsWithTwoOnes.at(i), primeImplicants);
            }
            for (int i = 0; i < colIZerosAndOnes.size(); i++) {
                addPrimeImplicant(colIZerosAndOnes.at(i), primeImplicants);
            }
            for (int i = 0; i < colIOnesAndTwos.size(); i++) {
                addPrimeImplicant(colIOnesAndTwos.at(i), primeImplicants);
            }
            for (int i = 0; i < colITwosAndThrees.size(); i++) {
                addPrimeImplicant(colITwosAndThrees.at(i), primeImplicants);
            }
            for (int i = 0; i < colIIZerosOnesTwos.size(); i++) {
                addPrimeImplicant(colIIZerosOnesTwos.at(i), primeImplicants);
            }
            if (noOfMinterms == 3) {
                for (int i = 0; i < MintermsWithThreeOnes.size(); i++)
                    addPrimeImplicant(MintermsWithThreeOnes.at(i), primeImplicants);
                for (int i = 0; i < colIIOnesTwosThrees.size(); i++)
                    addPrimeImplicant(colIIOnesTwosThrees.at(i), primeImplicants);
                for (int i = 0; i < colIII.size(); i++)
                    addPrimeImplicant(colIII.at(i), primeImplicants);
            }

            // finding the variable expression for all the PIs in the PI vector
            for (int i = 0; i < primeImplicants.size(); i++) {
                primeImplicants.at(i).variableExpression = convertToVariables(primeImplicants.at(i).binary);
            }

            // creating an output stream to print the boolean expression into the output file
            ofstream outputStream2; 
            outputStream2.open(outputFileDirectory, ios::app);
            if (outputStream2.fail()) {
                cout << "Problem in opening the output file\n";
            }
            else {
                outputStream2 << endl << "F = ";
                // printing the expression for the finalized boolean expression
                for (int i = 0; i < primeImplicants.size(); i++) {
                    if (i != primeImplicants.size() - 1)
                        outputStream2 << primeImplicants.at(i).variableExpression << " + ";
                    else
                        outputStream2 << primeImplicants.at(i).variableExpression;
                }
            }
            outputStream2 << endl << endl;
        }
    }
    inputStream.close();
    cout << "\nOutput file successfully created in the same directory as the input file. Required data is stored there.\n";
}


// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu
