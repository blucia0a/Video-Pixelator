#include <OpenCV/OpenCV.h>
#include <cassert>
#include <iostream>
#include "Pixelator.h"

const char  * WINDOW_NAME  = "Video Pixelator";

using namespace std;

int main (int argc, char * const argv[]) 
{
    const int scale = 2;
    
    // create all necessary instances
    cvNamedWindow (WINDOW_NAME, CV_WINDOW_AUTOSIZE);
    CvCapture * camera = cvCreateCameraCapture (CV_CAP_ANY);
    CvMemStorage* storage = cvCreateMemStorage(0);
    assert (storage);

    // you do own an iSight, don't you ?!?
    if (! camera)
        abort ();

    // get an initial frame and duplicate it for later work
    IplImage *  current_frame = cvQueryFrame (camera);
    IplImage *  draw_image    = cvCreateImage(cvSize (current_frame->width, current_frame->height), IPL_DEPTH_8U, 3);
    IplImage *  gray_image    = cvCreateImage(cvSize (current_frame->width, current_frame->height), IPL_DEPTH_8U, 1);
	 assert (current_frame && gray_image);
    
    // as long as there are images ...
    while (current_frame = cvQueryFrame (camera))
    {
	
        // convert to gray and downsize
        cvCvtColor (current_frame, gray_image, CV_BGR2GRAY);
        
		 pixelate(gray_image);
		
        // just show the image
        cvShowImage (WINDOW_NAME, gray_image);

        // cvShowImage (WINDOW_NAME, current_frame);
        // wait a tenth of a second for keypress and window drawing
        int key = cvWaitKey (30);
        if (key == 'q' || key == 'Q')
            break;
    }
    
    // be nice and return no error
    return 0;
}
