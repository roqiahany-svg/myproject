#include <iostream>
#include "Image_Class.h"
using namespace std;
Image image;
string filename;
void Black_White(Image& img) {
    for (int i = 0; i < img.width; ++i) {
        for (int j = 0; j < img.height; ++j) {
            int avg = 0;
            for (int k = 0; k < 3; ++k) {
                avg += img(i, j, k);
            }
            avg /= 3;
            for (int k = 0; k < 3; ++k) {
                img(i, j, k) = avg;
            }
        }
    }
}
void Flip_vertically(Image& image) {
    Image temp = image;
    for (int i = 0; i < image.width; i++) {
        for (int j = 0; j < image.height; j++) {
            for (int k = 0; k < image.channels; k++) {
                image(i, j, k)= temp(i, image.height-1-j, k);

            }
        }
    }
}
void Flip_Horizontally(Image& image) {
    Image temp = image;
    for (int i = 0; i < image.width; i++) {
        for (int j = 0; j < image.height; j++) {
            for (int k = 0; k < image.channels; k++) {
                image(i, j, k)= temp(image.width-1-i, j, k);

            }
        }
    }
}
void applygrayfilter(Image& image) {
    for (int i = 0; i < image.width; ++i) {
        for (int j = 0; j < image.height; ++j) {
            unsigned int avg = 0;
            for (int k = 0; k < image.channels; ++k) {
                avg += image(i, j, k);
            }
            avg /= 3;
            for (int k = 0; k < image.channels; ++k) {
                image(i, j, k) = avg;
            }
        }
    }
}
void invertImage(Image& img) {
    for (int i = 0; i < img.height; i++) {
        for (int j = 0; j < img.width; j++) {
            for (int k = 0; k < 3; k++) {
                img(i, j, k) = 255 - img(i, j, k);
            }
        }
    }
}
Image rotate90(const Image& img) {
    Image rotated(img.height, img.width);
    for (int i = 0; i < img.width; i++) {
        for (int j = 0; j < img.height; j++) {
            for (int k = 0; k < 3; k++) {
                rotated(img.height - 1 - j, i, k) = img(i, j, k);
            }
        }
    }
    return rotated;
}
Image rotate180(const Image& img) {
    Image rotated(img.width, img.height);
    for (int i = 0; i < img.width; i++) {
        for (int j = 0; j < img.height; j++) {
            for (int k = 0; k < 3; k++) {
                rotated(img.width - 1 - i, img.height - 1 - j, k) = img(i, j, k);
            }
        }
    }
    return rotated;
}
Image rotate270(const Image& img) {
    Image rotated(img.height, img.width);
    for (int i = 0; i < img.width; i++) {
        for (int j = 0; j < img.height; j++) {
            for (int k = 0; k < 3; k++) {
                rotated(j, img.width - 1 - i, k) = img(i, j, k);
            }
        }
    }
    return rotated;
}
void applyLighten(Image& img) {
    for (int i = 0; i < img.width; i++) {
        for (int j = 0; j < img.height; j++) {
            for (int k = 0; k < img.channels; k++) {
                img(i, j, k) = min(255, int(img(i, j, k) * 1.5));
            }
        }
    }
}
void applyDarken(Image& img) {
    for (int i = 0; i < img.width; i++) {
        for (int j = 0; j < img.height; j++) {
            for (int k = 0; k < img.channels; k++) {
                img(i, j, k) = max(0, int(img(i, j, k) * 0.5));
            }
        }
    }
}
void cropfunction(Image& image) {
    int x, y, width, height;
    cout << "Enter the starting point (x , y ) of the area to crop:  ";
    cin >> x >> y;
    cout << "Enter the new width and height (W H): ";
    cin >> width >> height;
    if (x < 0 || y < 0 || width <= 0 || height <= 0 ||
        x + width > image.width || y + height > image.height) {
        cout << "Cropping dimensions are out of bounds.\n";
        return;
        }
    Image croppedImage(width, height);
    for (int i = 0; i < width; ++i) {
        for (int j = 0; j < height; ++j) {
            for (int k = 0; k < image.channels; ++k) {
                croppedImage.setPixel(i, j, k, image.getPixel(x + i, y + j, k));
            }
        }
    }
    image = croppedImage;
}
void addFrame(Image& img, int thickness, int thin_frame,
              unsigned char R, unsigned char G, unsigned char B,
              unsigned char R1, unsigned char G1, unsigned char B1,
              bool add_thick, bool add_thin) {

    int Height = img.height;
    int Width  = img.width;

    for (int i = 0; i < Width; i++) {
        for (int j = 0; j < Height; j++) {

            if (add_thick && (i < thickness || i >= Width - thickness ||
                              j < thickness || j >= Height - thickness)) {
                img(i, j, 0) = R;
                img(i, j, 1) = G;
                img(i, j, 2) = B;
                              }

            else if (add_thin && (i < thickness + thin_frame || i >= Width - (thickness + thin_frame) ||
                                  j < thickness + thin_frame || j >= Height - (thickness + thin_frame))) {
                img(i, j, 0) = R1;
                img(i, j, 1) = G1;
                img(i, j, 2) = B1;
                                  }
        }
    }
}

void detect_image_edges(Image& img) {
    Image temp = img;
    for (int i = 0; i < temp.width; ++i) {
        for (int j = 0; j < temp.height; ++j) {
            int avg = 0;
            for (int k = 0; k < 3; ++k) {
                avg += temp(i, j, k);
            }
            avg /= 3;
            int bw = (avg >= 128) ? 255 : 0;
            for (int k = 0; k < 3; ++k) {
                temp(i, j, k) = bw;
            }
        }
    }
    int w = temp.width,h = temp.height;
    Image newimage(w, h);

    for (int i = 1; i < w - 1; ++i) {
        for (int j = 1; j < h - 1; ++j) {
            if ((temp(i - 1, j, 0) == 255 ||
                 temp(i + 1, j, 0) == 255 ||
                 temp(i, j - 1, 0) == 255 ||
                 temp(i, j + 1, 0) == 255)
                && temp(i, j, 0) == 0) {

                newimage(i, j, 0) = 0;
                newimage(i, j, 1) = 0;
                newimage(i, j, 2) = 0;
                } else {
                    newimage(i, j, 0) = 255;
                    newimage(i, j, 1) = 255;
                    newimage(i, j, 2) = 255;
                }
        }
    }

    img = newimage;
}

void load(Image& img) {
    while (true) {
        try {
            cout << "Enter the image filename (with extension .jpg, .png, etc.): ";
            cin >> filename;
            img.loadNewImage(filename);
            break;
        } catch (...) {
            cout << "Error: Could not load image. Try again." << endl;
        }
    }
}
void save() {
    string choice, filename2;
    cout << "1 - Save to new file\n2 - Overwrite current file\nEnter your choice: ";
    cin >> choice;
    if (choice == "1") {
        cout << "Enter new filename with extension: ";
        cin >> filename2;
        image.saveImage(filename2);
        cout << "Image saved as " << filename2 << endl;
    } else if (choice == "2") {
        image.saveImage(filename);
        cout << "Image saved as " << filename << endl;
    } else {
        cout << "Invalid choice!\n";
    }
}
int main() {
    cout << "Please load the image first.\n";
    load(image);
    string choice;
    bool edited = false;
    while (true) {
        cout << "     MENU     \n";
        cout << "{1} Load new image\n";
        cout << "{2} Grayscale\n";
        cout << "{3} Invert Image\n";
        cout << "{4} Rotate (90, 180, 270)\n";
        cout << "{5} Lighten Image\n";
        cout << "{6} Darken Image\n";
        cout << "{7} Black_White Image\n";
        cout << "{8} flip Image verticaly\n";
        cout << "{9} flip Image horizontally\n";
        cout << "{10} crop the Image\n";
        cout<< "{11}  addFrame \n";
        cout << "{12} detect_image_edges\n";
        cout << "{13} Save Image\n";
        cout << "{14} Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        if (choice == "1") {
            load(image);
            edited = false;
        } else if (choice == "2") {
            applygrayfilter(image);
            edited = true;
        } else if (choice == "3") {
            invertImage(image);
            edited = true;
        } else if (choice == "4") {
            string rotate;
            cout << "Rotate: {1} 90° {2} 180° {3} 270°\n";
            cin >> rotate;
            if (rotate == "1") image = rotate90(image);
            else if (rotate == "2") image = rotate180(image);
            else if (rotate == "3") image = rotate270(image);
            else cout << "Invalid!\n";
            edited = true;
        } else if (choice == "5") {
            applyLighten(image);
            edited = true;
        } else if (choice == "6") {
            applyDarken(image);
            edited = true;
        }
        else if (choice == "7") {
            Black_White(image);
            edited = true;
        }
        else if (choice == "8") {
            Flip_vertically(image);
            edited = true;
        }
        else if (choice == "9") {
            Flip_Horizontally(image);
            edited = true;
        }
        else if (choice == "10") {
           cropfunction(image);
            edited = true;
        }
        else if (choice == "11") {
            int thickness = 25;
          int thin_frame = 15;
          unsigned char blackR = 0, blackG = 0, blackB = 0;
          unsigned char grayR = 128, grayG = 128, grayB = 128;
            unsigned char thickR = 0, thickG = 0, thickB = 0;
            unsigned char thinR = 0, thinG = 0, thinB = 0;
            bool add_thick = false, add_thin = false;
            int choice;
            cout << "Choose frame option:\n";
            cout << "1. Thick frame only\n";
            cout << "2. Thin frame only\n";
            cout << "3. Both frames\n";
            cout << "Enter your choice (1–3): ";
            cin >> choice;
            if (choice == 1) add_thick = true;
            else if (choice == 2) add_thin = true;
            else if (choice == 3) { add_thick = true; add_thin = true; }
            else {
                cout << "Invalid choice. Exiting.\n";
                return 0;
            }if (add_thick) {
                int color_choice;
                cout << "\nChoose color for THICK frame:\n";
                cout << "1. Black\n";
                cout << "2. Gray\n";
                cout << "Enter your choice (1 or 2): ";
                cin >> color_choice;
                if (color_choice == 1)
            thickR = blackR, thickG = blackG, thickB = blackB;
                else if (color_choice == 2)
                    thickR = grayR, thickG = grayG, thickB = grayB;
                else {
                    cout << "Invalid color choice. Defaulting to black.\n";
                    thickR = blackR; thickG = blackG; thickB = blackB;
        }
    }


    if (add_thin) {
        int color_choice;
        cout << "\nChoose color for THIN frame:\n";
        cout << "1. Black\n";
        cout << "2. Gray\n";
        cout << "Enter your choice (1 or 2): ";
        cin >> color_choice;

        if (color_choice == 1)
            thinR = blackR, thinG = blackG, thinB = blackB;
        else if (color_choice == 2)
            thinR = grayR, thinG = grayG, thinB = grayB;
        else {
            cout << "Invalid color choice. Defaulting to black.\n";
            thinR = blackR; thinG = blackG; thinB = blackB;
        }
    }

    addFrame(image, thickness, thin_frame,
             thickR, thickG, thickB,
             thinR, thinG, thinB,
             add_thick, add_thin);


        }
        else if (choice == "12") {
           detect_image_edges(image);
            edited = true;
        }
        else if (choice == "13") {
            save();
            edited = false;
        }
        else if (choice == "14") {
            if (edited) {
                cout << "Do you want to save before exiting? (y/n): ";
                char c; cin >> c;
                if (c == 'y' || c == 'Y') save();
            }
            cout << "Exit\n";
            break;
        } else {
            cout << "Invalid choice! Try again.\n";
        }

    }
    return 0;
}