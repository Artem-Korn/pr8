#include "Header.h"

unsigned RSA::GCD(unsigned a, unsigned b)
{
	if (b == 0) 
    {
		return a;
	}
	return GCD(b, a % b);
}

bool RSA::IsPrime(unsigned a)
{
    if (a <= 1) 
    {
        return false;
    }
    for (unsigned i = 2; i * i <= a; i++)
    {
        if (a % i == 0) 
        {
            return false;
        }
    }
    return true;
}

unsigned RSA::ModInverse(unsigned a, unsigned m)
{
    a = a % m;
    for (unsigned x = 1; x < m; x++)
    {
        if ((a * x) % m == 1) 
        {
            return x;
        }
    }
    return -1;
}

unsigned RSA::ModularPow(unsigned base, unsigned exponent, unsigned modulus)
{
    unsigned result = 1;
    base = base % modulus;

    while (exponent > 0) {
        if (exponent & 1) {
            result = (result * base) % modulus;
        }
        exponent = exponent >> 1;
        base = (base * base) % modulus;
    }

    return result;
}

void RSA::GenerateKeys(unsigned p, unsigned q, 
    tuple<unsigned, unsigned>& public_key, tuple<unsigned, unsigned>& private_key)
{
    if (!IsPrime(p) || !IsPrime(q))
    {
        cout << "Both numbers must be prime!\n";
        return;
    }

    unsigned n = p * q;
    unsigned m = (p - 1) * (q - 1);
    unsigned d;

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<unsigned> dist(2, m - 1);

    do
    {
        d = dist(gen);
    } 
    while (GCD(d, m) != 1);

    unsigned e = ModInverse(d, m);

    get<0>(public_key) = d;
    get<1>(public_key) = n;

    get<0>(private_key) = e;
    get<1>(private_key) = n;
}

unsigned RSA::Encrypt(unsigned message, tuple<unsigned, unsigned> public_key)
{
    return ModularPow(message, get<0>(public_key), get<1>(public_key));
}

unsigned RSA::Decrypt(unsigned ciphertext, tuple<unsigned, unsigned> private_key)
{
    return ModularPow(ciphertext, get<0>(private_key), get<1>(private_key));
}


Tester::Tester()
{
    unsigned num = 3, counter = 0;

    while (counter < N) {
        for (unsigned j = 2; j <= num; j++)
        {
            if (!(num % j) && (num != j))
            {
                break;
            }
            if (j == num)
            {
                prime[counter] = num;
                counter++;
            }
        }
        num++;
    }
}

void Tester::TestRSA(unsigned tests_count)
{
    // Random index of array generator for choosing p and q
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<unsigned> dist(0, N - 1);

    unsigned p;
    unsigned q;
    tuple<unsigned, unsigned> public_key;
    tuple<unsigned, unsigned> private_key;
    unsigned message;
    unsigned encrypted;

    for (unsigned i = 0; i < tests_count; i++)
    {
        cout << "Test " << i;

        p = prime[dist(gen)];
        q = prime[dist(gen)];

        while (p == q) 
        {
            q = prime[dist(gen)];
        }

        RSA::GenerateKeys(p, q, public_key, private_key);

        // Random message using this n should be less than n to be decrypted correctly.
        uniform_int_distribution<unsigned> message_dist(0, get<1>(public_key) - 1);
        message = message_dist(gen);

        encrypted = RSA::Encrypt(message, public_key);

        if (message == RSA::Decrypt(encrypted, private_key))
        {
            cout << " - successful!\n";
        }
        else {
            cout << " - failed!\n";
        }
    }  
}