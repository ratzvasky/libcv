/*
    Computer Vision coursework
    Licentiate degree in Computer Systems Engineering 2016/2017
    Ivo Gomes - a10700@alunos.ipca.pt, Rúben Guimarães - a11156@alunos.ipca.pt
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <math.h>
#include <malloc.h>
#include <opencv\cv.h>
#include <opencv\cxcore.h>
#include <opencv\highgui.h>
#include "libcv.h"

#pragma region Inversions

int vc_gray_negative(IVC *image)
{
	int position = 0;
	int i, j;

	if ((image->width <= 0) || (image->height <= 0) || (image->data == NULL))
		return 0;
	if (image->channels != 1)
		return 0;

	for (i = 0; i < image->width; i++)
	{
		for (j = 0; j < image->height; j++)
		{
			position = (j * image->bytesperline) + (i * image->channels);
			image->data[position] = (unsigned char)255 - (unsigned char)image->data[position];
		}
	}

	return 1;
}

int vc_rgb_negative(IVC *image)
{
	int position = 0;
	int i, j;

	if ((image->width <= 0) || (image->height <= 0) || (image->data == NULL))
		return 0;
	if (image->channels != 3)
		return 0;

	for (i = 0; i < image->width; i++)
	{
		for (j = 0; j < image->height; j++)
		{
			position = (j * image->bytesperline) + (i * image->channels);

			image->data[position] = (unsigned char)255 - (unsigned char)image->data[position];
			image->data[position + 1] = (unsigned char)255 - (unsigned char)image->data[position + 1];
			image->data[position + 2] = (unsigned char)255 - (unsigned char)image->data[position + 2];
		}
	}

	return 1;
}

#pragma endregion

#pragma region Extractions

int vc_rgb_bgr_max(unsigned char red, unsigned char green, unsigned char blue)
{
	if ((red >= green) && (red >= blue))
		return (int)red;
	else if ((green >= red) && (green >= blue))
		return (int)green;
	else if ((blue >= red) && (blue >= green))
		return (int)blue;
	else
		return -1;
}

int vc_rgb_bgr_min(unsigned char red, unsigned char green, unsigned char blue)
{
	if ((red <= green) && (red <= blue))
		return (int)red;
	else if ((green <= red) && (green <= blue))
		return (int)green;
	else if ((blue <= red) && (blue <= green))
		return (int)blue;
	else
		return -1;
}

int vc_rgb_bgr_get_red_gray(IVC *image)
{
	int position = 0;
	int i, j;

	if ((image->width <= 0) || (image->height <= 0) || (image->data == NULL))
		return 0;
	if (image->channels != 3)
		return 0;

	for (i = 0; i < image->width; i++)
	{
		for (j = 0; j < image->height; j++)
		{
			position = (j * image->bytesperline) + (i * image->channels);

			image->data[position + 1] = image->data[position];
			image->data[position + 2] = image->data[position];
		}
	}

	return 1;
}

int vc_rgb_bgr_get_green_gray(IVC *image)
{
	int position = 0;
	int i, j;

	if ((image->width <= 0) || (image->height <= 0) || (image->data == NULL))
		return 0;
	if (image->channels != 3)
		return 0;

	for (i = 0; i < image->width; i++)
	{
		for (j = 0; j < image->height; j++)
		{
			position = (j * image->bytesperline) + (i * image->channels);

			image->data[position] = image->data[position + 1];
			image->data[position + 2] = image->data[position + 1];
		}
	}

	return 1;
}

int vc_rgb_bgr_get_blue_gray(IVC *image)
{
	int position = 0;
	int i, j;

	if ((image->width <= 0) || (image->height <= 0) || (image->data == NULL))
		return 0;
	if (image->channels != 3)
		return 0;

	for (i = 0; i < image->width; i++)
	{
		for (j = 0; j < image->height; j++)
		{
			position = (j * image->bytesperline) + (i * image->channels);

			image->data[position] = image->data[position + 2];
			image->data[position + 1] = image->data[position + 2];
		}
	}

	return 1;
}

int vc_print_hsv_values(IVC *originalImage)
{
	int position = 0;
	int i, j, k = 0;

	if ((originalImage->width <= 0) || (originalImage->height <= 0) || (originalImage->data == NULL))
		return 0;
	if (originalImage->channels != 3)
		return 0;

	printf("\nHue\tSaturation\tValue\n\n");

	for (i = 0; i < originalImage->width; i++)
	{
		for (j = 0; j < originalImage->height; j++)
		{
			position = (j * originalImage->bytesperline) + (i * originalImage->channels);
			printf("%d\t%d\t%d\n", originalImage->data[position], originalImage->data[position + 1], originalImage->data[position + 2]);
			k++;
		}
	}

	printf("\nPixel numbers: %d\n", k);
}

#pragma endregion

#pragma region Conversions

int vc_rgb_to_gray(IVC *originalImage, IVC *destinationImage)
{
	int originalPosition = 0, destinationPosition = 0;
	int i, j;

	if ((originalImage->width <= 0) || (originalImage->height <= 0) || (originalImage->data == NULL))
		return 0;
	if (originalImage->channels != 3)
		return 0;

	if ((destinationImage->width <= 0) || (destinationImage->height <= 0) || (destinationImage->data == NULL))
		return 0;
	if (destinationImage->channels != 1)
		return 0;

	for (i = 0; i < originalImage->width; i++)
	{
		for (j = 0; j < originalImage->height; j++)
		{
			originalPosition = (j * originalImage->bytesperline) + (i * originalImage->channels);
			destinationPosition = (j * destinationImage->bytesperline) + (i * destinationImage->channels);
			destinationImage->data[destinationPosition] = (unsigned char)((originalImage->data[originalPosition] * 0.299) + (originalImage->data[originalPosition + 1] * 0.527) + (originalImage->data[originalPosition + 2] * 0.114));
		}
	}

	return 1;
}

int vc_rgb_to_hsv(IVC *originalImage)
{
	int position = 0;
	int colorMin, colorMax;
	int i, j;
	float red, green, blue;

	if ((originalImage->width <= 0) || (originalImage->height <= 0) || (originalImage->data == NULL))
		return 0;
	if (originalImage->channels != 3)
		return 0;

	for (i = 0; i < originalImage->width; i++)
	{
		for (j = 0; j < originalImage->height; j++)
		{
			position = (j * originalImage->bytesperline) + (i * originalImage->channels);

			colorMin = vc_rgb_bgr_min(originalImage->data[position], originalImage->data[position + 1], originalImage->data[position + 2]);
			colorMax = vc_rgb_bgr_max(originalImage->data[position], originalImage->data[position + 1], originalImage->data[position + 2]);

			red = (float)originalImage->data[position];
			green = (float)originalImage->data[position + 1];
			blue = (float)originalImage->data[position + 2];

			originalImage->data[position + 2] = (unsigned char)colorMax;

			if (originalImage->data[position + 2] == 0)
			{
				originalImage->data[position + 1] = 0;
				originalImage->data[position] = 0;
			}
			else
			{
				originalImage->data[position + 1] = (unsigned char)((float)(originalImage->data[position + 2] - colorMin) / (float)originalImage->data[position + 2] * 255.0f);

				if (originalImage->data[position + 1] == 0)
					originalImage->data[position] = 0;
				else
				{
					if ((colorMax == red) && (green >= blue))
						originalImage->data[position] = (unsigned char)(((60.0f * (green - blue) / (colorMax - colorMin)) / 360.0f) * 255.0f);

					else if ((colorMax == red) && (blue > green))
						originalImage->data[position] = (unsigned char)((((360.0f + 60.0f * (green - blue) / (colorMax - colorMin)) / 360.0f) * 255.0f));

					else if (colorMax == green)
						originalImage->data[position] = (unsigned char)((((120.0f + 60.0f * (blue - red) / (colorMax - colorMin)) / 360.0f) * 255.0f));

					else if (colorMax == blue)
						originalImage->data[position] = (unsigned char)((((240.0f + 60.0f * (red - green) / (colorMax - colorMin)) / 360.0f) * 255.0f));

					else if (colorMax == colorMin)
						originalImage->data[position] = (unsigned char)0;
				}
			}
		}
	}
}

int vc_scale_gray_to_rgb(IVC *originalImage, IVC *destinationImage)
{
	int originalPosition = 0, destinationPosition = 0;
	int i, j;

	if ((originalImage->width <= 0) || (originalImage->height <= 0) || (originalImage->data == NULL))
		return 0;
	if (originalImage->channels != 1)
		return 0;

	for (i = 0; i < originalImage->width; i++)
	{
		for (j = 0; j < originalImage->height; j++)
		{
			originalPosition = (j * originalImage->bytesperline) + (i * originalImage->channels);

			destinationPosition = (j * destinationImage->bytesperline) + (i * destinationImage->channels);

			if (originalImage->data[originalPosition] < 64)
			{
				destinationImage->data[destinationPosition] = (unsigned char)0;
				destinationImage->data[destinationPosition + 1] = originalImage->data[originalPosition] * (unsigned char)4;
				destinationImage->data[destinationPosition + 2] = (unsigned char)255;
			}
			else if ((originalImage->data[originalPosition] >= 64) && (originalImage->data[originalPosition] < 128))
			{
				destinationImage->data[destinationPosition] = (unsigned char)0;
				destinationImage->data[destinationPosition + 1] = (unsigned char)255;
				destinationImage->data[destinationPosition + 2] = (unsigned char)(255 - (originalImage->data[originalPosition] - 128) * 4);
			}
			else if ((originalImage->data[originalPosition] >= 128) && (originalImage->data[originalPosition] < 192))
			{
				destinationImage->data[destinationPosition] = (unsigned char)(0 + (originalImage->data[originalPosition] - 128) * 4);
				destinationImage->data[destinationPosition + 1] = (unsigned char)255;
				destinationImage->data[destinationPosition + 2] = (unsigned char)0;
			}
			else if ((originalImage->data[originalPosition] >= 192) && (originalImage->data[originalPosition] <= 255))
			{
				destinationImage->data[destinationPosition] = (unsigned char)255;
				destinationImage->data[destinationPosition + 1] = (unsigned char)(255 - (originalImage->data[originalPosition] - 192) * 4);
				destinationImage->data[destinationPosition + 2] = (unsigned char)0;
			}
			else
			{
				destinationImage->data[destinationPosition] = (unsigned char)0;
				destinationImage->data[destinationPosition + 1] = (unsigned char)0;
				destinationImage->data[destinationPosition + 2] = (unsigned char)0;
			}
		}
	}

	return 1;
}

int vc_gray_to_binary(IVC *image, int threshold)
{
	int position = 0;
	int i, j;

	if ((image->width <= 0) || (image->height <= 0) || (image->data == NULL))
		return 0;
	if (image->channels != 1)
		return 0;

	for (i = 0; i < image->width; i++)
	{
		for (j = 0; j < image->height; j++)
		{
			position = (j * image->bytesperline) + (i * image->channels);

			if (image->data[position] >= threshold)
				image->data[position] = 255;
			else if (image->data[position] < threshold)
				image->data[position] = 0;
		}
	}

	image->levels = 1;

	return 1;
}

int vc_gray_to_binary_global_mean(IVC *image)
{
	int position = 0;
	int i, j;
	int averageSum = 0;
	float average;

	if ((image->width <= 0) || (image->height <= 0) || (image->data == NULL))
		return 0;
	if (image->channels != 1)
		return 0;

	for (i = 0; i < image->width; i++)
	{
		for (j = 0; j < image->height; j++)
		{
			position = (j * image->bytesperline) + (i * image->channels);
			averageSum = averageSum + image->data[position];
		}
	}

	average = ((float)averageSum / (float)(image->width * image->height));

	vc_gray_to_binary(image, (int)average);

	return 1;
}

int vc_hsv_to_binary_in_range(IVC *originalImage, IVC *destinationImage, unsigned short colorRange)
{
	int originalPosition = 0, destinationPosition = 0;
	int i, j;

	if ((originalImage->width <= 0) || (originalImage->height <= 0) || (originalImage->data == NULL))
		return 0;
	if (originalImage->channels != 3)
		return 0;

	if ((destinationImage->width <= 0) || (destinationImage->height <= 0) || (destinationImage->data == NULL))
		return 0;
	if (destinationImage->channels != 1)
		return 0;

	for (i = 0; i < originalImage->width; i++)
	{
		for (j = 0; j < originalImage->height; j++)
		{
			originalPosition = (j * originalImage->bytesperline) + (i * originalImage->channels);
			destinationPosition = (j * destinationImage->bytesperline) + (i * destinationImage->channels);

			if (colorRange == 0)
			{
				if ((originalImage->data[originalPosition + 1] < 80) || (originalImage->data[originalPosition + 2] < 80) || (originalImage->data[originalPosition] > 20 && originalImage->data[originalPosition] < 230))
					destinationImage->data[destinationPosition] = 0;
				else
					destinationImage->data[destinationPosition] = 255;
			}
			if (colorRange == 1)
			{
				if ((originalImage->data[originalPosition + 1] < 40) || (originalImage->data[originalPosition + 2] < 35) || (originalImage->data[originalPosition] < 150 || originalImage->data[originalPosition] > 200))
					destinationImage->data[destinationPosition] = 0;
				else
					destinationImage->data[destinationPosition] = 255;
			}
			if (colorRange == 2)
			{
				if (originalImage->data[originalPosition + 1] < 60)
					destinationImage->data[destinationPosition] = 0;
				else
					destinationImage->data[destinationPosition] = 255;
			}
		}
	}

	return 1;
}

int vc_gray_black_to_white(IVC *image)
{
	int position = 0;
	int i, j;

	if ((image->width <= 0) || (image->height <= 0) || (image->data == NULL))
		return 0;
	if (image->channels != 1)
		return 0;

	for (i = 0; i < image->width; i++)
	{
		for (j = 0; j < image->height; j++)
		{
			position = (j * image->bytesperline) + (i * image->channels);

			if (image->data[position] == 0)
				image->data[position] = 255;
		}
	}

	return 1;
}

int vc_binary_to_rgb(IVC *originalImage, IVC *destinationImage)
{
	int originalPosition = 0, destinationPosition = 0;
	int i, j;

	if ((originalImage->width <= 0) || (originalImage->height <= 0) || (originalImage->data == NULL))
		return 0;
	if (originalImage->channels != 1)
		return 0;

	if ((destinationImage->width <= 0) || (destinationImage->height <= 0) || (destinationImage->data == NULL))
		return 0;
	if (destinationImage->channels != 3)
		return 0;

	for (i = 0; i < destinationImage->width; i++)
	{
		for (j = 0; j < destinationImage->height; j++)
		{
			originalPosition = (j * originalImage->bytesperline) + (i * originalImage->channels);
			destinationPosition = (j * destinationImage->bytesperline) + (i * destinationImage->channels);

			if (originalImage->data[originalPosition] == 255)
			{
				destinationImage->data[destinationPosition] = 255;
				destinationImage->data[destinationPosition + 1] = 255;
				destinationImage->data[destinationPosition + 2] = 255;
			}
			else
			{
				destinationImage->data[destinationPosition] = 0;
				destinationImage->data[destinationPosition + 1] = 0;
				destinationImage->data[destinationPosition + 2] = 0;
			}
		}
	}

	return 1;
}

int vc_binary_to_bgr(IVC *originalImage, IplImage *destinationImage)
{
	int originalPosition = 0, destinationPosition = 0;
	int i, j;

	if ((originalImage->width <= 0) || (originalImage->height <= 0) || (originalImage->data == NULL))
		return 0;
	if (originalImage->channels != 1)
		return 0;

	if ((destinationImage->width <= 0) || (destinationImage->height <= 0) || (destinationImage->imageData == NULL))
		return 0;
	if (destinationImage->nChannels != 3)
		return 0;

	for (i = 0; i < destinationImage->width; i++)
	{
		for (j = 0; j < destinationImage->height; j++)
		{
			originalPosition = (j * originalImage->bytesperline) + (i * originalImage->channels);
			destinationPosition = (j * destinationImage->widthStep) + (i * destinationImage->nChannels);

			if (originalImage->data[originalPosition] == 255)
			{
				destinationImage->imageData[destinationPosition] = 255;
				destinationImage->imageData[destinationPosition + 1] = 255;
				destinationImage->imageData[destinationPosition + 2] = 255;
			}
			else
			{
				destinationImage->imageData[destinationPosition] = 0;
				destinationImage->imageData[destinationPosition + 1] = 0;
				destinationImage->imageData[destinationPosition + 2] = 0;
			}
		}
	}
}

int vc_bgr_to_rgb(IplImage *originalImage, IVC *destinationImage)
{
	int position = 0;
	int i, j;

	if ((originalImage->width <= 0) || (originalImage->height <= 0) || (originalImage->imageData == NULL))
		return 0;
	if (originalImage->nChannels != 3)
		return 0;

	if ((destinationImage->width <= 0) || (destinationImage->height <= 0) || (destinationImage->data == NULL))
		return 0;
	if (destinationImage->channels != 3)
		return 0;

	for (i = 0; i < destinationImage->width; i++)
	{
		for (j = 0; j < destinationImage->height; j++)
		{
			position = (j * destinationImage->bytesperline) + (i * destinationImage->channels);

			destinationImage->data[position] = originalImage->imageData[position + 2];
			destinationImage->data[position + 1] = originalImage->imageData[position + 1];
			destinationImage->data[position + 2] = originalImage->imageData[position];
		}
	}

	return 1;
}

int vc_rgb_to_bgr(IVC *originalImage, IplImage *destinationImage)
{
	int position = 0;
	int i, j;

	if ((originalImage->width <= 0) || (originalImage->height <= 0) || (originalImage->data == NULL))
		return 0;
	if (originalImage->channels != 3)
		return 0;

	if ((destinationImage->width <= 0) || (destinationImage->height <= 0) || (destinationImage->imageData == NULL))
		return 0;
	if (destinationImage->nChannels != 3)
		return 0;

	for (i = 0; i < originalImage->width; i++)
	{
		for (j = 0; j < originalImage->height; j++)
		{
			position = (j * originalImage->bytesperline) + (i * originalImage->channels);

			destinationImage->imageData[position] = originalImage->data[position + 2];
			destinationImage->imageData[position + 1] = originalImage->data[position + 1];
			destinationImage->imageData[position + 2] = originalImage->data[position];
		}
	}

	return 1;
}

#pragma endregion

#pragma region Erosion and dilation

int vc_binary_dilate(IVC *originalImage, IVC *destinationImage, int kernelSize)
{
	int i, j, xx, yy;
	int kernelSide;
	int destinationPosition, neighborhoodPosition;
	unsigned short breakCycle = 0;

	if ((originalImage->width <= 0) || (originalImage->height <= 0) || (originalImage->data == NULL))
		return 0;
	if (originalImage->channels != 1)
		return 0;

	memcpy(destinationImage->data, originalImage->data, originalImage->bytesperline * originalImage->height);

	kernelSide = ((kernelSize - 1) / 2);

	for (i = 0; i < originalImage->width; i++)
	{
		for (j = 0; j < originalImage->height; j++)
		{
			destinationPosition = (j * destinationImage->bytesperline) + (i * destinationImage->channels);

			for (xx = i - kernelSide; xx <= i + kernelSide; xx++)
			{
				for (yy = j - kernelSide; yy <= j + kernelSide; yy++)
				{
					if ((xx < 0) || (yy < 0) || (xx >= originalImage->width) || (yy >= originalImage->height))
						continue;

					neighborhoodPosition = (yy * originalImage->bytesperline + xx * originalImage->channels);

					if (originalImage->data[neighborhoodPosition] == (unsigned char)255)
					{
						destinationImage->data[destinationPosition] = (unsigned char)255;
						breakCycle = 1;
						break;
					}
				}

				if (breakCycle == 1)
					break;
			}

			breakCycle = 0;
		}
	}

	return 1;
}

int vc_binary_erode(IVC *originalImage, IVC *destinationImage, int kernelSize)
{
	int i, j, xx, yy;
	int kernelSide;
	long int destinationPosition, neighborhoodPosition;
	unsigned int breakCycle = 0;

	if ((originalImage->width <= 0) || (originalImage->height <= 0) || (originalImage->data == NULL))
		return 0;
	if (originalImage->channels != 1)
		return 0;

	memcpy(destinationImage->data, originalImage->data, originalImage->bytesperline * originalImage->height);

	kernelSide = ((kernelSize - 1) / 2);

	for (i = 0; i < originalImage->width; i++)
	{
		for (j = 0; j < originalImage->height; j++)
		{
			destinationPosition = (j * destinationImage->bytesperline) + (i * destinationImage->channels);

			for (xx = i - kernelSide; xx <= i + kernelSide; xx++)
			{
				for (yy = j - kernelSide; yy <= j + kernelSide; yy++)
				{
					if ((xx < 0) || (yy < 0) || (xx >= originalImage->width) || (yy >= originalImage->height))
						continue;

					neighborhoodPosition = (yy * originalImage->bytesperline + xx * originalImage->channels);

					if (originalImage->data[neighborhoodPosition] == 0)
					{
						destinationImage->data[destinationPosition] = (unsigned char)0;
						breakCycle = 1;
						break;
					}
				}

				if (breakCycle == 1)
					break;
			}

			breakCycle = 0;
		}
	}

	return 1;
}

#pragma endregion

#pragma region Open / close operations

int vc_binary_close(IVC *originalImage, IVC *destinationImage, int erodeSize, int dilateSize)
{
	IVC *temporaryImage;
	temporaryImage = vc_image_new(originalImage->width, originalImage->height, originalImage->channels, originalImage->levels);

	if ((originalImage->width <= 0) || (originalImage->height <= 0) || (originalImage->data == NULL))
		return 0;
	if (originalImage->channels != 1)
		return 0;

	if ((destinationImage->width <= 0) || (destinationImage->height <= 0) || (destinationImage->data == NULL))
		return 0;
	if (destinationImage->channels != 1)
		return 0;

	if (vc_binary_dilate(originalImage, temporaryImage, dilateSize) == 0)
		return 0;

	if (vc_binary_erode(temporaryImage, destinationImage, erodeSize) == 0)
		return 0;

	vc_image_free(temporaryImage);

	return 1;
}

int vc_binary_open(IVC *originalImage, IVC *destinationImage, int erodeSize, int dilateSize)
{
	IVC *temporaryImage;
	temporaryImage = vc_image_new(originalImage->width, originalImage->height, originalImage->channels, originalImage->levels);

	if ((originalImage->width <= 0) || (originalImage->height <= 0) || (originalImage->data == NULL))
		return 0;
	if (originalImage->channels != 1)
		return 0;

	if ((destinationImage->width <= 0) || (destinationImage->height <= 0) || (destinationImage->data == NULL))
		return 0;
	if (destinationImage->channels != 1)
		return 0;

	if (vc_binary_erode(originalImage, temporaryImage, erodeSize) == 0)
		return 0;

	if (vc_binary_dilate(temporaryImage, destinationImage, dilateSize) == 0)
		return 0;

	vc_image_free(temporaryImage);

	return 1;
}

#pragma endregion

#pragma region Blobs and labeling

OVC *vc_binary_blob_labelling(IVC *src, IVC *dst, int *nlabels)
{
	unsigned char *datasrc = (unsigned char *)src->data;
	unsigned char *datadst = (unsigned char *)dst->data;
	int width = src->width;
	int height = src->height;
	int bytesperline = src->bytesperline;
	int channels = src->channels;
	int x, y, a, b;
	long int i, size;
	long int posX, posA, posB, posC, posD;
	int labeltable[256] = {0};
	int labelarea[256] = {0};
	int label = 1;
	int num;
	OVC *blobs;

	if ((src->width <= 0) || (src->height <= 0) || (src->data == NULL))
		return 0;
	if ((src->width != dst->width) || (src->height != dst->height) || (src->channels != dst->channels))
		return NULL;
	if (channels != 1)
		return NULL;

	memcpy(datadst, datasrc, bytesperline * height);

	for (i = 0, size = bytesperline * height; i < size; i++)
	{
		if (datadst[i] != 0)
			datadst[i] = 255;
	}

	for (y = 0; y < height; y++)
	{
		datadst[y * bytesperline + 0 * channels] = 0;
		datadst[y * bytesperline + (width - 1) * channels] = 0;
	}

	for (x = 0; x < width; x++)
	{
		datadst[0 * bytesperline + x * channels] = 0;
		datadst[(height - 1) * bytesperline + x * channels] = 0;
	}

	for (y = 1; y < height - 1; y++)
	{
		for (x = 1; x < width - 1; x++)
		{
			posA = (y - 1) * bytesperline + (x - 1) * channels;
			posB = (y - 1) * bytesperline + x * channels;
			posC = (y - 1) * bytesperline + (x + 1) * channels;
			posD = y * bytesperline + (x - 1) * channels;
			posX = y * bytesperline + x * channels;

			if (datadst[posX] != 0)
			{
				if ((datadst[posA] == 0) && (datadst[posB] == 0) && (datadst[posC] == 0) && (datadst[posD] == 0))
				{
					datadst[posX] = label;
					labeltable[label] = label;
					label++;
				}
				else
				{
					num = 255;

					if ((datadst[posA] != 0) && (datadst[posA] != 255) && (datadst[posA] < num))
					{
						num = datadst[posA];
					}
					if ((datadst[posB] != 0) && (datadst[posB] != 255) && (datadst[posB] < num))
					{
						num = datadst[posB];
					}
					if ((datadst[posC] != 0) && (datadst[posC] != 255) && (datadst[posC] < num))
					{
						num = datadst[posC];
					}
					if ((datadst[posD] != 0) && (datadst[posD] != 255) && (datadst[posD] < num))
					{
						num = datadst[posD];
					}

					if ((datadst[posA] != 0) && (datadst[posA] != 255))
					{
						if (labeltable[datadst[posA]] != labeltable[num])
						{
							for (a = 1; a < label; a++)
							{
								if (labeltable[a] == labeltable[datadst[posA]])
								{
									labeltable[a] = labeltable[num];
								}
							}
						}
					}
					if ((datadst[posB] != 0) && (datadst[posB] != 255))
					{
						if (labeltable[datadst[posB]] != labeltable[num])
						{
							for (a = 1; a < label; a++)
							{
								if (labeltable[a] == labeltable[datadst[posB]])
								{
									labeltable[a] = labeltable[num];
								}
							}
						}
					}
					if ((datadst[posC] != 0) && (datadst[posC] != 255))
					{
						if (labeltable[datadst[posC]] != labeltable[num])
						{
							for (a = 1; a < label; a++)
							{
								if (labeltable[a] == labeltable[datadst[posC]])
								{
									labeltable[a] = labeltable[num];
								}
							}
						}
					}
					if ((datadst[posD] != 0) && (datadst[posD] != 255))
					{
						if (labeltable[datadst[posD]] != labeltable[num])
						{
							for (a = 1; a < label; a++)
							{
								if (labeltable[a] == labeltable[datadst[posD]])
								{
									labeltable[a] = labeltable[num];
								}
							}
						}
					}
					labeltable[datadst[posX]] = num;

					datadst[posX] = num;
				}
			}
		}
	}

	for (y = 1; y < height - 1; y++)
	{
		for (x = 1; x < width - 1; x++)
		{
			posX = y * bytesperline + x * channels; // X

			if (datadst[posX] != 0)
			{
				datadst[posX] = labeltable[datadst[posX]];
			}
		}
	}

	for (a = 1; a < label - 1; a++)
	{
		for (b = a + 1; b < label; b++)
		{
			if (labeltable[a] == labeltable[b])
				labeltable[b] = 0;
		}
	}

	*nlabels = 0;

	for (a = 1; a < label; a++)
	{
		if (labeltable[a] != 0)
		{
			labeltable[*nlabels] = labeltable[a];
			(*nlabels)++;
		}
	}

	if (*nlabels == 0)
		return NULL;

	blobs = (OVC *)calloc((*nlabels), sizeof(OVC));
	if (blobs != NULL)
	{
		for (a = 0; a < (*nlabels); a++)
			blobs[a].label = labeltable[a];
	}
	else
		return NULL;

	return blobs;
}

int vc_binary_blob_info(IVC *src, OVC *blobs, int nblobs)
{
	unsigned char *data = (unsigned char *)src->data;
	int width = src->width;
	int height = src->height;
	int bytesperline = src->bytesperline;
	int channels = src->channels;
	int x, y, i;
	long int pos;
	int xmin, ymin, xmax, ymax;
	long int sumx, sumy;

	if ((src->width <= 0) || (src->height <= 0) || (src->data == NULL))
		return 0;
	if (channels != 1)
		return 0;

	for (i = 0; i < nblobs; i++)
	{
		xmin = width - 1;
		ymin = height - 1;
		xmax = 0;
		ymax = 0;

		sumx = 0;
		sumy = 0;

		blobs[i].area = 0;

		for (y = 1; y < height - 1; y++)
		{
			for (x = 1; x < width - 1; x++)
			{
				pos = y * bytesperline + x * channels;

				if (data[pos] == blobs[i].label)
				{
					blobs[i].area++;

					sumx += x;
					sumy += y;

					if (xmin > x)
						xmin = x;
					if (ymin > y)
						ymin = y;
					if (xmax < x)
						xmax = x;
					if (ymax < y)
						ymax = y;

					if ((data[pos - 1] != blobs[i].label) || (data[pos + 1] != blobs[i].label) || (data[pos - bytesperline] != blobs[i].label) || (data[pos + bytesperline] != blobs[i].label))
						blobs[i].perimeter++;
				}
			}
		}

		blobs[i].x = xmin;
		blobs[i].y = ymin;
		blobs[i].width = (xmax - xmin) + 1;
		blobs[i].height = (ymax - ymin) + 1;

		blobs[i].xc = sumx / (blobs[i].area > 1 ? blobs[i].area : 1);
		blobs[i].yc = sumy / (blobs[i].area > 1 ? blobs[i].area : 1);
	}

	return 1;
}

int vc_print_blob_info(OVC *blob, int indiceBlob)
{
	printf("\n[Blob of interest]\n");
	printf("Label: %d\n", blob[indiceBlob].label);
	printf("Area: %d\n", blob[indiceBlob].area);
	printf("Perimeter: %d\n", blob[indiceBlob].perimeter);
	printf("Width: %d\n", blob[indiceBlob].width);
	printf("Height: %d\n", blob[indiceBlob].height);
	printf("X coordinate: %d\n", blob[indiceBlob].x);
	printf("Y coordinate: %d\n", blob[indiceBlob].y);
	printf("X center-of-mass: %d\n", blob[indiceBlob].xc);
	printf("Y center-of-mass: %d\n", blob[indiceBlob].yc);

	return 1;
}

int vc_print_blobs_info(OVC *blobs, int blobNumber)
{
	unsigned int i;

	for (i = 0; i < blobNumber; i++)
	{
		printf("\nBlob %d:\n", blobs[i].label);
		printf("Area: %d\n", blobs[i].area);
		printf("Perimeter: %d\n", blobs[i].perimeter);
		printf("Width: %d\n", blobs[i].width);
		printf("Height: %d\n", blobs[i].height);
		printf("X coordinate: %d\n", blobs[i].x);
		printf("Y coordinate: %d\n", blobs[i].y);
		printf("X center-of-mass: %d\n", blobs[i].xc);
		printf("Y center-of-mass: %d\n", blobs[i].yc);
	}

	return 1;
}

int vc_get_blob_label_max_area(OVC *blobs, int blobNumber)
{
	unsigned int i, maiorArea = 0, indiceMaiorArea = -1;

	for (i = 0; i < blobNumber; i++)
	{
		if (blobs[i].area > maiorArea)
		{
			maiorArea = blobs[i].area;
			indiceMaiorArea = i;
		}
	}

	return indiceMaiorArea;
}

int vc_is_blob_inside_interest_blob(OVC *segmentedImageBlobs, int interestBlobLabel, OVC *segmentedInvertedImageBlobs, int invertedBlobLabel)
{
	int xMin, xMax, yMin, yMax;

	xMin = segmentedImageBlobs[interestBlobLabel].x;
	xMax = segmentedImageBlobs[interestBlobLabel].x + segmentedImageBlobs[interestBlobLabel].width;
	yMin = segmentedImageBlobs[interestBlobLabel].y;
	yMax = segmentedImageBlobs[interestBlobLabel].y + segmentedImageBlobs[interestBlobLabel].height;

	if ((segmentedInvertedImageBlobs[invertedBlobLabel].x >= xMin && segmentedInvertedImageBlobs[invertedBlobLabel].x <= xMax) && (segmentedInvertedImageBlobs[invertedBlobLabel].y >= yMin && segmentedInvertedImageBlobs[invertedBlobLabel].y <= yMax))
		return 1;
	else
		return 0;
}

int vc_count_blobs_inside_interest_blob(OVC *segmentedImageBlobs, int interestBlobLabel, OVC *segmentedInvertedImageBlobs, int invertedBlobsNumber)
{
	int i, blobCount = 0;

	for (i = 0; i < invertedBlobsNumber; i++)
		if (vc_is_blob_inside_interest_blob(segmentedImageBlobs, interestBlobLabel, segmentedInvertedImageBlobs, i) == 1)
			blobCount++;

	return blobCount;
}

int vc_isolate_interest_blob(IVC *segmentedInvertedImage, OVC *segmentedInvertedImageBlobs, int segmentedInvertedImageBlobNumber, OVC *segmentedImageBlobs, int segmentedImageInterestBlobLabel)
{
	int i, j, k;
	int position, xMin, xMax, yMin, yMax;

	if ((segmentedInvertedImage->width <= 0) || (segmentedInvertedImage->height <= 0) || (segmentedInvertedImage->data == NULL))
		return 0;
	if (segmentedInvertedImage->channels != 1)
		return 0;

	for (i = 0; i < segmentedInvertedImageBlobNumber; i++)
	{
		if (vc_is_blob_inside_interest_blob(segmentedImageBlobs, segmentedImageInterestBlobLabel, segmentedInvertedImageBlobs, i) == 1)
		{
			xMin = segmentedInvertedImageBlobs[i].x;
			xMax = segmentedInvertedImageBlobs[i].x + segmentedInvertedImageBlobs[i].width;
			yMin = segmentedInvertedImageBlobs[i].y;
			yMax = segmentedInvertedImageBlobs[i].y + segmentedInvertedImageBlobs[i].height;

			for (j = 0; j < segmentedInvertedImage->width; j++)
			{
				for (k = 0; k < segmentedInvertedImage->height; k++)
				{
					position = (k * segmentedInvertedImage->bytesperline) + (j * segmentedInvertedImage->channels);

					if ((j >= xMin && j <= xMax) && (k >= yMin && k <= yMax))
						segmentedInvertedImage->data[position] = 255;
				}
			}
		}
	}

	return 1;
}

int vc_draw_blob_boundary_box_rgb(IVC *image, int x, int y, int width, int height)
{
	int xMax, yMax, position, i, j;

	xMax = x + width;
	yMax = y + height;

	if ((image->width <= 0) || (image->height <= 0) || (image->data == NULL))
		return 0;
	if (image->channels != 3)
		return 0;

	for (i = x; i <= xMax; i++)
	{
		position = y * image->bytesperline + (i * image->channels);
		image->data[position] = 0;
		image->data[position + 1] = 255;
		image->data[position + 2] = 0;

		position = yMax * image->bytesperline + (i * image->channels);
		image->data[position] = 0;
		image->data[position + 1] = 255;
		image->data[position + 2] = 0;
	}

	for (j = y; j <= yMax; j++)
	{
		position = j * image->bytesperline + (x * image->channels);
		image->data[position] = 0;
		image->data[position + 1] = 255;
		image->data[position + 2] = 0;

		position = j * image->bytesperline + (xMax * image->channels);
		image->data[position] = 0;
		image->data[position + 1] = 255;
		image->data[position + 2] = 0;
	}

	return 1;
}

int vc_draw_blob_boundary_box_binary(IVC *image, int x, int y, int xMax, int yMax)
{
	int position, i, j;

	if ((image->width <= 0) || (image->height <= 0) || (image->data == NULL))
		return 0;
	if (image->channels != 1)
		return 0;

	for (i = x; i <= xMax; i++)
	{
		position = y * image->bytesperline + (i * image->channels);

		if (image->data[position] == 255)
			image->data[position] = 0;
		else
			image->data[position] = 255;

		position = yMax * image->bytesperline + (i * image->channels);

		if (image->data[position] == 255)
			image->data[position] = 0;
		else
			image->data[position] = 255;
	}

	for (j = y; j <= yMax; j++)
	{
		position = j * image->bytesperline + (x * image->channels);

		if (image->data[position] == 255)
			image->data[position] = 0;
		else
			image->data[position] = 255;

		position = j * image->bytesperline + (xMax * image->channels);

		if (image->data[position] == 255)
			image->data[position] = 0;
		else
			image->data[position] = 255;
	}

	return 1;
}

int vc_draw_blob_boundary_box_bgr(IplImage *image, int x, int y, int width, int height)
{
	int xMax, yMax, position, i, j;

	xMax = x + width;
	yMax = y + height;

	if ((image->width <= 0) || (image->height <= 0) || (image->imageData == NULL))
		return 0;
	if (image->nChannels != 3)
		return 0;

	for (i = x; i <= xMax; i++)
	{
		position = y * image->widthStep + (i * image->nChannels);
		image->imageData[position] = 0;
		image->imageData[position + 1] = 255;
		image->imageData[position + 2] = 0;

		position = yMax * image->widthStep + (i * image->nChannels);
		image->imageData[position] = 0;
		image->imageData[position + 1] = 255;
		image->imageData[position + 2] = 0;
	}

	for (j = y; j <= yMax; j++)
	{
		position = j * image->widthStep + (x * image->nChannels);
		image->imageData[position] = 0;
		image->imageData[position + 1] = 255;
		image->imageData[position + 2] = 0;

		position = j * image->widthStep + (xMax * image->nChannels);
		image->imageData[position] = 0;
		image->imageData[position + 1] = 255;
		image->imageData[position + 2] = 0;
	}

	return 1;
}

float vc_get_blob_circularity(int blobArea, int blobPerimeter)
{
	const float pi = 3.14159265358979323846;
	return sqrt(4 * pi * blobArea / pow(blobPerimeter, 2));
}

int vc_gray_compare_segmentation_areas(OVC *redBlobs, int redBlobsNumber, OVC *blueBlobs, int blueBlobsNumber)
{
	int maxAreaRedBlobs, maxAreaBlueBlobs;

	maxAreaRedBlobs = vc_get_blob_label_max_area(redBlobs, redBlobsNumber);
	maxAreaBlueBlobs = vc_get_blob_label_max_area(blueBlobs, blueBlobsNumber);

	if (maxAreaRedBlobs > maxAreaBlueBlobs)
		return 0;
	else
		return 1;
}

int vc_count_pixel_half_boundary_box_horizontal(IVC *image, OVC *blobList, int interestBlobLabel, int *upPixels, int *downPixels)
{
	int i, j, position;
	int xMin, xMax, yMin, yMax;

	*upPixels = 0, *downPixels = 0;

	if ((image->width <= 0) || (image->height <= 0) || (image->data == NULL))
		return 0;
	if (image->channels != 1)
		return 0;

	xMin = blobList[interestBlobLabel].x;
	xMax = blobList[interestBlobLabel].x + blobList[interestBlobLabel].width;
	yMin = blobList[interestBlobLabel].y;
	yMax = blobList[interestBlobLabel].y + blobList[interestBlobLabel].height;

	for (i = 0; i < image->width; i++)
	{
		for (j = 0; j < image->height; j++)
		{
			position = (j * image->bytesperline) + (i * image->channels);

			if ((i >= xMin && i <= xMax) && (j >= yMin && j <= yMin + (blobList[interestBlobLabel].height / 2)))
				if (image->data[position] == 0)
					*upPixels = *upPixels + 1;

			if ((i >= xMin && i <= xMax) && (j > yMin + (blobList[interestBlobLabel].height / 2) && j <= yMax))
				if (image->data[position] == 0)
					*downPixels = *downPixels + 1;
		}
	}

	return 1;
}

int vc_count_pixel_half_boundary_box_vertical(IVC *image, OVC *blobList, int interestBlobLabel, int *leftPixels, int *rightPixels)
{
	int i, j, position;
	int xMin, xMax, yMin, yMax;

	*leftPixels = 0, *rightPixels = 0;

	if ((image->width <= 0) || (image->height <= 0) || (image->data == NULL))
		return 0;
	if (image->channels != 1)
		return 0;

	xMin = blobList[interestBlobLabel].x;
	xMax = blobList[interestBlobLabel].x + blobList[interestBlobLabel].width;
	yMin = blobList[interestBlobLabel].y;
	yMax = blobList[interestBlobLabel].y + blobList[interestBlobLabel].height;

	for (i = 0; i < image->width; i++)
	{
		for (j = 0; j < image->height; j++)
		{
			position = (j * image->bytesperline) + (i * image->channels);

			if ((i >= xMin && i <= xMin + (blobList[interestBlobLabel].width / 2) && (j >= yMin && j <= yMax)))
				if (image->data[position] == 0)
					*leftPixels = *leftPixels + 1;

			if ((i > xMin + (blobList[interestBlobLabel].width / 2) && i <= xMax) && (j >= yMin && j <= yMax))
				if (image->data[position] == 0)
					*rightPixels = *rightPixels + 1;
		}
	}

	return 1;
}

int vc_get_bigger_boundary_box_side(int upPixels, int downPixels, int leftPixels, int rightPixels)
{
	if ((upPixels > downPixels) && (upPixels > leftPixels) && (upPixels > rightPixels))
		return 1;
	if ((leftPixels > upPixels) && (leftPixels > downPixels) && (leftPixels > rightPixels))
		return 2;
	if ((rightPixels > upPixels) && (rightPixels > leftPixels) && (rightPixels > downPixels))
		return 3;
	else if ((downPixels > upPixels) && (downPixels > leftPixels) && (downPixels > rightPixels))
		return 4;
	else
		return 0;
}

int vc_conditional_draw_boundary_box_all_blobs(OVC *blobs, int blobNumber, int blobMinimumArea, IplImage *originalImage)
{
	unsigned int i;

	for (i = 0; i < blobNumber; i++)
		if (blobs[i].area > blobMinimumArea)
			vc_draw_blob_boundary_box_bgr(originalImage, blobs[i].x, blobs[i].y, blobs[i].width, blobs[i].height);

	return 1;
}

int vc_get_verified_blob_state(verifiedBlobList list, int index, int area, int pixelTolerance)
{
	while (list != NULL)
	{
		if ((index == list->index) && (area >= list->area - pixelTolerance) && (area <= list->area + pixelTolerance))
			return 1;
		else
			list = list->next;
	}

	return 0;
}

verifiedBlobList vc_add_verified_blob(verifiedBlobList list, int index, int area, int perimeter, const char *tipology)
{
	verifiedBlobList newVerifiedBlob = (verifiedBlobList)malloc(sizeof(struct verifiedBlob));

	newVerifiedBlob->index = index;
	newVerifiedBlob->area = area;
	newVerifiedBlob->perimeter = perimeter;
	newVerifiedBlob->tipology = tipology;
	newVerifiedBlob->next = list;

	return newVerifiedBlob;
}

unsigned int vc_count_verified_blobs(verifiedBlobList list)
{
	int verifiedBlobNumber = 0;

	while (list != NULL)
	{
		verifiedBlobNumber++;
		list = list->next;
	}

	return verifiedBlobNumber;
}

int vc_print_verified_blob_list(verifiedBlobList list)
{
	unsigned int i = vc_count_verified_blobs(list);

	while (list != NULL)
	{
		printf("Order: %d\n", i--);
		printf("Typology: %s\n", list->tipology);
		printf("Area: %d\n", list->area);
		printf("Perimeter: %d\n\n", list->perimeter);

		list = list->next;
	}

	return 1;
}

int vc_free_verified_blob_list(verifiedBlobList list)
{
	struct verifiedBlob *aux;

	while (list != NULL)
	{
		aux = list;
		list = list->next;
		free(aux);
	}

	return 1;
}

int vc_draw_blob_crosshair(IplImage *image, int blobWidth, int blobHeight, int xCenterMass, int yCenterMass, int crosshairSize, int crossHairColor)
{
	int i, j, position;

	if ((image->width <= 0) || (image->height <= 0) || (image->imageData == NULL))
		return 0;
	if (image->nChannels != 3)
		return 0;
	if (xCenterMass <= crosshairSize || yCenterMass <= crosshairSize)
		return 0;

	for (i = xCenterMass - crosshairSize; i <= xCenterMass + crosshairSize; i++)
	{
		position = yCenterMass * image->widthStep + (i * image->nChannels);

		if (crossHairColor == 0)
		{
			image->imageData[position] = 0;
			image->imageData[position + 1] = 255;
			image->imageData[position + 2] = 0;
		}
		else
		{
			image->imageData[position] = 0;
			image->imageData[position + 1] = 0;
			image->imageData[position + 2] = 255;
		}
	}

	for (j = yCenterMass - crosshairSize; j <= yCenterMass + crosshairSize; j++)
	{
		position = j * image->widthStep + (xCenterMass * image->nChannels);

		if (crossHairColor == 0)
		{
			image->imageData[position] = 0;
			image->imageData[position + 1] = 255;
			image->imageData[position + 2] = 0;
		}
		else
		{
			image->imageData[position] = 0;
			image->imageData[position + 1] = 0;
			image->imageData[position + 2] = 255;
		}
	}

	return 1;
}

int vc_draw_crosshair_all_blobs(OVC *blobs, int blobNumber, int blobMinimumArea, int crosshairSize, int crossHairColor, IplImage *originalImage)
{
	unsigned int i;

	for (i = 0; i < blobNumber; i++)
		if (blobs[i].area > blobMinimumArea)
			vc_draw_blob_crosshair(originalImage, blobs[i].width, blobs[i].height, blobs[i].xc, blobs[i].yc, crosshairSize, crossHairColor);

	return 1;
}

int vc_detect_blob_inside_vertical_area(int height, OVC *blobs, int blobIndex, int offset)
{
	int verticalCenter = height / 2;

	if (blobs[blobIndex].yc >= (verticalCenter - offset) && blobs[blobIndex].yc < (verticalCenter + offset))
		return 1;
	else
		return 0;
}

#pragma endregion

#pragma region Histograms

unsigned int *vc_gray_get_histogram(IVC *image)
{
	const unsigned int levels = 256;

	unsigned int *histogram = (unsigned int *)(calloc(levels, sizeof(unsigned int)));
	unsigned int position = 0;
	unsigned int i, j, k;

	if ((image->width <= 0) || (image->height <= 0) || (image->data == NULL))
		return 0;
	if (image->channels != 1)
		return 0;

	for (i = 0; i < image->width; i++)
	{
		for (j = 0; j < image->height; j++)
		{
			position = (j * image->bytesperline) + (i * image->channels);
			histogram[image->data[position]]++;
		}
	}

	return histogram;
}

unsigned int vc_gray_get_histogram_max(unsigned int *histogram)
{
	const unsigned int levels = 256;

	unsigned int i, max = 0;

	for (i = 0; i < levels; i++)
		if (histogram[i] > max)
			max = histogram[i];

	return max;
}

int vc_gray_print_histogram(unsigned int *histogram)
{
	const unsigned int levels = 256;

	unsigned int i;

	for (i = 0; i < levels; i++)
		printf("\nLevel %d = %d", i, histogram[i]);

	return 1;
}

double *vc_gray_get_pdf_histogram(IVC *image, unsigned int *histogram)
{
	const unsigned short levels = 256;

	unsigned long pixelCount = image->width * image->height;
	double *pdfHistogram = (double *)(calloc(levels, sizeof(double)));
	unsigned int i;

	for (i = 0; i < levels; i++)
		pdfHistogram[i] = (double)histogram[i] / pixelCount;

	return pdfHistogram;
}

double vc_gray_get_pdf_histogram_max(double *pdfHistogram)
{
	const unsigned int levels = 256;

	unsigned int i;
	double max = 0;

	for (i = 0; i < levels; i++)
		if (pdfHistogram[i] > max)
			max = pdfHistogram[i];

	return max;
}

int vc_gray_print_pdf_histogram(double *pdfHistogram)
{
	const unsigned int levels = 256;

	unsigned int i;

	for (i = 0; i < levels; i++)
		printf("\nLevel %d = %lf%", i, pdfHistogram[i]);

	return 1;
}

#pragma endregion

#pragma region Drawing

int vc_draw_horizontal_line_binary(IVC *image, int offset)
{
	int i, position, xMax = image->width, verticalCenter;

	verticalCenter = image->height / 2 + offset;

	for (i = 0; i < xMax; i++)
	{
		position = (verticalCenter * image->bytesperline) + (i * image->channels);

		if (image->data[position] == 0)
			image->data[position] = 255;
		else
			image->data[position] = 0;
	}

	return 1;
}

int vc_draw_horizontal_line_bgr(IplImage *originalImage, int offset)
{
	int i, position, xMax = originalImage->width, verticalCenter;

	if ((originalImage->width <= 0) || (originalImage->height <= 0) || (originalImage->imageData == NULL))
		return 0;
	if (originalImage->nChannels != 3)
		return 0;

	verticalCenter = originalImage->height / 2 + offset;

	for (i = 0; i < xMax; i++)
	{
		position = (verticalCenter * originalImage->widthStep) + (i * originalImage->nChannels);

		originalImage->imageData[position] = 255;
		originalImage->imageData[position + 1] = 0;
		originalImage->imageData[position + 2] = 0;
	}

	return 1;
}

#pragma endregion

#pragma region Allocation, freeing and persistence

IVC *vc_image_new(int width, int height, int channels, int levels)
{
	IVC *image = (IVC *)malloc(sizeof(IVC));

	if (image == NULL)
		return NULL;
	if ((levels <= 0) || (levels > 255))
		return NULL;

	image->width = width;
	image->height = height;
	image->channels = channels;
	image->levels = levels;
	image->bytesperline = image->width * image->channels;
	image->data = (unsigned char *)malloc(image->width * image->height * image->channels * sizeof(char));

	if (image->data == NULL)
		return vc_image_free(image);

	return image;
}

IVC *vc_image_free(IVC *image)
{
	if (image != NULL)
	{
		if (image->data != NULL)
		{
			free(image->data);
			image->data = NULL;
		}

		free(image);
		image = NULL;
	}

	return image;
}

char *netpbm_get_token(FILE *file, char *tok, int len)
{
	char *t;
	int c;

	for (;;)
	{
		while (isspace(c = getc(file)))
			;

		if (c != '#')
			break;

		do
			c = getc(file);
		while ((c != '\n') && (c != EOF));

		if (c == EOF)
			break;
	}

	t = tok;

	if (c != EOF)
	{
		do
		{
			*t++ = c;
			c = getc(file);

		} while ((!isspace(c)) && (c != '#') && (c != EOF) && (t - tok < len - 1));

		if (c == '#')
			ungetc(c, file);
	}

	*t = 0;

	return tok;
}

long int unsigned_char_to_bit(unsigned char *datauchar, unsigned char *databit, int width, int height)
{
	int x, y;
	int countbits;
	long int pos, counttotalbytes;
	unsigned char *p = databit;

	*p = 0;
	countbits = 1;
	counttotalbytes = 0;

	for (y = 0; y < height; y++)
	{
		for (x = 0; x < width; x++)
		{
			pos = width * y + x;

			if (countbits <= 8)
			{
				*p |= (datauchar[pos] == 0) << (8 - countbits);
				countbits++;
			}
			if ((countbits > 8) || (x == width - 1))
			{
				p++;
				*p = 0;
				countbits = 1;
				counttotalbytes++;
			}
		}
	}

	return counttotalbytes;
}

void bit_to_unsigned_char(unsigned char *databit, unsigned char *datauchar, int width, int height)
{
	int x, y;
	int countbits;
	long int pos;
	unsigned char *p = databit;

	countbits = 1;

	for (y = 0; y < height; y++)
	{
		for (x = 0; x < width; x++)
		{
			pos = width * y + x;

			if (countbits <= 8)
			{
				datauchar[pos] = (*p & (1 << (8 - countbits))) ? 0 : 1;
				countbits++;
			}
			if ((countbits > 8) || (x == width - 1))
			{
				p++;
				countbits = 1;
			}
		}
	}
}

IVC *vc_read_image(char *filename)
{
	FILE *file = NULL;
	IVC *image = NULL;
	unsigned char *tmp;
	char tok[20];
	long int size, sizeofbinarydata;
	int width, height, channels;
	int levels = 255;
	int v;

	if ((file = fopen(filename, "rb")) != NULL)
	{
		netpbm_get_token(file, tok, sizeof(tok));

		if (strcmp(tok, "P4") == 0)
		{
			channels = 1;
			levels = 1;
		}
		else if (strcmp(tok, "P5") == 0)
			channels = 1;
		else if (strcmp(tok, "P6") == 0)
			channels = 3;
		else
		{
#ifdef VC_DEBUG
			printf("The PBM, PGM or PPM file isn't valid.\n");
#endif

			fclose(file);
			return NULL;
		}

		if (levels == 1)
		{
			if (sscanf(netpbm_get_token(file, tok, sizeof(tok)), "%d", &width) != 1 || sscanf(netpbm_get_token(file, tok, sizeof(tok)), "%d", &height) != 1)
			{
#ifdef VC_DEBUG
				printf("The PBM file isn't valid.\n");
#endif

				fclose(file);
				return NULL;
			}

			image = vc_image_new(width, height, channels, levels);

			if (image == NULL)
				return NULL;

			sizeofbinarydata = (image->width / 8 + ((image->width % 8) ? 1 : 0)) * image->height;
			tmp = (unsigned char *)malloc(sizeofbinarydata);

			if (tmp == NULL)
				return 0;

			if ((v = fread(tmp, sizeof(unsigned char), sizeofbinarydata, file)) != sizeofbinarydata)
			{
#ifdef VC_DEBUG
				printf("Premature file EOF.\n");
#endif

				vc_image_free(image);
				fclose(file);
				free(tmp);
				return NULL;
			}

			bit_to_unsigned_char(tmp, image->data, image->width, image->height);
			free(tmp);
		}
		else
		{
			if (sscanf(netpbm_get_token(file, tok, sizeof(tok)), "%d", &width) != 1 || sscanf(netpbm_get_token(file, tok, sizeof(tok)), "%d", &height) != 1 || sscanf(netpbm_get_token(file, tok, sizeof(tok)), "%d", &levels) != 1 || levels <= 0 || levels > 255)
			{
#ifdef VC_DEBUG
				printf("The PGM or PPM file isn't valid.\n");
#endif

				fclose(file);
				return NULL;
			}

			image = vc_image_new(width, height, channels, levels);
			if (image == NULL)
				return NULL;

			size = image->width * image->height * image->channels;

			if ((v = fread(image->data, sizeof(unsigned char), size, file)) != size)
			{
#ifdef VC_DEBUG
				printf("Premature file EOF.\n");
#endif

				vc_image_free(image);
				fclose(file);
				return NULL;
			}
		}

		fclose(file);
	}

	return image;
}

int vc_write_image(char *filename, IVC *image)
{
	FILE *file = NULL;
	unsigned char *tmp;
	long int totalbytes, sizeofbinarydata;

	if (image == NULL)
		return 0;

	if ((file = fopen(filename, "wb")) != NULL)
	{
		if (image->levels == 1)
		{
			sizeofbinarydata = (image->width / 8 + ((image->width % 8) ? 1 : 0)) * image->height + 1;
			tmp = (unsigned char *)malloc(sizeofbinarydata);

			if (tmp == NULL)
				return 0;

			fprintf(file, "%s %d %d\n", "P4", image->width, image->height);
			totalbytes = unsigned_char_to_bit(image->data, tmp, image->width, image->height);

			if (fwrite(tmp, sizeof(unsigned char), totalbytes, file) != totalbytes)
			{

#ifdef VC_DEBUG
				fprintf(stderr, "ERROR -> vc_read_image():\n\tError writing PBM, PGM or PPM file.\n");
#endif

				fclose(file);
				free(tmp);
				return 0;
			}

			free(tmp);
		}
		else
		{
			fprintf(file, "%s %d %d 255\n", (image->channels == 1) ? "P5" : "P6", image->width, image->height);

			if (fwrite(image->data, image->bytesperline, image->height, file) != image->height)
			{
#ifdef VC_DEBUG
				fprintf(stderr, "ERROR -> vc_read_image():\n\tError writing PBM, PGM or PPM file.\n");
#endif

				fclose(file);
				return 0;
			}
		}

		fclose(file);
		return 1;
	}

	return 0;
}

#pragma endregion
