
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include"10 functions.h" //Header file for project functions
#include"header.h" // Additional project specific header
using namespace std;

//Checks if a file exists by attempting to open it
bool fileExists (const string& this_file) {
    ifstream file(this_file);
    return file.good();
}

// Checks if a string ends with a specific suffix
bool endsWith(const std::string& str, const std::string& suffix) {
    if (str.length() >= suffix.length()) {
        return (0 == str.compare(str.length() - suffix.length(), suffix.length(), suffix));
    }
    return false;
}


int main(int argc, char* argv[]) {
    Processing top_layer;         // Instance of processing class for top image layer
    string checkIfTga = ".tga";   // Expected file extension for image files
    vector<string> args;          // Vector to hold command line arguments

    // Connect command line arguments into a vector of strings
    for(int i = 0; i < argc; i++) {
        args.push_back((string)(argv[i]));
    }

    // Iterate over the arguments to check for errors and conditions
    for(int i = 0; i < args.size(); i++) {
        if (argc > 1 && args.at(1) == "--help" || argc < 2){
            cout << "Project 2: Image Processing, Fall 2024" << endl;
            cout << endl;
            cout << "Usage:" << endl;
            cout << "\t./project2.out [output] [firstImage] [method] [...]" << endl;
            return 0;
        }
        // Validate output file name format
        if (!endsWith(args.at(1), checkIfTga)) {
            //checks the out file name
            cout << "Invalid file name." << endl;
            return 0;
        }
        // Check if the method provided is valid
        if(argc > 3 && !(args.at(3) == "multiply" || args.at(3) == "subtract" || args.at(3) == "screen" ||
            args.at(3) == "overlay" || args.at(3) == "addred" || args.at(3) == "addgreen" ||
            args.at(3) == "addblue" || args.at(3) == "scalered" || args.at(3) == "scalegreen" ||
            args.at(3) == "scaleblue" || args.at(3) == "flip" || args.at(3) == "onlyred" ||
            args.at(3) == "onlygreen" || args.at(3) == "onlyblue" || args.at(3) == "combine")) {
            //checks to see if the method name is valid
            cout << "Invalid method name." << endl;
            return 0;
        }
        // Validate the format and existence of files for certain methods
        if(argc > 4 && ((args.at(3) == "multiply" || args.at(3) == "subtract" || args.at(3) == "screen" ||
            args.at(3) == "overlay")  && (!endsWith(args.at(4), checkIfTga)))) {
            //checks to see if the file after the given methods is a valid tga name
            cout << "Invalid argument, invalid file name." << endl;
            return 0;

        } if(argc > 4 && (!fileExists(args.at(4)) && (((args.at(3) == "multiply" ||
            args.at(3) == "subtract" || args.at(3) == "screen" ||
            args.at(3) == "overlay"))))) {
            //checks to see if the file after the given methods exists
            cout << "Invalid argument, file does not exist." << endl;
            return 0;

        }
        // Ensure required arguments are provided for color operations
        if(argc == i+1 && (args.at(i) == "addred" ||
            args.at(i) == "addgreen" || args.at(i) == "addblue" ||
            args.at(i) == "scalered" || args.at(i) == "scalegreen" || args.at(i) == "scaleblue")) {
            cout <<"Missing argument."<< endl;
            return 0;
        }
        // Validate the primary image file format and existence
        if((!fileExists(args.at(2)) || !endsWith(args.at(2), checkIfTga))) {
            cout << "File does not exist." << endl;
            return 0;
        }
        i++;
    }

    // Process input arguments for methods and file operations
    int i = 0;
    const string& image1 = args.at(2);  // First image argument
    top_layer = ReadHeader(image1);       // Read first image's header info

    i+= 3;
    while (i < args.size()) {
        // Process each method with its associated file(s) or integer values
        if ((fileExists(args.at(i)) && endsWith(args.at(1) ,checkIfTga)) ||
            args.at(i) == "multiply" || args.at(i) == "subtract" || args.at(i) == "screen" ||
            args.at(i) == "overlay" || args.at(i) == "addred" || args.at(i) == "addgreen" ||
            args.at(i) == "addblue" || args.at(i) == "scalered" || args.at(i) == "scalegreen" ||
            args.at(i) == "scaleblue" || args.at(i) == "flip" || args.at(i) == "onlyred" ||
            args.at(i) == "onlygreen" || args.at(i) == "onlyblue" || args.at(i) == "combine"){
            cout << "i =" << i << endl;
            const string& output = args.at(1); // Output file
            if(i >= args.size()) {
                cout << "Missing method" << endl;
                return 1;
            }
            cout << "i =" << i << endl;
            const string& method = args.at(i);  // Selected method

            i++; // Advance to next argument

            // Apply different image processing methods based on the input
            if(method == "multiply" || method == "subtract" || method == "overlay" || method == "screen") {
                if(i >= args.size()) {
                    cout << "Missing argument." << endl;
                } else if (!fileExists(args.at(2)) || !endsWith(args.at(2), checkIfTga)) {
                    if(!endsWith(args.at(1), checkIfTga)) {
                        cout << "Invalid argument, invalid file name." << endl;
                    }
                }
                const string& image2 = args.at(i);
                cout << "Computing given method: " << method << endl;
                cout << "Between these two files: " << image1 << " and " << image2 << endl;
                Processing bottom_layer = ReadHeader(image2); // Read header of second image for method

                // Apply method
                if(method == "multiply") {
                    top_layer = multiply(top_layer, bottom_layer);
                } else if (method == "subtract") {
                    top_layer = subtract(top_layer, bottom_layer);
                } else if (method == "overlay") {
                    top_layer = overlay(top_layer, bottom_layer);
                } else if (method == "screen") {
                    top_layer = screen(top_layer, bottom_layer);
                }
                write_File(output, top_layer);

            } else if(method == "addred" || method == "addgreen" || method == "addblue") {
                if(i >= args.size()) {
                    cout << "No integer after add color called" << endl;
                }
                const string& image2 = args.at(i);
                int integer = stoi(image2);
                cout << "Computing given method: " << method << endl;
                cout << "Between add color and integer: " << image1 << " and " << image2 << endl;

                if(method == "addred") {
                    top_layer = addRed(top_layer, integer);
                } else if (method == "addgreen") {
                    top_layer = addGreen(top_layer, integer);
                } else if (method == "addblue") {
                    top_layer = addBlue(top_layer, integer);
                }
                write_File(output, top_layer);

            } else if(method == "scalered" || method == "scalegreen" || method == "scaleblue") {
                if(i >= args.size()) {
                    cout << "No integer after add color called" << endl;
                }
                const string& image2 = args.at(i);
                int integer = stoi(image2);
                cout << "Computing given method: " << method << endl;
                cout << "Between add color and integer: " << image1 << " and " << image2 << endl;

                if(method == "scalered") {
                    top_layer = scaleRed(top_layer, integer);
                } else if (method == "scalegreen") {
                    top_layer = scaleGreen(top_layer, integer);
                } else if (method == "scaleblue") {
                    top_layer = scaleBlue(top_layer, integer);
                }
                write_File(output, top_layer);
            } else if(method == "flip" || method == "onlyred" || method == "onlygreen" || method == "onlyblue") {
                cout << "Computing given method: " << method << endl;
                cout << "On given file: " << image1 << endl;

                if(method == "flip") {
                    top_layer = rotate(top_layer);
                } else if (method == "onlyred") {
                    top_layer = separate_channels(top_layer, 3);
                } else if (method == "onlygreen") {
                    top_layer = separate_channels(top_layer, 2);
                } else if (method == "onlyblue") {
                    top_layer = separate_channels(top_layer, 1);
                }
                write_File(output, top_layer);
            } else if (method == "combine") {
                if(i >= args.size() || !endsWith(args.at(i), checkIfTga) || !fileExists(args.at(i))) {
                    cout << "First argument doesnt exist" << endl;
                    if(i+1 >= args.size() || !endsWith(args.at(i+1), checkIfTga) || !fileExists(args.at(i+1))) {
                        cout << "No second argument after method or file doesnt exist" << endl;
                    }
                }
                const string& image2 = args.at(i);
                const string& image3 = args.at(i+1);
                cout << "Computing given method: " << method << endl;
                cout << "Between these three files: " << image1 << " and " << image2 << image3 << endl;
                Processing middle_layer = ReadHeader(image2);
                Processing bottom_layer = ReadHeader(image3);


                if(method == "combine") {
                    top_layer = combine_channels(top_layer, middle_layer, bottom_layer);
                }
                write_File(output, top_layer);
                i++;

            }
            else {
                cout << "Invalid method name." << endl;
            }
        } else if(i >= args.size()) {
            break;
        } else{
            cout << "Invalid file name." << endl;
            break;
        }
        i++;
    }
    return 0;
}