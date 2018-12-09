//
// Created by iceytan on 18-12-9.
//

#include <iostream>
#include <opencv2/opencv.hpp>
#include "PSO.h"


int main() {
    const int height = 400, width = 300;
    cv::Mat data_mat(height, width, CV_8UC3);
    cv::namedWindow("result");

    auto fx = [](int x) {
        return 150.0 * sin(x * M_PI / 150.0 - 0.5) + 200.0;
    };

    std::vector<cv::Point2i> points;
    for (int i = 0; i < width; ++i) points.emplace_back(i, height - fx(i));
    cv::polylines(data_mat, points, false, {0, 255, 255}, 1, cv::LineTypes::LINE_AA);


    // do pso
    PSO pso;

    pso.SetLossFunction([&](std::vector<double> input) -> double {
        if (input[0] < 0 || input[0] >= width) return 1000;
        return 150.0 * sin(input[0] * M_PI / 150.0 - 0.5) + 200.0;
    });

    auto r = pso.Process(50, 51, 20);

    cv::circle(data_mat, {int(r[0]), int(height - fx(r[0]))}, 10, {255, 0, 0});

    cv::imshow("result", data_mat);
    cv::waitKey(0);
}