#include <iostream>
#include <iomanip>
#include <fstream>
#include <ios>
#include <list>
#include <vector>
#include <chrono>
#include <iterator>
#include <stdlib.h>
#include <ctime>
#include <math.h>
// Program by: Nithya Chintalapati
// 04/12/2021
class RGB {
public:

    RGB()
    {
        Red = 0;
        Green = 0;
        Blue = 0;
        grayScale =0;

    }
    RGB(int red, int green, int blue)
    {
        Red = red;
        Green = green;
        Blue = blue;
        grayScale = (red + blue + green)/3;
    }
    double getGrayScale()
    {
        return grayScale;
    }

private:
    int Red;
    int Blue;
    int Green;
    double grayScale;

};

using namespace std;

void read();


void optimization();



void fillWeakVals(int x, int y, int i, int i1);

void voting();

void bresenham(double xchange, double ychange, double xminus, double yminus);

int	GX[3][3];
int	GY[3][3];

vector<RGB> magicNumbers;
int pixel;
string pix;
vector<int> after;
vector<int> afterT;
vector<double> direction;
vector<int> nms;
vector<int> hyst;
vector<int> combine;

vector<int> recur;
int width = 0;
int height = 0;
const int UPPER_THRESHOLD = 140;
const int LOWER_THRESHOLD = 90;


int main() {

    optimization();
//    cout << "here";
    voting();

    return 0;
}

void voting() {

    cout << "here";
    int edges[height][width];
    int votes[height][width];
    int track =0;
    int edgeCount =0;
    int edgeCount2 =0;
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            edges[y][x] = (combine[track]);
            if(combine[track] ==1)
                edgeCount++;

            votes[y][x] =0;
            track++;

        }
    }

    track = 0;
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            if(edges[y][x] == 1)
            {

                edgeCount2++;
                    double slope = direction[track];// -1/tan(direction[track]);

                    cout << x << "  " << y << "  " << direction[track] << "  " << ((direction[track] / 3.14159) * 180.0)
                         << "  " << slope << endl;

                    double xchange = x;
                    double ychange = y;
                    double xminus = x;
                    double yminus = y;

                if(direction[track] !=-99999999) {
                    while (xchange < width && ychange < height && xchange > 0 && ychange > 0) {
                        xchange = xchange + 0.1;
                        ychange = y - (slope * (x - xchange));

                    }



                    while (xminus < width && yminus < height && xminus > 0 && yminus > 0) {
                        xminus = xminus - 0.1;
                        yminus = y - (slope * (x - xminus));

                    }

                    if (xchange > width) {
                        xchange = width;
                        ychange = y - (slope * (x - xchange));
                    }

                    if (xchange < 0) {
                        xchange = 0;
                        ychange = y - (slope * (x - xchange));
                    }

                    if (xminus > width) {
                        xminus = width;
                        yminus = y - (slope * (x - xminus));
                    }

                    if (xminus < 0) {
                        xminus = 0;
                        yminus = y - (slope * (x - xminus));
                    }


                    if (ychange > height) {

                        ychange = height;
                        xchange = x - ((y - ychange) / slope);

                    }

                    if (ychange < 0) {
                        ychange = 0;
                        xchange = x - ((y - ychange) / slope);
                    }

                    if (yminus > height) {
                        yminus = height;
                        xminus = x - ((y - yminus) / slope);
                    }

                    if (yminus < 0) {
                        yminus = 0;
                        xminus = x - ((y - yminus) / slope);
                    }

//                cout<< xchange << "  " << ychange << endl;
//                cout<< xminus << "  " << yminus << endl;
//
//                cout << endl;

                    //bresenham(xchange, ychange, xminus, yminus);
                }
                else if(direction[track] == -99999999)
                {
                    xchange = x;
                    xminus = x;
                    ychange = height;
                    yminus = 0;
                }

//                xchange = width - xchange;
//                ychange = height - ychange;
////
//                xminus = width - xminus;
//                yminus = height-yminus;

                int x2 = (int)xchange;
                int y2 = (int)ychange;

                int x1 = (int)xminus;
                int y1 = (int)yminus;

                int dx = x2 - x1 ;
                int dy = y2 - y1 ;
                int dx1 = 0, dy1 = 0, dx2 = 0, dy2 = 0 ;
                if (dy<0){
                    dy1 = -1 ;
                }
                else if (dy>0){
                    dy1 = 1 ;
                }
                if (dx<0) {
                    dx1 = -1;
                }
                else if (dx>0){
                    dx1 = 1 ;}
                if (dy<0){
                    dy2 = -1;
                }
                else if (dy>0){
                    dy2 = 1 ;
                }
                int longest = abs(dy) ;
                int shortest = abs(dx) ;
                if (!
                        (longest>shortest)) {
                    longest = abs(dx) ;
                    shortest = abs(dy) ;
                    if (dx<0)
                    {
                        dx2 = -1 ;
                    }
                    else if (dx>0) {
                        dx2 = 1;
                    }
                    dy2 = 0 ;
                }
                int numerator = longest >> 1 ;
                for (int i=0;i<=longest;i++) {
                    votes[y1][x1]++;
                    numerator += shortest ;
                    if (!
                            (numerator<longest)) {
                        numerator -= longest ;
                        x1 += dx1 ;
                        y1 += dy1 ;
                    } else {
                        x1 += dx2 ;
                        y1 += dy2 ;
                    }
                }


                // end of bresenham


            }
            track++;
        }
    }

    int maxvotes = 0;
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {

            if(votes[y][x]> maxvotes)
                maxvotes = votes[y][x];

//            cout << votes[y][x] << endl;
        }
    }

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {

            if(votes[y][x]< 1)
                votes[y][x]=0;

           // cout << votes[y][x] << endl;

        }
    }

    cout << "Max Votes: " << maxvotes << endl;
    cout << "EC1: " << edgeCount << endl;
    cout << "EC2: " << edgeCount2 << endl;
    std::ofstream output;
    output.open("imagev.ppm");
    output << pix << endl << width << ' ' << height << endl << maxvotes << endl;

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {

//            if(votes[y][x] == 0) {
//                votes[y][x] = edges[y][x];
//            }
        }
    }
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {

            if(votes[y][x]> maxvotes)
                maxvotes = votes[y][x];

            output << votes[y][x] << " " << votes[y][x] << " " << votes[y][x] << "     ";


        }
    }

    output.close();

}



void fillWeakVals(int y, int x, int ch, int tracker) {
    if (x < 0 || x >= width-8 || y < 0 || y >= height-8)
        return;

    recur[tracker] = 2;
    if(recur[tracker+1] == 1)
    {
        x++;
        tracker++;
        fillWeakVals(y, x, ch, tracker);
    }
    else if(recur[tracker-1] == 1)
    {
        x--;
        tracker--;
        fillWeakVals(y, x, ch, tracker);
    }
    else if(recur[tracker+7] == 1)
    {
        y++;
        tracker = tracker+7;
        fillWeakVals(y, x, ch, tracker);
    }
    else if(recur[tracker-7] == 1)
    {
        y--;
        tracker = tracker-7;
        fillWeakVals(y, x, ch, tracker);
    }
    else if(recur[tracker-8] == 1)
    {
        y= y-8;
        tracker = tracker-8;
        fillWeakVals(y, x, ch, tracker);
    }

    else if(recur[tracker+8] == 1)
    {
        y= y+8;
        tracker = tracker+8;
        fillWeakVals(y, x, ch, tracker);
    }

    else if(recur[tracker-6] == 1)
    {
        y= y-6;
        tracker = tracker-6;
        fillWeakVals(y, x, ch, tracker);
    }

    else if(recur[tracker+6] == 1)
    {
        y= y+6;
        tracker = tracker+6;
        fillWeakVals(y, x, ch, tracker);
    }
}

void optimization() {
    read();
    int matrixM[height][width];
//    int matrixT[height][width];
// cout << "here";
//    cout << "here";
    cout << "Width: " << width << endl;
    cout << "Height: " << height << endl;

//    cout << afterT.size() << endl;
//    cout << after.size() << endl;
//
//    std::ofstream output;
//    output.open("image1.ppm");
//    output << pix << endl << width << ' ' << height << endl << 1 << endl;
//    cout << "here";
//
//    std::ofstream output2;
//    output2.open("image2.ppm");
//    output2 << pix << endl << width << ' ' << height << endl << 1 << endl;

    std::ofstream output3;
    output3.open("imagef.ppm");
    output3 << pix << endl << width << ' ' << height << endl << 1 << endl;



    int track = 0;
    int track2 =0;
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            matrixM[y][x] = (after[track]);
            track++;

        }
    }

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {

            //cout << matrixM[y][x] << endl;
            if(y == 0 || x ==0 || y==height-1 || x ==width-1)
            {
                nms.push_back(1);
            }
            else
            {
                if(afterT[track2] == 0)
                {
                    int valRight = matrixM[y][x+1];
                    int valLeft = matrixM[y][x-1];
                    if(matrixM[y][x] > valLeft && matrixM[y][x] > valRight)
                    {
                        nms.push_back(1);
                    }
                    else
                    {
                        nms.push_back(0);
                    }

                }

                else if(afterT[track2] == 45)
                {
                    int valRight = matrixM[y-1][x+1];
                    int valLeft = matrixM[y+1][x-1];
                    if(matrixM[y][x] > valLeft && matrixM[y][x] > valRight)
                    {
                        nms.push_back(1);
                    }
                    else
                    {
                        nms.push_back(0);
                    }

                }

                else if(afterT[track2] == 90)
                {
                    int valRight = matrixM[y+1][x];
                    int valLeft = matrixM[y-1][x];
                    //cout << "here" << endl;
                    if(matrixM[y][x] > valLeft && matrixM[y][x] > valRight)
                    {
                        nms.push_back(1);
                    }
                    else
                    {
                        nms.push_back(0);
                    }

                }

                else if(afterT[track2] == 135)
                {
                    int valRight = matrixM[y-1][x-1];
                    int valLeft = matrixM[y+1][x+1];
                    //cout << "here" << endl;
                    if(matrixM[y][x] > valLeft && matrixM[y][x] > valRight)
                    {
                        nms.push_back(1);
                    }
                    else
                    {
                        nms.push_back(0);
                    }

                }

            }



            track2++;
        }
    }
///non max done//
    for (int h = 0; h < height; h++) {
        for (int w = 0; w < width; w++) {

            //   cout << matrixM[h][w] ;

            if(matrixM[h][w] >= UPPER_THRESHOLD)
            {

                matrixM[h][w] = 2;

            }
            else if (matrixM[h][w] <= LOWER_THRESHOLD)
            {

                matrixM[h][w] = 0;
            }
            else if(matrixM[h][w] > LOWER_THRESHOLD && matrixM[h][w] < UPPER_THRESHOLD)
            {
                matrixM[h][w] = 1;
            }
            // cout << "  new: " << matrixM[h][w] << endl;
        }
    }

    for(int y =0; y < height; y++)
    {
        for(int x=0; x <width;x++)
        {
            // cout<< matrixTest[y][x] << "  ";

            recur.push_back(matrixM[y][x]);

        }

        // cout << endl;
    }

    int tracker =0;
    for(int y =0; y < 7; y++) {
        for (int x = 0; x < 7; x++) {
            if(matrixM[y][x] ==1) {

                if ((matrixM[y+1][x-1] == 2) || (matrixM[y+1][x] == 2) || (matrixM[y+1][ x+1] == 2)
                    || (matrixM[y][x-1] == 2) || (matrixM[y][x+1] == 2)
                    || (matrixM[y-1][x-1] == 2) || (matrixM[y-1][x] == 2) || (matrixM[y-1][x+1] == 2)) {
                    fillWeakVals(y, x, 2, tracker);
                }
                else
                {
                    matrixM[y][x] = 0;
                    recur[tracker] = 0;
                }

            }
            tracker++;
        }
    }


    for (int h = 0; h < (int)recur.size(); h++) {


        if(recur[h] == 2)
        {
            hyst.push_back(1);
        }
        else
        {
            //cout << recur[h] << endl;
            hyst.push_back(0);
        }

    }

    for (int y = 0; y < (int)nms.size(); y++) {

//        output << int(nms[y]) << " " << int(nms[y]) << " " << int(nms[y]) << "     ";
//        output2 << int(hyst[y]) << " " << int(hyst[y]) << " " << int(hyst[y]) << "     ";

        if(int(nms[y]) == 1 && int(hyst[y]) == 1)
        {
            combine.push_back(1);
        }
        else
        {
            combine.push_back(0);
        }
        output3 << int(combine[y]) << " " << int(combine[y]) << " " << int(combine[y]) << "     ";

    }


//    output.close();
//    output2.close();
    output3.close();


}



void read() {

    string magic;
    std::ifstream test;
    int red;
    int blue;
    int green;
    test.open ("coins3.ppm");
    int i = 0;
    while (test >> magic)
    {
        if(i>3) {
            if(i%3 == 1)
            {
                red = stoi(magic);
            }
            if(i%3 == 2)
            {
                blue = stoi(magic);
            }
            if(i%3 == 0)
            {
                green = stoi(magic);
                RGB gen(red, green, blue);
                magicNumbers.push_back(gen);
            }
        }
        else if( i ==0)
        {
            pix = magic;
            cout << "Magic Num: " <<pix << endl;
        }
        else if( i ==1)
        {
            width = stoi(magic);
            cout << "Width: " <<width << endl;
        }
        else if( i ==2)
        {
            height = stoi(magic);
            cout << "Height: " <<height << endl;
        }

        else if(i ==3)
        {
            pixel = stoi(magic);
            //cout << "Max Pixel: " <<pixel << endl;
        }

        i++;
    }
    test.close();


   // cout << height << endl;
    int matrix[height][width];
    cout << "here" << endl;
    int iii = 0;
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {

            matrix[y][x] = int(magicNumbers[iii].getGrayScale());
            iii++;
        }

    }

    GX[0][0] = -1; GX[0][1] = 0; GX[0][2] = 1;
    GX[1][0] = -2; GX[1][1] = 0; GX[1][2] = 2;
    GX[2][0] = -1; GX[2][1] = 0; GX[2][2] = 1;

    GY[0][0] =  1; GY[0][1] =  2; GY[0][2] =  1;
    GY[1][0] =  0; GY[1][1] =  0; GY[1][2] =  0;
    GY[2][0] = -1; GY[2][1] = -2; GY[2][2] = -1;



    for (int h = 0; h < height; h++) {
        for (int w = 0; w < width; w++) {
            int xval;
            int yval;
            if(h == 0 || w== 0 || h == height-1 || w == width-1)
            {
                xval = yval =0;


            }
            else
            {
                xval = yval =0;
                for (int x = -1; x <= 1; x++)
                {
                    for (int y = -1; y <= 1; y++)
                    {
                        xval = xval + matrix[h+x][w+y] * GX[1+x][1+y];
                        yval = yval + matrix[h+x][w+y]* GY[1+x][1+y];
                    }
                }
            }
            after.push_back(sqrt((xval*xval) + (yval * yval)));





            float thisAngle = ((atan2(yval,xval)/3.14159) * 180.0);
            float newAngle =0;

            if (xval != 0) {
                direction.push_back(-(double)((double)yval / (double)xval));
                cout <<"check: " << w<< "  "<<h << "  "<<xval << "  " << yval << "  " <<(-(double)((double)yval / (double)xval)) <<  endl;

            }
            else
                direction.push_back(-99999999);




            if ( ( (thisAngle < 22.5) && (thisAngle > -22.5) ) || (thisAngle > 157.5) || (thisAngle < -157.5) )
                newAngle = 0;
            if ( ( (thisAngle > 22.5) && (thisAngle < 67.5) ) || ( (thisAngle < -112.5) && (thisAngle > -157.5) ) )
                newAngle = 45;
            if ( ( (thisAngle > 67.5) && (thisAngle < 112.5) ) || ( (thisAngle < -67.5) && (thisAngle > -112.5) ) )
                newAngle = 90;
            if ( ( (thisAngle > 112.5) && (thisAngle < 157.5) ) || ( (thisAngle < -22.5) && (thisAngle > -67.5) ) )
                newAngle = 135;

            afterT.push_back((int)newAngle);

            //cout << "here" << "  ";


//            if ( (thisAngle < 22.5) && (thisAngle > -22.5) ) {
//                direction.push_back(0);
//               // cout << 0 << endl;
//            }
//            if ((thisAngle > 157.5) || (thisAngle < -157.5)) {
//                direction.push_back(180);
//                //cout << 180 << endl;
//            }
//            if ( (thisAngle > 22.5) && (thisAngle < 67.5) ) {
//                direction.push_back(45);
//                //cout << 45 << endl;
//            }
//            if( (thisAngle < -112.5) && (thisAngle > -157.5) ) {
//                direction.push_back(225);
//                //cout << 225 << endl;
//            }


//            if ( (thisAngle > 67.5) && (thisAngle < 112.5) )
//                direction.push_back(90);
//
//            if  ( (thisAngle < -67.5) && (thisAngle > -112.5) )
//                direction.push_back(270);
//
//
//            if ( (thisAngle > 112.5) && (thisAngle < 157.5) )
//                direction.push_back(135);
//
//            if ( (thisAngle < -22.5) && (thisAngle > -67.5) )
//                direction.push_back(315);




        }

    }

}