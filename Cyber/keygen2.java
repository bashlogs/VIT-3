import java.util.Arrays;

public class keygen2 {

    public static void main(String[] args) {
        String keyString = "010010101110101";
        byte[] key = convertBinaryStringToBytes(keyString);

        // Perform key expansion
        byte[][] roundKeys = keyExpansion(key);

        // Display the round keys
        for (int i = 0; i < roundKeys.length; i++) {
            System.out.println("Round Key " + i + ": " + Arrays.toString(roundKeys[i]));
        }
    }

    private static byte[][] keyExpansion(byte[] key) {
        int keySize = key.length;
        int numRounds = 10; // For a 128-bit key

        int wordSize = keySize / 4;
        int expandedKeySize = 4 * (numRounds + 1);
        byte[][] roundKeys = new byte[expandedKeySize][wordSize];

        // Copy the original key to the first round key
        for (int i = 0; i < keySize; i++) {
            roundKeys[i / wordSize][i % wordSize] = key[i];
        }

        for (int i = keySize; i < expandedKeySize * wordSize; i++) {
            byte[] temp = Arrays.copyOf(roundKeys[(i - 1) / wordSize], wordSize);

            if (i % keySize == 0) {
                temp = subWord(rotWord(temp));
                temp[0] ^= (byte) (Rcon(i / keySize) & 0xFF);
            } else if (keySize == 32 && i % keySize == 16) {
                temp = subWord(temp);
            }

            for (int j = 0; j < wordSize; j++) {
                roundKeys[i / wordSize][j] = (byte) (roundKeys[(i - keySize) / wordSize][j] ^ temp[j]);
            }
        }

        return roundKeys;
    }

    private static byte[] rotWord(byte[] word) {
        byte[] result = new byte[word.length];
        System.arraycopy(word, 1, result, 0, word.length - 1);
        result[word.length - 1] = word[0];
        return result;
    }

    private static byte[] subWord(byte[] word) {
        for (int i = 0; i < word.length; i++) {
            word[i] = getSBoxValue(word[i]);
        }
        return word;
    }

    private static byte getSBoxValue(byte value) {
        return value;
    }

    private static int Rcon(int round) {
        return 0;
    }

    private static byte[] convertBinaryStringToBytes(String binaryString) {
        int len = binaryString.length();
        byte[] result = new byte[len / 8];

        for (int i = 0; i < len; i += 8) {
            result[i / 8] = (byte) Integer.parseInt(binaryString.substring(i, i + 8), 2);
        }

        return result;
    }
}
