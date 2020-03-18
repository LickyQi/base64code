#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "base64.h"

using namespace cv;
using namespace std;

int main() {

    Mat image = imread("/Users/liqi/Desktop/lena.jpg");

    //转换为灰度图
    cvtColor(image,image,CV_RGB2GRAY);

    //显示原始图像灰度图
    imshow("Origin Image",image);
    waitKey();

    int row = image.rows;
    int col = image.cols;

    //输出原图数据
//    for(int i=0;i<row*col;i++)
//        cout << image.at<uchar>(i);
//    cout << endl;

    //首先必须进行 imencode
    vector<unsigned char> buff;//buffer for coding
    vector<int> param= vector<int>(2);
    param[0]=CV_IMWRITE_JPEG_QUALITY;
    param[1]=95;//default(95) 0-100

    imencode(".jpg",image,buff,param);

    //base64编码
    unsigned int encode_col=0;
    //获取编码长度
    encode_col = BASE64_ENCODE_OUT_SIZE(buff.size())-1;
    //申请内存,动态创建数组
    char *image_encode = new char[encode_col];
    unsigned char *data = &buff[0];
    //编码
    base64_encode(data,buff.size(),image_encode);

    //输出编码结果
//    for (int i = 0; i < encode_col; i ++){
//        cout << image_encode[i];
//    }
//    cout << endl;


    //base64解码

    unsigned int decode_col = 0;
    //获取解码长度
    decode_col = BASE64_DECODE_OUT_SIZE(encode_col)-2;
    //申请内存，动态创建数组
    unsigned char * image_decode = new unsigned char[decode_col];
    //解码
    base64_decode(image_encode,encode_col,image_decode);

    //输出解码结果
//    for (int i = 0; i < decode_col; i ++){
//        cout << image_decode[i];
//    }
//    cout << endl;

    vector<unsigned char> str;
    for(int i=0;i<decode_col;i++)
        str.push_back(image_decode[i]);

    Mat decode_image = imdecode(str,CV_LOAD_IMAGE_GRAYSCALE);
    //显示解码图像

    imshow("Decode Image", decode_image);
    waitKey();

    // 释放分配空间

    delete [] image_decode;
    delete [] image_encode;

    return 0;

}