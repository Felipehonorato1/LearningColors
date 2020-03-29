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

int detectColor(int posX, int posY, vector<string> paths, int *pontos, int *recorde, bool *posicaoJogoAnterior)
{
    //cout << posX << "," << posY << endl;
    if((posX > 20)&&(posX < 100)&&(posY > 80)&&(posY < 120)&&!(*posicaoJogoAnterior))
    {
        if(paths[0][3] == paths[1][3])
        {
            mp3Player(paths[0][3]);
            *pontos = *pontos + 1;
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

    else if((posX > 510)&&(posX < 590)&&(posY > 80)&&(posY < 120)&&!(*posicaoJogoAnterior))
    {
        if(paths[0][3] == paths[2][3])
        {
            mp3Player(paths[0][3]);
            *pontos = *pontos + 1;
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
    
    else if ((posX > 20)&&(posX < 100)&&(posY > 370)&&(posY < 410)&&!(*posicaoJogoAnterior))
    {
        if(paths[0][3] == paths[3][3])
        {
            mp3Player(paths[0][3]);
            *pontos = *pontos + 1;
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

    else if ((posX > 510)&&(posX < 590)&&(posY > 370)&&(posY < 410)&&!(*posicaoJogoAnterior))
    {
        if(paths[0][3] == paths[4][3])
        {
            mp3Player(paths[0][3]);
            *pontos = *pontos + 1;
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
    else if ((posX > 290)&&(posX < 370)&&(posY > 220)&&(posY < 260))
    {
        *posicaoJogoAnterior = false;
        cout << "=====================================READY======================================" << endl;
    }

    return 0;
}

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

int Generate(int total){
    srand(time(NULL));
    return rand()% total;
}

vector<string> newGame()
{
    int RandomPath = Generate(4);
    int RandomImg = Generate(3);
    cout << "\n=================================SELEÇÃO DE COR=================================" << endl;
    cout << "MAIN FILE FROM PATH: " << RandomPath << endl;
    cout << "WITH INDEX OF: " << RandomImg << endl;
    cout << "================================================================================\n" << endl;

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
            cout << "Tentado no path: " << paths[0] << endl;
    }

    return paths;
}

vector<string> Start(bool *posicaoJogoAnterior){
    while(1){
        Mat image;
        image = imread("start.jpg", WINDOW_AUTOSIZE);
        imshow("Start", image);

        if(waitKey(10) == 's' || waitKey(10) == 'S' ){
            destroyAllWindows();
            *posicaoJogoAnterior = true;
            return newGame();
        }

        if (waitKey(30) == 27) //wait for 'esc' key press for 30ms. If 'esc' key is pressed, break loop
        {
            cout << "Esc key pressed by user" << endl;
            throw 0; 
        }    
    }
}

int main(int argc, const char** argv){
    int pontos = 0, recorde = 0;
    bool posicaoJogoAnterior = false;

    Mat frame;
    VideoCapture cap(0); //capture the video from web cam

    if ( !cap.isOpened() )  // if not success, exit program
    {
        cout << "Cannot open the web cam" << endl;
        return -1;
    }

    namedWindow("Control", WINDOW_AUTOSIZE); //create a window called "Control"

    int iLowH = 22;
    int iHighH = 38;

    int iLowS = 65; 
    int iHighS = 165;

    int iLowV = 70;
    int iHighV = 255;

    //Create trackbars in "Control" window
    createTrackbar("LowH", "Control", &iLowH, 179); //Hue (0 - 179)
    createTrackbar("HighH", "Control", &iHighH, 179);

    createTrackbar("LowS", "Control", &iLowS, 255); //Saturation (0 - 255)
    createTrackbar("HighS", "Control", &iHighS, 255);

    createTrackbar("LowV", "Control", &iLowV, 255); //Value (0 - 255)
    createTrackbar("HighV", "Control", &iHighV, 255);

    vector<string> paths(5);
    try
    {
        paths = Start(&posicaoJogoAnterior);
    }
    catch (int i)
    {
        return 0;
    }
    
    while (true)
    {
        Mat imgOriginal;

        bool bSuccess = cap.read(imgOriginal); // read a new frame from video

        if (!bSuccess) //if not success, break loop
        {
            cout << "Cannot read a frame from video stream" << endl;
            break;
        }

        flip(imgOriginal,imgOriginal,1);

        drawTransparency2(imgOriginal, imread(paths[0], IMREAD_UNCHANGED), 270, 195);
        drawTransparency2(imgOriginal, imread(paths[1], IMREAD_UNCHANGED), 20, 20);
        drawTransparency2(imgOriginal, imread(paths[2], IMREAD_UNCHANGED), 520, 20);
        drawTransparency2(imgOriginal, imread(paths[3], IMREAD_UNCHANGED), 20, 370);
        drawTransparency2(imgOriginal, imread(paths[4], IMREAD_UNCHANGED), 520, 370);

        Mat imgHSV;

        cvtColor(imgOriginal, imgHSV, COLOR_BGR2HSV); //Convert the captured frame from BGR to HSV
        
        Mat imgThresholded;

        inRange(imgHSV, Scalar(iLowH, iLowS, iLowV), Scalar(iHighH, iHighS, iHighV), imgThresholded); //Threshold the image
            
        //morphological opening (remove small objects from the foreground)
        erode(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) );
        dilate( imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) ); 

        //morphological closing (fill small holes in the foreground)
        dilate( imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) ); 
        erode(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) );

        //Calculate the moments of the thresholded image
        Moments oMoments = moments(imgThresholded);

        // if the area <= 1000000, I consider that the there are no object in the image and it's because of the noise, the area is not zero 
        if (oMoments.m00 > 1000000)
        {
            if(detectColor(oMoments.m10/oMoments.m00, oMoments.m01/oMoments.m00, paths, &pontos, &recorde, &posicaoJogoAnterior) == 1)
                paths = newGame();
            else if(detectColor(oMoments.m10/oMoments.m00, oMoments.m01/oMoments.m00, paths, &pontos, &recorde, &posicaoJogoAnterior) == 2)
            {
                try
                {
                    paths = Start(&posicaoJogoAnterior);
                }
                catch (int i)
                {
                    return 0;
                }
            }
        }

        imshow("Thresholded Image", imgThresholded); //show the thresholded image
        imshow("Original", imgOriginal); //show the original image

        if (waitKey(30) == 27) //wait for 'esc' key press for 30ms. If 'esc' key is pressed, break loop
        {
            cout << "Esc key pressed by user" << endl;
            break; 
        }
    }

    return 0;
}
