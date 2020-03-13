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
cout << "\n ============SELEÇÃO DE COR=================================" << endl;
cout << "MAIN FILE FROM PATH: " << RandomPath << endl;
cout << "WITH INDEX OF: " << RandomImg << endl;
cout << "==============================================================" << endl;


// PASTA 0 - VERDE
// PASTA 1 - VERMELHO
// PASTA 2 - ROSA
// PASTA 3 - AZUL


int paths[] = {0,1,2,3};
int imgs[] = {0,1,2};
vector<int> cabinhos (paths,paths + sizeof(paths) /sizeof(int));
vector<int> ibagens (imgs, imgs + sizeof(imgs) /sizeof(int));

cabinhos.erase(cabinhos.begin()+RandomPath);
ibagens.erase(ibagens.begin()+RandomImg);

cout << "TAMANHO DO MEU VECTOR DE PATHS: " << cabinhos.size() << endl;
cout << "EXPECTED TO BE 3" << endl;
cout << "TAMANHO DO VECTOR DE IMAGENS: " << ibagens.size() << endl;
cout << "EXPECTED TO BE 2" << endl;

int SelectedColor;

Mat Otherimages[4];

for(int i = 0; i < 4; i++){
    // srand(time(NULL));
    // random_shuffle(ibagens.begin(),ibagens.end());
    int OddImage = ibagens.at(rand()%2);
    string otherPaths = "cor" + to_string(i) + "/" + to_string(OddImage) + ".png";
    Otherimages[i] = imread(otherPaths);
    cout << "[IMAGE TAKEN FROM PATH: " << i << " INDEX: " << OddImage<< "]" << endl; 
}


string MainColorPath = "cor" + to_string(RandomPath) + "/" + to_string(RandomImg) + ".png";




// LÊ A IMAGEM SELECIONADA
image = imread(MainColorPath);
if(!image.data){
    cout << "[ERRO] Imagem nao encontrada" << endl;
    cout << "Tentei no path: " << MainColorPath << endl;
}

imshow("Display window", image);
waitKey(0);

imshow("IMAGEM DE BORDA", Otherimages[1]);
waitKey(0);


imshow("IMAGEM DE BORDA", Otherimages[2]);
waitKey(0);

imshow("IMAGEM DE BORDA", Otherimages[3]);
waitKey(0);


imshow("IMAGEM DE BORDA", Otherimages[4]);
waitKey(0);

return 0;
}