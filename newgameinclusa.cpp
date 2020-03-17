#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/objdetect.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/videoio.hpp"
#include <iostream>
#include <string>
#include <time.h>
#include <vector>

using namespace std;
using namespace cv;

vector<Mat> newGame(){
 
    
    srand(time(NULL));
    int randomPath = rand() % 4;
    int randomImg = rand() % 3;

    vector <Mat> images;

    int imgs[] = {0,1,2};
    vector<int> imagens (imgs, imgs + sizeof(imgs) /sizeof(int));

    imagens.erase(imagens.begin()+randomImg);

    //pointer = images;
    cout << "LEITURA DA IMAGEM 0" << endl;
    string path = "cor"+ to_string(randomPath) + "/" + to_string(randomImg) + ".png";
    cout << "LEITURA BEM SUCEDIDA" <<endl;
    images.push_back(imread(path,IMREAD_UNCHANGED));
    string otherpaths;
    int oddImage;
    for(int i = 0; i<= 3; i++){
        cout << "RODANDO " << i << "x" << endl;
        if(i == randomPath){
            oddImage = imagens.at(rand()%2);
        }
        else{
            srand(time(NULL));
            oddImage = rand() % 3;
        }

    otherpaths = "cor" + to_string(i) +"/"+ to_string(oddImage) + ".png"; 
    cout << otherpaths << endl;
    images.push_back(imread(otherpaths,IMREAD_UNCHANGED));
    // imshow("QUEISSO",images[i+1]);
    // waitKey(0);
    }
    return images;
}

void detectAndDraw( Mat& img, CascadeClassifier& cascade,
                    CascadeClassifier& nestedCascade,
                    double scale);

string cascadeName;
string nestedCascadeName;

void drawTransparency2(Mat frame, Mat transp, int xPos, int yPos){
    Mat mask;
    vector<Mat> layers;
    
    split(transp, layers); // seperate channels
    Mat rgb[3] = { layers[0],layers[1],layers[2] };
    mask = layers[3]; // png"s alpha channel used as mask
    merge(rgb, 3, transp);  // put together the RGB channels, now transp insn"t transparent 
    Mat roi1 = frame(Rect(xPos, yPos, transp.cols, transp.rows));
    Mat roi2 = roi1.clone();
    transp.copyTo(roi2.rowRange(0, transp.rows).colRange(0, transp.cols), mask);
    printf("%p, %p\n", roi1.data, roi2.data);
    double alpha = 0.9;
    addWeighted(roi2, alpha, roi1, 1.0 - alpha, 0.0, roi1);
}

void PreencheCores(vector<string> &cores)
{
    cores.push_back("amarelo");
    cores.push_back("azul");
    cores.push_back("verde");
    cores.push_back("vermelho");
}

void detectAndDraw( Mat& img, CascadeClassifier& cascade,
                    CascadeClassifier& nestedCascade,
                    double scale)
{
    static int frames = 0;
    double t = 0;
    vector<Rect> faces, faces2;
    const static Scalar colors[] =
    {
        Scalar(255,0,0),
        Scalar(255,128,0),
        Scalar(255,255,0),
        Scalar(0,255,0),
        Scalar(0,128,255),
        Scalar(0,255,255),
        Scalar(0,0,255),
        Scalar(255,0,255)
    };
    Mat gray, smallImg;

    cvtColor( img, gray, COLOR_BGR2GRAY );
    double fx = 1 / scale;
    resize( gray, smallImg, Size(), fx, fx, INTER_LINEAR_EXACT );
    equalizeHist( smallImg, smallImg );

    t = (double)getTickCount();
    cascade.detectMultiScale( smallImg, faces,
        1.2, 2, 0
        //|CASCADE_FIND_BIGGEST_OBJECT
        //|CASCADE_DO_ROUGH_SEARCH
        |CASCADE_SCALE_IMAGE,
        Size(30, 30) );

    frames++;

    if (frames % 30 == 0)
        system("mplayer /usr/lib/libreoffice/share/gallery/sounds/kling.wav &");

    t = (double)getTickCount() - t;
//    printf( "detection time = %g ms\n", t*1000/getTickFrequency());
    for ( size_t i = 0; i < faces.size(); i++ )
    {
        Rect r = faces[i];
        printf( "[%3d, %3d]\n", r.x, r.y);
        Mat smallImgROI;
        vector<Rect> nestedObjects;
        Point center;
        Scalar color = colors[i%8];

        rectangle( img, Point(cvRound(r.x*scale), cvRound(r.y*scale)),
                   Point(cvRound((r.x + r.width-1)*scale), cvRound((r.y + r.height-1)*scale)),
                   color, 3, 8, 0);
        if( nestedCascade.empty() )
            continue;
        smallImgROI = smallImg( r );
        nestedCascade.detectMultiScale( smallImgROI, nestedObjects,
            1.1, 2, 0
            //|CASCADE_FIND_BIGGEST_OBJECT
            //|CASCADE_DO_ROUGH_SEARCH
            //|CASCADE_DO_CANNY_PRUNING
            |CASCADE_SCALE_IMAGE,
            Size(30, 30) );
    }

    imshow( "result", img );
}

int main(int argc, const char** argv){
    vector<string> cores, sequencia;
    VideoCapture capture;
    Mat frame;
    string inputName;
    CascadeClassifier cascade, nestedCascade;
    double scale = 1;

    vector<Mat> Otherimages = newGame();
    cout << "TENTEI ABRIR A IMG" << endl;
    cout << "IMAGE SIZE " << Otherimages.size() << endl;
    imshow("OTTT",Otherimages.at(0));

    
    
    string folder = "/home/felipe/Downloads/opencv-4.1.2/data/haarcascades/";
    cascadeName = folder + "haarcascade_frontalface_alt.xml";
    nestedCascadeName = folder + "haarcascade_eye_tree_eyeglasses.xml";
    inputName = "/dev/video0";
    //inputName = inputName = "video2019.2.mp4";



    if (!nestedCascade.load(samples::findFileOrKeep(nestedCascadeName)))
        cerr << "WARNING: Could not load classifier cascade for nested objects" << endl;
    if (!cascade.load(samples::findFile(cascadeName)))
    {
        cerr << "ERROR: Could not load classifier cascade" << endl;
        return -1;
    }

    if(!capture.open(inputName))
    {
        cout << "Capture from camera #" <<  inputName << " didn't work" << endl;
        return 1;
    }

    if( capture.isOpened() )
    {
        while(1)
        {
            capture >> frame;
            flip(frame,frame,1);
            if( frame.empty() )
                break;

            //Mat frame1 = frame.clone();
            drawTransparency2(frame, Otherimages[0], 270, 195);
            drawTransparency2(frame, Otherimages[1], 20, 20);
            drawTransparency2(frame, Otherimages[2], 520, 20);
            drawTransparency2(frame, Otherimages[3], 20, 370);
            drawTransparency2(frame, Otherimages[4], 520, 370);
            detectAndDraw( frame, cascade, nestedCascade, scale);

            char c = (char)waitKey(10);
            if( c == 27 || c == 'q' || c == 'Q' )
                break;
        }
    }

    return 0;
}