#ifndef	_ownFunction_H_
#define	_ownFunction_H_


// #include <asn_application.h>
#include <RRCMessage.h>

#ifdef __cplusplus
extern "C" {
#endif

static int save_to_file(const void *data, size_t size, void *key);

unsigned char * Message_encode(RRCMessage_t *rect);

RRCMessage_t * addData(RRCMessage_t * mess);

void printMess(unsigned char buffer[], int size);

#ifdef __cplusplus
}
#endif

#endif