#include <stdio.h>
#include <sys/types.h>
#include <RRCMessage.h>

static int save_to_file(const void *data, size_t size, void *key) {
    FILE *fp = key;
    return (fwrite(data, 1, size, fp) == size) ? 0 : -1;
}

unsigned char * Message_encode(RRCMessage_t *rect){
    asn_enc_rval_t er;
    unsigned char buffer[1024];
    for(int i = 0; i<1024; i++){
        buffer[i] = 0;
    }

    FILE *fp = fopen("file.bin", "wb");
    if(!fp) {
        printf("Error open file\n");
        exit(1);
    }
    er = der_encode(&asn_DEF_RRCMessage, rect, save_to_file, fp);
    fclose(fp);

    if(er.encoded == -1) {
        fprintf(stderr, "Failed to encode %s\n", asn_DEF_RRCMessage.name);
        exit(1);
    } else {
        fprintf(stderr, "%s encoded in %zd bytes\n", asn_DEF_RRCMessage.name, er.encoded);
    }

    fp = fopen("file.bin", "rb");
    fread(buffer,sizeof(buffer),1,fp);
    fclose(fp);
    
    printMess(buffer, er.encoded);

    unsigned char * temp;
    temp = (unsigned char*) malloc(1024 * sizeof(unsigned char));
    for(int i=0; i<1024; i++){
        *(temp + i) = buffer[i];
    }

    return temp;
}

RRCMessage_t * addData(RRCMessage_t * mess){
    BIT_STRING_t *cont;
    cont = calloc(1, sizeof(BIT_STRING_t)); 
    uint8_t *arr;
    arr = calloc(1,sizeof(uint8_t) * 16);
    
    srand(time(NULL));
    for(int i=0; i<16; i++){
        *(arr + i) = rand() % 256;
    }
    cont->buf = arr;
    cont->size = 16;
    cont->bits_unused = 0;

    mess->data = *cont;
    return mess;
}

void printMess(unsigned char buffer[], int size){
    for(int i=0; i<size; i++){
        if (buffer[i] <16){
            printf("0%X ", buffer[i]);
        } else {
            printf("%X ", buffer[i]);
        }
    }
    printf("\n");

    return;
}