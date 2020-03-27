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

void Start(){
   while(1){
        Mat image;
        image = imread("start.jpg", WINDOW_AUTOSIZE);
        imshow("Start", image);
        char s = (char)waitKey(10);
            if(s == 's' || s == 'S' ){
                destroyAllWindows();
                break;
            }
    
    }
}

string cascadeName;
string nestedCascadeName;

void drawTransparency2(Mat frame, Mat transp, int xPos, int yPos) {
    Mat mask;
    vector<Mat> layers;
    
    split(transp, layers); // seperate channels
    Mat rgb[3] = { layers[0],layers[1],layers[2] };
    mask = layers[3]; // png's alpha channel used as mask
    merge(rgb, 3, transp);  // put together the RGB channels, now transp insn't transparent 
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

void mp3Player(char file)
{    
    switch(file)
    {
        case '0':
            system("mpg321 /home/lara/Downloads/LearningColors-master/colors/0.mp3 &");
            //system("mpg321 /home/dudahardman/Área de Trabalho/LearningColors-master/colors/0.mp3 &");
        break;

        case '1':
            system("mpg321 /home/lara/Downloads/LearningColors-master/colors/1.mp3 &");
            //system("mpg321 /home/dudahardman/Área de Trabalho/LearningColors-master/colors/1.mp3 &");
        break;

        case '2':
            system("mpg321 /home/lara/Downloads/LearningColors-master/colors/2.mp3 &");
            //system("mpg321 /home/dudahardman/Área de Trabalho/LearningColors-master/colors/2.mp3 &");
        break;

        case '3':
            system("mpg321 /home/lara/Downloads/LearningColors-master/colors/3.mp3 &");
            //system("mpg321 /home/dudahardman/Área de Trabalho/LearningColors-master/colors/3.mp3 &");
    }
}

int detectAndDraw( Mat& img, CascadeClassifier& cascade,
                    CascadeClassifier& nestedCascade,
                    double scale, vector<string> paths, int *pontos, int *recorde, bool *posicaoJogoAnterior)
{
    static int frames = 0;
    double t = 0;
    vector<Rect> faces;
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

    t = (double)getTickCount() - t;
//    printf( "detection time = %g ms\n", t*1000/getTickFrequency());
    for ( size_t i = 0; i < faces.size(); i++ )
    {
        Rect r = faces[i];
        //printf( "[%3d, %3d]\n", r.x, r.y);

        if((r.x > 20)&&(r.x < 120)&&(r.y > 20)&&(r.y < 90)&&!(*posicaoJogoAnterior))
        {
            if(paths[0][3] == paths[1][3])
            {
                mp3Player(paths[0][3]);
                *pontos++;
                *posicaoJogoAnterior = true;
                return 1;
            }
             else
             {
                if(*pontos > *recorde)
                    *recorde = *pontos;

                *pontos = 0;
                return 2;
             }
        }

        else if((r.x > 420)&&(r.x < 520)&&(r.y > 20)&&(r.y < 90)&&!(*posicaoJogoAnterior))
        {
            if(paths[0][3] == paths[2][3])
            {
                mp3Player(paths[0][3]);
                *pontos++;
                *posicaoJogoAnterior = true;
                return 1;
            }
            else
             {
                if(*pontos > *recorde)
                    *recorde = *pontos;

                *pontos = 0;
                return 2;
             }
        }
        
        else if ((r.x > 20)&&(r.x < 120)&&(r.y > 300)&&(r.y < 370)&&!(*posicaoJogoAnterior))
        {
            if(paths[0][3] == paths[3][3])
            {
                mp3Player(paths[0][3]);
                *pontos++;
                *posicaoJogoAnterior = true;
                return 1;
            }
            else
             {
                if(*pontos > *recorde)
                    *recorde = *pontos;

                *pontos = 0;
                return 2;
             }
        }

        else if ((r.x > 420)&&(r.x < 520)&&(r.y > 300)&&(r.y < 370)&&!(*posicaoJogoAnterior))
        {
            if(paths[0][3] == paths[4][3])
            {
                mp3Player(paths[0][3]);
                *pontos++;
                *posicaoJogoAnterior = true;
                return 1;
            }
            else
             {
                if(*pontos > *recorde)
                    *recorde = *pontos;

                *pontos = 0;
                return 2;
             }
        }
        else 
            *posicaoJogoAnterior = false;

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

    return 0;
}

int Generate(int total){
    srand(time(NULL));
    return rand()% total;
}

vector<string> newGame()
{
    int RandomPath = Generate(4);
    int RandomImg = Generate(3);
    cout << "\n ================SELEÇÃO DE COR=================================" << endl;
    cout << "MAIN FILE FROM PATH: " << RandomPath << endl;
    cout << "WITH INDEX OF: " << RandomImg << endl;
    cout << "==============================================================\n" << endl;

    // PASTA 0 - VERDE
    // PASTA 1 - VERMELHO
    // PASTA 2 - ROSA
    // PASTA 3 - AZUL

    int imgs[] = {0,1,2};
    vector<int> ibagens (imgs, imgs + sizeof(imgs) /sizeof(int));

    ibagens.erase(ibagens.begin()+RandomImg);

    vector<string> paths(5);

    paths[0] = "cor" + to_string(RandomPath) + "/" + to_string(RandomImg) + ".png";
    
    int OddImage;
    vector<int> j = {0, 1, 2, 3};
    for(int i = 1; i < 5; i++){
        // srand(time(NULL));
        // random_shuffle(ibagens.begin(),ibagens.end());
        int n = rand()%j.size();
        if(j[n] == RandomPath){
            OddImage = ibagens.at(rand()%2);
        }else
            OddImage = rand()%3;
        
        paths[i] = "cor" + to_string(j[n]) + "/" + to_string(OddImage) + ".png";
        j.erase(j.begin() + n);
        cout << "PATH SENDO LIDO: " << paths[i] << endl;
    }

        // LÊ A IMAGEM SELECIONADA
        if(!imread(paths[0], IMREAD_UNCHANGED).data){
            cout << "[ERRO] Imagem nao encontrada" << endl;
            cout << "Tentei no path: " << paths[0] << endl;
    }

    return paths;
}

int main(int argc, const char** argv){
    vector<string> cores;
    VideoCapture capture;
    Mat frame;
    string inputName;
    CascadeClassifier cascade, nestedCascade;
    double scale = 1;
    int pontos = 0, recorde = 0;
    bool posicaoJogoAnterior = false;

    //lê o arquivo
    //recorde = valorLidoNoArquivo;
    
    string folder = "/home/lara/Downloads/opencv-4.1.2/data/haarcascades/";
    //string folder = "/home/dudahardman/Downloads/opencv-4.1.2/data/haarcascades/";
    cascadeName = folder + "haarcascade_frontalface_alt.xml";
    nestedCascadeName = folder + "haarcascade_eye_tree_eyeglasses.xml";
    inputName = "/dev/video0";
    //inputName = inputName = "video2019.2.mp4";

    if (!nestedCascade.load(samples::findFileOrKeep(nestedCascadeName)))
        cerr << "WARNING: Could not load classifier cascade for nested objects" << endl;
    if (!cascade.load(samples::findFile(cascadeName)))
    {
        cerr << "ERROR: Could not load classifier cascade" << endl;
        //exception
        return -1;
    }
    
    Start();

    if(!capture.open(inputName))
    {
        cout << "Capture from camera #" <<  inputName << " didn't work" << endl;
        //exception
        return 1;
    }
    
    if( capture.isOpened() )
    {
        //system("mpg321 /home/dudahardman/Área de Trabalho/colors.mp3 &");
        vector<string> paths(5);
        paths = newGame();
        while(1)
        {
            capture >> frame;
            flip(frame,frame,1);
            if( frame.empty() )
                break;

            //Mat frame1 = frame.clone();
            drawTransparency2(frame, imread(paths[0], IMREAD_UNCHANGED), 270, 195);
            drawTransparency2(frame, imread(paths[1], IMREAD_UNCHANGED), 20, 20);
            drawTransparency2(frame, imread(paths[2], IMREAD_UNCHANGED), 520, 20);
            drawTransparency2(frame, imread(paths[3], IMREAD_UNCHANGED), 20, 370);
            drawTransparency2(frame, imread(paths[4], IMREAD_UNCHANGED), 520, 370);
            if(detectAndDraw(frame, cascade, nestedCascade, scale, paths, &pontos, &recorde, &posicaoJogoAnterior) == 1)
                paths = newGame();
            else if(detectAndDraw(frame, cascade, nestedCascade, scale, paths, &pontos, &recorde, &posicaoJogoAnterior) == 2)
            {
                destroyAllWindows();
                Start();
                paths = newGame();
            }

            char c = (char)waitKey(10);
            if( c == 27 || c == 'q' || c == 'Q' )
                break;
        }
    }

    return 0;
}
