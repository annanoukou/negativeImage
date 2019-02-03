#include "Image.h"
#include "Color.h"
#include "ppm/ppm.h"
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

using namespace std;
using namespace imaging;

int main(int argc, char * argv[]) {

	string filename;
	string filename_neg;
	string format;

	if (argc > 2) {
		cerr << "Not correct input ";
		return -1;
	}
	else if (argc == 1) {
		cout << "Enter the name of file you want to produce the negative of: " << endl;
		cin >> filename;
	}
	else {
		filename = argv[1];
	}

	transform(filename.begin(), filename.end(), filename.begin(), tolower); //Transform FILENAME to lowercase

	filename_neg = filename.substr(0, filename.size() - 4) + "_neg.ppm";
	format = filename.substr(filename.find_last_of(".") + 1);

	transform(format.begin(), format.end(), format.begin(), tolower); //Transform FORMAT to lowercase

	cout << " " << endl;
	cout << "Format ...  " << format << endl;
	cout << "Read  File: " << filename << endl;
	cout << "Write File: " << filename_neg << endl;
	cout << " " << endl;

	if (format.compare("ppm") == 0) 
	{
		Image * neg_Image = new Image();
		
		if (neg_Image->load(filename, format))
		{
			cout << "The image was successfully loaded " << endl;
			
			unsigned int width = neg_Image->getWidth();
			unsigned int height = neg_Image->getHeight();
			int size = width * height;

			//Negative
			Color * total = neg_Image->getRawDataPtr();
			Color black(1, 1, 1);
			for (int i = 0; i < size; i++)
			{
				total[i] = black - total[i];
			}
			
			
			/*Color ttn(1, 1, 1);
			for (int i = 0; i < width; i++) {
				for (int j = 0; j < height; j++) {
					ttn = 1 - neg_Image->getPixel(i, j);
					neg_Image->setPixel(i, j, ttn);
				}
			}
			buffer = new Color[size];
			this->buffer = newBuffer;*/
			

			neg_Image->save(filename_neg, format);
			cout << "The neg image has been created!" << endl;
			cout << "The image is: " << width << " x " << height << " pixels." << endl;

		}else{
			cout << "The image was not loaded succesfuly" << endl;
		}

	}else{
		cerr << "Something is not working" << endl;
		return 1;
	}

	system("pause");
	return 0;
}
