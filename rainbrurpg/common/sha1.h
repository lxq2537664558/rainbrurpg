/*
 *  sha1.h
 *
 *  Description:
 *      This is the header file for code which implements the Secure
 *      Hashing Algorithm 1 as defined in FIPS PUB 180-1 published
 *      April 17, 1995.
 *
 *      Many of the variable names in this code, especially the
 *      single character names, were used because those were the names
 *      used in the publication.
 *
 *      Please read the file sha1.c for more information.
 *
 */

/** \file sha1.h
  * Declares the Secure Hashing Algorithm
  *
  * Modifications :
  * - 18 apr 2009 : Uses gettext 
  * - 08 aug 2008 : Documentation update
  * - 21 jul 2007 : Documentation for doxygen
  *                 Making functions static members of a class
  *
  */

#ifndef _SHA1_H_
#define _SHA1_H_

#include "rainbrudef.h"

#include <stdint.h>
/*
 * If you do not have the ISO standard stdint.h header file, then you
 * must typdef the following:
 *    name              meaning
 *  uint32_t         unsigned 32 bit integer
 *  uint8_t          unsigned 8 bit integer (i.e., unsigned char)
 *  int_least16_t    integer of >= 16 bits
 *
 */

#ifndef _SHA_enum_
#define _SHA_enum_
enum
{
    shaSuccess = 0,
    shaNull,            /* Null pointer parameter */
    shaInputTooLong,    /* input data too long */
    shaStateError       /* called Input after Result */
};
#endif

/** The size of the hashsum */
#define SHA1HashSize 20

/**  This structure will hold context information for the SHA-1
  *  hashing operation
  */
typedef struct SHA1Context
{
  uint32_t Intermediate_Hash[SHA1HashSize/4]; //!< Message Digest/

  uint32_t Length_Low;            //!< Message length in bits
  uint32_t Length_High;           //!< Message length in bits

                               
  int_least16_t Message_Block_Index;//!< Index into message block array
  uint8_t Message_Block[64];      //!< 512-bit message blocks

  int Computed;              //!< Is the digest computed?
  int Corrupted;             //!< Is the message digest corrupted?
} SHA1Context;

/**
  * This class implements the Secure Hashing Algorithm 1 as defined 
  * in FIPS PUB 180-1 published April 17, 1995.
  *
  * Many of the variable names in this code, especially the
  * single character names, were used because those were the names
  * used in the publication.
  *
  */
class Sha1{
 public:
  static int SHA1Reset(  SHA1Context *);
  static int SHA1Input(  SHA1Context *,
		  const uint8_t *,
		  unsigned int);
  static int SHA1Result( SHA1Context *,
		  uint8_t Message_Digest[SHA1HashSize]);

 private:
  static void SHA1PadMessage(SHA1Context *);
  static void SHA1ProcessMessageBlock(SHA1Context *);

};
#endif

