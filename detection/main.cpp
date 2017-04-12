#include <iostream>
#include "MTCNN.h"

using namespace std;
using namespace cv;

int main() {

    vector<string> model_file = {
            "/home/xileli/Documents/program/MTCNN/model/det1.prototxt",
            "/home/xileli/Documents/program/MTCNN/model/det2.prototxt",
            "/home/xileli/Documents/program/MTCNN/model/det3.prototxt"
//            "../model/det4.prototxt"
    };

    vector<string> trained_file = {
            "/home/xileli/Documents/program/MTCNN/model/det1.caffemodel",
            "/home/xileli/Documents/program/MTCNN/model/det2.caffemodel",
            "/home/xileli/Documents/program/MTCNN/model/det3.caffemodel"
//            "../model/det4.caffemodel"
    };
    MTCNN mtcnn(model_file, trained_file);



/*
// image input starts
//    vector<Rect> rectangles;
//    string img_path = "/home/xileli/Desktop/1.png";
//    Mat img = imread(img_path);
//
//    mtcnn.detection(img, rectangles);
//    mtcnn.crop_face(img);
//    mtcnn.vector_copy();
//    string img_path_2 = "/home/xileli/Desktop/2.png";
//    img = imread(img_path_2);
//
//    mtcnn.detection(img, rectangles);
//    mtcnn.crop_face(img);
//    float a = mtcnn.cosine_similarity(0,0);
//    cout<< a <<endl;
//
//
//    std::cout << "Hello, World!" << std::endl;
//
//    for(int i = 0; i < rectangles.size(); i++) {
//        rectangle(img, rectangles[i], Scalar(255, 0, 0), 4);
//        string txt = "face " + to_string(i);
//        Point bottom_left_pos(rectangles[i].x, rectangles[i].y);
//        putText(img, txt, bottom_left_pos, FONT_HERSHEY_SIMPLEX, 1.3, Scalar(255, 0, 255), 3);
//    }
//
//    imshow("face", img);
//    waitKey(0);
*/




//video output time record----txt file

    string time_output = "/home/xileli/Documents/video/RossVideo/output/time_rec.txt";




//video input starts
//    VideoCapture cap(0);
//    VideoCapture cap("/home/xileli/Downloads/Omarosa and Bethenny Get Into It.mp4");
    //VideoCapture cap("/home/xileli/Documents/video/RossVideo/VTS_01_2_clip.mp4");
    VideoCapture cap("/home/xileli/Documents/video/recognition/1.mp4");
    Mat img_scr;
    cap >> img_scr;
    VideoWriter out_video;
    out_video.open("/home/xileli/Documents/video/RossVideo/output/output1.avi",
                   CV_FOURCC('M', 'J', 'P', 'G'), 30, img_scr.size());
    int index = 0;

    if (!cap.isOpened())// check if we succeeded
    return -1;

    for(;;)
    {
        Mat img;
        cap >> img; // get a new frame from camera/video

        vector<Rect> rectangles;


        mtcnn.timer_begin();
        mtcnn.detection(img, rectangles);
        vector<int> name_list = mtcnn.name_list_;
//        float a = mtcnn.cosine_similarity(0,0);
//        if(rectangles.size() > 2)
//        {
//            float m = mtcnn.cosine_similarity(0,2);
//            cout<< a << ' ' << m <<endl;
//        }
//        else
//            cout<< a <<endl;
        mtcnn.timer_end();

        std::fstream file("/home/xileli/Documents/video/RossVideo/output/face_num.txt", ios::app);// record the face num of current frame
        //std::cout << rectangles.size() << std::endl;
        file << rectangles.size() << std::endl;
        file.close();

        for(int i = 0; i < rectangles.size(); i++)
        {
            rectangle(img, rectangles[i], Scalar(255, 0, 0), 4);
            string txt = "face " + to_string(name_list[rectangles.size() - i - 1]);
            Point bottom_left_pos(rectangles[i].x, rectangles[i].y);
            putText(img, txt, bottom_left_pos, FONT_HERSHEY_SIMPLEX, 1.0, Scalar(255, 0, 255), 3);
         }
        imshow("face", img);
        out_video<<img;
        waitKey(1);

        //cout << index << endl;
        index++;
//        time_rec<<
//        if(waitKey(30) >= 0) break;
    }


    return 0;
}

