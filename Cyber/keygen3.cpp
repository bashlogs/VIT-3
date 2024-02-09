#include<iostream>
#include<vector>
#include<string>
#include <unordered_map>
using namespace std;

//Map for S-Box Substituion for Encryption.
unordered_map<string, string> Sbox = {
    {"0000", "1001"},
    {"0001", "0100"},
    {"0010", "1010"},
    {"0011", "1011"},
    {"0100", "1101"},
    {"0101", "0001"},
    {"0110", "1000"},
    {"0111", "0101"},
    {"1000", "0110"},
    {"1001", "0010"},
    {"1010", "0000"},
    {"1011", "0011"},
    {"1100", "1100"},
    {"1101", "1110"},
    {"1110", "1111"},
    {"1111", "0111"}};

//Map for S-Box Substituion for decryption.
//Inverse of S-box for encrytion.
unordered_map<string, string> SboxInverse = {
    {"1001", "0000"},
    {"0100", "0001"},
    {"1010", "0010"},
    {"1011", "0011"},
    {"1101", "0100"},
    {"0111", "0101"},
    {"1000", "0110"},
    {"0101", "0111"},
    {"0110", "1000"},
    {"0010", "1001"},
    {"0000", "1010"},
    {"0011", "1011"},
    {"1100", "1100"},
    {"1110", "1101"},
    {"1111", "1110"},
    {"0111", "1111"}};



void RotateNibble(vector<int> &W)
{
    int n = W.size();
    int temp;

    for (int i = 0; i < 4; i++)
    {
        temp = W[i];
        W[i] = W[i + 4];
        W[i + 4] = temp;
    }
}

void SubNibble(vector<int> &w)
{
    int n = w.size();

    for (int i = 0; i < n / 4; i++)
    {
        string temp = "";
        for (int j = 4 * i; j < 4 * (i + 1); j++)
        {
            temp += to_string(w[j]);
        }

        temp = Sbox[temp];
        for (int j = 4 * i; j < 4 * (i + 1); j++)
        {
            w[j] = (int)temp[j % 4] - 48;
        }
    }
}


void keyGeneration(vector<int> &key,vector<int> &key1,vector<int> &key2,vector<int> &key3)
{
    vector<int> w0(8, 0);
    vector<int> w1(8, 0);
    
    for (int i = 0; i < 8; i++)
    {
        w0[i] = key[i];
        w1[i] = key[i + 8];
    }

    for (int i = 0; i < 8; i++)
    {
        key1[i] = w0[i];
        key1[i + 8] = w1[i];
    }

    //Printing key1
    cout << "\nKey1 :";
    for (int i = 0; i < 16; i++)
    {
        cout << key1[i];
    }

    vector<int> w2(16, 0);
    vector<int> temp1(8, 0);
    vector<int> temp2(8, 0);
    vector<int> xorwith1 = {1, 0, 0, 0, 0, 0, 0, 0};

    for (int i = 0; i < 8; i++)
    {
        temp2[i] = w1[i];
    }

    RotateNibble(temp2);
    SubNibble(temp2);

    for (int i = 0; i < 8; i++)
    {
        temp1[i] = w0[i] ^ xorwith1[i];
    }

    for (int i = 0; i < 8; i++)
    {
        w2[i] = temp1[i] ^ temp2[i];
    }

    vector<int> w3(8, 0);

    for (int i = 0; i < 8; i++)
    {
        w3[i] = w2[i] ^ w1[i];
    }

    vector<int> w4(8, 0);
    vector<int> xorwith2 = {0, 0, 1, 1, 0, 0, 0, 0};

    for (int i = 0; i < 8; i++)
    {
        temp2[i] = w3[i];
    }

    RotateNibble(temp2);
    SubNibble(temp2);

    for (int i = 0; i < 8; i++)
    {
        temp1[i] = w2[i] ^ xorwith2[i];
    }

    for (int i = 0; i < 8; i++)
    {
        w4[i] = temp1[i] ^ temp2[i];
    }

    vector<int> w5(8, 0);

    for (int i = 0; i < 8; i++)
    {
        w5[i] = w4[i] ^ w3[i];
    }

    for (int i = 0; i < 8; i++)
    {
        key2[i] = w2[i];
        key2[i + 8] = w3[i];
    }

    cout << "\nKey2 :";
    for (int i = 0; i < 16; i++)
    {
        cout << key2[i];
    }

    //Key2 is concatenation of w4 and w5
    for (int i = 0; i < 8; i++)
    {
        key3[i] = w4[i];
        key3[i + 8] = w5[i];
    }

    //Printing key3
    cout << "\nKey3 :";
    for (int i = 0; i < 16; i++)
    {
        cout << key3[i];
    }
}


int main(){

    vector<int> plaintext(16);
    vector<int> key(16);

    cout << "Enter Key : " ;
	for (int i = 0; i < 16; i++)
	{
		cin>>key[i];
	}

    vector<int> key1(16,0);
    vector<int> key2(16,0);
    vector<int> key3(16,0);

    keyGeneration(key,key1,key2,key3);
    
    return 0;
}