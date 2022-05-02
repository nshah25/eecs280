// Project UID af1f95f547e44c8ea88730dfb185559d
#include "Matrix.h"
#include "Image_test_helpers.h"
#include "unit_test_framework.h"
#include <iostream>
#include <string>
#include <sstream>
#include <cassert>
using namespace std;
// Here's a free test for you! Model yours after this one.
// Test functions have no interface and thus no RMEs, but
// add a comment like the one here to say what it is testing.
// -----
// Sets various pixels in a 2x2 Image and checks
// that Image_print produces the correct output.
TEST(test_print_basic) {
	Image* img = new Image; // create an Image in dynamic memory
	const Pixel red = { 255, 0, 0 };
	const Pixel green = { 0, 255, 0 };
	const Pixel blue = { 0, 0, 255 };
	const Pixel white = { 255, 255, 255 };
	Image_init(img, 2, 2);
	Image_set_pixel(img, 0, 0, red);
	Image_set_pixel(img, 0, 1, green);
	Image_set_pixel(img, 1, 0, blue);
	Image_set_pixel(img, 1, 1, white);
	// Capture our output
	ostringstream s;
	Image_print(img, s);
	// Correct output
	ostringstream correct;
	correct << "P3\n2 2\n255\n";
	correct << "255 0 0 0 255 0 \n";
	correct << "0 0 255 255 255 255 \n";
	ASSERT_EQUAL(s.str(), correct.str());

	delete img; // delete the Image
}
TEST(test_image_init1) {
	Image* img = new Image;
	Image_init(img, 5, 6);
	ASSERT_EQUAL(Image_width(img), 5);
	ASSERT_EQUAL(Image_height(img), 6);
	delete img;
}

TEST(test_image_init2)
{
Image *img = new Image;
string input = "P3 2 2\n255 255 0 0\n0\n255 0 \n0 0 255 255 255 \n";
std::istringstream rgb_input(input);
Image_init(img, rgb_input);
ASSERT_EQUAL(Image_height(img), 2);
ASSERT_EQUAL(Image_width(img), 2);
delete img;
}

TEST(test_image_width) {
	Image* img = new Image;
	Image_init(img, 5, 6);
	ASSERT_EQUAL(Image_width(img), 5);
	delete img;
}
TEST(test_image_height) {
	Image* img = new Image;
	Image_init(img, 5, 6);
	ASSERT_EQUAL(Image_height(img), 6);
	delete img;
}
TEST(test_get_set_pixel) {
	Image* img = new Image;
	Image_init(img, 3, 4);
	const Pixel r = { 255, 0, 0 };
	const Pixel g = { 0, 255, 0 };
	const Pixel b = { 0, 0, 255 };
	const Pixel white = { 255, 255, 255 };
	Image_fill(img, white);
	Image_set_pixel(img, 1, 1, r);
	Image_set_pixel(img, 2, 2, g);
	Image_set_pixel(img, 0, 0, b);
	Pixel_equal(Image_get_pixel(img, 1, 1), r);
	Pixel_equal(Image_get_pixel(img, 2, 2), g);
	Pixel_equal(Image_get_pixel(img, 0, 0), b);
	Pixel_equal(Image_get_pixel(img, 1, 2), white);
	delete img;
}
TEST(test_image_fill) {
	Image* img = new Image;
	Image_init(img, 5, 6);
	const Pixel blue = { 255, 0, 0 };
	Image_fill(img, blue);
	for (int row = 0; row < Image_height(img); ++row) {
		for (int column = 0; column < Image_width(img); ++column) {
			Pixel_equal(Image_get_pixel(img, row, column), blue);
		}
	}
	delete img;
}

TEST_MAIN() // Do NOT put a semicolon here