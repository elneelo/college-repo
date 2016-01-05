import java.util.Scanner;
import java.util.ArrayList;
import java.util.List;

public class JavaCache {

	public static int TOTAL_HITS = 0;

	public static void main( String[] args ) {

		System.out.print("\nPlease note that the default " +
			"cache size for this program is 128 bytes.\n" + "\n");

		Scanner scanner = new Scanner(System.in);

		System.out.print("Define L, (the number of bytes per cache line - way): ");
		int intL = scanner.nextInt();
		System.out.print("Define K, (the number of ways per set): ");
		int intK = scanner.nextInt();
		System.out.print("Define N, (the number of sets): ");
		int intN = scanner.nextInt();

		int cacheSize = 128;
		if ((intL*intK*intN) != cacheSize) {
			System.out.print("\nWARNING! " +
				"L * K * N does not equal the cache size of 128 bytes.\n" +"\n");
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

		List<String> cache = new ArrayList<String>();
		List<String> tempCache = new ArrayList<String>();

		for (int i = (0 + 48); i < (intN + 48); i++) {
			for (String adr : addresses) {
				if (extractBit(adr, intN) == i) {
					tempCache = cacheController(adr, cache, intL, intK, intN);
					cache = tempCache;
				}
			}
			cache.clear();
			tempCache.clear();
		}

		System.out.println("\n" + "Total Hits: " + TOTAL_HITS +"\n");
	}

	public static List<String> cacheController( String adr, List<String> cache,
			int intL, int intK, int intN ) {

		List<String> tempCache = new ArrayList<String>();
		boolean hit = false;

		if (!cache.isEmpty()) {
			for (String element : cache) {
				if (cacheBits(adr).equalsIgnoreCase(element)) {
					tempCache = rearrangeCache(cache, element);
					hit = true;
					TOTAL_HITS += 1;
					break;
				}
			}
		} else {
			String temp = cacheBits(adr);
			tempCache.add(temp);
			return tempCache;
		}

		if (!hit) { tempCache = manageCache(cache, adr, intK); }

		return tempCache;
	}

	public static List<String> rearrangeCache( List<String> cache, String adr ) {

		String temp = cacheBits(adr);
		cache.remove(temp);
		cache.add(temp);

		return cache;
	}

	public static List<String> manageCache( List<String> cache, String adr, int intK ) {
		
		String temp = cacheBits(adr);

		if (cache.size() != intK) {
			cache.add(temp);
		} else {
			cache.remove(0);
			cache.add(temp);
		}

		return cache;
	}

	public static String cacheBits( String adr ) {

		char[] array = adr.toCharArray();
		char[] temp = new char[3];

		for (int i = 0; i < 3; i++) {
			temp[i] = array[i];
		}

		String ret = new String(temp);
		return ret;
	}

	public static int extractBit( String adr, int intN ) {

		char[] array = adr.toCharArray();
		char extractedBit = array[2];
		int value = (int) extractedBit;

		if (value >= 97 && value <= 102) {
			value -= 39;
		}

		for (int i = 0; i < intN; i++) {
			if (value % intN == i) {
				return (i + 48);
			}
		}

		return -1;
	}

}