#pragma once
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>

static inline uint32_t rol(uint32_t value, int shifts)
{
    return (value << shifts) | (value >> ((sizeof(value)<<3) - shifts));
}

static inline uint32_t rol1(uint32_t value)
{
    return (value << 1) | (value >> ((sizeof(value)<<3) - 1));
}

static inline uint32_t ror(uint32_t value, int shifts)
{
    return (value >> shifts) | (value << ((sizeof(value)<<3) - shifts));
}

static inline uint32_t ror1(uint32_t value)
{
    return (value >> 1) | (value << ((sizeof(value)<<3) - 1));
}

static inline uint32_t min(uint32_t a, uint32_t b)
{
    return (a <= b) ? a : b;
}

uint64_t md5_sum(const void* buffer, size_t size)
{
    uint64_t _size = 0;
    uint32_t _h0 = 0x67452301;
    uint32_t _h1 = 0xEFCDAB89;
    uint32_t _h2 = 0x98BADCFE;
    uint32_t _h3 = 0x10325476;
    uint32_t _h4 = 0xC3D2E1F0;
    uint32_t _words[80] =
    {
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
    };
    bool _bit_pad_written = false;

    uint8_t* p = (uint8_t*)buffer;
    size_t offset = _size & 0x3f;
    size_t remain = 64 - offset;

    while(size > 0)
    {
        size_t n = min(remain, size);

        for(int j = 0; j < n; ++j)
        {
            _words[offset + j] = p[j];
        }

        _size += n;
        remain -= n;

        if(remain != 0)
        {
            break;
        }

        // process chunk

        {
            int i = 0;

#if ENDIAN == LITTLE_ENDIAN
            // PATCH FOR LITTLE ENDIAN ->

            for(i = 0; i < 16; ++i)
            {
                _words[i] = swap(_words[i]);
            }
#endif
            for(; i < 32; ++i)
            {
                _words[i] = rol1(_words[i-3] ^_words[i-8]^_words[i-14]^_words[i-16]);
            }
            for(; i < 80; ++i)
            {
                _words[i] = rol(_words[i-6] ^_words[i-16]^_words[i-28]^_words[i-32], 2);
            }

            uint32_t a = _h0;
            uint32_t b = _h1;
            uint32_t c = _h2;
            uint32_t d = _h3;
            uint32_t e = _h4;

            uint32_t f = 0, k = 0, temp = 0;

            for(i = 0; i < 20; ++i)
            {
                f = d^(b&(c^d)); // f = (b&c)|((~b)&d);
                k = 0x5a827999;

                temp = rol(a, 5) + f + e + k + _words[i];
                e = d;
                d = c;
                c = rol(b, 30);
                b = a;
                a = temp;
            }

            for(; i < 40; ++i)
            {
                f = b^c^d;
                k = 0x6ed9eba1;

                temp = rol(a, 5) + f + e + k + _words[i];
                e = d;
                d = c;
                c = rol(b, 30);
                b = a;
                a = temp;
            }

            for(; i < 60; ++i)
            {
                f = (b&c)|(d&(b|c)); // f = (b&c)|(b&d)|(c&d);
                k = 0x8f1bbcdc;

                temp = rol(a, 5) + f + e + k + _words[i];
                e = d;
                d = c;
                c = rol(b, 30);
                b = a;
                a = temp;
            }

            for(; i < 80; ++i)
            {
                f = b^c^d;
                k = 0xca62c1d6;

                temp = rol(a, 5) + f + e + k + _words[i];
                e = d;
                d = c;
                c = rol(b, 30);
                b = a;
                a = temp;
            }

            _h0 += a;
            _h1 += b;
            _h2 += c;
            _h3 += d;
            _h4 += e;
        }

        // next chunk

        p += n;
        size -= n;
        offset = 0;
        remain = 64;
    }

    // last step

    if(!_bit_pad_written)
    {
        offset = _size & 0x3f;

        uint8_t* pad = (uint8_t*)_words;
        pad[offset++] = 0x80;
        remain = 64 - offset;
        if(remain > 8)
        {
            memset(&pad[offset], 0, remain - 8);
        }
        else
        {
            memset(&pad[offset], 0, remain);
            // process chunk

            {
                int i = 0;

#if ENDIAN == LITTLE_ENDIAN
                // PATCH FOR LITTLE ENDIAN ->

                for(i = 0; i < 16; ++i)
                {
                    _words[i] = swap(_words[i]);
                }
#endif
                for(; i < 32; ++i)
                {
                    _words[i] = rol1(_words[i-3] ^_words[i-8]^_words[i-14]^_words[i-16]);
                }
                for(; i < 80; ++i)
                {
                    _words[i] = rol(_words[i-6] ^_words[i-16]^_words[i-28]^_words[i-32], 2);
                }

                uint32_t a = _h0;
                uint32_t b = _h1;
                uint32_t c = _h2;
                uint32_t d = _h3;
                uint32_t e = _h4;

                uint32_t f = 0, k = 0, temp = 0;

                for(i = 0; i < 20; ++i)
                {
                    f = d^(b&(c^d)); // f = (b&c)|((~b)&d);
                    k = 0x5a827999;

                    temp = rol(a, 5) + f + e + k + _words[i];
                    e = d;
                    d = c;
                    c = rol(b, 30);
                    b = a;
                    a = temp;
                }

                for(; i < 40; ++i)
                {
                    f = b^c^d;
                    k = 0x6ed9eba1;

                    temp = rol(a, 5) + f + e + k + _words[i];
                    e = d;
                    d = c;
                    c = rol(b, 30);
                    b = a;
                    a = temp;
                }

                for(; i < 60; ++i)
                {
                    f = (b&c)|(d&(b|c)); // f = (b&c)|(b&d)|(c&d);
                    k = 0x8f1bbcdc;

                    temp = rol(a, 5) + f + e + k + _words[i];
                    e = d;
                    d = c;
                    c = rol(b, 30);
                    b = a;
                    a = temp;
                }

                for(; i < 80; ++i)
                {
                    f = b^c^d;
                    k = 0xca62c1d6;

                    temp = rol(a, 5) + f + e + k + _words[i];
                    e = d;
                    d = c;
                    c = rol(b, 30);
                    b = a;
                    a = temp;
                }

                _h0 += a;
                _h1 += b;
                _h2 += c;
                _h3 += d;
                _h4 += e;
            }

            // next chunk
            memset(pad, 0, offset);
        }

        uint64_t* sizep = (uint64_t*)&_words[16 - 2];

#if ENDIAN == LITTLE_ENDIAN
        *sizep = swap(_size<<3);
#else
        *sizep = _size;
#endif
        // process chunk

        {
            int i = 0;

#if ENDIAN == LITTLE_ENDIAN
            // PATCH FOR LITTLE ENDIAN ->

            for(i = 0; i < 16; ++i)
            {
                _words[i] = swap(_words[i]);
            }
#endif
            for(; i < 32; ++i)
            {
                _words[i] = rol1(_words[i-3] ^_words[i-8]^_words[i-14]^_words[i-16]);
            }
            for(; i < 80; ++i)
            {
                _words[i] = rol(_words[i-6] ^_words[i-16]^_words[i-28]^_words[i-32], 2);
            }

            uint32_t a = _h0;
            uint32_t b = _h1;
            uint32_t c = _h2;
            uint32_t d = _h3;
            uint32_t e = _h4;

            uint32_t f = 0, k = 0, temp = 0;

            for(i = 0; i < 20; ++i)
            {
                f = d^(b&(c^d)); // f = (b&c)|((~b)&d);
                k = 0x5a827999;

                temp = rol(a, 5) + f + e + k + _words[i];
                e = d;
                d = c;
                c = rol(b, 30);
                b = a;
                a = temp;
            }

            for(; i < 40; ++i)
            {
                f = b^c^d;
                k = 0x6ed9eba1;

                temp = rol(a, 5) + f + e + k + _words[i];
                e = d;
                d = c;
                c = rol(b, 30);
                b = a;
                a = temp;
            }

            for(; i < 60; ++i)
            {
                f = (b&c)|(d&(b|c)); // f = (b&c)|(b&d)|(c&d);
                k = 0x8f1bbcdc;

                temp = rol(a, 5) + f + e + k + _words[i];
                e = d;
                d = c;
                c = rol(b, 30);
                b = a;
                a = temp;
            }

            for(; i < 80; ++i)
            {
                f = b^c^d;
                k = 0xca62c1d6;

                temp = rol(a, 5) + f + e + k + _words[i];
                e = d;
                d = c;
                c = rol(b, 30);
                b = a;
                a = temp;
            }

            _h0 += a;
            _h1 += b;
            _h2 += c;
            _h3 += d;
            _h4 += e;
        }

        // next chunk

        _bit_pad_written = true;
    }

#if ENDIAN == LITTLE_ENDIAN
    uint64_t hh = (((uint64_t)swap(_h1)) << 32) | swap(_h0);
#else
    uint64_t hh = (((uint64_t)_h1) << 32) | _h0;
#endif

    return hh;
}

uint64_t md5_sum_string(const char* text)
{
    return md5_sum(text, strlen(text));
}
