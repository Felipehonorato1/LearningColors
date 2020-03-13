#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <string>
#include <time.h>
#include <vector>

using namespace cv;
using namespace std;

int Generate(int total){
    srand(time(NULL));
    return rand()% total;
}

int main(){

Mat image; 

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


int paths[] = {0,1,2,3};
int imgs[] = {0,1,2};
vector<int> ibagens (imgs, imgs + sizeof(imgs) /sizeof(int));

ibagens.erase(ibagens.begin()+RandomImg);

Mat Otherimages[4];

string otherPaths;
int OddImage;
int i;
for(i = 0; i < 4; i++){
    // srand(time(NULL));
    // random_shuffle(ibagens.begin(),ibagens.end());
    if(i == RandomPath){
        OddImage = ibagens.at(rand()%2);
    }else
        OddImage = rand()%3;
    otherPaths = "cor" + to_string(i) + "/" + to_string(OddImage) + ".png";
    cout << "PATH SENDO LIDO: " << otherPaths << endl;
    Otherimages[i] = imread(otherPaths);

    }


string MainColorPath = "cor" + to_string(RandomPath) + "/" + to_string(RandomImg) + ".png";




// LÊ A IMAGEM SELECIONADA
image = imread(MainColorPath);
if(!image.data){
    cout << "[ERRO] Imagem nao encontrada" << endl;
    cout << "Tentei no path: " << MainColorPath << endl;
}

cout << "SHOWING SELECTED" << endl;
imshow("SELECTED", image);
waitKey(0);

imshow("IMAGEM DE BORDA 1", Otherimages[0]);
cout << "SHOWING SELECTED 1" << endl;
waitKey(0);

imshow("IMAGEM DE BORDA 2", Otherimages[1]);
cout << "SHOWING SELECTED 2" << endl;
waitKey(0); 

imshow("IMAGEM DE BORDA 3", Otherimages[2]);
cout << "SHOWING SELECTED 3" << endl;
waitKey(0);

imshow("IMAGEM DE BORDA 4", Otherimages[3]);
cout << "SHOWING SELECTED 4" << endl;
waitKey(0);


return 0;
}