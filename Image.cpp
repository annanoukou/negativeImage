#include "Image.h"
#include "Color.h"
#include "ppm/ppm.cpp"
#include <algorithm>

namespace imaging {

	Color * Image::getRawDataPtr() {
		return buffer;
	}

	Color Image::getPixel(unsigned int x, unsigned int y) const {
		
		Color * pixel = new Color();
		if (x<=width && y<=height) 
		{
			int i = 3 * (width * y + x);// 3 cells for each pixel
			*pixel = buffer[i];
			return *pixel;
		}
		return *pixel;
	}

	void Image::setPixel(unsigned int x, unsigned int y, Color & value) {
		
		if (x<=width && y<=height) 
		{
			int i = 3 * (width * x + y);
			buffer[i] = value;
		}
	}

	void Image::setData(const Color * & data_ptr) {

		memcpy(this->buffer, data_ptr, width * height * 3);
		/*this->buffer = const_cast<Color*>(data_ptr);*/
	}

	Image::Image() : width(0), height(0), buffer(nullptr) {}

	Image::Image(unsigned int width, unsigned int height) : width(width), height(height), buffer(nullptr) {}

	Image::Image(unsigned int width, unsigned int height, const Color * data_ptr) : width(width), height(height) {
		this->buffer = const_cast<Color*>(data_ptr);
	}

	Image::Image(const Image &src) {
		width = src.width;
		height = src.height;
		buffer = src.buffer;
		Image(width, height, buffer);
	}

	Image::~Image() {
		delete[] buffer;
	}

	Image & Image::operator = (const Image & right) {
		if (buffer != nullptr) delete[] buffer;
		width = right.width;
		height = right.height;
		buffer = right.buffer;
		return *(this);
	}


	bool Image::load(const string & filename, const string & format) {

		if (format.compare("ppm") == 0) 
		{
			unsigned int * w = &width;
			unsigned int * h = &height;
			
			const char * file_to_pass = filename.c_str(); //From string to const char *
			float * arr = ReadPPM(file_to_pass, (int*)w, (int*)h); //ReadPPM

			int size = width * height;
			buffer = new Color[size];

			for (int i = 0; i < size; i++) {
				buffer[i].r = arr[3*i];
				buffer[i].g = arr[3*i + 1];
				buffer[i].b = arr[3*i + 2];
			}

			/*
			Color * newArr = new Color[size];
			buffer = new Color[size];
			for (int i = 0; i < size; i++) {
				Color * newBuff = new Color(arr[3 * i], arr[3 * i + 1], arr[3 * i + 2]);
				buffer[i] = *newBuff;
			}
			this->buffer = newArr;
			*/

			return true;
		}
		return false;
	}

	bool Image::save(const std::string & filename, const std::string & format) {
		
		if (format.compare("ppm") == 0)
		{
			float * arr_last = new float[width * height * 3];
			for (unsigned int i = 0; i < width*height; i++)
			{
				arr_last[3*i] = buffer[i].r;
				arr_last[3*i+1] = buffer[i].g;
				arr_last[3*i+2] = buffer[i].b;
			}
			return WritePPM(arr_last, width, height, filename.c_str());
		}
		return false;
	}
}




