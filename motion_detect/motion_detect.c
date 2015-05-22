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

    CvCapture* webcam = cvCreateCameraCapture(0);
    if (!webcam)
        return 1;
    prev_img = cvQueryFrame(webcam);
    IplImage* prev_prepared = cvCreateImage(cvGetSize(prev_img), IPL_DEPTH_32F, 1);
    cvCvtColor(prev_img, prev_prepared, CV_BGR2GRAY);
    cvSaveImage("prev.jpg", prev_prepared, 0);
    computed_img = cvCreateImage(cvGetSize(prev_img), IPL_DEPTH_32F, 1);
    sleep(1);
    curr_img = cvQueryFrame(webcam);
    cvCvtColor(curr_img, curr_img, CV_BGR2GRAY);
    if (curr_img)
    {
        cvCalcOpticalFlowFarneback(prev_img, curr_img, computed_img, 0.5, 3, 15, 3, 5, 1.2, 0);
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
