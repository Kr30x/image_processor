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

#### Grayscale (-gs)

Converts image to grayscale.

#### Negative (-neg)

Converts image to its Negative.

#### Sharpening (-sharp)

Sharpens image. 

#### Edge Detection (-edge threshold)

Detects edges in image. Image is converted to grayscale, than threshold is applied.

Pixels with value greater than threshold become white, other become black. 

#### Gaussian Blur (-blur sigma)
[Гауссово размытие](https://ru.wikipedia.org/wiki/Размытие_по_Гауссу),
param – sigma.

#### Flash (-flash x y radius brightness min_brightness angle (yet not supported, can be any integer))

Draws flash on image in position (x, y) counting from bottom-right with given radius and brightness. All pixels with brightness lower than min_brightness become black. 
