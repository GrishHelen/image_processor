## Educational project (HSE, Faculty of CS, AMI, C++ course)

This is a console application to edit photos with various filters.

### Available filters:

Crop <span style="color:#46b210">-crop</span> <span style="color:rgb(150,100,255)">width height</span> 
*Crops the image to the given size. The upper left part of the image is used.*

Grayscale <span style="color:#46b210">-gs</span> 
*Converts the image to grayscale*

Negative <span style="color:#46b210">-neg</span> 
*Converts the image to a negative*

Sharpening <span style="color:#46b210">-sharp</span> 
*Increases the sharpness of the image*

Edge Detection <span style="color:#46b210">-edge</span> <span style="color:rgb(150,100,255)">threshold</span>
*Highlights the borders of the image*

Gaussian Blur <span style="color:#46b210">-blur</span> <span style="color:rgb(150,100,255)">sigma</span> 
*Applies Gaussian blur to the image with sigma parameter*

Anaglyph <span style="color:#46b210">-anaglyph</span> 
*Makes the effect of using 3d-glasses*

Merge_Images <span style="color:#46b210">-merge</span> <span style="color:rgb(150,100,255)">other_path</span> 
*Merges two images together*

### Usage

<u>To use the application, enter the parameters in the following way:</u>
./src/image_processor <span style="color:rgb(0,153,204)">{path to the input file} {path to the
output file}</span>
[-{<span style="color:#46b210">filter_1 name</span>
} [<span style="color:rgb(150,100,255)">arguments for filter_1</span>]]
[-{<span style="color:#46b210">filter_2
name</span>} [<span style="color:rgb(150,100,255)">arguments for filter_2</span>]] ...


<u>Example of usage:</u>
./image_processor input.bmp /tmp/output.bmp -crop 800 600 -gs -blur 0.5
