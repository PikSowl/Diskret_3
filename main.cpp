#include <iostream>
#include <cmath>
#include <bitset>
#include <string>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::bitset;

string HammingCreate(string block) {

    for (int d = 1; d <= 32; d *= 2) {
        block.insert(d - 1, "0");
    }

    for (int d = 1; d <= 32; d *= 2) {
        bool b = false;
        for(int i = d - 1; i < block.size(); i += 2*d)
            for(int j = i; (j < i + d)&&(j < block.size()); j++)
                if (block[j]=='1') b =! b;

        if (b) block[d - 1] = '1';
        else block[d - 1] = '0';
    }
    return block;
}

string HammingFix(string block) {
    int errorCounter = 0;
    for (int d = 1; d <= 32; d *= 2){
        bool b = (block[d-1] == '1');
        for(int i = d - 1; i < block.size(); i += 2*d)
            for(int j = i; (j < i + d)&&(j < block.size()); j++)
                if(block[j]=='1') b =! b;

        if((block[d-1] == '1') != b) errorCounter += d;
    }

    cout << errorCounter << " ";

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

    cout << endl << block1 << " " << block2 << endl;
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
        /*case 2:{
            task2();
            break;
        }
        case 6:{
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
