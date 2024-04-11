#include <iostream>
#include <cmath>
#include <bitset>
#include <string>
#include <map>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::bitset;
using std::map;
using std::byte;
using std::pair;

string SwapBit(string block, int poz){
    if ('0' == block[poz]) block[poz] = '1';
    else block[poz] = '0';
    return block;
}

string HammingCreate(string block) {

    for (int d = 1; d <= block.size(); d *= 2) {
        block.insert(d - 1, "0");
    }

    for (int d = 1; d <= block.size(); d *= 2) {
        bool b = false;
        for(int i = d - 1; i < block.size(); i += 2*d)
            for(int j = i; (j < i + d)&&(j < block.size()); j++)
                if (block[j]=='1') b =! b;

        if (b) block[d - 1] = '1';
        else block[d - 1] = '0';
    }

    /*bool b = false;
    for(char j : block)
        if (j=='1') b =! b;

    if (b) block[0] = '1';
    else block[0] = '0';
*/
    return block;
}

int FindErrors(string block){
    int errorCount = -1;
    for (int d = 1; d <= block.size(); d *= 2) {
        bool b = false;
        for(int i = d - 1; i < block.size(); i += 2*d)
            for(int j = i; (j < i + d)&&(j < block.size()); j++)
                if (block[j]=='1') b =! b;

        if (b) errorCount += d;
    }
    return errorCount;
}

bool HammingHasErrors(string block) {
    int errorCount = FindErrors(block);
    return (-1 != errorCount);
}

string HammingFix(string block) {
    int errorCount = FindErrors(block);
    if (-1 != errorCount)
        block = SwapBit(block, errorCount);
    return block;
}

string IntToByte(int num, int byteNum = 1){
    string line;
    for(long long i = 1; i < pow (256, byteNum); i*=2){
        if (bool((num / i) % 2)) line.insert(0,"1");
        else line.insert(0,"0");
    }
    return line;
}

string StringToByte(const string& line){
    string byteLine;
    for(char c : line)
        byteLine.append(IntToByte(int(c)));

    return byteLine;
}


void task1() {
    string word = "computer";
    string binary, block1, block2;

    for (char ch: word)
        binary += bitset<8>(ch).to_string();

    for (int i = 0; i < 32; i++) {
        block1.push_back(binary[i]);
        block2.push_back(binary[i + 32]);
    }

    block1 = HammingCreate(block1);
    block2 = HammingCreate(block2);

    cout << block1 << " " << block2 << endl;

    block1 = SwapBit(block1, 2);
    block2 = SwapBit(block2, 24);

    cout << block1 << " " << block2 << endl;

    block1 = HammingFix(block1);
    block2 = HammingFix(block2);

    cout << block1 << " " << block2 << endl;
}

void task2() {
    map<char, string> Letters2;
    string abcd = "abcdefgh";

    int startingSize = int(log2 (double(abcd.size())));
    int counter = 0;
    for(char ch: abcd){
        string buffer;
        int temp = counter;
        for(int i = 0; i < startingSize; i++) {
            if (0 == temp%2)
                buffer.insert(0, "0");
            else
                buffer.insert(0, "1");
            temp/=2;
        }
        Letters2.insert({ch, buffer});
        counter++;
    }

    for(auto& [ch, st] : Letters2) {
        Letters2[ch] = HammingCreate(st);
        cout << ch << " " << Letters2[ch] << "; ";
    }
    cout << endl;

    Letters2['b'] = SwapBit(Letters2['b'], 3);
    Letters2['d'] = SwapBit(Letters2['d'], 2);

    for(auto& [ch, st] : Letters2)
        cout << ch << " " << Letters2[ch] << "; ";
    cout << endl;

    for(auto& [ch, st] : Letters2)
        if (HammingHasErrors(st)) cout << "Error in letter '" << ch << "' ";
    cout << endl << endl;

    map<char, string> Letters3{};
    counter = 0;
    for(char ch: abcd){
        string buffer;
        int temp = counter;
        for(int i = 0; i < startingSize; i++) {
            if (0 == temp%2)
                buffer.insert(0, "0");
            else
                buffer.insert(0, "1");
            temp/=2;
        }
        Letters3.insert({ch, buffer});
        counter++;
    }

    for(auto& [ch, st] : Letters3) {
        Letters3[ch] = HammingCreate(st);
        cout << ch << " " << Letters3[ch] << "; ";
    }
    cout << endl;

    Letters3['b'] = SwapBit(Letters3['b'], 3);
    Letters3['d'] = SwapBit(Letters3['d'], 2);

    for(auto& [ch, st] : Letters3)
        cout << ch << " " << Letters3[ch] << "; ";
    cout << endl;

    for(auto& [ch, st] : Letters3) {
        Letters3[ch] = HammingFix(st);
        cout << ch << " " << Letters3[ch] << "; ";
    }
}

void task3(){
    string line;
    cout << "Enter line:";
    cin >> line;

    //addddghtyyyyyyyyyiklopppppppppppp
    string rLine;

    for(int i = 0; i < line.size(); i++){
        if (line[i] == line[i+1]) {
            int pos = i;
            for (;(line[i] == line[i+1]) && (line.size() > i + 1); i++) { }
            rLine.push_back(char(i - pos + 1));
            rLine.push_back(line[i]);
        }
        else {
            int pos = i;
            for (;(line[i] != line[i+1]) && (line.size() > i + 1); i++) { }
            if (line.size() != i + 1) i--;
            rLine.push_back(char(0));
            rLine.push_back(char(i - pos + 1));
            for (int j = pos; i >= j; j++) rLine.push_back(line[j]);

        }
    }

    cout << endl;
    for(char c : rLine)
        cout << int(c) << ' ';

    cout << endl << endl;

    string bLine = StringToByte(rLine);
    for(int i = 0; i < bLine.size(); i++){
        cout << bLine[i];
        if (0 == (i + 1) % 8) cout << ' ';
    }
}

void task5() {
    string line;
    cout << "Enter line:";
    cin >> line;

    map<char, float> probability = {{'a', 0.1},
                                    {'b', 0.15},
                                    {'c', 0.05},
                                    {'d', 0.5},
                                    {'e', 0.1},
                                    {'f', 0.1}};

    map<char,pair<float, float>> lineDistance;

    float temp = 0;
    while (!probability.empty()){
        float max = 0;
        char curent;
        for (auto& [c,  f] : probability){
            if (max < f) {
                max = f;
                curent = c;
            }
        }
        lineDistance[curent] = pair<float, float>(temp, temp + max);
        temp += max;
        probability.erase(curent);
    }
    for (auto& [c,  f] : lineDistance){
        cout << c << ':' << get<0>(f) << "," <<  get<1>(f) << " ";
    }
    long double  leftB = 0, rightB = 1, dist;
    cout << endl;
    for (char ch : line){
        dist = rightB-leftB;
        rightB = leftB + (dist)*get<1>(lineDistance[ch]);
        leftB = leftB + (dist)*get<0>(lineDistance[ch]);
    }
    cout << leftB << ' ' << rightB << endl;
    int answer;
    for(int i = 1;i > 0; i++){
        if(1 <= (rightB-leftB)*pow(10,i)){
            answer =  int(leftB*pow(10,i)+2);
            i = -9;
        }
    }
    cout << answer << endl;
    string byteAnswer = IntToByte(answer, 3);

    for(int i = 0; i < byteAnswer.size(); i++){
        cout << byteAnswer[i];
        if (0 == (i + 1) % 8) cout << ' ';
    }

}

int main(){
    int t;
    cout << "Task number: ";
    cin >> t;
    cout << endl;
    switch (t) {
        case 1 :{
            task1();
            break;
        }
        case 2:{
            task2();
            break;
        }
        case 3:{
            task3();
            break;
        }
        case 5:{
            task5();
            break;
        }
        default:{
            cout << "wrong number" << endl;
            break;
        }
    }
    return 0;
}
