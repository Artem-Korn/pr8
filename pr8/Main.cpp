#include "Header.h"

int main()
{
    unsigned p = 61, q = 53;

    tuple<unsigned, unsigned> my_public_key;
    tuple<unsigned, unsigned> my_private_key;

    RSA::GenerateKeys(p, q, my_public_key, my_private_key);

    cout << "Demonstration\n";
    cout << "My Public Key (e, n): (" << get<0>(my_public_key) << ", " << get<1>(my_public_key) << ")\n";
    cout << "My Private Key (d, n): (" << get<0>(my_private_key) << ", " << get<1>(my_private_key) << ")\n";

    unsigned message = 10, encrypted, decrypted;
    cout << "Message: " << message << endl;

    encrypted = RSA::Encrypt(message, my_public_key);
    cout << "Encrypted Message: " << encrypted << endl;

    decrypted = RSA::Decrypt(encrypted, my_private_key);
    cout << "Decrypted Message: " << decrypted << endl;

    cout << "\nTests\n";
    Tester tester;
    tester.TestRSA(100);

    return 0;
}