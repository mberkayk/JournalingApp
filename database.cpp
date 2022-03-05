#include "database.h"
#include <QStandardPaths>
#include <QDir>
#include <QDebug>
#include <QSqlDatabase>
#include <QSqlError>
#include <openssl/evp.h>
#include <openssl/rand.h>
#include <openssl/err.h>

Database::Database() {

    QString dirStr = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    QDir dir(dirStr);
    if(!dir.exists()){
        qDebug() << "data directory does not exist";
        if(dir.mkpath(dirStr)) qDebug() << "data directory was created";
        else qDebug() << "data directory couldn't be created";
    }else{
        qDebug() << "data directory alredy exists" << dirStr;
    }


    keyFile = new QFile(dirStr + "/key");
    QString dbPath = dirStr + "/database.db";
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");//not dbConnection
    db.setDatabaseName(dbPath);
    if(!db.open()) qDebug() << db.lastError();

}

Database::~Database(){
    delete keyFile;
}

void Database::handleErrors() {
    ERR_print_errors_fp(stderr);
    abort();
}


int Database::encrypt(unsigned char *plaintext, int plaintext_len, unsigned char *key, unsigned char *iv, unsigned char *ciphertext) {
    EVP_CIPHER_CTX *ctx;

    int len;

    int ciphertext_len;

    /* Create and initialise the context */
    if(!(ctx = EVP_CIPHER_CTX_new()))
        handleErrors();

    /*
     * Initialise the encryption operation. IMPORTANT - ensure you use a key
     * and IV size appropriate for your cipher
     * In this example we are using 256 bit AES (i.e. a 256 bit key). The
     * IV size for *most* modes is the same as the block size. For AES this
     * is 128 bits
     */
    if(1 != EVP_EncryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, key, iv))
        handleErrors();

    /*
     * Provide the message to be encrypted, and obtain the encrypted output.
     * EVP_EncryptUpdate can be called multiple times if necessary
     */
    if(1 != EVP_EncryptUpdate(ctx, ciphertext, &len, plaintext, plaintext_len))
        handleErrors();
    ciphertext_len = len;

    /*
     * Finalise the encryption. Further ciphertext bytes may be written at
     * this stage.
     */
    if(1 != EVP_EncryptFinal_ex(ctx, ciphertext + len, &len))
        handleErrors();
    ciphertext_len += len;

    /* Clean up */
    EVP_CIPHER_CTX_free(ctx);

    return ciphertext_len;
}

int Database::decrypt(unsigned char *ciphertext, int ciphertext_len, unsigned char *key, unsigned char *iv, unsigned char *plaintext) {
    EVP_CIPHER_CTX *ctx;

    int len;

    int plaintext_len;

    if(!(ctx = EVP_CIPHER_CTX_new()))
        handleErrors();

    if(1 != EVP_DecryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, key, iv))
        handleErrors();

    if(1 != EVP_DecryptUpdate(ctx, plaintext, &len, ciphertext, ciphertext_len))
        handleErrors();
    plaintext_len = len;

    if(1 != EVP_DecryptFinal_ex(ctx, plaintext + len, &len))
        handleErrors();
    plaintext_len += len;

    /* Clean up */
    EVP_CIPHER_CTX_free(ctx);

    return plaintext_len;
}

void Database::newPasswordEntered(QByteArray a){

	//generate a random encryption key to be encryted
	//this key will be encryted with the password generated key
	//and stored in the keyFile
	unsigned char *key = new unsigned char[32];
	RAND_bytes(key, 32);
	QByteArray tmparr = QByteArray::fromRawData((char*)key, 32);
	qDebug() << "this is the second key:" << tmparr;

	//the key which is generated from the password
	unsigned char *passKey = new unsigned char[32];
	for(int i=0; i < 32; i++){
		passKey[i] = a.at(i);
	}

	unsigned char *iv = new unsigned char[16];
	RAND_bytes(iv, 16);
	tmparr = QByteArray::fromRawData((char*)iv, 16);
	qDebug() << "iv: " << tmparr;

	unsigned char *out = new unsigned char[32];
	int outlen = encrypt(key, 32, passKey, iv, out);

	qDebug() << "out length is:" << outlen;


	keyFile->open(QIODevice::WriteOnly);
	keyFile->write((char*)iv, 16);
	keyFile->write((char*)out, outlen);

	QByteArray arr;
	for(int i = 0; i < outlen; i++){
		arr.append(out[i]);
	}
	qDebug() << "digest:" << arr;

	keyFile->close();

	emit passInitComplete();

}

void Database::oldPassEntered(QByteArray arr) {

	qDebug() << "passKey:" << arr.size() << arr;

	unsigned char passKey[32];
	for(int i=0; i < 32; i++){
		passKey[i] = arr.at(i);
	}

	keyFile->open(QIODevice::ReadOnly);

	unsigned char iv[16];
	keyFile->read((char*)iv, 16);
	QByteArray tmparr = QByteArray::fromRawData((char*)iv, 16);
	qDebug() << "iv: " << tmparr;


	QByteArray cipherArr = keyFile->read(100);
	unsigned char ciphertext[48];
	qDebug() << "cipher: " << cipherArr.size() << cipherArr;
	for(int i = 0; i < 48; i++){
		ciphertext[i] = cipherArr.at(i);
	}

	keyFile->close();

	unsigned char plaintext[128];


	int outputlen = decrypt(ciphertext, 48, passKey, iv, plaintext);

	QByteArray tmp;
	for(int i = 0; i < outputlen; i++){
		tmp.append(plaintext[i]);
	}
	qDebug() << "key: " << tmp;

}

