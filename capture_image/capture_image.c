#include <opencv/highgui.h>
#include <stdio.h>
#define MAX_LENGTH 80

int main( int argc, char** argv )
{
    char* filename = argv[1];
    char cmd[MAX_LENGTH];

    CvCapture* webcam = cvCreateCameraCapture(0);
    if (!webcam)
        return 1;
    IplImage* image = cvQueryFrame(webcam);
    if (image)
    {
        cvSaveImage(filename, image, 0);
        sprintf(cmd, "ristretto %s", filename);
        system(cmd);
        return 0;
    }
    else
    {
        puts("Nothing to show");
    }
}
