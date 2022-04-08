#include <stdio.h>
#include <assert.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"


// gcc main.c -lm


// Greyscale-Image definition
typedef struct {
	int w;        // 4
	int h;        // 4
	uint8_t *data; // 8?
} Image;

void img_dump(FILE *stream, Image const *image) {
	fprintf(stream, "Image Intesity Values:\n");
	int size = image->h*image->w;
	for (int row=0; row < image->h; ++row) {
		for (int col=0; col < image->w; ++col) {
			fprintf(stream, "%d", image->data[row*image->w+col]);
			if (row*col < size-1) {
				fprintf(stream, ", ");
			}
		}
		fprintf(stream, "\n");
	}
}

void convert_to_greyscale(uint8_t *old_data, int w, int h, int channels, uint8_t *data) {
	if (channels == 1) {
		memcpy(data, old_data, (w*h) * sizeof(uint8_t));
	} else {
		
		// https://www.dynamsoft.com/blog/insights/image-processing/image-processing-101-color-space-conversion/
		for (int i=0; i<w*h; i+=channels) {
			uint8_t r = floor(old_data[i+0] * 0.299f);
			uint8_t g = floor(old_data[i+1] * 0.587f);
			uint8_t b = floor(old_data[i+2] * 0.114f);

			memset(&data[i], r+g+b, 1 * sizeof(uint8_t));
		}
	}
}

Image img_load_jpg(FILE *stream, const char *filename) {
	int w,h, channels;
	uint8_t *old_data = stbi_load(filename, &w, &h, &channels, 1);
	fprintf(stream, "Loaded image: '%s' %dx%d - %d channels\n", filename, h, w, channels);

	uint8_t *data = (uint8_t*) malloc(w*h*sizeof(uint8_t));
	convert_to_greyscale(old_data, w, h, channels, data);

	Image image = {
		.data = data,
		.w = w,
		.h = h
	};

	return image;
}

void img_save_jpg(FILE *stream, const char *filename, Image const *image) {
	int size = image->w * image->h;
	uint8_t *new_data = (uint8_t*) malloc(size * sizeof(uint8_t));
	for (int i=0; i<size; i++) {
		new_data[i] = image->data[i];
	}

	stbi_write_jpg(filename, image->w, image->h, 1, new_data, 100);
	fprintf(stream, "Successfully saved image to: '%s'\n", filename);
}

void img_free(Image *image) {
	free(image->data);
	image->w = 0; image->h = 0;
}

// Histogram definition
typedef struct {
	int values[256];
} Histogram;

Histogram hist_build(Image const *image) {
	Histogram h = {0};
	for (int i=0; i<image->w*image->h; ++i) {
		h.values[image->data[i]] += 1;
	}
	return h;
}

void hist_dump(FILE *stream, Histogram const *histogram) {
	fprintf(stream, "Histogram:\n");
	for (int intensity=0; intensity<256; ++intensity) {
		fprintf(stream, "%3d->%zu\n", intensity, histogram->values[intensity]);
	}
}

int main() {
	int w, h, channels;
	//	const char *filename = "original.jpg";
	const char *filename = "../imgs/1_small.jpg";
	Image image = img_load_jpg(stdout, filename);
	// img_dump(stdout, &image);

	Histogram histogram = hist_build(&image);
	hist_dump(stdout, &histogram);

	//  const char *output_filename = "output.jpg";
	//  img_save_jpg(stdout, output_filename, &image);

	img_free(&image);
	return 0;
}
