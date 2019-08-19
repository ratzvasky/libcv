/*
    Computer Vision coursework
    Licentiate degree in Computer Systems Engineering 2016/2017
    Ivo Gomes - a10700@alunos.ipca.pt, Rúben Guimarães - a11156@alunos.ipca.pt
*/

#define VC_DEBUG

typedef struct 
{
	unsigned char *data;
	int width, height;
	int channels;					
	int levels;						
	int bytesperline;		
} IVC;

typedef struct 
{	
	int x, y, width, height;		 
	int area;						 
	int xc, yc;						 
	int perimeter;					 
	int label;	
} OVC;

typedef struct verifiedBlob 
{	
	unsigned int index;				
	const char *tipology;			
	int area;					    
	int perimeter;					
	struct verifiedBlob *next;	
} *verifiedBlobList;

// Allocation, freeing and persistence
IVC *vc_image_new(int width, int height, int channels, int levels);
IVC *vc_image_free(IVC *image);
IVC *vc_read_image(char *filename);
int vc_write_image(char *filename, IVC *image);

// Inversions
int vc_gray_negative(IVC *image);
int vc_rgb_negative(IVC *image);

// Extractions
int vc_rgb_bgr_max(unsigned char red, unsigned char green, unsigned char blue);
int vc_rgb_bgr_min(unsigned char red, unsigned char green, unsigned char blue);
int vc_rgb_bgr_get_red_gray(IVC *image);
int vc_rgb_bgr_get_green_gray(IVC *image);
int vc_rgb_bgr_get_blue_gray(IVC *image);
int vc_print_hsv_values(IVC *imagemOriginal);

// Conversions
int vc_rgb_to_gray(IVC *originalImage, IVC *destinationImage);
int vc_scale_gray_to_rgb(IVC *originalImage, IVC *destinationImage);
int vc_rgb_to_hsv(IVC *imagem);
int vc_gray_to_binary(IVC *image, int threshold);
int vc_gray_to_binary_global_mean(IVC *imagem);
int vc_hsv_to_binary_in_range(IVC *imagemOriginal, IVC *imagemDestino, unsigned short rangeCor);
int vc_gray_black_to_white(IVC *image);
int vc_binary_to_rgb(IVC *originalImage, IVC *destinationImage);
int vc_binary_to_bgr(IVC *originalImage, IplImage *destinationImage);
int vc_bgr_to_rgb(IplImage *originalImage, IVC *destinationImage);
int vc_rgb_to_bgr(IVC *originalImage, IplImage *destinationImage);

// Erosion and dilation
int vc_binary_dilate(IVC *originalImage, IVC *destinationImage, int kernelSize);
int vc_binary_erode(IVC *originalImage, IVC *destinationImage, int kernelSize);

// Open/close operations
int vc_binary_open(IVC *originalImage, IVC *destinationImage, int erodeSize, int dilateSize);
int vc_binary_close(IVC *originalImage, IVC *destinationImage, int erodeSize, int dilateSize);

// Blobs and labeling
OVC* vc_binary_blob_labelling(IVC *src, IVC *dst, int *nlabels);
int vc_binary_blob_info(IVC *src, OVC *blobs, int nblobs);
int vc_print_blobs_info(OVC *blobs, int blobNumber);
int vc_print_blob_info(OVC *blob, int indiceBlob);
int vc_get_blob_label_max_area(OVC *blobs, int blobNumber);
int vc_draw_blob_boundary_box_rgb(IVC *image, int x, int y, int width, int height);
int vc_draw_blob_boundary_box_binary(IVC *image, int x, int y, int xMax, int yMax);
int vc_draw_blob_boundary_box_bgr(IplImage *image, int x, int y, int width, int height);
int vc_gray_compare_segmentation_areas(OVC *redBlobs, int redBlobsNumber, OVC *blueBlobs, int blueBlobsNumber);
int vc_is_blob_inside_interest_blob(OVC *segmentedImageBlobs, int interestBlobLabel, OVC *segmentedInvertedImageBlobs, int invertedBlobLabel);
int vc_count_blobs_inside_interest_blob(OVC *segmentedImageBlobs, int interestBlobLabel, OVC *segmentedInvertedImageBlobs, int invertedBlobsNumber);
int vc_isolate_interest_blob(IVC *segmentedInvertedImage, OVC *segmentedInvertedImageBlobs, int segmentedInvertedImageBlobNumber, OVC *segmentedImageBlobs, int segmentedImageInterestBlobLabel);
float vc_get_blob_circularity(int blobArea, int blobPerimeter);
int vc_count_pixel_half_boundary_box_horizontal(IVC *image, OVC *blobList, int interestBlobLabel, int *upPixels, int *downPixels);
int vc_count_pixel_half_boundary_box_vertical(IVC *image, OVC *blobList, int interestBlobLabel, int *leftPixels, int *rightPixels);
int vc_get_bigger_boundary_box_side(int upPixels, int downPixels, int leftPixels, int rightPixels);
int vc_get_verified_blob_state(verifiedBlobList list, int index, int area, int pixelTolerance);
verifiedBlobList vc_add_verified_blob(verifiedBlobList list, int index, int area, int perimeter, const char* tipologia);
unsigned int vc_count_verified_blobs(verifiedBlobList list);
int vc_print_verified_blob_list(verifiedBlobList list);
int vc_free_verified_blob_list(verifiedBlobList list);
int vc_draw_blob_crosshair(IplImage *image, int blobWidth, int blobHeight, int xCenterMass, int yCenterMass, int crosshairSize, int crossHairColor);
int vc_detect_blob_inside_vertical_area(int height, OVC *blobs, int blobIndex, int offset);
int vc_draw_crosshair_all_blobs(OVC *blobs, int blobNumber, int blobMinimumArea, int crosshairSize, int crossHairColor, IplImage *originalImage);
int vc_conditional_draw_boundary_box_all_blobs(OVC *blobs, int blobNumber, int blobMinimumArea, IplImage *originalImage);

// Histograms
unsigned int *vc_gray_get_histogram(IVC *image);
unsigned int vc_gray_get_histogram_max(unsigned int *histogram);
int vc_gray_print_histogram(unsigned int *histogram);
double *vc_gray_get_pdf_histogram(IVC *image, unsigned int *histogram);
double vc_gray_get_pdf_histogram_max(double *pdfHistogram);
int vc_gray_print_pdf_histogram(double *pdfHistogram);

// Drawing
int vc_draw_horizontal_line_binary(IVC *image, int offset);
int vc_draw_horizontal_line_bgr(IplImage *originalImage, int offset);
