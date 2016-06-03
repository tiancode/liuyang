#include "linux_fingerprint.h"

#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <assert.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <netinet/in_systm.h>
#include <netinet/ip.h>
#include <netinet/ip_icmp.h>
 
#include <sys/types.h>
#include <sys/ioctl.h>
#include <sys/resource.h>
#include <sys/utsname.h>

void getMacHash( unsigned short* mac1, unsigned short* mac2 )
{}

unsigned short getVolumeHash()
{
	
	return 0;
}

 static void getCpuid( unsigned int* p, unsigned int ax )
 {
 	__asm __volatile
	(   "movl %%ebx, %%esi\n\t"
	    "cpuid\n\t"
            "xchgl %%ebx, %%esi"
            : "=a" (p[0]), "=S" (p[1]),
              "=c" (p[2]), "=d" (p[3])
            : "0" (ax)
        );
 }
unsigned short getCpuHash()
{
	unsigned int cpuinfo[4] = { 0, 0, 0, 0 };
	getCpuid( cpuinfo, 0 );
	unsigned short hash = 0;
	unsigned int* ptr = (&cpuinfo[0]);
	for ( int i = 0; i < 4; i++ )
		hash += (ptr[i] & 0xFFFF) + ( ptr[i] >> 16 ); 
	return hash;
}

const char* getMachineName()
{
	static struct utsname u;
 
	if ( uname( &u ) < 0 )
	{
		assert(0);
		return "unknown";
	}
 
	return u.nodename;
}

int main(int argc, char* argv[])
{
	printf("%s\n", getMachineName());
	printf("%d\n", getCpuHash());
	return 0;
}
