//#define GODOHK			//defines God/OHK support
//#define OFFTHERECORD	//defines Off-The-Record Edition
//#define PUBLIC			//defines Public Edition
//#undef PUBLIC			//defines Private Edition

#ifdef OFFTHERECORD		//ensures Public Edition takes higher prescedience than Off-The-Record Edition
#ifdef PUBLIC
#undef OFFTHERECORD
#endif
#endif

#ifndef PUBLIC			//esnures God/OHK always available in Private Editions
#ifndef GODOHK
#define GODOHK
#endif
#endif

#define USE_CLIENTCMD	5

#define NOP __asm _emit 0x90
//#define NOP __asm {NOP}
//#define NOP
