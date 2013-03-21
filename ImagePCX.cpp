/////////////////////////////////////////////////////////////////////////////
//
// Copyright(c) Darkseb
//
// This code is licenced under the MIT license.
//
// Implementation of ImagePCX loader class for PCX Image format
//
// Use a bit of David Henry's tutorial code on how to write a MD2 loader
//
/////////////////////////////////////////////////////////////////////////////

#include "ImagePCX.h"

ImagePCX::~ImagePCX()
{
    delete [] _pixels;
    _pixels = NULL;
    delete [] _data;
    _data = NULL;
}

ImagePCX::ImagePCX(const std::string &filename)
    : _header(NULL), _width(0), _height(0), _numMipmaps(0), _format(0), _components(0),
    _pixels(NULL),  _filename(filename), _data(NULL), _length(0), _standardCoordSystem(true)
{
    std::ifstream ifs(filename.c_str(), std::ios::in | std::ios::binary);
    if(ifs.fail())
    {
        std::cerr << "\nCouldn't open PCX file" << filename;
    }
    ifs.seekg(0, std::ios::end);
    _length = ifs.tellg();
    ifs.seekg(0, std::ios::beg);
    try
    {
        // Allocate memory for holding file data
        _data = new GLubyte[_length];
        // Read whole file data
        ifs.read(reinterpret_cast<char *>(_data), _length);
        ifs.close();
    }
    catch(...)
    {
        delete [] _data;
        std::cerr << "\nCannot allocate PCX data memory";
    }

    const GLubyte *data_ptr;
    try
    {
        _name = _filename;
        _standardCoordSystem = true;
        // Get pointer on file data
        data_ptr = _data;
        // Read PCX header
        _header = reinterpret_cast<const PCX_Header *>(data_ptr);
        data_ptr += sizeof(PCX_Header);
        // Check if is valid PCX file
        if(_header->manufacturer != 0x0a)
        {
            std::cerr << "\nBad PCX version number "<< _name;
        }
        _width = _header->xmax - _header->xmin + 1;
        _height = _header->ymax - _header->ymin + 1;
        _format = GL_RGB;
        _components = 3;
        _pixels = new GLubyte[_width * _height * _components];
        //readPCX24bits
        GLubyte *ptr;
        int rle_count = 0, rle_value = 0;
        for (int y = 0; y < _height; ++y)
        {
            // For each color plane
            for (int c = 0; c < 3; ++c)
            {
                ptr = &_pixels[(_height - (y + 1)) * _width * 3];
                int bytes = _header->bytesPerScanLine;

                // Decode line number y
                while (bytes--)
                {
                    if (rle_count == 0)
                    {
                        if( (rle_value = *(data_ptr++)) < 0xc0)
                        {
                            rle_count = 1;
                        }
                        else
                        {
                            rle_count = rle_value - 0xc0;
                            rle_value = *(data_ptr++);
                        }
                    }

                    rle_count--;
                    ptr[c] = static_cast<GLubyte>(rle_value);
                    ptr += 3;
                }
            }
        }
    }
    catch(...)
    {
        delete [] _pixels;
        std::cerr << "\nCannot allocate PCX pixels memory";
    }
}
