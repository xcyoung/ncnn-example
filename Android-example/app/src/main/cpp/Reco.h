
#ifndef NCNN_EXMAPLE_RECO_H
#define NCNN_EXMAPLE_RECO_H
#include <string>
#include <opencv2/core/core.hpp>

void init(const std::string &paramPath, const std::string &binPath);
int interface(const cv::Mat &bgr);

#endif //NCNN_EXMAPLE_RECO_H
