#ifndef MD5_H
#define MD5_H

/**
 *    MD5 context structure
 */
typedef struct 
{
	unsigned int total[2];
	unsigned int state[4];
	unsigned char buffer[64];

}md5_context;

/**
 *	md5_context to be initialized
 */
void md5_init(md5_context *ctx);

/**
 *	md5 process buffer   
 */
void md5_update(md5_context *ctx, const unsigned char *input, unsigned int len);

/**
 *	md5 final digest
 */
void md5_finish(md5_context *ctx, unsigned char output[16]);

/**
 *	output = md5(input buffer)
 */
void md5( const unsigned char *input, unsigned int len, unsigned char output[16]);

/**
 *	output = md5(file)
 */
int md5_file(const char *path, unsigned char output[16]);

#endif