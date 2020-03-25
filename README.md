# GenerateCertificatesAndSignatures
C++ codes to generate ECDSA certificates and signatures for PKI and Blockchain framework (using Crypto++ library - https://www.cryptopp.com/wiki/Elliptic_Curve_Digital_Signature_Algorithm). You may need to install this library - https://www.cryptopp.com/.

The RestAPI.cc file contains the functions for different transactions in the Blockchain network. These functions include the one for generating assests in the Blockchain framework. To execute this function, you will need to download the C++ Rest SDK - https://github.com/microsoft/cpprestsdk. When you compile the file, you will need to provide addition command line arguments like: -lboost_system -lcrypto -lssl -lcpprest.
