#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>


//additional libraries:

#include <vector>
#include <string>
#include <sstream>
#include <stdexcept>

using namespace std;


//code provided

struct Header {
    char idLength;
    char colorMapType;
    char dataTypeCode;
    short colorMapOrigin;
    short colorMapLength;
    char colorMapDepth;
    short xOrigin;
    short yOrigin;
    short width;
    short height;
    char bitsPerPixel;
    char imageDescriptor;
};

struct Pixel {
    unsigned char BLUE;
    unsigned char GREEN;
    unsigned char RED;
};

struct Image {
    Header header;
    vector<Pixel> pixeldata;
};

Image ReadTGA(const string &filename) {
    ifstream file(filename, ios::binary);
    Image image;

    if (!file.is_open()) {
        cerr << "Unable to open file " << filename << " not found" << endl;
        return image; // return those image that fails
    }

    Header header;




    file.read(reinterpret_cast<char *>(&header.idLength), sizeof(header.idLength));
    file.read(reinterpret_cast<char *>(&header.colorMapType), sizeof(header.colorMapType));
    file.read(reinterpret_cast<char *>(&header.dataTypeCode), sizeof(header.dataTypeCode));
    file.read(reinterpret_cast<char *>(&header.colorMapOrigin), sizeof(header.colorMapOrigin));
    file.read(reinterpret_cast<char *>(&header.colorMapLength), sizeof(header.colorMapLength));
    file.read(reinterpret_cast<char *>(&header.colorMapDepth), sizeof(header.colorMapDepth));
    file.read(reinterpret_cast<char *>(&header.xOrigin), sizeof(header.xOrigin));
    file.read(reinterpret_cast<char *>(&header.yOrigin), sizeof(header.yOrigin));
    file.read(reinterpret_cast<char *>(&header.width), sizeof(header.width));
    file.read(reinterpret_cast<char *>(&header.height), sizeof(header.height));
    file.read(reinterpret_cast<char *>(&header.bitsPerPixel), sizeof(header.bitsPerPixel));
    file.read(reinterpret_cast<char *>(&header.imageDescriptor), sizeof(header.imageDescriptor));

    image.header = header;

    // Check for valid width and height
    if (header.width <= 0 || header.height <= 0) {
        cerr << "Image is empty! Wrong dimensions!" << endl;
        return image;
    }

    int pixelCount = header.width * header.height;
    image.pixeldata.resize(pixelCount); // We need to resize vector to expected size

    // Read pixel data in BGR order ( NOT RGB order!)
    for (int i = 0; i < pixelCount; i++) {
        file.read(reinterpret_cast<char *>(&image.pixeldata[i].BLUE), sizeof(image.pixeldata[i].BLUE));
        file.read(reinterpret_cast<char *>(&image.pixeldata[i].GREEN), sizeof(image.pixeldata[i].GREEN));
        file.read(reinterpret_cast<char *>(&image.pixeldata[i].RED), sizeof(image.pixeldata[i].RED));
    }

    file.close();
    return image;
}
void Writefile(Image image, const string &outputFilename) {
    ofstream outputfile(outputFilename, ios::binary);

    if (!outputfile.is_open()) {
        cout << "Unable to open file " << outputFilename << endl;
        return;
    }

    // Write header
    outputfile.write(reinterpret_cast<char *>(&image.header.idLength), sizeof(image.header.idLength));
    outputfile.write(reinterpret_cast<char *>(&image.header.colorMapType), sizeof(image.header.colorMapType));
    outputfile.write(reinterpret_cast<char *>(&image.header.dataTypeCode), sizeof(image.header.dataTypeCode));
    outputfile.write(reinterpret_cast<char *>(&image.header.colorMapOrigin), sizeof(image.header.colorMapOrigin));
    outputfile.write(reinterpret_cast<char *>(&image.header.colorMapLength), sizeof(image.header.colorMapLength));
    outputfile.write(reinterpret_cast<char *>(&image.header.colorMapDepth), sizeof(image.header.colorMapDepth));
    outputfile.write(reinterpret_cast<char *>(&image.header.xOrigin), sizeof(image.header.xOrigin));
    outputfile.write(reinterpret_cast<char *>(&image.header.yOrigin), sizeof(image.header.yOrigin));
    outputfile.write(reinterpret_cast<char *>(&image.header.width), sizeof(image.header.width));
    outputfile.write(reinterpret_cast<char *>(&image.header.height), sizeof(image.header.height));
    outputfile.write(reinterpret_cast<char *>(&image.header.bitsPerPixel), sizeof(image.header.bitsPerPixel));
    outputfile.write(reinterpret_cast<char *>(&image.header.imageDescriptor), sizeof(image.header.imageDescriptor));

    // Write pixel data in BGR order (Blue, Green, Red)
    for (int i = 0; i < (image.header.width * image.header.height); i++) {
        outputfile.write(reinterpret_cast<char *>(&image.pixeldata[i].BLUE), sizeof(image.pixeldata[i].BLUE));
        outputfile.write(reinterpret_cast<char *>(&image.pixeldata[i].GREEN), sizeof(image.pixeldata[i].GREEN));
        outputfile.write(reinterpret_cast<char *>(&image.pixeldata[i].RED), sizeof(image.pixeldata[i].RED));
    }

    outputfile.close();
}


unsigned char clamp(int value) {
    // make sure the value is between 0 and 255
    return static_cast<unsigned char>(std::max(0, std::min(255, value)));
    // or do it in a normal way:
    /*
    unsigned char clamp(int value) {
    if (value < 0) {
        return 0;
    } else if (value > 255) {
        return 255;
    } else {
        return static_cast<unsigned char>(value);
    }
}
     */

}

Image Multiply(const Image& image1, const Image& image2) {
    Image result = image1;
    for (size_t i = 0; i < result.pixeldata.size(); i++) {
        // Use integer arithmetic with rounding (very important ...)
        //combine two images by multiplying their pixel values.
        //With +127, we get round-to-nearest:
        //also use the clamp function for each one
        result.pixeldata[i].BLUE = clamp((image1.pixeldata[i].BLUE * image2.pixeldata[i].BLUE + 127) / 255);
        result.pixeldata[i].GREEN = clamp((image1.pixeldata[i].GREEN * image2.pixeldata[i].GREEN + 127) / 255);
        result.pixeldata[i].RED = clamp((image1.pixeldata[i].RED * image2.pixeldata[i].RED + 127) / 255);
    }
    return result;
}

Image Screen(const Image& image1, const Image& image2) {
      //brightens the image by combining inverted pixel values.
    Image result = image1;
    for (size_t i = 0; i < result.pixeldata.size(); i++) {
        // Calculate screen effect for BGR (BLUE, GREEN, RED)
        auto screenFunc = [](unsigned char a, unsigned char b) -> unsigned char {
            // Convert to float for precision ( 0 to 1)
            float fa = a / 255.0f, fb = b / 255.0f;
            // Screen blending (multiply them together) formula
            float result = 1.0f - (1.0f - fa) * (1.0f - fb);
            // Convert back to [0, 255] range and round the result before clamping
            return clamp(static_cast<int>(255 * result + 0.5f)); // Adding 0.5 for proper rounding
        };

        result.pixeldata[i].BLUE = screenFunc(image1.pixeldata[i].BLUE, image2.pixeldata[i].BLUE);
        result.pixeldata[i].GREEN = screenFunc(image1.pixeldata[i].GREEN, image2.pixeldata[i].GREEN);
        result.pixeldata[i].RED = screenFunc(image1.pixeldata[i].RED, image2.pixeldata[i].RED);
    }
    return result;
}



Image Subtract(const Image& image1, const Image& image2) {
    Image result = image1;
    for (size_t i = 0; i < result.pixeldata.size(); i++) {
        // Clamping the result
        result.pixeldata[i].BLUE = clamp(image1.pixeldata[i].BLUE - image2.pixeldata[i].BLUE);
        result.pixeldata[i].GREEN = clamp(image1.pixeldata[i].GREEN - image2.pixeldata[i].GREEN);
        result.pixeldata[i].RED = clamp(image1.pixeldata[i].RED - image2.pixeldata[i].RED);
    }
    return result;
}

Image Addition(const Image& image1, const Image& image2) {
    Image result = image1;
    for (size_t i = 0; i < result.pixeldata.size(); i++) {
        // Clamping the result
        result.pixeldata[i].BLUE = clamp(image1.pixeldata[i].BLUE + image2.pixeldata[i].BLUE);
        result.pixeldata[i].GREEN = clamp(image1.pixeldata[i].GREEN + image2.pixeldata[i].GREEN);
        result.pixeldata[i].RED = clamp(image1.pixeldata[i].RED + image2.pixeldata[i].RED);
    }
    return result;
}

Image Overlay(const Image& image1, const Image& image2) {
    Image result = image1;
    for (size_t i = 0; i < result.pixeldata.size(); i++) {

      //lambda  function
        auto overlayFunc = [](unsigned char a, unsigned char b) -> unsigned char {
            // convert it back to the integer range (0 to 1)
            float fa = a / 255.0f, fb = b / 255.0f;
            // proper rounding
            float result = fb <= 0.5f ? (2 * fa * fb) : (1 - 2 * (1 - fa) * (1 - fb));
            return clamp(static_cast<int>(round(result * 255))); // put it back to 0-255
        };

        result.pixeldata[i].BLUE = overlayFunc(image1.pixeldata[i].BLUE, image2.pixeldata[i].BLUE);
        result.pixeldata[i].GREEN = overlayFunc(image1.pixeldata[i].GREEN, image2.pixeldata[i].GREEN);
        result.pixeldata[i].RED = overlayFunc(image1.pixeldata[i].RED, image2.pixeldata[i].RED);
    }
    return result;
}

void Task1() {
    Image layer1 = ReadTGA("input/layer1.tga");
    Image pattern1 = ReadTGA("input/pattern1.tga");
    Writefile(Multiply(layer1, pattern1), "output/part1.tga");
}

void Task2() {
    Image car = ReadTGA("input/car.tga");
    Image layer2 = ReadTGA("input/layer2.tga");
    Writefile(Subtract(car, layer2), "output/part2.tga");
}

void Task3() {
    Image layer1 = ReadTGA("input/layer1.tga");
    Image pattern2 = ReadTGA("input/pattern2.tga");
    Image temp = Multiply(layer1, pattern2);
    Image text = ReadTGA("input/text.tga");
    Writefile(Screen(temp, text), "output/part3.tga");
}

void Task4() {
    Image layer2 = ReadTGA("input/layer2.tga");
    Image circles = ReadTGA("input/circles.tga");
    Image temp = Multiply(layer2, circles);
    Image pattern2 = ReadTGA("input/pattern2.tga");
    Writefile(Subtract(temp, pattern2), "output/part4.tga");
}

void Task5() {
    Image layer1 = ReadTGA("input/layer1.tga");
    Image pattern1 = ReadTGA("input/pattern1.tga");
    Writefile(Overlay(layer1, pattern1), "output/part5.tga");
}

void Task6() {
    Image car = ReadTGA("input/car.tga");
    for (auto& pixel : car.pixeldata) {
        pixel.GREEN = clamp(pixel.GREEN + 200);
    }
    Writefile(car, "output/part6.tga");
}

void Task7() {
    Image car = ReadTGA("input/car.tga");
    for (auto& pixel : car.pixeldata) {
        pixel.RED = clamp(pixel.RED * 4);
        pixel.BLUE = clamp(pixel.BLUE * 0);
    }
    Writefile(car, "output/part7.tga");
}

void Task8() {
    Image car = ReadTGA("input/car.tga");

    // Create separate copies of the image for each channel
    Image redChannel = car;
    Image greenChannel = car;
    Image blueChannel = car;

    for (size_t i = 0; i < car.pixeldata.size(); i++) {
        // Set each channel while keeping grayscale representation
        redChannel.pixeldata[i] = {car.pixeldata[i].RED, car.pixeldata[i].RED, car.pixeldata[i].RED}; // Keep only RED
        greenChannel.pixeldata[i] = {car.pixeldata[i].GREEN, car.pixeldata[i].GREEN, car.pixeldata[i].GREEN}; // Keep only GREEN
        blueChannel.pixeldata[i] = {car.pixeldata[i].BLUE, car.pixeldata[i].BLUE, car.pixeldata[i].BLUE}; // Keep only BLUE
    }

    // Write the modified channels to separate files
    Writefile(redChannel, "output/part8_r.tga");
    Writefile(greenChannel, "output/part8_g.tga");
    Writefile(blueChannel, "output/part8_b.tga");
}





void Task9() {
    Image layerRed = ReadTGA("input/layer_red.tga");
    Image layerGreen = ReadTGA("input/layer_green.tga");
    Image layerBlue = ReadTGA("input/layer_blue.tga");

    Image result = layerRed;
    for (size_t i = 0; i < result.pixeldata.size(); ++i) {
        result.pixeldata[i].GREEN = layerGreen.pixeldata[i].GREEN;
        result.pixeldata[i].BLUE = layerBlue.pixeldata[i].BLUE;
    }

    Writefile(result, "output/part9.tga");
}

void Task10() {
    Image text2 = ReadTGA("input/text2.tga");
    Image result = text2;
    std::reverse(result.pixeldata.begin(), result.pixeldata.end());
    Writefile(result, "output/part10.tga");
}



// ===== Here are the new CLI helper function =====
// follow the instruction
void PrintHelp() {
    cout << "Project 2: Image Processing, Spring 2025" << endl;
    cout << endl;  // Add this empty line
    cout << "Usage:" << endl;
    cout << "\t./project2.out [output] [firstImage] [method] [...]" << endl;
}


//check if file ends with tga, also the length of that file name


bool IsValidFilename(const string& filename) {
    if (filename.length() < 4) return false;
    return filename.substr(filename.length() - 4) == ".tga";
}

//now we need to parse a string argument into an integer and throws error if invalid

int ParseIntArg(const string& arg) {
    try {
        // stoi: convert string to int
        return stoi(arg);
    } catch (const invalid_argument&) {
        throw runtime_error("Invalid argument, expected number.");
    } catch (const out_of_range&) {
        throw runtime_error("Invalid argument, expected number.");
    }
}

// ===== NEW MAIN FUNCTION FOR CLI =====

// main


int main(int argc, char* argv[]) {

    // If no arguments or help flag is passed, just print the help message
    if (argc == 1 || (argc == 2 && string(argv[1]) == "--help")) {
        PrintHelp();
        return 0;
    }

    try {
        // Check minimum arguments (output and input file)
        // Must have at least both output file and input file
        if (argc < 3) {
            throw runtime_error("Invalid file name.");
        }

        string outputFilename = argv[1];
        string inputFilename = argv[2];

        // Validate filenames:
        // Now check both filenames are valid .tga files
        if (!IsValidFilename(outputFilename)) {
            throw runtime_error("Invalid file name.");
        }
        if (!IsValidFilename(inputFilename)) {
            throw runtime_error("Invalid file name.");
        }

        // Load the initial image (tracking image)
        // The image will be modified throughout the process
        Image trackingImage = ReadTGA(inputFilename);
        if (trackingImage.pixeldata.empty()) {
            throw runtime_error("File does not exist.");
        }

        // Process commands starting from argv[3]
        // now we need to loop through the rest of the arguments
        // And apply operations we did before

        //start at index 3
        for (int i = 3; i < argc; i++) {
            string command = argv[i];

            // load another image

            if (command == "multiply") {
                //missing another image
                if (i + 1 >= argc) throw runtime_error("Missing argument.");
                string secondImage = argv[++i]; //move to the next image
                if (!IsValidFilename(secondImage)) throw runtime_error("Invalid argument, invalid file name.");

                Image otherImage = ReadTGA(secondImage); //load the second image
                if (otherImage.pixeldata.empty()) throw runtime_error("Invalid argument, file does not exist.");

                trackingImage = Multiply(trackingImage, otherImage);
            }

            // apply it to trackimage
            //trackimage holds the current version of image after each operation we do
            //it stores stuff

            else if (command == "subtract") {
                if (i + 1 >= argc) throw runtime_error("Missing argument.");
                string secondImage = argv[++i];
                if (!IsValidFilename(secondImage)) throw runtime_error("Invalid argument, invalid file name.");

                Image otherImage = ReadTGA(secondImage);
                if (otherImage.pixeldata.empty()) throw runtime_error("Invalid argument, file does not exist.");

                trackingImage = Subtract(trackingImage, otherImage);
            }
            else if (command == "overlay") {
                if (i + 1 >= argc) throw runtime_error("Missing argument.");
                string secondImage = argv[++i];
                if (!IsValidFilename(secondImage)) throw runtime_error("Invalid argument, invalid file name.");

                Image otherImage = ReadTGA(secondImage);
                if (otherImage.pixeldata.empty()) throw runtime_error("Invalid argument, file does not exist.");

                trackingImage = Overlay(trackingImage, otherImage);
            }
            else if (command == "screen") {
                if (i + 1 >= argc) throw runtime_error("Missing argument.");
                string secondImage = argv[++i];
                if (!IsValidFilename(secondImage)) throw runtime_error("Invalid argument, invalid file name.");

                Image otherImage = ReadTGA(secondImage);
                if (otherImage.pixeldata.empty()) throw runtime_error("Invalid argument, file does not exist.");

                trackingImage = Screen(otherImage, trackingImage); // Note: order is reversed for screen
            }


            // combine the BGR/RGB channels for 3 different images



            else if (command == "combine") {
                if (i + 2 >= argc) throw runtime_error("Missing argument.");
                string greenImage = argv[++i];
                string blueImage = argv[++i];
                if (!IsValidFilename(greenImage) || !IsValidFilename(blueImage)) {
                    throw runtime_error("Invalid argument, invalid file name.");
                }

                Image green = ReadTGA(greenImage);
                Image blue = ReadTGA(blueImage);
                if (green.pixeldata.empty() || blue.pixeldata.empty()) {
                    throw runtime_error("Invalid argument, file does not exist.");
                }

                // Implement combine similar to Task9
                // but this time we need to replace the green and blue channel
                // from green/blue images into trackingImage

                for (size_t j = 0; j < trackingImage.pixeldata.size(); ++j) {
                    trackingImage.pixeldata[j].GREEN = green.pixeldata[j].GREEN;
                    trackingImage.pixeldata[j].BLUE = blue.pixeldata[j].BLUE;
                }
            }
            else if (command == "flip") {
                // then we flip the image vertically
                std::reverse(trackingImage.pixeldata.begin(), trackingImage.pixeldata.end());
            }
            else if (command == "onlyred") {
                for (auto& pixel : trackingImage.pixeldata) {

                    // then we only keep the red channel
                    // and copy it to all channels

                    pixel = {pixel.RED, pixel.RED, pixel.RED};
                }
            }
            else if (command == "onlygreen") {
                for (auto& pixel : trackingImage.pixeldata) {
                    pixel = {pixel.GREEN, pixel.GREEN, pixel.GREEN};
                }
            }
            else if (command == "onlyblue") {
                for (auto& pixel : trackingImage.pixeldata) {
                    pixel = {pixel.BLUE, pixel.BLUE, pixel.BLUE};
                }
            }
            else if (command == "addred") {
                if (i + 1 >= argc) throw runtime_error("Missing argument.");
                int value = ParseIntArg(argv[++i]);

                for (auto& pixel : trackingImage.pixeldata) {
                    pixel.RED = clamp(pixel.RED + value);
                }
            }
            else if (command == "addgreen") {
                if (i + 1 >= argc) throw runtime_error("Missing argument.");
                int value = ParseIntArg(argv[++i]);

                for (auto& pixel : trackingImage.pixeldata) {
                    pixel.GREEN = clamp(pixel.GREEN + value);
                }
            }
            else if (command == "addblue") {
                if (i + 1 >= argc) throw runtime_error("Missing argument.");
                int value = ParseIntArg(argv[++i]);

                for (auto& pixel : trackingImage.pixeldata) {
                    pixel.BLUE = clamp(pixel.BLUE + value);
                }
            }
            else if (command == "scalered") {
                if (i + 1 >= argc) throw runtime_error("Missing argument.");
                int value = ParseIntArg(argv[++i]);

                for (auto& pixel : trackingImage.pixeldata) {
                    pixel.RED = clamp(pixel.RED * value);
                }
            }
            else if (command == "scalegreen") {
                if (i + 1 >= argc) throw runtime_error("Missing argument.");
                int value = ParseIntArg(argv[++i]);

                for (auto& pixel : trackingImage.pixeldata) {
                    pixel.GREEN = clamp(pixel.GREEN * value);
                }
            }
            else if (command == "scaleblue") {
                if (i + 1 >= argc) throw runtime_error("Missing argument.");
                int value = ParseIntArg(argv[++i]);

                for (auto& pixel : trackingImage.pixeldata) {
                    pixel.BLUE = clamp(pixel.BLUE * value);
                }
            }
            else {
                throw runtime_error("Invalid method name.");
            }
        }

        // Write  and save our final result

        Writefile(trackingImage, outputFilename);

    } catch (const exception& e) {

        // print the error message from exception

        cerr << e.what() << endl;
        return 1;
    }

    return 0;
}