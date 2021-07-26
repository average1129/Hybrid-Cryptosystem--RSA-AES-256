
SRC_1 = src/aes.c  src/AES_functions.c src/filefunctions.c  src/RSA.c src/pkcs7_padding.c src/file_function_test.c 
SRC_2 = src/aes.c  src/AES_functions.c src/filefunctions.c  src/RSA.c src/pkcs7_padding.c src/RSA_test.c
SRC_3 = src/aes.c  src/AES_functions.c src/filefunctions.c  src/RSA.c src/pkcs7_padding.c src/AES_test_19.c
INCLUDE = include

compile1 :	$(SRC_1) 
	gcc -o file_functions $^ -I$(INCLUDE) -lgmp 

compile2 :	$(SRC_2) 
	gcc -o file_RSA $^ -I$(INCLUDE) -lgmp 

compile3 :	$(SRC_3) 
	gcc -o file_AES $^ -I$(INCLUDE) -lgmp 

test1 :	compile1	
	./file_functions

test2 :	compile1	
	./file_RSA

test3 :	compile1	
	./file_AES

mem_leak:	compile1 compile2 compile3 
	valgrind ./file_RSA
	

clean :	
	rm *.o src/*.o file_AES file_function_test file_functions
