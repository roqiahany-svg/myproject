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
        cout << "{10} Save Image\n";
        cout << "{11} Exit\n";
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
            save();
            edited = false;
        }
        else if (choice == "11") {
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