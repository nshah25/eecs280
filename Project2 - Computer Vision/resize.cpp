#include <fstream>
#include <string>
#include "processing.h"
using namespace std;

int main(int argc, char *argv[])
{
string ifile = argv[1];
string ofile = argv[2];

int targetwidth = atoi(argv[3]);
int targetheight = 0;

ifstream fin;
fin.open(ifile);
ofstream fout;
fout.open(ofile);
Image *img = new Image;
Image_init(img, fin);

string message  = "Usage: resize.exe IN_FILENAME OUT_FILENAME WIDTH [HEIGHT]\n"
"WIDTH and HEIGHT must be less than or equal to original";

if (argc == 4)
{
    targetheight = Image_height(img);
}

if (argc == 5)
{
    targetheight = atoi(argv[4]);
}

if (argc !=4 && argc != 5)
{
cout << message << endl;
delete img;
return -2;
}

if(!(targetwidth > 0 && targetwidth <= Image_width(img)))
{
cout << message << endl;
delete img;
return -2;

}
if (!(targetheight > 0 && targetheight <= Image_height(img))){
cout << message << endl;
delete img;
return -2;
}
if (!fin.is_open()){
cout << message << endl;
delete img;
return -2;
}
if (!fout.is_open())
{
cout << message << endl;
delete img;
return -2;
}
seam_carve(img, targetwidth, targetheight);
Image_print(img, fout);
delete img;
}