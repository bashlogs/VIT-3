package Ass_1;
import java.lang.reflect.Array;
import java.util.*;

public class DES {
    int plaintext[] = { 0, 0, 1, 1, 0, 1, 1, 0 };
    int cipherText[] = new int[8];
    int key[] = { 0, 0, 1, 0, 0, 1, 0, 1, 1, 1 };
    int P10[] = { 3, 5, 2, 7, 4, 10, 1, 9, 8, 6 };
    int P8[] = { 6, 3, 7, 4, 8, 5, 10, 9 };
    int P4[] = { 2, 4, 3, 1 };
    int EP[] = { 4, 1, 2, 3, 2, 3, 4, 1 };
    int IP[] = { 2, 6, 3, 1, 4, 8, 5, 7 };
    int IPI[] = { 4, 1, 3, 5, 7, 2, 8, 6 };

    String S0[][] = {{"01", "00", "11", "10"},
                    {"11", "10", "01", "00"},
                    {"00", "10", "01", "11"},
            { "11", "01", "11", "10" } };
    String S1[][] = {{"00", "01", "10", "11"},
                    {"10", "00", "01", "11"},
                    {"11", "00", "01", "00"},
            { "10", "01", "00", "11" } };
    
    int k1[] = new int[8]; // Key 1 -> 00101111
    int k2[] = new int[8]; // Key 2 -> 11101010

    public int[] leftRotate(int arr[], int numRotate) {

        for (int i = 0; i < numRotate; i++) {
            int t = arr[0];
            for (int j = 1; j < arr.length; j++) {
                arr[j - 1] = arr[j];
            }
            arr[arr.length - 1] = t;
        }

        return arr;
    }

    public int[] P10Permutation(int arr[], int k[]) {
        int after[] = new int[10];
        for (int i = 0; i < 10; i++) {
            after[i] = arr[k[i] - 1];
        }

        return after;
    }

    public int[] P8Permutation(int arr[], int k[]) {
        int after[] = new int[8];
        for (int i = 0; i < 8; i++) {
            after[i] = arr[k[i] - 1];
        }

        return after;
    }

    public int[] initialPermutation(int arr[]) {
        int after[] = new int[arr.length];
        for (int i = 0; i < 8; i++) {
            after[i] = arr[IP[i] - 1];
        }

        return after;
    }

    public int[] concatenateArrays(int a1[], int a2[]) {
        int con[] = new int[a1.length + a2.length];

        for (int i = 0; i < a1.length; i++) {
            con[i] = a1[i];
        }

        for (int i = 0; i < a2.length; i++) {
            con[i + a1.length] = a2[i];
        }

        return con;
    }
    
    public int[] expansionPermutation(int arr[]) {
        int a[] = new int[8];

        for (int i = 0; i < 8; i++) {
            a[i] = arr[EP[i] - 1];
        }
        return a;
    }

    public int[] XORArrays(int a[], int b[]) {
        int t[] = new int[a.length];

        for (int i = 0; i < a.length; i++) {
            t[i] = a[i] ^ b[i];
        }

        return t;

    }
    
    public String S0Permutation(int arr[]) {
        String r1 = arr[0] + "" + arr[3];
        String c1 = arr[1] + "" + arr[2];

        int row1 = Integer.parseInt(r1, 2);
        int col1 = Integer.parseInt(c1, 2);

        return S0[row1][col1];
    }

    public String S1Permutation(int arr[]) {
        String r1 = arr[4] + "" + arr[7];
        String c1 = arr[5] + "" + arr[6];

        int row1 = Integer.parseInt(r1, 2);
        int col1 = Integer.parseInt(c1, 2);

        return S1[row1][col1];
    }

    public int[] P4Permutation(int arr[]) {
        int after[] = new int[4];

        for (int i = 0; i < 4; i++) {
            after[i] = arr[P4[i] - 1];
        }

        return after;
    }

    public int[] IPInverse(int arr[]) {
        int after[] = new int[8];
        for (int i = 0; i < 8; i++) {
            after[i] = arr[IPI[i] - 1];
        }
        return after;
    }

    public void createKeys() {
        int newKey[] = new int[10]; 

        newKey = P10Permutation(key, P10);

        int temp1[] = new int[5];
        int temp2[] = new int[5];

        for (int i = 0; i < 5; i++) {
            temp1[i] = newKey[i];
        }

        for (int i = 5; i < 10; i++) {
            temp2[i - 5] = newKey[i];
        }

        //Key 1 creation
        //Left rotate by 1
        temp1 = leftRotate(temp1, 1);
        temp2 = leftRotate(temp2, 1);
        newKey = concatenateArrays(temp1, temp2);
        k1 = P8Permutation(newKey, P8);

        //Key2 creation
        for (int i = 0; i < 5; i++) {
            temp1[i] = newKey[i];
        }

        for (int i = 5; i < 10; i++) {
            temp2[i - 5] = newKey[i];
        }

        //Left rotate by 2
        temp1 = leftRotate(temp1, 2);
        temp2 = leftRotate(temp2, 2);
        newKey = concatenateArrays(temp1, temp2);
        k2 = P8Permutation(newKey, P8);

    }

    public void encryption() {
        int afterIP[] = initialPermutation(plaintext); 
        int firstHalf[] = Arrays.copyOfRange(afterIP, 0, 4);
        int secondHalf[] = Arrays.copyOfRange(afterIP, 4, 8);
        int afterEP[] = expansionPermutation(secondHalf); 
        afterEP = XORArrays(afterEP, k1);

        String temp = S0Permutation(afterEP) + S1Permutation(afterEP); 
        int afterS1[] = new int[4];

        for (int i = 0; i < 4; i++) {
            afterS1[i] = Integer.parseInt(temp.charAt(i) + "");
        }

        afterS1 = P4Permutation(afterS1);

        int afterXOR[] = XORArrays(afterS1, firstHalf); 

        int newFirst[] = Arrays.copyOfRange(secondHalf, 0, 4); 
        int sEP[] = expansionPermutation(afterXOR);
        int sXOR[] = XORArrays(sEP, k2);
        String t = S0Permutation(sXOR) + S1Permutation(sXOR);

        int afterSP[] = new int[4];
        for (int i = 0; i < 4; i++) {
            afterSP[i] = Integer.parseInt(t.charAt(i) + "");
        }
        afterSP = P4Permutation(afterSP);
        int newXor[] = XORArrays(afterSP, newFirst);
        int finalArr[] = concatenateArrays(newXor, afterXOR);

        int[] cipherText1 = IPInverse(finalArr);

        for (int i = 0; i < 8; i++) {
            System.out.print(cipherText1[i] + " ");
            cipherText[i] = cipherText1[i];
        }
    }

    public void decryption() {
        int afterIP[] = initialPermutation(cipherText); 
        int firstHalf[] = Arrays.copyOfRange(afterIP, 0, 4);
        int secondHalf[] = Arrays.copyOfRange(afterIP, 4, 8);
        int afterEP[] = expansionPermutation(secondHalf); 
        afterEP = XORArrays(afterEP, k2);

        String temp = S0Permutation(afterEP) + S1Permutation(afterEP); 
        int afterS1[] = new int[4];

        for (int i = 0; i < 4; i++) {
            afterS1[i] = Integer.parseInt(temp.charAt(i) + "");
        }

        afterS1 = P4Permutation(afterS1);

        int afterXOR[] = XORArrays(afterS1, firstHalf); 

        int newFirst[] = Arrays.copyOfRange(secondHalf, 0, 4); 
        int sEP[] = expansionPermutation(afterXOR);
        int sXOR[] = XORArrays(sEP, k1);
        String t = S0Permutation(sXOR) + S1Permutation(sXOR);

        int afterSP[] = new int[4];
        for (int i = 0; i < 4; i++) {
            afterSP[i] = Integer.parseInt(t.charAt(i) + "");
        }
        afterSP = P4Permutation(afterSP);
        int newXor[] = XORArrays(afterSP, newFirst);
        int finalArr[] = concatenateArrays(newXor, afterXOR);

        int[] plainText = IPInverse(finalArr);

        for (int i = 0; i < 8; i++) {
            System.out.print(plainText[i] + " ");
        }
    }

    public static void main(String[] args) {
        DES obj = new DES();
        obj.createKeys();
        System.out.print("Ciphertext: ");
        obj.encryption();
        System.out.print("\nPlaintext: ");
        obj.decryption();
    }
}
