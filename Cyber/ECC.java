import java.util.ArrayList;
import java.util.List;

public class ECC {

	static long power(long a, long b, long p) {
		if (b == 0)
			return 1;
		long result = power(a, b / 2, p) % p;
		result = (result * result) % p;
		if (b % 2 == 1)
			result = (result * a) % p;
		return result;
	}

	static void diffieHellmanKeyExchange() {
		long prime = 23; 
		long primitiveRoot = 5; 

		long privateKeyA = 6;
		long privateKeyB = 15;

		long publicKeyA = power(primitiveRoot, privateKeyA, prime);
		long publicKeyB = power(primitiveRoot, privateKeyB, prime);
		System.out.println(publicKeyA);
		System.out.println(publicKeyB);

		long secretKeyA = power(publicKeyB, privateKeyA, prime);
		long secretKeyB = power(publicKeyA, privateKeyB, prime);

		System.out.println("Shared secret key for Alice: " + secretKeyA);
		System.out.println("Shared secret key for Bob: " + secretKeyB);

		String message = "Hello, Bob!";
		List<Character> encryptedMessage = new ArrayList<>();
		List<Character> decryptedMessage = new ArrayList<>();

		for (char c : message.toCharArray()) {
			encryptedMessage.add((char) (c ^ secretKeyA)); 
		}

		for (char c : encryptedMessage) {
			decryptedMessage.add((char) (c ^ secretKeyB)); 
		}
				
		System.out.print("Encrypted message: ");
		for (char c : encryptedMessage) {
			System.out.print(c);
		}
		System.out.println();

		System.out.print("Decrypted message: ");
		for (char c : decryptedMessage) {
			System.out.print(c);
		}
		System.out.println();
	}

	public static void main(String[] args) {
		diffieHellmanKeyExchange();
	}
}
