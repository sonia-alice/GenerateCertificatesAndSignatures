#include <iostream>
#include <vector> 
#include <sstream>
#include <fstream>
#include "/usr/include/crypto++/eccrypto.h"
#include "/usr/include/crypto++/osrng.h"
#include "/usr/include/crypto++/oids.h"
#include "/usr/include/crypto++/files.h"

using namespace CryptoPP;
using namespace std; 

int main(int argc, const char* argv[]) 
{   
    //AutoSeededRandomPool prng;
    ECDSA<ECP, SHA256>::PublicKey publicKeyCA;
    FileSource fs1( "public.ec.der", true  );
    publicKeyCA.Load(fs1);
    ECDSA<ECP, SHA256>::Verifier verifier(publicKeyCA);
    vector<ECDSA<ECP, SHA256>::PublicKey> pkey;
    std::string signature;
    ECDSA<ECP, SHA256>::PublicKey publicKey;
    FileSource fs2( "public.ec.der", true  );

    // ifstream rfile ("signPK.dat", ios::out|ios::binary);
   // if(rfile.is_open())
   // {
    for (int i=1; i<30;i++){
        std::string fileName = "/home/sonia/temporary/signPK" + std::to_string(i) + ".dat";
        ifstream rfile (fileName, ios::in|ios::binary);
        std::string buffer ;
        getline(rfile, buffer);
        signature = buffer;
        getline(rfile, buffer);
        signature = signature + "\n" + buffer;
        getline(rfile, buffer);
        signature = signature + "\n" + buffer;
        //rfile >> signature;
        /*char buffer[80] = {};
        rfile.read(buffer,80);
        signature = buffer;*/
        publicKey.Load( fs2 );
        const ECP::Point& q = publicKey.GetPublicElement();
        const Integer& qx = q.x;
        const Integer& qy = q.y;
        std::stringstream ss;
        ss << std::hex<<qx;
        std::string msg = ss.str();
        std::cout<<"Message: "<<msg<<std::endl;
        std::cout<<"Certificate: "<<signature<<std::endl;
        bool result = verifier.VerifyMessage( (const byte*)&msg[0], msg.size(), (const byte*)&signature[0], signature.size() );
        if(result){
            std::cout<<"Validated successfully"<<std::endl;
        }
        else
        {
            std::cout<<"Validated unsuccessfully"<<std::endl;
            //std::cout<<"MSG : "<<msg<<std::endl;
            //std::cout<<"Sig : "<<signature<<std::endl;
        }
        std::cout<<std::endl;
    }
   // }
    //rfile.close();

    return 0;
}