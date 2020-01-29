#include <iostream>
#include "/usr/include/crypto++/eccrypto.h"
#include "/usr/include/crypto++/osrng.h"
#include "/usr/include/crypto++/oids.h"

using namespace CryptoPP;

int main(int argc, const char* argv[]) 
{
    AutoSeededRandomPool prng;

    ECDSA<ECP, SHA256>::PrivateKey k1, k2, k3, k4, k5;
    k1.Initialize( prng, ASN1::secp256r1() );
    ECDSA<ECP, SHA256>::Signer signer1(k1);
    k2.Initialize( prng, ASN1::secp256r1() );
    ECDSA<ECP, SHA256>::Signer signer2(k2);
    k3.Initialize( prng, ASN1::secp256r1() );
    ECDSA<ECP, SHA256>::Signer signer3(k3);
    k4.Initialize( prng, ASN1::secp256r1() );
    ECDSA<ECP, SHA256>::Signer signer4(k4);
    k5.Initialize( prng, ASN1::secp256r1() );
    ECDSA<ECP, SHA256>::Signer signer5(k5);

    std::string message = "Do or do not. There is no try.";
    size_t siglen = signer1.MaxSignatureLength();
    std::string signature1(siglen, 0x00);
    std::string signature2(siglen, 0x00);
    std::string signature3(siglen, 0x00);
    std::string signature4(siglen, 0x00);
    std::string signature5(siglen, 0x00);

    siglen = signer1.SignMessage( prng, (const byte*)&message[0], message.size(), (byte*)&signature1[0] );
    signature1.resize(siglen);
    siglen = signer2.SignMessage( prng, (const byte*)&message[0], message.size(), (byte*)&signature2[0] );
    signature2.resize(siglen);
    siglen = signer3.SignMessage( prng, (const byte*)&message[0], message.size(), (byte*)&signature3[0] );
    signature3.resize(siglen);
    siglen = signer4.SignMessage( prng, (const byte*)&message[0], message.size(), (byte*)&signature4[0] );
    signature4.resize(siglen);
    siglen = signer5.SignMessage( prng, (const byte*)&message[0], message.size(), (byte*)&signature5[0] );
    signature5.resize(siglen);

    ECDSA<ECP, SHA256>::PublicKey publicKey1, publicKey2, publicKey3, publicKey4, publicKey5;
    k1.MakePublicKey(publicKey1);
    ECDSA<ECP, SHA256>::Verifier verifier1(publicKey1);
    k2.MakePublicKey(publicKey2);
    ECDSA<ECP, SHA256>::Verifier verifier2(publicKey2);
    k3.MakePublicKey(publicKey3);
    ECDSA<ECP, SHA256>::Verifier verifier3(publicKey3);
    k4.MakePublicKey(publicKey4);
    ECDSA<ECP, SHA256>::Verifier verifier4(publicKey4);
    k5.MakePublicKey(publicKey5);
    ECDSA<ECP, SHA256>::Verifier verifier5(publicKey5);

    bool result = verifier1.VerifyMessage( (const byte*)&message[0], message.size(), (const byte*)&signature1[0], signature1.size() );
    // Verification failure?
    if( !result ) {
        std::cout << "Failed to verify signature on message#" <<1<< std::endl;
    } else {
        std::cout << "All good! For MSG#"<<1<< std::endl;
    }
    result = verifier2.VerifyMessage( (const byte*)&message[0], message.size(), (const byte*)&signature2[0], signature2.size() );
    // Verification failure?
    if( !result ) {
        std::cout << "Failed to verify signature on message#" <<2<< std::endl;
    } else {
        std::cout << "All good! For MSG#"<<2<< std::endl;
    }
    result = verifier3.VerifyMessage( (const byte*)&message[0], message.size(), (const byte*)&signature3[0], signature3.size() );
    // Verification failure?
    if( !result ) {
        std::cout << "Failed to verify signature on message#" <<3<< std::endl;
    } else {
        std::cout << "All good! For MSG#"<<3<< std::endl;
    }
    result = verifier4.VerifyMessage( (const byte*)&message[0], message.size(), (const byte*)&signature4[0], signature4.size() );
    // Verification failure?
    if( !result ) {
        std::cout << "Failed to verify signature on message#" <<4<< std::endl;
    } else {
        std::cout << "All good! For MSG#"<<4<< std::endl;
    }
    result = verifier5.VerifyMessage( (const byte*)&message[0], message.size(), (const byte*)&signature5[0], signature5.size() );
    // Verification failure?
    if( !result ) {
        std::cout << "Failed to verify signature on message#" <<5<< std::endl;
    } else {
        std::cout << "All good! For MSG#"<<5<< std::endl;
    }
    
    return 0;
}