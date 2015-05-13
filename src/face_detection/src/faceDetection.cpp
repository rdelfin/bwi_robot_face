 #include <opencv2/objdetect/objdetect.hpp>
 #include <opencv2/highgui/highgui.hpp>
 #include <opencv2/imgproc/imgproc.hpp>

 #include <ros/ros.h>
 #include "face_detection/eye.h"
 #include "face_detection/face.h"
 #include "face_detection/faceDetection.h"

 #include <iostream>
 #include <stdio.h>

 using namespace std;
 using namespace cv;

 /** Function Headers */
void detectAndDisplay( Mat frame , ros::Publisher face_pub);

 /** Global variables */
 String face_cascade_name = "/home/joedan/haarcascade_frontalface_alt.xml";
 String eyes_cascade_name = "/home/joedan/haarcascade_eye_tree_eyeglasses.xml";
 CascadeClassifier face_cascade;
 CascadeClassifier eyes_cascade;
 string window_name = "Capture - Face detection";
 RNG rng(12345);

int frameWidth;
int frameHeight;

struct matchedFace //For matching faces with eyes
{
    Rect face;
    std::vector<Rect> eyes;
};
  

 /** @function main */
 int main( int argc, char** argv )
 {
    CvCapture* capture;
    Mat frame;
    //-- ROS portion
    ros::init(argc, argv, "faceDetectorNode");
    ros::NodeHandle n;
    ros::Publisher face_pub = n.advertise<face_detection::faceDetection>("detectedFaces", 1000);
    ros::Rate loop_rate(10);


    //-- 1. Load the cascades
    if( !face_cascade.load( face_cascade_name ) ){ printf("--(!)Error loading faceCascade\n"); return -1; };
    if( !eyes_cascade.load( eyes_cascade_name ) ){ printf("--(!)Error loading eyeCascade\n"); return -1; };

    //-- 2. Read the video stream
    capture = cvCaptureFromCAM( 0 );
    if( capture )
    {
        while( true )
        {
            frame = cvQueryFrame( capture );

            //GETTING FRAME DIMENSIONS
            frameWidth = (double) cvGetCaptureProperty(capture, CV_CAP_PROP_FRAME_WIDTH);
            frameHeight = (double) cvGetCaptureProperty(capture, CV_CAP_PROP_FRAME_HEIGHT);

            ROS_INFO("Capturing frames");
            //-- 3. Apply the classifier to the frame
            if( !frame.empty() ) {
                detectAndDisplay( frame , face_pub);
            } else {
                printf(" --(!) No captured frame -- Break!");
                break;
            }

            int c = waitKey(10);
            if( (char)c == 'c' ) 
                break;
        }
    }

    ros::spin();
    return 0;
 }

/** @function detectAndDisplay */
void detectAndDisplay( Mat frame, ros::Publisher face_pub )
{
    std::vector<Rect> faces;
    std::vector<matchedFace> matchedFaceVector;
    Mat frame_gray;

    cvtColor( frame, frame_gray, CV_BGR2GRAY );
    equalizeHist( frame_gray, frame_gray );

    //-- Detect faces
    face_cascade.detectMultiScale( frame_gray, faces, 1.1, 2, 0|CV_HAAR_SCALE_IMAGE, Size(30, 30) );
    ROS_INFO("Processing Faces -----");
    for( size_t i = 0; i < faces.size(); i++ )
    {
        matchedFace newFace;
        newFace.face=faces[i];
        matchedFaceVector.push_back(newFace);
        Point center( faces[i].x + faces[i].width*0.5, faces[i].y + faces[i].height*0.5 );
        ellipse( frame, center, Size( faces[i].width*0.5, faces[i].height*0.5), 0, 0, 360, Scalar( 255, 0, 255 ), 4, 8, 0 );

        Mat faceROI = frame_gray( faces[i] );
        std::vector<Rect> eyes;

        //-- In each face, detect eyes
        eyes_cascade.detectMultiScale( faceROI, eyes, 1.1, 2, 0 |CV_HAAR_SCALE_IMAGE, Size(30, 30) );

        for(int j = 0; j<eyes.size(); j++)
            matchedFaceVector[i].eyes.push_back(eyes[j]);
    }

//******************************************************
//-- facesDetected is what we will publish
//-- facesDetected is a msg composed of the following
//	int32 frameWidth
//	int32 frameHeight
//	int32 faceCount
//	face[] faces
//	--face is a msg composed of the following
//		int32 x
//		int32 y
//		int32 width
//		int32 height
//		eye[] eyes
//		--eye is a msg composed of the following
//			int32 x
//			int32 y
//			int32 width
//			int32 height
//******************************************************
    face_detection::faceDetection facesDetected;
    ROS_INFO("Creating faceDetected msg");
    facesDetected.faceCount = matchedFaceVector.size();
    for(int i = 0; i < matchedFaceVector.size(); i++) {
        ROS_INFO("\tAdding face %i", i);
        face_detection::face newFace;
        newFace.x = matchedFaceVector[i].face.x;
        newFace.y = matchedFaceVector[i].face.y;
        newFace.width = matchedFaceVector[i].face.width;
        newFace.height = matchedFaceVector[i].face.height;

        for(int k=0; k< matchedFaceVector[i].eyes.size(); k++) {
            ROS_INFO("\t\tAdding eye %i to face %i", k, i);
            face_detection::eye newEye;
            newEye.x = matchedFaceVector[i].eyes[k].x;
            newEye.y = matchedFaceVector[i].eyes[k].y;
            newEye.width = matchedFaceVector[i].eyes[k].width;
            newEye.height = matchedFaceVector[i].eyes[k].height;
            newFace.eyes.push_back(newEye);
        }

        facesDetected.faces.push_back(newFace);
    }
    ROS_INFO("Publishing facesDetected");

    facesDetected.frameWidth = frameWidth;
    facesDetected.frameHeight = frameHeight;
    face_pub.publish(facesDetected);

 }
