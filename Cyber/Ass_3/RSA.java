package Ass_3;
import java.util.*;
import java.math.*;

public class RSA {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        System.out.print("Enter Values of p and q: ");
        String pStr = sc.next();
        String qStr = sc.next();
        BigInteger p = new BigInteger(pStr);
        BigInteger q = new BigInteger(qStr);

        BigInteger N = p.multiply(q);
        BigInteger phiN = p.subtract(BigInteger.ONE).multiply(q.subtract(BigInteger.ONE));
        
        BigInteger e = calculateE(phiN);
        BigInteger d = e.modInverse(phiN);
        
        // Taking message as input.
        System.out.print("Enter message: ");
        String msg = sc.next();
        
        BigInteger plainText = new BigInteger(msg);
        BigInteger cipherText = plainText.modPow(e, N);
        
        System.out.println("CipherText: " + cipherText);
        
        BigInteger decryptedText = cipherText.modPow(d, N);
        
        System.out.println("Decrypted Text: " + decryptedText);
    }
    
    public static BigInteger calculateE(BigInteger phiN) {
        BigInteger e = new BigInteger("2");
        while (e.compareTo(phiN) < 0) {
            if (phiN.gcd(e).equals(BigInteger.ONE)) {
                break;
            }
            e = e.add(BigInteger.ONE);
        }
        return e;
    }
}
