#pragma once

#include <fstream>

struct Bitmap
{
	struct Pixel
	{
		Pixel(int ir, int ig, int ib)
		{
			r = uint8_t(ir);
			g = uint8_t(ig);
			b = uint8_t(ib);
		}

		union {
			struct {
				uint8_t r, g, b;
			};
			uint8_t rgb[3];
		};
	};

	// http://tfc.duke.free.fr/coding/tga_specs.pdf
	// L'entete TGA a une taille attendue de 18 octets
	// Cependant, le compilateur aligne automatiquement certaines variables a l'adresse relative
	// multiple de l'alignement des structures (generalement 4 octets ou 8 octets avec des pointeurs 64 bits)
	// Le compilateur doit donc introduire du bourrage (padding) afin garantir cet alignement.
	// Dans notre cas notre structure aurait une taille memoire de 20 ou 24 octets, 
	// ce qui fausse la lecture de l'entete par un logiciel de visualisation d'image.
	// Il est cependant possible de forcer un alignement specifique a l'aide de directive du compilateur comme ici
#pragma pack(push, 1)
	struct TGAHeader
	{
		uint8_t  identsize;          // size of ID field that follows 18 byte header (0 usually)
		uint8_t  colourmaptype;      // type of colour map 0=none, 1=has palette
		uint8_t  imagetype;          // type of image 0=none,1=indexed,2=rgb,3=grey,+8=rle packed
									 // padding !
		uint16_t colourmapstart;     // first colour map entry in palette
		uint16_t colourmaplength;    // number of colours in palette
		uint8_t  colourmapbits;      // number of bits per palette entry 15,16,24,32
									 // padding !
		uint16_t xstart;             // image x origin
		uint16_t ystart;             // image y origin
		uint16_t width;              // image width in pixels
		uint16_t height;             // image height in pixels
		uint8_t  bits;               // image bits per pixel 8,16,24,32
		uint8_t  descriptor;         // image descriptor bits (vh flip bits)
	};
#pragma pack(pop)

	std::ofstream m_File;
	uint32_t m_Width;
	uint32_t m_Height;
	uint8_t* m_Data;

	Bitmap() = delete;
	Bitmap(const int width, const int height);
	~Bitmap();
	// cf. regle des 3 en C++ et regle des 5 en C++11
	// https://cpppatterns.com/patterns/rule-of-five.html
	Bitmap(const Bitmap&) = delete;
	Bitmap& operator=(const Bitmap&) const = delete;
	Bitmap(Bitmap&&) = delete;
	Bitmap& operator=(Bitmap&&) = delete;

	void SetPixel(int x, int y, Pixel p);

	void WriteToDisk();

	void SetHeader();
	void OutputColor(const int ir, const int ig, const int ib);
};
