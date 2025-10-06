#include <iostream>
#include "Image_Class.h"
using namespace std;
Image image;
string filename;
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
        cout << "{3} Lighten Image\n";
        cout << "{4} Darken Image\n";
        cout << "{5} Save Image\n";
        cout << "{6} Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        if (choice == "1") {
            load(image);
            edited = false;
        } else if (choice == "2") {
            applygrayfilter(image);
            edited = true;
        } else if (choice == "3") {
            applyLighten(image);
            edited = true;
        } else if (choice == "4") {
            applyDarken(image);
            edited = true;
        } else if (choice == "5") {
            save();
            edited = false;
        } else if (choice == "6") {
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