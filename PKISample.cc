#include <iostream>
#include <vector> 
#include "/usr/include/crypto++/eccrypto.h"
#include "/usr/include/crypto++/osrng.h"
#include "/usr/include/crypto++/oids.h"
#include "/usr/include/crypto++/files.h"

using namespace CryptoPP;
using namespace std; 

int main(int argc, const char* argv[]) 
{   
    AutoSeededRandomPool prng;
    ECDSA<ECP, SHA256>::PrivateKey k;
    vector<ECDSA<ECP, SHA256>::PrivateKey> skey;
    FileSource fs1( "private.ec.der", true  );
    ECDSA<ECP, SHA256>::PublicKey publicKey;
    vector<ECDSA<ECP, SHA256>::PublicKey> pkey;
    FileSource fs2( "public.ec.der", true  );
    for (int i=0; i<5;i++){
        k.Load( fs1 );
        const Integer& x = k.GetPrivateExponent();
        std::cout << "K: " << std::hex << x << std::endl;
        skey.push_back(k);
        publicKey.Load( fs2 );
        pkey.push_back(publicKey);
    }

    for (int i=0; i<5;i++){
        k = skey.at(i);
        ECDSA<ECP, SHA256>::Signer signer(k);
        publicKey = pkey.at(i);
        ECDSA<ECP, SHA256>::Verifier verifier(publicKey);

        ECDSA<ECP, SHA256>::PublicKey publicKeyCA;
        std::string message = "Do or do not. There is no try.";
        size_t siglen = signer.MaxSignatureLength();
        std::string signature(siglen, 0x00);
        siglen = signer.SignMessage( prng, (const byte*)&message[0], message.size(), (byte*)&signature[0] );
        signature.resize(siglen);

        bool result = verifier.VerifyMessage( (const byte*)&message[0], message.size(), (const byte*)&signature[0], signature.size() );
        // Verification failure?
        if( !result ) {
            std::cout << "Failed to verify signature on message#" <<1<< std::endl;
        } else {
            std::cout << "All good! For MSG"<< std::endl;
            const Integer& x = k.GetPrivateExponent();
            std::cout << "K: " << std::hex << x << std::endl;

        }
    }

    /*ECDSA<ECP, SHA256>::PrivateKey k;
    FileSource fs5( "private.ec.der", true  );
    fs5.Skip(2);
    k.Load(fs5);
    const Integer& x = k.GetPrivateExponent();
    std::cout << "K: " << std::hex << x << std::endl;*/


    return 0;
}
