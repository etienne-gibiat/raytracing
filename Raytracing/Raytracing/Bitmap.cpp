#include "Bitmap.hpp"

Bitmap::Bitmap(const int width, const int height) : m_Width(width), m_Height(height), m_Data(nullptr)
{
	// 24 bits
	m_Data = new uint8_t[m_Width * m_Height * 3];
}

Bitmap::~Bitmap()
{
	delete[] m_Data;
}

void Bitmap::SetPixel(int x, int y, Pixel p)
{
	const int stride = m_Width * 3;
	uint8_t& rawPixel = m_Data[y*stride + x * 3];
	reinterpret_cast<Pixel &>(rawPixel) = p;
}

void Bitmap::WriteToDisk()
{
	m_File.open("rendu.tga", std::ios::binary);

	SetHeader();
	//m_File.write((const char *)m_Data, m_Width * m_Height * 3);
	// format BGR en sortie, il est necessaire d'ecrire octet par octet
	Pixel* pixel = reinterpret_cast<Pixel *>(m_Data);
	for (int j = 0; j < m_Height; j++) {
		for (int i = 0; i < m_Width; i++) {
			m_File.write((char *)&pixel->b, sizeof(uint8_t));
			m_File.write((char *)&pixel->g, sizeof(uint8_t));
			m_File.write((char *)&pixel->r, sizeof(uint8_t));
			pixel++;
		}
	}

	m_File.close();
}

void Bitmap::SetHeader()
{
	// entête fichier PPM
	//file << "P3\n" << width << " " << height << "\n255\n";
	// entête fichier TGA
	TGAHeader header;
	memset(&header, 0, sizeof(TGAHeader));
	header.imagetype = 2;			// indique couleurs en RGB
	header.bits = 24;
	header.width = m_Width;
	header.height = m_Height;
	header.descriptor = 1 << 5;		// bit 5 => origine coin haut-gauche (flip Y)
	m_File.write((const char*)&header, sizeof(TGAHeader));
}

void Bitmap::OutputColor(const int ir, const int ig, const int ib)
{
	// stockage TGA (attention le TGA stocke les données en BGR)
	// notez que je converti les entiers implicitement en un seul octet (via un cast en char)
	// cela fonctionne tel quel car le CPU est little-endian (architecture x86/x86-64)
	// cad que l'octet de poids faible est stockée en premier en mémoire
	m_File.write((const char*)&ib, sizeof(uint8_t));
	m_File.write((const char*)&ig, sizeof(uint8_t));
	m_File.write((const char*)&ir, sizeof(uint8_t));
}
