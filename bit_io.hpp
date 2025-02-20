#ifndef BIT_IO_HPP
#define BIT_IO_HPP

#include <fstream>

class BitWriter
{
private:
    std::ofstream &output;
    char buffer;
    int bitCount;

public:
    BitWriter(std::ofstream &os);
    void writeBit(int bit);
    void writeByte(char c);
    void flush();
};

class BitReader
{
private:
    std::ifstream &input;
    char buffer;
    int bitCount;

public:
    BitReader(std::ifstream &is);
    int readBit();
    char readByte();
};

#endif
