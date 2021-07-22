## Introduction 

This project attempts to create a simple Hybrid Cryptosystem for secure file transfer. There are two broad classes of Cryptopgraphic algorithms in use:
Asymmetric and Symmetric.

Asymmetric Algorithms use a "trap door" function which is easily calculated one way, but computationally impossible without a key piece of information. This results in the generation of two keys : 1 Public and 1 Private Key. This allows a sender to freely distribute a public key, but without the private key the data remains secure.

Symmetric algorithms use a single key. They allow for faster encryption especially for larger data sizes, an example of such an encryption algorithm is AES 128. However, symmetric keys have a drawback, since the sensitive key needs to be exchanged between sender and reciever, a man in the middle attack can be carried out.

Both classes have their own sets of disadvantages and advantages. We can nullify each systems disadvantages by using a system which uses both classes of encryption algorithms for added security. In this project we encrypt our data using a symmetric algorithm like AES 128 and encrypt the AES 128 key using RSA algorithm, the RSA public key is then distributed.
The intended reciever will be able to decrypt the AES key and succesfully decrypt the recieved data . 

### RSA Encryption Algorithm 
In a public-key cryptosystem, the encryption key is public and distinct from the decryption key, which is kept secret (private). An RSA user creates and publishes a public key based on two large prime numbers, along with another value. The prime numbers are kept secret. Messages can be encrypted by anyone, via the public key, but can only be decoded by someone who knows the prime numbers. RSA is often used in hybrid Cryptosystems to facilitate the transfer of sensitive data which has a small length, specifically keys from other types of encryption. 

![Picture1](https://user-images.githubusercontent.com/71325016/126684129-ac5c8be6-c95f-47cf-9517-1722ee2e8a6f.png)
### AES Encryption Algorithm 
AES is a subset of the Rijndael block cipher, It sees widespread use for a variety of needs. It is based on the concept of substitution permutation networks. There are a number of key lengths and methodologies of AES used, and is a popular choise for symmetric encryption.  

![Picture2](https://user-images.githubusercontent.com/71325016/126684408-b799462a-d0d5-448a-af8a-e28de498bda9.jpg)


## Defining the System
[INSERT SYSTEM DIAGRAM]

The project aims to facilitate secure file transfer over a TCP connection.  We encrypt our data using a symmetric algorithm like AES 128 and encrypt the AES 128 key using RSA algorithm, the RSA public key is then distributed. The intended reciever will be able to decrypt the AES key and succesfully decrypt the recieved data .




#### NOTE

This project is meant for educational purposes and the cryptographic algorithms should **NOT** be used in a production environment. 

## 5W's & 1H 
### WHAT 
Program to securely transfer files from one client to the other 

### WHY
Symmetric Algorithms share a common key for decryption and encryption, the transmission of this key can make a file transfer system vulnerable to man in the middle attacks. Encryption of the key using an asymmetric algorithm allows us to safely transfer the keys without worries.

### HOW
Using AES 128 (CBC mode) to encrypt our file and using RSA 2048 to encrypt our AES 128 key, which are all then transmitted over a socket connection.

### WHEN
Whenever user wishes to securely transmit a file.

### WHERE 
In any computing application, especially one which requires secure file transfer. This could include bank transactions, identity verifications, sharing of personal details, etc. 

### WHO
Anyone who wants to transmit a file from their system to another system. 





## Requirements: 

### High Level Requirements 
|Requirement ID| Description|
|----|---------------------------------------------------------------------------------|
|HR_1 |Secure Asymmetric Encryption Algorithm| 
|HR_2 |Secure Symmetric Encryption Algorithm |
|HR_3 |Asymmetric Encryption algorithm should be able to effectively encrypt data that is atleast the size of Symmetric Algorithm's Key Length|
|HR_4 |Effective Key Distribution Method for RSA |
|HR_5 |Padding system for padding input data |
|HR_6 |Keys used should be random|
|HR_7 |All pertinent data should be transmitted reliably|
|HR_8 |Ability to flexibly select files to send |
|HR_9 |File Size Flexibility|
|HR_10 |Data transfer is from single user-to-single user only|


### Low Level Requirements 
|Requirement ID| Description|
|----|---------------------------------------------------------------------------------|
|LR_1| Use of RSA for Asymmetric Encryption|
|LR_2|Using RSA - 2048 ((2048 bit key)) for security , since lower key sizes have known vulnerabilities.|
|LR_3| Using AES for Symmetric Encryption|
|LR_4 |Using AES 128 since this key size (128 bits) is effectively encrypted by RSA 2048, and is very secure|
|LR_5 |Use of a Randomizer for generation of AES Initialization vector and AES Key using rand() function |
|LR_6 |Padding of input file to ensure file is a multiple of 16 bytes (AES 128 requirement)- General and PCKS7| 
|LR_7 |Data transmission over TCP sockets (RSA public key, Encrypted AES key, Encrypted File Contents) |
|LR_8 |Simple User Interface to select file by writing  full pathname into std input upon prompt|
|LR_9 |Application quits upon typing in "quit" into user interface|
|LR_10 |Use of GNU Multi Precision Library for generation of large primes for RSA| 
|LR_11 |Use of Open Source AES library : Tiny AES for implementing AES functionalities|
LR_12 |File Read-Write using built in libraries |



