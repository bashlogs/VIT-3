#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
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

//Matrix for Polynomial Reduction in encryption
int Smatrix[2][2] = {{1, 4}, {4, 1}};

//Matrix for Polynomial Reduction in decryption
int InverseSmatrix[2][2] = {{9, 2}, {2, 9}};

//4 bit binary=X^4+X+1 is polynomial irreducible
vector<int> irreducible = {1, 0, 0, 1, 1};

//Exchange 1st and 2nd nibble.
//e.g. 1101 1001 => 1001 1101
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

//Exchange 2nd and 4th nibble.
//e.g. 1001 1101 1110 0011 => 1001 0011 1110 1101
void ShiftRow(vector<int> &W)
{
    int temp;
    for (int i = 4; i < 8; i++)
    {
        temp = W[i];
        W[i] = W[i + 8];
        W[i + 8] = temp;
    }
}

//Substitues values of S-box with given nibbles.
void SubNibble(vector<int> &w)
{
    int n = w.size();

    for (int i = 0; i < n / 4; i++)
    {
        //converting the nibble to string as map is of string.
        string temp = "";
        for (int j = 4 * i; j < 4 * (i + 1); j++)
        {
            temp += to_string(w[j]);
        }

        //Substituting the Sbox value
        temp = Sbox[temp];

        //replacing with original nibble.
        for (int j = 4 * i; j < 4 * (i + 1); j++)
        {
            w[j] = (int)temp[j % 4] - 48;
        }
    }
}

//Substitues values of InverseS-box with given nibbles.
void InverseSubNibble(vector<int> &w)
{
    int n = w.size();

    for (int i = 0; i < n / 4; i++)
    {
        //converting the nibble to string as map is of string.
        string temp = "";
        for (int j = 4 * i; j < 4 * (i + 1); j++)
        {
            temp += to_string(w[j]);
        }

        //Substituting the InverseSbox value
        temp = SboxInverse[temp];

        //replacing with original nibble.
        for (int j = 4 * i; j < 4 * (i + 1); j++)
        {
            w[j] = (int)temp[j % 4] - 48;
        }
    }
}

//Convert binary string to decimal.
int BinaryToDecimal(string s)
{
    int value = stoull(s, 0, 2);

    return value;
}

//returns binary value in terms of vector from decimal value.
vector<int> DecimalToBinary(int n)
{
    //vector to store binary bits.
    vector<int> binary;

    //converting decimal to binary.
    while (n > 0)
    {
        binary.push_back(n % 2);
        n = n / 2;
    }

    // reversing the vector as it stores the binary value in reverse.
    reverse(binary.begin(), binary.end());

    //if length is less than four converting it to 4 bit binary by adding zeros at front.
    if (binary.size() == 2)
    {
        binary.insert(binary.begin(), 0);
        binary.insert(binary.begin(), 0);
    }

    else if (binary.size() == 3)
        binary.insert(binary.begin(), 0);

    return binary;
}

//Reduce the given value to four bit binary using polynomial irreducible.
int polynomialReducer(int value)
{
    //If value is less than 16 means it is already four bit so return same value;
    if (value < 16)
        return value;

    //condition where we get two X^3 while reducing so we cannot solve using XOR operation so directly returning the value.
    if (value == 135)
        return 14;

    //binary value of given decimal value.
    vector<int> reduceMe = DecimalToBinary(value);

    //Reducing the decimal value to 4bit binary
    while (reduceMe.size() > 4)
    {
        for (int i = 0; i < 5; i++)
        {
            //XOR with polynomial irreducible.
            reduceMe[i] = reduceMe[i] ^ irreducible[i];
        }

        while (reduceMe[0] == 0)
        {
            //Removing all MSB zeros.
            reduceMe.erase(reduceMe.begin());
        }
    }

    //converting the reduced value to binary string.
    string temp = "";
    for (int i = 0; i < reduceMe.size(); i++)
    {
        temp += to_string(reduceMe[i]);
    }

    //returning the reduced decimal value.
    return BinaryToDecimal(temp);
}

//Function to perform mixcolumn operation in encryption.
void MixColumn(vector<int> &plain)
{
    //Matrix for plaintext message. First two nibbles become first column and remaining two become second column.
    int plainmatrix[2][2] = {{0, 0}, {0, 0}};
    //Matrix to store the values after multiplication of plainmatrix with Smatrix.
    int multiplied[2][2] = {{0, 0}, {0, 0}};

    //Converting all nibble(4-bit) to decimal and storing it to plainMatrix.
    int nibble = 0;
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            string temp = "";
            for (int k = 4 * nibble; k < 4 * (nibble + 1); k++)
            {
                temp += to_string(plain[k]);
            }

            plainmatrix[j][i] = BinaryToDecimal(temp);
            nibble++;
        }
    }

    //Multiplication of plainmatrix with SMatrix.
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            //Storing multiplied value and also passing it to polynomialReducer to reduce it to 4-bit binary.
            multiplied[i][j] = (polynomialReducer(Smatrix[i][0] * plainmatrix[0][j])) ^ (polynomialReducer(Smatrix[i][1] * plainmatrix[1][j]));
        }
    }

    //start with first nibble
    nibble = 0;
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            //converting the decimal value to binary and storing it to vector temp;
            vector<int> temp;
            temp = DecimalToBinary(multiplied[j][i]);

            // Replacing the resultant mixcolumn value with original value in plaintext;
            for (int k = 4 * nibble; k < 4 * (nibble + 1); k++)
            {
                plain[k] = temp[k % 4];
            }
            //next nibble.
            nibble++;
        }
    }
}

//Function to perform mixcolumn operation in decryption.
void InverseMixColumn(vector<int> &cipher)
{
    //Matrix for ciphertext message. First two nibbles become first column and remaining two become second column.
    int ciphermatrix[2][2] = {{0, 0}, {0, 0}};
    //Matrix to store the values after multiplication of ciphermatrix with Smatrix.
    int multiplied1[2][2] = {{0, 0}, {0, 0}};

    //Converting all nibble(4-bit) to decimal and storing it to cipherMatrix.
    int nibble = 0;
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            string temp = "";
            for (int k = 4 * nibble; k < 4 * (nibble + 1); k++)
            {
                temp += to_string(cipher[k]);
            }

            ciphermatrix[j][i] = BinaryToDecimal(temp);
            nibble++;
        }
    }

    //Multiplication of ciphermatrix with SMatrix.
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            //Storing multiplied value and also passing it to polynomialReducer to reduce it to 4-bit binary.
            multiplied1[i][j] = (polynomialReducer(InverseSmatrix[i][0] * ciphermatrix[0][j])) ^ (polynomialReducer(InverseSmatrix[i][1] * ciphermatrix[1][j]));
        }
    }

    //start with first nibble
    nibble = 0;
    for (int i = 0; i < 2; i++)
    {
        //converting the decimal value to binary and storing it to vector temp;
        for (int j = 0; j < 2; j++)
        {
            //converting the decimal value to binary and storing it to vector temp;
            vector<int> temp;
            temp = DecimalToBinary(multiplied1[j][i]);

            // Replacing the resultant mixcolumn value with original value in ciphertext;
            for (int k = 4 * nibble; k < 4 * (nibble + 1); k++)
            {
                cipher[k] = temp[k % 4];
            }
            //next nibble.
            nibble++;
        }
    }
}


//Key generation for encryption.
//There are total three keys key1,key2,key3.
void keyGeneration(vector<int> &key,vector<int> &key1,vector<int> &key2,vector<int> &key3)
{
    //declaring w0 and w1 for key1;
    vector<int> w0(8, 0);
    vector<int> w1(8, 0);
    
    //w0 is first eight bits of original key and w1 is last eight bits of original key.
    for (int i = 0; i < 8; i++)
    {
        w0[i] = key[i];
        w1[i] = key[i + 8];
    }

    //key1 is concatenation of w0 andd w1.
    for (int i = 0; i < 8; i++)
    {
        key1[i] = w0[i];
        key1[i + 8] = w1[i];
    }

    //Printing key1
    cout << "\nKEY1 :";
    for (int i = 0; i < 16; i++)
    {
        cout << key1[i] << " ";
    }

    //for calculating w2 we perform following operations
    //w2 = w0 XOR 10000000 XOR SubstituteNibble(RotateNibble(w1))
    //temp1 is w0 XOR 10000000
    //temp2 is SubstituteNibble(RotateNibble(w1))
    //xorwith1 is 10000000
    //declaring w2 and two temporary vectors for
    vector<int> w2(16, 0);
    vector<int> temp1(8, 0);
    vector<int> temp2(8, 0);
    vector<int> xorwith1 = {1, 0, 0, 0, 0, 0, 0, 0};

    //storing value of w1 to temp2
    for (int i = 0; i < 8; i++)
    {
        temp2[i] = w1[i];
    }

    //Rotating nibble of temp2 i.e.w1
    RotateNibble(temp2);
    //Substituting nibble of temp2 i.e.w1
    SubNibble(temp2);

    //performing w0 XOR 10000000
    for (int i = 0; i < 8; i++)
    {
        temp1[i] = w0[i] ^ xorwith1[i];
    }

    //performing w0 XOR 10000000 XOR SubstituteNibble(RotateNibble(w1)).
    for (int i = 0; i < 8; i++)
    {
        w2[i] = temp1[i] ^ temp2[i];
    }

    //w3 is XOR operation of w1 and w2.
    vector<int> w3(8, 0);

    for (int i = 0; i < 8; i++)
    {
        w3[i] = w2[i] ^ w1[i];
    }

    //declaring w4 and xorwith 2;
    //for calculating w4 we perform operations same as w2
    //w4 = w2 XOR 00110000 XOR SubstituteNibble(RotateNibble(w3)).
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

    //Calculating w5
    //w5 = w4 XOR w3.
    vector<int> w5(8, 0);

    for (int i = 0; i < 8; i++)
    {
        w5[i] = w4[i] ^ w3[i];
    }

    //Key2 is concatenation of w2 and w3
    for (int i = 0; i < 8; i++)
    {
        key2[i] = w2[i];
        key2[i + 8] = w3[i];
    }

    //Printing key2
    cout << "\nKEY2 :";
    for (int i = 0; i < 16; i++)
    {
        cout << key2[i] << " ";
    }

    //Key2 is concatenation of w4 and w5
    for (int i = 0; i < 8; i++)
    {
        key3[i] = w4[i];
        key3[i + 8] = w5[i];
    }

    //Printing key3
    cout << "\nKEY3 :";
    for (int i = 0; i < 16; i++)
    {
        cout << key3[i] << " ";
    }
}

void encryption(vector<int> key1,vector<int> key2,vector<int> key3,vector<int> &plaintext)
{
    //Encryption shown as in diagram.
    //Performing Add Round key1
    for(int i=0;i<16;i++)
    {
        plaintext[i] = plaintext[i] ^ key1[i];
    }

    //Substitute nibble
    SubNibble(plaintext);
    //Shift row
    ShiftRow(plaintext);
    //mixcolunm operation
    MixColumn(plaintext);

    //Performing Add Round key2
    for(int i=0;i<16;i++)
    {
        plaintext[i] = plaintext[i] ^ key2[i];
    }
    SubNibble(plaintext);
    ShiftRow(plaintext);

    //Performing Add Round key3
    for(int i=0;i<16;i++)
    {
        plaintext[i] = plaintext[i] ^ key3[i];
    }

    //Printing Ciphertext
    cout << "\nCipher Text : ";
    for(int i=0;i<16;i++)
    {
        cout << plaintext[i] << " " << ends;
    }
}

void decryption(vector<int> key1,vector<int> key2,vector<int> key3,vector<int> &ciphertext)
{
    //Decryption is exactly opposite of encryption

    ////Performing Add Round key3
    for(int i=0;i<16;i++)
    {
        ciphertext[i] = ciphertext[i] ^ key3[i];
    }

    //Shift row operation
    ShiftRow(ciphertext);
    //Inverse Substitute Nibble
    InverseSubNibble(ciphertext);

    //Performing Add Round key2
    for(int i=0;i<16;i++)
    {
        ciphertext[i] = ciphertext[i] ^ key2[i];
    }

    //Inverse mix column
    InverseMixColumn(ciphertext);
    //Shift row operation
    ShiftRow(ciphertext);
    //Inverse Substitute Nibble
    InverseSubNibble(ciphertext);

    //Performing Add Round key1
    for(int i=0;i<16;i++)
    {
        ciphertext[i] = ciphertext[i] ^ key1[i];
    }

    //Printing Decrypted Message
    cout << "\nDecrypted Message : ";
    for(int i=0;i<16;i++)
    {
        cout << ciphertext[i] << " " << ends;
    }
}


int main()
{
    //Plaintext message  = {1 1 0 1 0 1 1 1 0 0 1 0 1 0 0 0};
    vector<int> plaintext;


    //Input Key = 0 1 0 0 1 0 1 0 1 1 1 1 0 1 0 1
    vector<int> key;

    cout<<"Enter the 16 bit plaintext: ";
    for (int i = 0; i < 16; i++)
	{
        int a;
        cin>>a;
		plaintext.push_back(a);
	}


    cout<<"Enter the 16 bit key: ";
    for (int i = 0; i < 16; i++)
	{
		int a;
        cin>>a;
		key.push_back(a);
	}

    //Three keys for encryption initialized it to zeros.
    vector<int> key1(16,0);
    vector<int> key2(16,0);
    vector<int> key3(16,0);

    //Performing keyGeneration, it will return key1, key2, key3
    keyGeneration(key,key1,key2,key3);

    //Copying the plaintext message to ciphertext
    vector<int> ciphertext(16,0);
    ciphertext = plaintext;

    cout << "\n\n";
    //encryption, input plaintext, prints ciphertext(encrypted message).
    encryption(key1,key2,key3,ciphertext);
    //decryption, input ciphertext, prints decrypted message(original message).
    decryption(key1,key2,key3,ciphertext);
}