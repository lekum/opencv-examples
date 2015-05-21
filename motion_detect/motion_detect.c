#include <opencv/highgui.h>
#include <opencv/cv.h>
#include <stdio.h>
#include <unistd.h>
#define MAX_LENGTH 80

int main( int argc, char** argv )
{
    char* filename = argv[1];
    char cmd[MAX_LENGTH];
    IplImage* prev_img;
    IplImage* curr_img;
    IplImage* computed_img;
    CvSize isize = cvSize(80,80);

    CvCapture* webcam = cvCreateCameraCapture(0);
    if (!webcam)
        return 1;
    prev_img = cvQueryFrame(webcam);
    computed_img = cvCreateImage(isize, IPL_DEPTH_32F, 1); 
    sleep(1);
    curr_img = cvQueryFrame(webcam);
    if (curr_img)
    {
        cvCalcOpticalFlowFarneback(prev_img, curr_img, computed_img, 0.5, 1, 1, 1, 5, 1.1, 0);
        cvSaveImage(filename, computed_img, 0);
        sprintf(cmd, "ristretto %s", filename);
        system(cmd);
        return 0;
    }
    else
    {
        puts("Nothing to show");
    }
}
