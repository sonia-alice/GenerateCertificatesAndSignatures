#include <iostream>
#include <vector> 
#include <sstream>
#include <fstream>
#include <string>
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
    FileSource fs1( "private.ec.der", true  );
    k.Load(fs1);
    ECDSA<ECP, SHA256>::Signer signer(k);
    ECDSA<ECP, SHA256>::PublicKey publicKey;
    vector<ECDSA<ECP, SHA256>::PublicKey> pkey;
    FileSource fs2( "public.ec.der", true  );

    ofstream wfile;
    //wfile.open("signPK.dat", ios::out|ios::binary);
    for (int i=1; i<55;i++){
        std::string fileName = "/home/sonia/temporary/signPK" + std::to_string(i) + ".dat";
        wfile.open(fileName, ios::out|ios::binary);
        publicKey.Load( fs2 );
        pkey.push_back(publicKey);
        const ECP::Point& q = publicKey.GetPublicElement();
        const Integer& qx = q.x;
        const Integer& qy = q.y;
        std::stringstream ss;
        ss << std::hex<<qx;
        std::string msg = ss.str();
        size_t siglen = signer.MaxSignatureLength();
        std::string signature(siglen, 0x00);
        siglen = signer.SignMessage( prng, (const byte*)&msg[0], msg.size(), (byte*)&signature[0] );
        signature.resize(siglen);
        std::cout<<"Sig: "<<signature<<std::endl;
        //std::cout<<"Sig len: "<<siglen<<std::endl;
        wfile<<signature;
        std::cout<<signature.size()<<std::endl;
        wfile.close();
    }

    return 0;
}