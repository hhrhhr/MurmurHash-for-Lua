//extern "C" {
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
//}

typedef unsigned __int64 uint64_t;

//static int hash64A(lua_State *L);
//extern "C" {
//    int __declspec(dllexport) luaopen_murmur(lua_State *L);
//}

/*  usage:
 *
 *  murmur = require("murmur")
 *  hash = murmur.hash64A( str [, sL [, sH]] )
 *
 *  str - string
 *  sL - seed low bits (32bit)
 *  sH - seed high bits
 *
 *  return two values, 'hashHigh' and 'hashLow' of full 64 bit
 */

static int hash64A(lua_State *L)
{
    unsigned int len;
    const char *key    = lua_tolstring(L, 1, &len);
    unsigned int seedL = lua_tounsignedx(L, 2, NULL);
    unsigned int seedH = lua_tounsignedx(L, 3, NULL);

    uint64_t seed = ((uint64_t)seedH << 32) | (uint64_t)seedL;

    const uint64_t m = 0xc6a4a7935bd1e995ULL;
    const int r = 47;
    
    uint64_t h = seed ^ (len * m);
    
    const uint64_t *data = (const uint64_t *)key;
    const uint64_t *end = (len >> 3) + data;
    while(data != end) {
        uint64_t k = *data++;

        k *= m; 
        k ^= k >> r; 
        k *= m; 
        
        h ^= k;
        h *= m;
    }
    
    const unsigned char *data2 = (const unsigned char *)data;
    switch(len & 7) {
    case 7: h ^= (uint64_t)(data2[6]) << 48;
    case 6: h ^= (uint64_t)(data2[5]) << 40;
    case 5: h ^= (uint64_t)(data2[4]) << 32;
    case 4: h ^= (uint64_t)(data2[3]) << 24;
    case 3: h ^= (uint64_t)(data2[2]) << 16;
    case 2: h ^= (uint64_t)(data2[1]) << 8;
    case 1: h ^= (uint64_t)(data2[0]);
          h *= m;
    };
    
    h ^= h >> r;
    h *= m;
    h ^= h >> r;

    unsigned int hashHigh = (h >> 32);
    unsigned int hashLow  = (unsigned int)h;

    lua_pushfstring(L, "%p",hashHigh);
    lua_pushfstring(L, "%p",hashLow);

    return 2;
}

static const struct luaL_Reg murmur[] = {
    {"hash64A", hash64A},
    {NULL, NULL}
};

int __declspec(dllexport) luaopen_murmur(lua_State *L)
{
  luaL_newlib(L, murmur);
  return 1;
}
