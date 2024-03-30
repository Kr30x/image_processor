# Image_processor

This project contains a console application for processing images.

## Supported filetypes

Input and output images are in the [BMP](http://en.wikipedia.org/wiki/BMP_file_format) file format.

BMP is using `DIB header` - `BITMAPINFOHEADER`.

There is an example [here (Example_1)](https://en.wikipedia.org/wiki/BMP_file_format#Example_1)
and [here (test_script/data)](test_script/data).

## Usage

`{./image_processor} {input filepath} {output filepath}
[-{filter name 1} [filter param 1] [filter param 2] ...]
[-{filter name 2} [filter param 1] [filter param 2] ...] ...`

If no params given, app returns schema of usage.

### Example
`./image_processor input.bmp /tmp/output.bmp -crop 800 600 -gs -blur 0.5`

In this example:
1. Image is loaded from `input.bmp`.
2. Image is cropped to 800х600 pixels, counting from top-left.
3. Image is converted to grayscale.
4. Blur with sigma 0.5 is applied.
5. Output image is saved in `/tmp/output.bmp`

If no filters are given, app saves input image to output filepath.

## Supported filters

#### Crop (-crop width height)

Crops image to given width and height, counting from top-left.

If widht of height is greater than source image width and height, image is cropped to available area.

![](https://github.com/Kr30x/image_processor/blob/main/test_script/data/lenna_crop.bmp?raw=true)
#### Grayscale (-gs)

Converts image to grayscale.

![](https://github.com/Kr30x/image_processor/blob/main/test_script/data/lenna_gs.bmp?raw=true)
#### Negative (-neg)

Converts image to its Negative.

![](https://github.com/Kr30x/image_processor/blob/main/test_script/data/lenna_neg.bmp?raw=true)
#### Sharpening (-sharp)

Sharpens image. 

![](https://github.com/Kr30x/image_processor/blob/main/test_script/data/lenna_sharp.bmp?raw=true)

![](https://github.com/Kr30x/image_processor/blob/main/test_script/data/lenna_sharp_sharp.bmp?raw=true)
#### Edge Detection (-edge threshold)

Detects edges in image. Image is converted to grayscale, than threshold is applied.

Pixels with value greater than threshold become white, other become black. 
![](https://github.com/Kr30x/image_processor/blob/main/test_script/data/lenna_edge.bmp?raw=true)
#### Gaussian Blur (-blur sigma)
[Gaussian blur](https://ru.wikipedia.org/wiki/Размытие_по_Гауссу),
param – sigma.

![](https://github.com/Kr30x/image_processor/blob/main/test_script/data/lenna_blur.bmp?raw=true)
#### Flash (-flash x y radius brightness min_brightness angle (yet not supported, can be any integer))

Draws flash on image in position (x, y) counting from bottom-right with given radius and brightness. All pixels with brightness lower than min_brightness become black. 

![](https://github.com/Kr30x/image_processor/blob/main/test_script/data/lenna_flash.bmp?raw=true)
