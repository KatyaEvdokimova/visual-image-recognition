#include <opencv2/opencv.hpp>
#include <opencv2/features2d.hpp>
#include <iostream>
#include <vector>
#include <string>

using namespace cv;
using namespace std;

struct CardSample {
    string name;
    Mat imageGray;
    vector<KeyPoint> keypoints;
    Mat descriptors;
};

int main() {
    string folderPath = "C:\\Users\\Екатерина\\Downloads";
    vector<string> templateNames = {
        "valetpicki.png",
        "kingkresti.png",
        "tuzbubi.png",
        "damacherv.png",
        "9kresti.png",
        "9buby.png",
        "5kresti.png",
        "3picki.png",
        "dvacherv.png"
    };

    
    Ptr<SIFT> sift = SIFT::create();

    // Загрузка шаблонов
    vector<CardSample> cardSamples;
    for (const auto& name : templateNames) {
        string fullPath = folderPath + name;
        Mat imgGray = imread(fullPath, IMREAD_GRAYSCALE);
        if (imgGray.empty()) {
            cerr << "Не удалось загрузить шаблон: " << name << endl;
            continue;
        }

        vector<KeyPoint> kps;
        Mat desc;
        sift->detectAndCompute(imgGray, noArray(), kps, desc);
        cardSamples.push_back({ name, imgGray, kps, desc });
    }

    // Загрузка изображения с картами
    string cardPath = folderPath + "image.png";
    Mat cardColor = imread(cardPath);
    if (cardColor.empty()) {
        cerr << "Не удалось загрузить image.png" << endl;
        return -1;
    }

    Mat cardGray;
    cvtColor(cardColor, cardGray, COLOR_BGR2GRAY);

    vector<KeyPoint> cardKps;
    Mat cardDesc;
    sift->detectAndCompute(cardGray, noArray(), cardKps, cardDesc);

    BFMatcher matcher(NORM_L2);

    for (const auto& sample : cardSamples) {
        vector<vector<DMatch>> knnMatches;
        matcher.knnMatch(sample.descriptors, cardDesc, knnMatches, 2);

        vector<DMatch> goodMatches;
        for (const auto& pair : knnMatches) {
            if (pair.size() >= 2 && pair[0].distance < 0.75 * pair[1].distance) {
                goodMatches.push_back(pair[0]);
            }
        }

        if (goodMatches.size() >= 4) {
            vector<Point2f> pts1, pts2;
            for (const auto& m : goodMatches) {
                pts1.push_back(sample.keypoints[m.queryIdx].pt);
                pts2.push_back(cardKps[m.trainIdx].pt);
            }

            Mat H = findHomography(pts1, pts2, RANSAC);
            if (!H.empty()) {
                vector<Point2f> corners = {
                    {0, 0},
                    {0, (float)sample.imageGray.rows},
                    {(float)sample.imageGray.cols, (float)sample.imageGray.rows},
                    {(float)sample.imageGray.cols, 0}
                };
                vector<Point2f> transformedCorners;
                perspectiveTransform(corners, transformedCorners, H);

                for (int i = 0; i < 4; i++) {
                    line(cardColor, transformedCorners[i], transformedCorners[(i + 1) % 4], Scalar(0, 255, 0), 3);
                }

                // Центр и подпись
                Point2f center(0.f, 0.f);
                for (const auto& pt : transformedCorners)
                    center += pt;
                center.x /= 4.0f;
                center.y /= 4.0f;

                putText(cardColor, sample.name, Point((int)center.x, (int)center.y),
                    FONT_HERSHEY_SIMPLEX, 0.8, Scalar(0, 255, 0), 2);
            }
        }
    }

    // 4. Отображение результата
    imshow("Распознанные карты", cardColor);
    waitKey(0);
    destroyAllWindows();

    return 0;
}
