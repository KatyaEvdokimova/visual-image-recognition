#include <opencv2/opencv.hpp>
#include <iostream>


std::string getShapeName(std::vector<cv::Point> contour) {
   
    std::vector<cv::Point> approx;
    double peri = cv::arcLength(contour, true);  
    cv::approxPolyDP(contour, approx, 0.02 * peri, true);  

    int vertices = approx.size(); 

    
    if (vertices == 3) {
        return "triangle";  
    }
    else if (vertices == 4) {
        return "square";  
    }
    else {
        return "circle";
    }
}

int main() {
    
    cv::Mat src = cv::imread("C:\\Users\\Екатерина\\Pictures\\figures.png");
    if (src.empty()) {
        std::cerr << "Ошибка: не удалось загрузить изображение!" << std::endl;
        return -1;
    }

   
    cv::Mat gray;
    cv::cvtColor(src, gray, cv::COLOR_BGR2GRAY);

    
    cv::Mat blurred;
    cv::GaussianBlur(gray, blurred, cv::Size(5, 5), 1.5);

    
    cv::Mat edges;
    cv::Canny(blurred, edges, 10, 50);

    
    std::vector<std::vector<cv::Point>> contours;
    std::vector<cv::Vec4i> hierarchy;
    cv::findContours(edges, contours, hierarchy, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

    
    cv::Mat contourOutput = cv::Mat::zeros(src.size(), CV_8UC3);

   
    for (size_t i = 0; i < contours.size(); i++) {
        
        std::string shape = getShapeName(contours[i]);

        
        cv::drawContours(contourOutput, contours, static_cast<int>(i), cv::Scalar(255, 0, 0), 2);

        
        cv::Moments M = cv::moments(contours[i]);
        if (M.m00 != 0) {
            int cx = static_cast<int>(M.m10 / M.m00);
            int cy = static_cast<int>(M.m01 / M.m00);

            
            cv::putText(contourOutput, shape, cv::Point(cx - 20, cy), cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(255, 255, 255), 1);
        }
    }

   
    cv::imshow("Исходное изображение", src);
    cv::imshow("Контуры", contourOutput);
    cv::waitKey(0);

    return 0;
}
