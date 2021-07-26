# STEPin-Mini-Project
![STEPin](https://user-images.githubusercontent.com/71325016/126390610-84b74fb3-c6d7-48cb-9597-5e16bc9d7ddc.JPG)

|Action| Status|
|------|--------|
|Build Project|[![Build_Project](https://github.com/average1129/STEPin-Mini-Project-/actions/workflows/Build_Project.yml/badge.svg)](https://github.com/average1129/STEPin-Mini-Project-/actions/workflows/Build_Project.yml)|
|Dynamic Code Quality Check|[![Memory Leak Test](https://github.com/average1129/STEPin-Mini-Project-/actions/workflows/Memory%20Leak%20Test.yml/badge.svg)](https://github.com/average1129/STEPin-Mini-Project-/actions/workflows/Memory%20Leak%20Test.yml)|
|Static Code Quality Check|[![Static Code Analysis](https://github.com/average1129/STEPin-Mini-Project-/actions/workflows/CppCheck.yml/badge.svg)](https://github.com/average1129/STEPin-Mini-Project-/actions/workflows/CppCheck.yml)|



This project attempts to create a simple Hybrid Cryptosystem for secure file transfer. There are two broad classes of Cryptopgraphic algorithms in use: Asymmetric and Symmetric:

Both systems have their own drawbacks, we can mitigate this issue  by using a hybrid Cryptosystem, which uses both classes of encryption algorithms for added security. In this project we encrypt our data using a symmetric algorithm like AES 128 and encrypt the AES 128 key using RSA algorithm, the  RSA public key is then distributed. The intended reciever will be able to decrypt the AES key and succesfully decrypt the recieved data . 

## Project Requirements 

This project  uses the open source GNU Multiprecision Library (GMPlib) for the implementation of RSA, and uses an open source implementation of AES (kokke/tiny-AES-c) intended for embedded development. 

### For general information on GMPlib:
https://gmplib.org/manual/Introduction-to-GMP

### GMPlib installation and build details: 
https://gmplib.org/manual/Installing-GMP
Following the instructions on this pafe should lead to a comfortable installation, after running make, make sure to implement the tests as well. 

### GMPlib API and function reference:
https://gmplib.org/manual/GMP-Basics

### Tiny-AES-C : 
https://github.com/kokke/tiny-AES-c
Simply download the ZIP folder from github and  run test makefile to ensure correct installation and working of program. Just add aes.c and aes.h to your project space. 


### Folder Structure 
| Folder         | Description |
|----------------|-------------|
|`1_Requirements & Research`  |Documents detailing requirements and research|
|`2_Design`        |Documents specifying design details|
|`3_Implementation`|Source Code|
|`4_Documentation`| Documentation of Project|


### Project Features

| Feature ID       | Features | Feature Status|
|----------------|-------------|--------------|
|`1` |Select File to send | Implemented|
|`2`|Encryption and transmission of File using AES |Implemented |
|`3`|Encryption and transmission of AES Key using RSA | Implemented|
|`4`|Transmission of RSA Key|Unable to Implement |
|`5`| Reception of RSA Key  |Unable to Implement|
|`6`|Decryption of AES Key |Implemented in exclusion|
|`7`|Decryption of File contents |Implemented in exclusion|
|`8`|File Write in Reciever System|In progress|
|`9`|Dual Threaded Large Prime Generation |Implemented in Exclusion|

### Acknowledgement

I would like to acknowledge Aadreesh's and Arihant's support in the project especially helping me understand how to implement the CI/CD features. I would also like to thank Bharat and Rajesh for their constant support and guidance on the project.   

