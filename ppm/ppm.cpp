#include <iostream>
#include <fstream>
#include <string>
#include "ppm.h"
#include "../Color.h"
#include "../Image.h"

using namespace std;

namespace imaging 
{
	float * ReadPPM(const char * filename, int *  w, int *  h) {

		ifstream ifs;
		float * float_buff;
		try {

			ifs.open(filename, ios::binary | ios::in);
			if (!ifs.is_open()) {
				cerr << "Cannot open file";
				return nullptr;
			}
			string header;
			ifs >> header;
			if (strcmp(header.c_str(), "P6") != 0) {
				cerr << "Wrong Format";
				return nullptr;
			}

			int width, height, b;
			ifs >> width >> height >> b;
			if (width < 0 || height < 0) {
				cerr << "Illegal dimensions";
				return nullptr;
			}
			*w = width;
			*h = height;

			ifs.ignore(256, '\n'); // skip empty lines in necessary until we get to the binary data 

			//Pinakes
			const int size = 3 * width * height;
			unsigned  char * rgb = new unsigned char[size]; //Assign memory during runtime using any variable value as size
			ifs.read((char*)rgb, size); // converted unsigned char to char for compability
			float_buff = new float[size]; //Pinakas float mas

			for (int i = 0; i < size; i++) {
				float_buff[i] = (unsigned char)rgb[i] / 255.f;
			}

			delete[] rgb;
			ifs.close();
		}
		catch (exception e) {
			cout << "An error occured" << endl;
			ifs.close();
			return nullptr;
		}

		return float_buff;
	}


	bool WritePPM(const float * data, int w, int h, const char * filename) {
		
		ofstream ofs;

		try {
			ofs.open(filename, ios::binary | ios::out);
			if (!ofs.is_open()) {
				cerr << "Could not open the file" << endl;
				return false;
			}

			string type = "P6";
			unsigned short width = w;
			unsigned short height = h;
			unsigned short max_pixels = 255;
			ofs << type << endl << width << endl << height << endl << max_pixels << endl;

			int size = w * h * 3;
			unsigned char * rgb = new unsigned char[size];

			for (int i = 0; i < size; i++) {
				rgb[i] = (unsigned char)(data[i] * 255.0f);
			}
			ofs.write((char*)rgb, size);

			ofs.flush();
			ofs.close();
			delete[] rgb;
			return true;
		}
		catch (exception e) {
			cerr << "Something went wrong while Writing PPM" << endl;
			return false;
		}
	}

}
