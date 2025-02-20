#include "bit_io.hpp"

BitWriter::BitWriter(std::ofstream &os) : output(os), buffer(0), bitCount(0) {}

void BitWriter::writeBit(int bit)
{
    buffer = (buffer << 1) | (bit & 1);
    bitCount++;
    if (bitCount == 8)
    {
        output.put(buffer);
        buffer = 0;
        bitCount = 0;
    }
}

void BitWriter::writeByte(char c)
{
    for (int i = 7; i >= 0; i--)
    {
        writeBit((c >> i) & 1);
    }
}

void BitWriter::flush()
{
    while (bitCount != 0)
    {
        writeBit(0);
    }
}

BitReader::BitReader(std::ifstream &is) : input(is), buffer(0), bitCount(0) {}

int BitReader::readBit()
{
    if (bitCount == 0)
    {
        if (!input.get(buffer))
            return -1;
        bitCount = 8;
    }
    int bit = (buffer >> (bitCount - 1)) & 1;
    bitCount--;
    return bit;
}

char BitReader::readByte()
{
    char c = 0;
    for (int i = 0; i < 8; i++)
    {
        int bit = readBit();
        if (bit == -1)
            break;
        c = (c << 1) | bit;
    }
    return c;
}
