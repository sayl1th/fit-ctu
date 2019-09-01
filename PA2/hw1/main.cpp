#ifndef __PROGTEST__
#include <cstdio>
#include <cstdlib>
#include <cstdint>
#include <cstring>
#include <cassert>
#include <cmath>
#include <cctype>
#include <climits>
#include <istream>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <list>
#include <algorithm>
#include <functional>
#include <memory>
using namespace std;

const uint16_t ENDIAN_LITTLE = 0x4949;
const uint16_t ENDIAN_BIG    = 0x4d4d;

#endif /* __PROGTEST__ */

class Image {
private:
    ifstream inFile;
    ofstream outFile;
    uint16_t endian;
    uint16_t width;
    uint16_t height;
    uint16_t format;
    uint16_t widthOrig;
    uint16_t heightOrig;
    uint16_t formatOrig;
    int bitsPerChannel;
    int channels;
    vector<vector<vector<uint16_t> > >data;
    bool vertical;
    bool horizontal;

    bool readHeader();
    bool writeHeader();
    bool write();
    bool read();
    void flip();


public:
    Image(const char  *srcFileName,const char *dstFileName,bool flipHorizontal, bool flipVertical);
    ~Image();
    bool processImage();    

};

Image::Image(const char  *srcFileName,const char *dstFileName,bool flipHorizontal, bool flipVertical)
{
    inFile.open(srcFileName, std::ios::binary | std::ios::in);
    outFile.open(dstFileName, std::ios::binary | std::ios::out);

    vertical = flipVertical;
    horizontal = flipHorizontal;

}

Image::~Image()
{
    inFile.close();
    outFile.close();
}

bool Image::processImage()
{

    if (!inFile.is_open() || !outFile.is_open()) {
        return false;
    }

    if (!readHeader())
      return false;

    data.resize(height,vector<vector<uint16_t> >(width, vector<uint16_t> (channels)));

    if (!read())
      return false;

    flip();

    if (!writeHeader())
      return false;

    if (!write())
      return false;

    return true;

}


void Image::flip() 
{
  if (horizontal) {
    for (int x = 0; x < height; x++) {
      for (int y = 0; y < width/2; y++) {
        for (int z = 0; z < channels; z ++) {
        uint16_t tmp = data[x][y][z];
        data[x][y][z] = data[x][width- 1 - y][z];
        data[x][width - 1 - y][z] = tmp;
      }
      }
    }
  }

  if (vertical) {
     for (int x = 0; x < height / 2; x++) {
      for (int y = 0; y < width; y++) {
        for (int z = 0; z < channels; z ++) {
        uint16_t tmp = data[x][y][z];
        data[x][y][z] = data[height - 1 - x][y][z];
        data[height -1 - x][y][z] = tmp;
      }
      }
    }
  }

  if (!vertical && !horizontal)
    return;

}

bool Image::readHeader()
{
    if (!inFile)
      return false;

    inFile.read(reinterpret_cast<char *> (&endian), 2);

    if (inFile.fail())
      return false;


    if (endian != ENDIAN_BIG && endian != ENDIAN_LITTLE)
      return false;
    
    inFile.read(reinterpret_cast<char *> (&width), 2);
    
    if (inFile.fail())
      return false;

    inFile.read(reinterpret_cast<char *> (&height), 2);

    if (inFile.fail() || height == 0 || width == 0)
      return false;

    inFile.read(reinterpret_cast<char *> (&format), 2);

    if (inFile.fail())
      return false;

    widthOrig = width;
    heightOrig= height;
    formatOrig = format;


    if (endian == ENDIAN_BIG) {
        width = (uint16_t) ((((width & 0xFF00) >> 8) + ((width & 0x00FF) << 8)));
        height = (uint16_t) ((((height & 0xFF00) >> 8) + ((height & 0x00FF) << 8)));
        format = (uint16_t) ((((format & 0xFF00) >> 8) + ((format & 0x00FF) << 8)));
    }



    channels = format & 0x3;
    ++channels;

    if (channels == 2)
      return false;


    bitsPerChannel = (format >> 2) & 0x7;



    switch (bitsPerChannel) {
      case 0:
          bitsPerChannel = 1;
          break;
      case 3:
          bitsPerChannel = 8;
          break;
      case 4:
          bitsPerChannel = 16;
          break;
      default:
          return false;
    }

    if ((format & 0xFF00) != 0) 
    {
        return false;
    }

    return true; 

}

bool Image::read() 
{
    if (!inFile) {
        return false;
    }

    uint16_t tmp;

    for (int x = 0; x < height ; x++) {
      for (int y = 0; y < width; y++ ) { 
        for (int z = 0; z < channels; z++) {

            inFile.read(reinterpret_cast<char *> (&tmp), ((bitsPerChannel / 8)));

           

            if (inFile.fail()) {
              return false;
            }

            data[x][y][z] = (uint16_t) tmp ;
          }

      }
    }

    inFile.get();
    return inFile.eof();
}

bool Image::writeHeader() 
{
    if (!outFile)
      return false;


    outFile.write(reinterpret_cast<char *> (&endian), 2);

    if (outFile.fail())
      return false;

    outFile.write(reinterpret_cast<char *> (&widthOrig), 2);

    if (outFile.fail())
      return false;

    outFile.write(reinterpret_cast<char *> (&heightOrig), 2);

    if (outFile.fail())
      return false;

    outFile.write(reinterpret_cast<char *> (&formatOrig), 2);

    return !outFile.fail();
}

bool Image::write() 
{
    if (!outFile) {
        return false;
    }

    for (int x = 0; x < height ; x++) {
        for (int y = 0; y < width; y++ ) {
          for (int z = 0; z < channels; z++) {


            uint16_t tmp =  data[x][y][z];
          
            outFile.write(reinterpret_cast<char *> (&tmp), ((bitsPerChannel / 8)));

            if (outFile.fail())
              return false;
          }
        }
    }

    return true;
}

bool flipImage ( const char  * srcFileName,
                 const char  * dstFileName,
                 bool          flipHorizontal,
                 bool          flipVertical )
{
    Image image(srcFileName, dstFileName, flipHorizontal, flipVertical);

    return image.processImage();
}


bool identicalFiles ( const char * fileName1,
                      const char * fileName2 )
{
    ifstream file1;
    file1.open(fileName1, std::ios::binary | std::ios::in);

    ifstream file2;
    file2.open(fileName2, std::ios::binary | std::ios::in);

    if (!file1 || !file2) {
        return false;
    }

    if (file1.is_open() && file2.is_open()) {
        char b1;
        char b2;

        while (true) {
            file1.get(b1);
            file2.get(b2);

            if (file1.eof() && file2.eof() && b1 == b2) {
                file1.close();
                file2.close();
                return true;
            } else if (file1.eof() || file2.eof()) {
                file1.close();
                file2.close();
                return false;
            }
        }

    }

    file1.close();
    file2.close();
    
    return false;
}

int main ( void )
{
}

