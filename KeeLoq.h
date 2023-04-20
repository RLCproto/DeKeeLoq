#include <stdint.h>
union __attribute__((packed)) encrypted_typedef
{
    struct __attribute__((packed))
    {
        unsigned int counter:16;
        unsigned int discriminationBits:12;
        unsigned int button:4;
    };
    unsigned int encrypted:32;
};

uint32_t KeeLoq_Encrypt(const uint32_t data, const uint64_t key);
uint32_t KeeLoq_Decrypt(const uint32_t data, const uint64_t key);
