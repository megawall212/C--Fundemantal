#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
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

int main() {
    string path = "input/car.tga";
    Image image = ReadTGA(path);
    string outputFilename = "output/task1.tga";
    Writefile(image, outputFilename);
    cout << "Finished!:C" << endl;

    Task1();
    Task2();
    Task3();
    Task4();
    Task5();
    Task6();
    Task7();
    Task8();
    Task9();
    Task10();

    cout << "Finished!:C" << endl;

    return 0;
}