
#include <cstdio>
#include "Reco.h"
#include <opencv2/highgui/highgui.hpp>
#include <ncnn/platform.h>
#include <ncnn/net.h>

ncnn::Net *net = nullptr;

void unInit() {
    if (net != nullptr) {
        delete net;
        net = nullptr;
    }
}

void init(const std::string &paramPath, const std::string &binPath) {
    unInit();

    net = new ncnn::Net;
    net->load_param(paramPath.c_str());
    net->load_model(binPath.c_str());
}

int detect(const cv::Mat &bgr, std::vector<float> &cls_scores) {
    if (net == nullptr) return 1;
    ncnn::Mat in = ncnn::Mat::from_pixels_resize(bgr.data, ncnn::Mat::PIXEL_BGR, bgr.cols, bgr.rows,
                                                 224, 224);

    const float mean[3] = {0.0f, 0.0f, 0.0f};
    const float normal[3] = {0.0f, 0.0f, 0.0f};

    in.substract_mean_normalize(mean, normal);
    ncnn::Extractor ex = net->create_extractor();

    ex.input("input", in);
    ncnn::Mat out;
    ex.extract("output", out);
    out = out.reshape(out.w * out.h * out.c);
    cls_scores.resize(out.w);
    for (int j = 0; j < out.w; j++) {
        cls_scores[j] = out[j];
    }
    return 0;
}

int process(const std::vector<float> &cls_scores) {
    return 0;
}

int interface(const cv::Mat &bgr) {
    std::vector<float> cls_scores;
    if (detect(bgr, cls_scores) == 0) {
        return 0;
    }
    process(cls_scores);
    return 0;
}