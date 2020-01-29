/*
* This code is used as the C++ code for executing 
* the different transactions for the Blockchain - REST API 
* calls. You can use this code with the veins application 
* to execute the different transactions.
*/

#include "/usr/include/crypto++/eccrypto.h"
#include "/usr/include/crypto++/osrng.h"
#include "/usr/include/crypto++/oids.h"
#include "/usr/include/crypto++/files.h"
#include "/usr/include/crypto++/hex.h"
#include <iostream>
#include <vector> 
#include <sstream>
#include <fstream>
#include <string>
#include <cpprest/http_client.h>
#include <cpprest/filestream.h>
#include <fstream>

using namespace utility;                    // Common utilities like string conversions
using namespace web;                        // Common features like URIs.
using namespace web::http;                  // Common HTTP functionality
using namespace web::http::client;          // HTTP client features
using namespace concurrency::streams;       // Asynchronous streams
using namespace CryptoPP;
using namespace std; 

bool verifyPseudnm(std::string pnm)
{
    http_client client(std::string("http://localhost:3000/api/queries/selectAllValidVehicles?PIDParam=")+pnm);
    http_response response = client.request(methods::GET).get();
    if(response.status_code() == status_codes::OK)
    {
        utility::string_t body = response.extract_string().get();
        if(body.compare("[]")==0)
            return false;
        string_t value = body.substr(49, 8);
        if(pnm.compare(value)==0)
            return true;
    }
    return false;
}

void registerVehicle(string_t vin, std::string pnm1, std::string pnm2, std::string pnm3)
{
    http_client client(std::string("http://localhost:3000/api/VehicleReg"));
    json::value json_v ;
    json_v["$class"] = json::value("org.vanet1.mynetwork.VehicleReg");
    json_v["VIN"] = json::value(vin);
    json_v["PID"] = json::value(pnm1);
    json_v["PID2"] = json::value(pnm2);
    json_v["PID3"] = json::value(pnm3);
    http_response response = client.request(methods::POST, std::string("/"), json_v).get();
    if(response.status_code() == status_codes::OK)
    {
        printf("VehicleReg Posted successfully\n");
    }
    else
    {
        printf("VehicleReg POST unsuccessful\n");
        const utility::string_t body = response.extract_string().get();
        std::cout << body << std::endl;
    }

}

void registerVehiclePID(std::string pnm1, std::string pk)
{
    http_client client(std::string("http://localhost:3000/api/Vehicle"));
    json::value json_v ;
    json_v["$class"] = json::value("org.vanet1.mynetwork.Vehicle");
    json_v["PID"] = json::value(pnm1);
    json_v["PK"] = json::value(pk);
    json_v["status"] = json::value("valid");
    json_v["misbehaviorRpt"] = json::value(0);
    http_response response = client.request(methods::POST, std::string("/"), json_v).get();
    if(response.status_code() == status_codes::OK)
    {
        printf("Vehicle Posted successfully\n");
    }
    else
    {
        printf("Vehicle POST unsuccessful\n");
        const utility::string_t body = response.extract_string().get();
        std::cout << body << std::endl;
    }
}

void misbehaviourRpt(std::string pid, std::string rsuID)
{
    http_client client(std::string("http://localhost:3000/api/Misbehavior"));
    json::value json_v ;
    json_v["$class"] = json::value("org.vanet1.mynetwork.Misbehavior");
    json_v["car"] = json::value("resource:org.vanet1.mynetwork.Vehicle#"+pid);
    json_v["RSUID"] = json::value(rsuID);
    http_response response = client.request(methods::POST, std::string("/"), json_v).get();
    if(response.status_code() == status_codes::OK)
    {
        printf("Misbehavior transaction Posted successfully\n");
    }
    else
    {
        printf("Misbehavior transaction POST unsuccessful\n");
        const utility::string_t body = response.extract_string().get();
        std::cout << body << std::endl;
    }
}

void readmitVehicle(std::string vID, std::string pnm1, std::string pnm2, std::string pnm3, std::string pk)
{
    http_client client(std::string("http://localhost:3000/api/Readmission"));
    json::value json_v ;
    json_v["$class"] = json::value("org.vanet.network.Readmission");
    json_v["car"] = json::value("resource:org.vanet.network.VehicleReg#"+vID);
    json_v["pseudo1"] = json::value(pnm1);
    json_v["pseudo2"] = json::value(pnm2);
    json_v["pseudo3"] = json::value(pnm3);
    http_response response = client.request(methods::POST, std::string("/"), json_v).get();
    if(response.status_code() == status_codes::OK)
    {
        printf("Readmission Posted successfully\n");
    }
    else
    {
        printf("Readmission POST unsuccessful\n");
        const utility::string_t body = response.extract_string().get();
        std::cout << body << std::endl;
    }

    http_client client2(std::string("http://localhost:3000/api/Vehicle"));
    json::value json_v2 ;
    json_v2["$class"] = json::value("org.vanet1.mynetwork.Vehicle");
    json_v2["PID"] = json::value(pnm1);
    json_v2["PK"] = json::value(pk);
    json_v2["status"] = json::value("valid");
    json_v2["misbehaviourRpt"] = json::value(0);
    http_response response2 = client2.request(methods::POST, std::string("/"), json_v2).get();
    if(response2.status_code() == status_codes::OK)
    {
        printf("Readmission Posted successfully\n");
    }
    else
    {
        printf("Readmission POST unsuccessful\n");
        const utility::string_t body = response2.extract_string().get();
        std::cout << body << std::endl;
    }
}
//This code will generate n no. of vehicles in a sequencial order
//in the Blockchain. Ensure that you have generated n no. of PK using 
//the code file - GeneratePK_SK.cc
bool createInputBC(int n){
    std::string vid = "1USWE1GHTY7";
    long num = 800000;
    long pid1 = 21000000, pid2 = 31000000, pid3 = 41000000;
    ifstream rfile ("stringPK.dat", ios::in|ios::binary);

    for(int i=0; i<n;i++){
        
        
        std::string pt;
        getline(rfile,pt) ;        
        if(i==0){
            continue;
        }
        else{
            num++, pid1++, pid2++, pid3++;
            std::string sVID = vid + to_string(num);
            registerVehicle(sVID,to_string(pid1), to_string(pid2), to_string(pid3));
            registerVehiclePID(to_string(pid1), pt);
        }
    }
    rfile.close();
}

int main(int argc, const char* argv[])
{
    if(verifyPseudnm("21000044"))
        std::cout<<"Valid vehicle"<<std::endl;
    else
    {
        std::cout<<"Invalid vehicle"<<std::endl;
    }
    
    return 0;
}
