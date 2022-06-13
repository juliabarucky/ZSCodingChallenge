//  Julia Barucky
//  main.cpp
//  Zeta Surgical Coding Challenge
//
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

Mat comb;

Mat grayAn(Mat image, Mat image1){
    //Convert to black and white
    Mat imgRed;
    Mat imgCyan;
    cvtColor(image, imgRed, COLOR_BGRA2GRAY);
    cvtColor(image1, imgCyan, COLOR_BGRA2GRAY);

    //For each pixel, change to red
    for(int y=0;y<image.rows;y++)
    {
        for(int x=0;x<image.cols;x++)
        {
            //blue
            image.at<Vec3b>(y, x)[0] = imgRed.at<unsigned char>(y, x)* (0)/200;
            //green
            image.at<Vec3b>(y, x)[1] = imgRed.at<unsigned char>(y, x)* (0)/200;
            //red
            image.at<Vec3b>(y, x)[2] = imgRed.at<unsigned char>(y, x)* (215)/200;
        }
    }
    
    //For each pixel, change to cyan
    for(int y=0;y<image1.rows;y++)
    {
        for(int x=0;x<image1.cols;x++)
        {
            //blue
            image1.at<Vec3b>(y, x)[0] = imgCyan.at<unsigned char>(y, x)* (215)/200;
            //green
            image1.at<Vec3b>(y, x)[1] = imgCyan.at<unsigned char>(y, x)* (215)/200;
            //red
            image1.at<Vec3b>(y, x)[2] = imgCyan.at<unsigned char>(y, x)* (0)/200;
        }
    }
    
    //Used to figure out why blending wouldn't work
    /*cout << "Width : " << image.cols << endl;
    cout << "Height: " << image.rows << endl;
    cout << "Width : " << image1.cols << endl;
    cout << "Height: " << image1.rows << endl;*/
    
    //Transparency of each image
    double alpha = .5;
    double beta = .5;
    //Blending two images and storing new image in comb
    addWeighted(image, alpha, image1, beta, 0.0, comb);
    return(comb);
}

int main(int argc, char** argv)
{
    // Read the image file
    Mat image = imread("/Users/juliabarucky/Desktop/StereoPair1.jpeg");
    Mat image1 = imread("/Users/juliabarucky/Desktop/StereoPair2.jpeg");
    
    // Check for failure
    if (image.empty() or image1.empty())
    {
        cout << "Could not open image" << endl;
        cin.get(); //wait for any key press
        return -1;
    }
    
    int cols = image.cols;
    int rows = image.rows;
    int cols1 = image1.cols;
    int rows1 = image1.cols;
    
    //check if images are the same dimensions and correct if not
    if (cols != cols1 or rows != rows1){
        resize(image, image, Size(cols,rows), INTER_LINEAR);
        resize(image1, image1, Size(cols,rows), INTER_LINEAR);
    }
        
    //Ask for input
    int type;
    cout << "Anaglyph Options:" << endl;
    cout << "   0 - Gray Anaglyphs" << endl;
    cout << "   1 - True Anaglyphs" << endl;
    cout << "   2 - Color Anaglyphs" << endl;
    cout << "Type a number: ";
    cin >> type;
    
    switch (type) {
        case 0:
            grayAn(image, image1);
            break;
        case 1:
            break;
        case 2:
            break;
        default:
            break;
    }

    // Display altered images
    String windowName = "Red";
    String windowName2 = "Cyan";
    String windowName3 = "Gray Anaglyphs";
    namedWindow(windowName); // Create window
    imshow(windowName, image); // Show our image
    namedWindow(windowName2); // Create a window
    imshow(windowName2, image1);
    moveWindow(windowName2, 0, 5);
    namedWindow(windowName3);
    imshow(windowName3, comb);
    moveWindow(windowName3, 0, 60);
    
    //Wait for any keystroke in the window
    waitKey(0);

    //Destroy the created windows
    destroyWindow(windowName);
    destroyWindow(windowName2);
    destroyWindow(windowName3);
    return 0;
}
