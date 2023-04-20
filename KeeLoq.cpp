#include "KeeLoq.h"
#include <QObject>

#define KeeLoq_NLF		0x3A5C742E
#define bit(x,n)		(((x)>>(n))&1)
#define g5(x,a,b,c,d,e)	(bit(x,a)+bit(x,b)*2+bit(x,c)*4+bit(x,d)*8+bit(x,e)*16)

uint32_t KeeLoq_Encrypt(const uint32_t data, const uint64_t key)
{
    unsigned int x = data, r;

    for (r = 0; r < 528; r++)
    {
        x = (x>>1)^((bit(x,0)^bit(x,16)^(unsigned int)bit(key,r&63)^bit(KeeLoq_NLF,g5(x,1,9,20,26,31)))<<31);
    }
    return x;
}

uint32_t KeeLoq_Decrypt(const uint32_t data, const uint64_t key)
{
    unsigned int	x = data, r;

    for (r = 0; r < 528; r++)
    {
        x = (x<<1)^bit(x,31)^bit(x,15)^(unsigned int)bit(key,(15-r)&63)^bit(KeeLoq_NLF,g5(x,0,8,19,25,30));
    }
    return x;
}
