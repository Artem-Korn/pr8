#pragma once
#include <iostream>
#include <tuple>
#include <random>
using namespace std;

// Count of prime numbers in Tester
#define N 20

class RSA {
	static unsigned GCD(unsigned a, unsigned b);
	static bool IsPrime(unsigned a);
	static unsigned ModInverse(unsigned a, unsigned m);
	static unsigned ModularPow(unsigned base, unsigned exponent, unsigned modulus);

public:
	static void GenerateKeys(unsigned p, unsigned q,
		tuple<unsigned, unsigned>& public_key, tuple<unsigned, unsigned>& private_key);

	static unsigned Encrypt(unsigned message, tuple<unsigned, unsigned> public_key);
	static unsigned Decrypt(unsigned ciphertext, tuple<unsigned, unsigned> private_key);
};

class Tester
{
	// Prime array for picking random values for p & q
	unsigned prime[N];

public:
	// Constructor to generate prime numbers for array
	Tester();

	// Test function for RSA class
	void TestRSA(unsigned tests_count);
};