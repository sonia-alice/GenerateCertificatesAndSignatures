#include <iostream>
#include <vector> 
#include <sstream>
#include <fstream>
#include <string>
#include "/usr/include/crypto++/eccrypto.h"
#include "/usr/include/crypto++/osrng.h"
#include "/usr/include/crypto++/oids.h"
#include "/usr/include/crypto++/files.h"
#include "/usr/include/crypto++/hex.h"

using namespace CryptoPP;
using namespace std; 

int main(int argc, const char* argv[]) 
{   
    ECDSA<ECP, SHA256>::PublicKey publicKey;
    FileSource fs2( "/home/sonia/public.ec.der", true  );
    AutoSeededRandomPool prng;
    ECDSA<ECP, SHA256>::PrivateKey k;
    FileSource fs1( "/home/sonia/private.ec.der", true  );
    ofstream wfile;
    wfile.open("stringPK.dat", ios::out|ios::binary);

    for (int i=0; i<55;i++){
        publicKey.Load( fs2 );
        const ECP::Point& q = publicKey.GetPublicElement();
        const Integer& qx = q.x;
        const Integer& qy = q.y;

        std::stringstream ss ;
        ss<<std::hex<<q.x<<q.y;
        std::string pt = ss.str();          // is the string to be stored in the BC as the Public Key
        
        wfile<<pt<<std::endl;

        //create the PK from the string stored in BC
        /*HexDecoder decoder;
        decoder.Put((byte*)&pt[0], pt.size());
        decoder.MessageEnd();
        ECP::Point p;
        size_t len = decoder.MaxRetrievable();
        p.identity = false;
        p.x.Decode(decoder, len/2);
        p.y.Decode(decoder, len/2);
        ECDSA<ECP, SHA256>::PublicKey PK;
        PK.Initialize( ASN1::secp256r1(), p );
        const ECP::Point& point = PK.GetPublicElement();
        const Integer& pointx = point.x;
        const Integer& pointy = point.y;*/

        /*k.Load( fs1 );
        ECDSA<ECP, SHA256>::Signer signer(k);
        ECDSA<ECP, SHA256>::Verifier verifier(PK);
        std::string message = "Do or do not. There is no try.";
        size_t siglen = signer.MaxSignatureLength();
        std::string signature(siglen, 0x00);
        siglen = signer.SignMessage( prng, (const byte*)&message[0], message.size(), (byte*)&signature[0] );
        signature.resize(siglen);*/
        
        /*bool result = verifier.VerifyMessage( (const byte*)&message[0], message.size(), (const byte*)&signature[0], signature.size() );
        if( !result ) {
            std::cout << "Failed to verify signature on message#" <<1<< std::endl;
        } else {
            std::cout << "All good! For MSG"<< std::endl;
            const Integer& x = k.GetPrivateExponent();
            //std::cout << "K: " << std::hex << x << std::endl;

        }*/
    }
    wfile.close();
    return 0;
}