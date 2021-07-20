# STEPin-Mini-Project
![STEPin](https://user-images.githubusercontent.com/71325016/126390610-84b74fb3-c6d7-48cb-9597-5e16bc9d7ddc.JPG)
This project attempts to create a simple Hybrid Cryptosystem for secure file transfer. There are two broad classes of Cryptopgraphic algorithms in use, Asymmetric and Symmetric. Asymmetric Algorithms use a "trap door" function which is easily calculated one way, but computationally impossible without a key piece of information. This results in the generation of two keys : 1 Public and 1 Private Key.  This allows a sender to freely distribute a public key, but without the private key the data remains secure. Symmetric algorithms use a single key. They allow for faster encryption especially for larger data sizes, an example of such an encryption algorithm is AES 128. However, symmetric keys have a drawback,  since the sensitive key needs to be exchanged between sender and reciever, a man in the middle attack can be carried out. This issue can be solved by using a hybrid Cryptosystem, which uses both classes of encryption algorithms for added security. In this project we encrypt our data using a symmetric algorithm like AES 128 and encrypt the AES 128 key using RSA algorithm, the  RSA public key is then distributed. The intended reciever will be able to decrypt the AES key and succesfully decrypt the recieved data . 

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

| Feature ID       | Features |
|----------------|-------------|
|`1_` ||
|`2_`||
|`3_`||
|`4_`||

Identified Bugs 

| Bug ID       | Description | Debugging Plan of Attack 
|----------------|-------------|----------------------|
|`1_` || |
|`2_`||  |
|`3_`||  |
|`4_`||  |
