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
unsigned short getCpuHash()
{
	return 0;
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
	return 0;
}
