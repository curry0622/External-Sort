#include <bits/stdc++.h>

using namespace std;
/*
void printVec(vector<int>& vec) {
    for(int i = 0; i < vec.size(); i++)
        cout << vec.at(i) << endl;
}

void countingSort(vector<int>& vec) {
    map<int, int> mp;
    for(int i = 0; i < vec.size(); i++) {
        if(mp.find(vec.at(i)) == mp.end()) {
            mp[vec.at(i)] = 1;
        }
        else {
            mp[vec.at(i)]++;
        }
    }
    vec.clear();
    map<int, int>::iterator iter;
    for(iter = mp.begin(); iter != mp.end(); iter++) {
        for(int i = 0; i < iter -> second; i++) {
            vec.push_back(iter -> first);
        }
    }
}
*/
int main(int argc, char *argv[]) {
    ios_base::sync_with_stdio(false);
    // create only one buffer as large as you can
    // read data from input.txt and put it into buffer while not reaching eof
        // if buffer is full
            // sort the buffer
            // output buffer content to a text file
            // clear buffer content and keep going on reading input.txt
    // has reached eof
    // sort the buffer
    // output buffer content to a text file
    // merge all text files into output.txt
    int bufferSize = 50000000;
    //cout << "buffer size : " << bufferSize << '\n';
    //cin >> bufferSize;
    vector<int> buffer = vector<int>(bufferSize, -1);
    ifstream fin;
    fin.open(argv[1]);
    //cout << "input size : 100000000" << '\n';
    int index = 0;
    int bufIndex = 0;
    while(!fin.eof()) {
        int get = 0;
        fin >> get;
        if(!fin.eof()) {
            buffer.at(index) = get;
            if(index == buffer.size() - 1) {
                // sort buffer
                sort(buffer.begin(), buffer.end());
                //countingSort(buffer);
                // buffer is full
                ofstream bufOut;
                ostringstream intToStr;
                intToStr << bufIndex;
                string fileName = intToStr.str();
                fileName.append(".txt");
                bufOut.open(fileName.c_str());
                // output buffer data to a file
                for(int i = 0; i < buffer.size(); i++) {
                    bufOut << buffer.at(i) << '\n';
                }
                //cout << "buffer[" << bufIndex << "] : " << endl;
                //printVec(buffer);
                //cout << "==============" << endl;
                buffer = vector<int>(bufferSize, -1);
                bufIndex++;
                index = 0;
            }
            else {
                // buffer isn't full
                index++;
            }
        }
        else {
            break;
        }
    }
    // sort the last buffer
    sort(buffer.begin(), buffer.begin() + index);
    buffer.erase(buffer.begin() + index, buffer.end());
    //
    if(buffer.size() != 0) {
        ofstream bufOut;
        ostringstream intToStr;
        intToStr << bufIndex;
        string fileName = intToStr.str();
        fileName.append(".txt");
        bufOut.open(fileName.c_str());
        // output buffer data to a file
        for(int i = 0; i < buffer.size(); i++) {
            bufOut << buffer.at(i) << '\n';
        }
        //cout << "buffer[" << bufIndex << "] : " << endl;
        //printVec(buffer);
        //cout << endl;
    }
    else {
        bufIndex--;
    }
    // create array of buffer's text file
    ifstream bufIn[bufIndex + 1];
    for(int i = 0; i <= bufIndex; i++) {
        ostringstream tmpIntToStr;
        tmpIntToStr << i;
        string tmpFileName = tmpIntToStr.str();
        tmpFileName.append(".txt");
        bufIn[i].open(tmpFileName.c_str());
    }
    //open output.txt
    ofstream fout;
    fout.open("output.txt");
    // merge files
    bool allFilesEof = false;
    bool firstTime = true;
    int minBufIndex = 0;
    bool bufferEof[bufIndex + 1];
    for(int i = 0; i <= bufIndex; i++) {
        bufferEof[i] = false;
    }
    while(1) {
        // start merging
        if(allFilesEof) {
            break;
        }
        else {
            int minInABuf[10];
            int minOfAllBufs = 0;
            if(firstTime) {
                firstTime = false;
                for(int i = 0; i <= bufIndex; i++) {
                    bufIn[i] >> minInABuf[i];
                }
                minOfAllBufs = minInABuf[0];
                minBufIndex = 0;
                for(int i = 1; i <= bufIndex; i++) {
                    if(minInABuf[i] < minOfAllBufs) {
                        minOfAllBufs = minInABuf[i];
                        minBufIndex = i;
                    }
                }
                // output to file
                fout << minOfAllBufs << '\n';
                //cout << "output buffer[" << minBufIndex << "] : " << minOfAllBufs << endl;
            }
            else {
                // renew the min
                bufIn[minBufIndex] >> minInABuf[minBufIndex];
                if(bufIn[minBufIndex].eof()) {
                    // reach buffer's eof
                    bufferEof[minBufIndex] = true;
                    //cout << "file[" << minBufIndex << "] is eof ====================" << endl;
                }
                for(int i = 0; i <= bufIndex; i++) {
                    if(!bufferEof[i]) {
                        allFilesEof = false;
                        minOfAllBufs = minInABuf[i];
                        minBufIndex = i;
                        //cout << "buffer[" << i << "] isn't eof" << endl;
                        break;
                    }
                    else if(i == bufIndex) {
                        allFilesEof = true;
                    }
                }
                for(int i = 0; i <= bufIndex; i++) {
                    if(!bufferEof[i] && minInABuf[i] < minOfAllBufs) {
                        minOfAllBufs = minInABuf[i];
                        minBufIndex = i;
                    }
                }
                // output to file
                if(!allFilesEof) {
                    fout << minOfAllBufs << '\n';
                    //cout << "output buffer[" << minBufIndex << "] : " << minOfAllBufs << endl;
                }
                //else cout << "allFilesEof = true" << endl;
            }
        }
    }
    cout << "time : " << (double)clock() / CLOCKS_PER_SEC << "S" << '\n';
}

