import java.util.Scanner;
import java.util.ArrayList;
import java.util.List;

public class JavaCache {

	public static void main( String[] args ) {

		Scanner scanner = new Scanner(System.in);

		System.out.print("\nPlease specify the cache size: "); 
		int cacheSize = scanner.nextInt();
		System.out.print("Define L, (the number of bytes per cache line - way): ");
		int intL = scanner.nextInt();
		System.out.print("Define K, (the number of ways per set): ");
		int intK = scanner.nextInt();
		System.out.print("Define N, (the number of sets): ");
		int intN = scanner.nextInt();

		if ((intL*intK*intN) != cacheSize) {
			System.out.print("\nWARNING! " +
				"L * K * N does not equal the cache size.\n" +"\n");
			System.exit(0);
		}

		List<String> addresses = new ArrayList<String>();
		addresses.add("0000");
		addresses.add("0004");
		addresses.add("000c");
		addresses.add("2200");
		addresses.add("00d0");
		addresses.add("00e0");
		addresses.add("1130");
		addresses.add("0028");
		addresses.add("113c");
		addresses.add("2204");
		addresses.add("0010");
		addresses.add("0020");
		addresses.add("0004");
		addresses.add("0040");
		addresses.add("2208");
		addresses.add("0008");
		addresses.add("00a0");
		addresses.add("0004");
		addresses.add("1104");
		addresses.add("0028");
		addresses.add("000c");
		addresses.add("0084");
		addresses.add("000c");
		addresses.add("3390");
		addresses.add("00b0");
		addresses.add("1100");
		addresses.add("0028");
		addresses.add("0064");
		addresses.add("0070");
		addresses.add("00d0");
		addresses.add("0008");
		addresses.add("3394");

		CacheObject co = new CacheObject(addresses, intL, intK, intN);
		
	}

}
