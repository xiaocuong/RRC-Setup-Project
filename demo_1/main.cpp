#include "UE.h"
#include "eNB.h"
#include "baseDevice.h"

using namespace std;

int main(){
    pthread_t thread1, thread2;

    UE myUE;
    eNB myeNB;
    baseDevice *p;
    
    // UE* p2 = &myUE;
    p = &myUE;
    pthread_create(&thread2, NULL, tRcConnectionEstablish, p);

    // eNB* p1 = &myeNB;
    p = &myeNB;
    pthread_create(&thread1, NULL, tListenSignal, p);

    pthread_exit(NULL);
}