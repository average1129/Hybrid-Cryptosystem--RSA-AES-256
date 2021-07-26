#include <stddef.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#ifndef _AES_FUNCTIONS_H_
#define _AES_FUNCTIONS_H_
//#include "pkcs7_padding.c" 
// create object file and link statically
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include "pkcs7_padding.h"


/**
 * @file AES_functions.h
 * @author adityasaggar2911@gmail.com
 * @brief This file defines the structure to hold important parameters for AES generation. and to randomly generate key and IV
 * @version 0.1
 * @date 2021-07-25
 * 
 * @copyright Copyright (c) 2021
 * 
 * 
 * */

 
 /**
 * @brief Structure holds 16 bit AES Key and 16 bit IV 
 * 
 * */
typedef struct 
{
    uint8_t  AES_KEY[16];
    uint8_t AES_IV[16];

}AES_parameters;

/** 
 * @brief generates randomized key
 * @param[in] Uninitialized Key array from AES_PARAMETERS
 * @param[out] Initialized Key array
 * @return void 
 * */
void generate_key(uint8_t key_array[16]);

/** 
 * @brief generates randomized IV
 * @param[in] Uninitialized IV array from AES_PARAMETERS
 * @param[out] Initialized IV array
 * @return void 
 * */
void generate_iv (uint8_t iv_array[16]);

/** 
 * @brief Initializes AES_parameters structure
 * @param[in] AES_p pointer to AES_parameters structure
 * @param[out] Initialized AES_parameters structure
 * @return void 
 * */
void initialize_AES_parameters(AES_parameters* new_parameters);

/** 
 * @brief Prints out hex array
 * @param[in] pointer to integer array 
 * @param[in] size of array
 * @param[out] array values are printed
 * @return void 
 * */
void print_hex_array (uint8_t * input_ptr, int buffer_size);


#endif 
