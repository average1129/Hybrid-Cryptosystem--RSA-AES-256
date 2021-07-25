# STEPin-Mini-Project
![STEPin](https://user-images.githubusercontent.com/71325016/126390610-84b74fb3-c6d7-48cb-9597-5e16bc9d7ddc.JPG)

|Badge|Status|
|-----|------|
|![Build_Env]|https://github.com/average1129/STEPin-Mini-Project-/blob/main/.github/workflows/Build_Project.yml|

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


Folder Structure 
| Folder         | Description |
|----------------|-------------|
|`1_Requirements & Research`  |Documents detailing requirements and research|
|`2_Design`        |Documents specifying design details|
|`3_Implementation`|All code and documentation|
|`4_Test _Plan`| Test plan and procedure|


Project Features

| Feature ID       | Features | Feature Status|
|----------------|-------------|--------------|
|`1_` |Select File to send | Implemented|
|`2_`|Encryption and transmission of File using AES |Implemented |
|`3_`|Encryption and transmission of AES Key using RSA | Implemented|
|`4_`|Transmission of RSA Key|Implemented |
|`5_`| Reception of RSA Key  ||
|`6`|Decryption of AES Key |Implemented in exclusion|
|`7`|Decryption of File contents |Implemented|
|`8`|File Write in Reciever System||
|`9`|Multi Client Connection to Central Server||
|`10`|Displaying Available Clients to Sender to choose||
|`11`|Dual Threaded Large Prime Generation |Implemented in Exclusion|



