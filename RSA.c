#include "openssl/bio.h"
#include "openssl/ssl.h"
#include "openssl/err.h"
#include "openssl/rsa.h"
#include "openssl/pem.h"

#include <string.h>
#include <stdlib.h>
#include "ByteArray.h"
#include "Declarations.h"

static char* DofusPublicKey="-----BEGIN PUBLIC KEY-----\n"
"MIIBUzANBgkqhkiG9w0BAQEFAAOCAUAAMIIBOwKCATIAgucoka9J2PXcNdjcu6CuDmgteIMB+rih\n"
"2UZJIuSoNT/0J/lEKL/W4UYbDA4U/6TDS0dkMhOpDsSCIDpO1gPG6+6JfhADRfIJItyHZflyXNUj\n"
"WOBG4zuxc/L6wldgX24jKo+iCvlDTNUedE553lrfSU23Hwwzt3+doEfgkgAf0l4ZBez5Z/ldp9it\n"
"2NH6/2/7spHm0Hsvt/YPrJ+EK8ly5fdLk9cvB4QIQel9SQ3JE8UQrxOAx2wrivc6P0gXp5Q6bHQo\n"
"ad1aUp81Ox77l5e8KBJXHzYhdeXaM91wnHTZNhuWmFS3snUHRCBpjDBCkZZ+CxPnKMtm2qJIi57R\n"
"slALQVTykEZoAETKWpLBlSm92X/eXY2DdGf+a7vju9EigYbX0aXxQy2Ln2ZBWmUJyZE8B58CAwEA\n"
"AQ==\n"
"-----END PUBLIC KEY-----";

static void init()
{
    SSL_load_error_strings();
	ERR_load_BIO_strings();
	OpenSSL_add_all_algorithms();
}

static byte* DofusPKeyDecrypt(byte* signature, int* size)
{
	BIO* bp_dofus = BIO_new_mem_buf(DofusPublicKey, -1);
	RSA* my_rsa = PEM_read_bio_RSA_PUBKEY(bp_dofus, NULL, NULL, NULL);
	byte* outputSignature = malloc(sizeof(char)*500);
	*size=RSA_public_decrypt(*size, signature, outputSignature, my_rsa, RSA_PKCS1_PADDING);

	printf("\n%d\n", *size);
	//for(int i = 0; i < *size; ++i)
        //printf("%x ", outputSignature[i]);
	return outputSignature;
}

static byte* LoginPKeyEncrypt(ByteArray credentials, char* DofusPK, int* size)
{
	BIO* bp_login = BIO_new_mem_buf(DofusPK, *size);
	RSA* my_second_rsa = PEM_read_bio_RSA_PUBKEY(bp_login, NULL, NULL, NULL);
	byte* outputCredentials = malloc(sizeof(char)*500);
    *size=RSA_public_encrypt(getPosition(credentials),getBuffer(credentials), outputCredentials, my_second_rsa, RSA_PKCS1_PADDING);
	return outputCredentials;
}

static char* setLoginPublicKey(byte* LoginPK, int* size)
{
	char* LoginPKChar=base64_encode(LoginPK, size);
	unsigned char* LoginPKChar2=malloc(sizeof(char)*500);
	int j=0;
	for(int i=0;i<*size;i++)
    {
        LoginPKChar2[i+j]=LoginPKChar[i];
        if ((i+1)%76==0)
        {
            LoginPKChar2[i+j+1]='\n';
            j++;
        }

	}
	int len_LPKChar2=*size+j;
	char* begin = "-----BEGIN PUBLIC KEY-----\n";
	char* end="\n-----END PUBLIC KEY-----";
	for(int i=0;i<27;i++)
        LoginPKChar[i]=begin[i];
	for(int i=0;i<len_LPKChar2;i++)
        LoginPKChar[i+27]=LoginPKChar2[i];
    for(int i=0;i<25;i++)
        LoginPKChar[i+27+len_LPKChar2]=end[i];
    LoginPKChar[27+25+len_LPKChar2]='\0';
    free(LoginPK);
    free(LoginPKChar2);
    *size=27+25+len_LPKChar2;
	return LoginPKChar;
}

static int* cipherRsa(char* pseudo, char* mdp, char* salt, char* DofusPKChar, int* size)
{
    ByteArray credBytes=creerByteArray(NULL,0);
    writeUTFBytes(credBytes, salt);
    writeByte(credBytes, strlen(pseudo));
    writeUTFBytes(credBytes, pseudo);
    writeUTFBytes(credBytes, mdp);
    setBuffer(credBytes,LoginPKeyEncrypt(credBytes,DofusPKChar,size),*size);
    int* credInt=malloc(*size*sizeof(int));
    for(int i=0;i<*size;++i)
        credInt[i]=ReadByte(credBytes);
    detruireByteArray(credBytes);
    return credInt;
}

int* encryption(byte* signature, int *size, char* pseudo, char* mdp, char* salt)
{
    init();
    byte* DofusPK=DofusPKeyDecrypt(signature, size);
    char* DofusPKChar=setLoginPublicKey(DofusPK, size);
    return cipherRsa(pseudo, mdp, salt, DofusPKChar, size);
}
