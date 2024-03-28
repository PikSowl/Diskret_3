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

string HammingCreate(string block) {

    for (int d = 1; d <= block.size(); d *= 2) {
        block.insert(d - 1, "0");
    }

    for (int d = 2; d <= block.size(); d *= 2) {
        bool b = false;
        for(int i = d - 1; i < block.size(); i += 2*d)
            for(int j = i; (j < i + d)&&(j < block.size()); j++)
                if (block[j]=='1') b =! b;

        if (b) block[d - 1] = '1';
        else block[d - 1] = '0';
    }

    bool b = false;
    for(char j : block)
        if (j=='1') b =! b;

    if (b) block[0] = '1';
    else block[0] = '0';

    return block;
}

bool HammingHasErrors(string block) {
    bool b = false;
    for (int i = 0; i <= block.size(); i++)
        if (block[i] == '1') b=!b;

    return b;
}

string HammingFix(string block) {
    int errorCounter = 0;
    for (int d = 2; d <= block.size(); d *= 2) {
        bool b = false;
        for(int i = d - 1; i < block.size(); i += 2*d)
            for(int j = i; (j < i + d)&&(j < block.size()); j++)
                if (block[j]=='1') b =! b;

        if(b) errorCounter += d;
    }
    if(HammingHasErrors(block)) errorCounter += 1;

    if (errorCounter != 0) {
        if (block[errorCounter - 1] == '1') block[errorCounter - 1] = '0';
        else block[errorCounter - 1] = '1';
    }
    return block;
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

    if(block1[2]=='1') block1[2] = '0';
    else block1[2] = '1';
    if(block2[24]=='1') block2[24] = '0';
    else block2[24] = '1';

    cout << block1 << " " << block2 << endl;

    block1 = HammingFix(block1);
    block2 = HammingFix(block2);

    cout << block1 << " " << block2 << endl;
}

void task2() {
    map<char, string> Letters2{};
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

    Letters2['b'].replace(3, 1, "0");
    Letters2['d'].replace(2, 1, "1");

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

    Letters3['a'].replace(1, 1, "1");
    Letters3['d'].replace(2, 1, "1");

    for(auto& [ch, st] : Letters3)
        cout << ch << " " << Letters3[ch] << "; ";
    cout << endl;

    for(auto& [ch, st] : Letters3) {
        Letters3[ch] = HammingFix(st);
        cout << ch << " " << Letters3[ch] << "; ";
    }
}

int main(){
    int i;
    cout << "Task number: ";
    cin >> i;
    cout << endl;
    switch (i) {
        case 1 :{
            task1();
            break;
        }
        case 2:{
            task2();
            break;
        }
        /*case 6:{
            task6();
            break;
        }*/
        default:{
            cout << "wrong number" << endl;
            break;
        }
    }
    return 0;
}
