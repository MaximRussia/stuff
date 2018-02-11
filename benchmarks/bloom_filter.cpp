
#include <math.h>
#include <stdint.h>
#include <iostream>
#include <string>
#include <string.h>
using namespace std;

/*************
Bloom filter written in C++ for strings. Tests whether an element belongs to a set.
False positive matches are possible, false negatives are not. Also implements Rabin�Karp algorithm with
Rabin fingerprint hashes for multiple substring searches.
**************/

// Functor for a hashing function
// Implements a Rabin fingerprint hash function
class HashFn {
public:
	// Initialize a HashFn with the PRIME p which is used as the base of the Rabin fingerprint algorithm
	HashFn(int p) {
		this->p = p;
	}

	virtual uint64_t operator()(const char *input, int len, unsigned char lastCharCode, uint64_t lastHash) {
		// See the abracadabra example: https://en.wikipedia.org/wiki/Rabin%E2%80%93Karp_algorithm
		return (lastHash - lastCharCode * pow(p, len - 1)) * p + input[len - 1];
	}

	virtual uint64_t operator()(const char *input, int len) {
		uint64_t total = 0;
		for (int i = 0; i < len; i++) {
			total += input[i] * pow(p, len - i - 1);
		}
		return total;
	}

private:
	int p;
};


HashFn defaultHashFns[5] = { HashFn(13), HashFn(17), HashFn(31), HashFn(41), HashFn(53) };
/**
 * Implements a Bloom Filter using Rabin Karp for char* buffer lookups
 */
class BloomFilter {
public:
	BloomFilter(unsigned int bitsPerElement = 10, unsigned int estimatedNumElements = 50000, HashFn hashFns[] = defaultHashFns,
		int numHashFns = sizeof(defaultHashFns) / sizeof(defaultHashFns[0]));
	BloomFilter(const char *buffer, int byteBufferSize, HashFn hashFns[] = defaultHashFns, int numHashFns = sizeof(defaultHashFns) / sizeof(defaultHashFns[0]));
	~BloomFilter();
	// Used for debuggging
	void print();
	void setBit(unsigned int bitLocation);
	bool isBitSet(unsigned int bitLocation);
	// Adds the specified buffer to the bloom filter
	void add(const char *input, int len);
	void add(const char *sz);

	/**
	 * Checks whether an element probably exists in the set, or definitely doesn't.
	 * @param str Either a string to check for existance or an array of the string's char codes
	 *   The main reason why you'd want to pass in a char code array is because passing a string
	 *   will use JS directly to get the char codes which is very inneficient compared to calling
	 *   into C++ code to get it and then making the call.
	 *
	 * Returns true if the element probably exists in the set
	 * Returns false if the element definitely does not exist in the set
	 */
	bool exists(const char *input, int len);
	bool exists(const char *sz);

	/**
	 * Checks if any substring of length substringLength probably exists or definitely doesn't
	 * If false is returned then no substring of the specified string of the specified length is in the bloom filter
	 * @param data The substring or char array to check substrings on.
	 */
	bool substringExists(const char *data, int dataLen, int substringLength);
	bool substringExists(const char *sz, int substringLength);

	const char * getBuffer() {
		return buffer;
	}

	int getByteBufferSize() {
		return byteBufferSize;
	}

private:
	HashFn *hashFns;
	uint64_t *lastHashes;
	int numHashFns;
	unsigned int byteBufferSize;
	unsigned int bitBufferSize;
	char *buffer;

	/**
	 * Obtains the hashes for the specified charCodes
	 * See "Rabin fingerprint" in https://en.wikipedia.org/wiki/Rabin%E2%80%93Karp_algorithm for more information.
	 *
	 * @param charCodes An array of the char codes to use for the hash
	 * @param lastHashes Input and output for the last hash value
	 * function for a faster computation.  Must be called with lastCharCode but can be nullptr otherwise.
	 * @param newHashses fills in the corresponding new hashes, can be the same as lastHashes
	 * @param lastCharCode if specified, it will pass the last char code
	 *  to the hashing function for a faster computation. Must be called with lastHashes.
	 */
	void getHashesForCharCodes(const char *input, int inputLen, uint64_t *lastHashes, uint64_t *newHashes, unsigned char lastCharCode);
};

BloomFilter::BloomFilter(unsigned int bitsPerElement, unsigned int estimatedNumElements, HashFn *hashFns, int numHashFns) :
hashFns(nullptr), numHashFns(0), byteBufferSize(0), buffer(nullptr) {
	this->hashFns = hashFns;
	this->numHashFns = numHashFns;
	lastHashes = new uint64_t[numHashFns];
	byteBufferSize = bitsPerElement * estimatedNumElements / 8 + 1;
	bitBufferSize = byteBufferSize * 8;
	buffer = new char[byteBufferSize];
	memset(buffer, 0, byteBufferSize);
}

// Constructs a BloomFilter by copying the specified buffer and number of bytes
BloomFilter::BloomFilter(const char *buffer, int byteBufferSize, HashFn *hashFns, int numHashFns) :
hashFns(nullptr), numHashFns(0), byteBufferSize(0), buffer(nullptr) {
	this->hashFns = hashFns;
	this->numHashFns = numHashFns;
	lastHashes = new uint64_t[numHashFns];
	this->byteBufferSize = byteBufferSize;
	bitBufferSize = byteBufferSize * 8;
	this->buffer = new char[byteBufferSize];
	memcpy(this->buffer, buffer, byteBufferSize);
}

BloomFilter::~BloomFilter() {
	if (buffer) {
		delete[] buffer;
	}
	if (lastHashes) {
		delete[] lastHashes;
	}
}

void BloomFilter::print() {
	for (unsigned int i = 0; i < byteBufferSize; i++) {
		int mask = 0x01;
		for (int j = 0; j < 8; j++) {
			cout << ((buffer[i] & mask) ? "1" : "0");
			mask <<= 1;
		}
		cout << " ";
	}
}

void BloomFilter::setBit(unsigned int bitLocation) {
	buffer[bitLocation / 8] |= 1 << bitLocation % 8;
}

bool BloomFilter::isBitSet(unsigned int bitLocation) {
	return !!(buffer[bitLocation / 8] & 1 << bitLocation % 8);
}

void BloomFilter::add(const char *input, int len) {
	for (int j = 0; j < numHashFns; j++) {
		setBit(hashFns[j](input, len) % bitBufferSize);
	}
}

void BloomFilter::add(const char *sz) {
	add(sz, strlen(sz));
}

bool BloomFilter::exists(const char *input, int len) {
	bool allSet = true;
	for (int j = 0; j < numHashFns; j++) {
		allSet = allSet && isBitSet(hashFns[j](input, len) % bitBufferSize);
	}
	return allSet;
}

bool BloomFilter::exists(const char *sz) {
	return exists(sz, strlen(sz));
}

void BloomFilter::getHashesForCharCodes(const char *input, int inputLen, uint64_t *lastHashes, uint64_t *newHashes, unsigned char lastCharCode) {
	for (int i = 0; i < numHashFns; i++) {
		if (lastHashes) {
			*(newHashes + i) = hashFns[i](input, inputLen, lastCharCode, *(lastHashes + i));
		} else {
			*(newHashes + i) = hashFns[i](input, inputLen);
		}
	}
}

bool BloomFilter::substringExists(const char *data, int dataLen, int substringLength) {
	unsigned char lastCharCode = 0;
	for (int i = 0; i < dataLen - substringLength + 1; i++) {
		getHashesForCharCodes(data + i, substringLength, i == 0 ? nullptr : lastHashes, lastHashes, lastCharCode);
		bool allSet = true;
		for (int j = 0; j < numHashFns; j++) {
			allSet = allSet && isBitSet(lastHashes[j] % bitBufferSize);
		}
		if (allSet) {
			return true;
		}
		lastCharCode = data[i];
	}
	return false;
}

bool BloomFilter::substringExists(const char *data, int substringLength) {
	return substringExists(data, strlen(data), substringLength);
}

int main(int argc, char**argv) {
	BloomFilter b;
	b.add("Brian");
	b.add("Ronald");
	b.add("Bondy");

	// Prints true
	cout << (b.exists("Brian") ? "true" : "false") << endl;

	// Prints false
	cout << (b.exists("Brian Ronald") ? "true" : "false") << endl;

	// Create a new BloomerFilter form a previous serialization
	BloomFilter b2(b.getBuffer(), b.getByteBufferSize());

	// Prints the same as above
	cout << (b2.exists("Brian") ? "true" : "false") << endl;
	cout << (b2.exists("Brian Ronald") ? "true" : "false") << endl;

	// And you can check if any substring of a passed string exists
	// Prints true
	cout << (b.substringExists("Hello my name is Brian", 5) ? "true" : "false") << endl;
	// Prints false
	cout << (b.substringExists("Hello my name is Bri", 3) ? "true" : "false") << endl;

	return 0;
}