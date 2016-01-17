import java.util.ArrayList;
import java.util.List;

class CacheObject {

	public static int TOTAL_HITS = 0;
	public static int TOTAL_MISSES = 0;

	public CacheObject( List<String> addresses, int intL,
			int intK, int intN ) {

		List<String> cache = new ArrayList<String>();

		for (int i = (0 + 48); i < (intN + 48); i++) {
			for (String adr : addresses) {
				if (extractBit(adr, intN) == i) {					
					cache = cacheController(adr, cache, intL, intK, intN);
				}
			}
			cache.clear();
		}

		System.out.println("\n" + "Total Hits: " + TOTAL_HITS +"\n");
		System.out.println("\n" + "Total Misses: " + TOTAL_MISSES +"\n");
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
					//System.out.println("\n" + "***CACHE HIT: " + tempCache + "\n");
					break;
				}
			}
		} else {
			TOTAL_MISSES += 1;
			String temp = cacheBits(adr);
			tempCache.add(temp);
			//System.out.println("\n" + "***CACHE MISS: " + tempCache + "\n");
			return tempCache;
		}

		if (!hit) {
			TOTAL_MISSES += 1;
			tempCache = manageCache(cache, adr, intK);
			//System.out.println("\n" + "***CACHE MISS: " + tempCache + "\n");
		}

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
		//System.out.println("\n" + "***CAPACITY" + "\n");
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