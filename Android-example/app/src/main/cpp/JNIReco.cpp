
#include <jni.h>
#include <android/log.h>
#include <android/bitmap.h>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include "Reco.h"

using namespace std;
using namespace cv;

#define  LOG_TAG    "JNIReco"
#define  LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)
#define ASSERT(status, ret)     if (!(status)) { return ret; }
#define ASSERT_FALSE(status)    ASSERT(status, false)

#define JNI_METHOD(return_type, method_name) \
  JNIEXPORT return_type JNICALL              \
  Java_me_xcyoung_ncnn_Reco_##method_name

extern "C" {
bool bitmapToMat(JNIEnv *env, jobject input_bitmap, cv::Mat &output) {
    void *bitmapPixels;
    AndroidBitmapInfo bitmapInfo;
    ASSERT_FALSE(AndroidBitmap_getInfo(env, input_bitmap, &bitmapInfo) >= 0)
    ASSERT_FALSE(bitmapInfo.format == ANDROID_BITMAP_FORMAT_RGBA_8888)

    ASSERT_FALSE(AndroidBitmap_lockPixels(env, input_bitmap, &bitmapPixels) >= 0)
    ASSERT_FALSE(bitmapPixels)

    cv::Mat tmp(bitmapInfo.height, bitmapInfo.width, CV_8UC4, bitmapPixels);
    cv::cvtColor(tmp, output, cv::COLOR_RGBA2BGR);

    AndroidBitmap_unlockPixels(env, input_bitmap);
    return true;
}

JNI_METHOD(void, nativeInit)(JNIEnv *env, jobject instance, jstring paramPath, jstring binPath) {
    jboolean isCopy;
    std::string mParamPath = env->GetStringUTFChars(paramPath, &isCopy);
    std::string mBinPath = env->GetStringUTFChars(binPath, &isCopy);
    init(mParamPath, mBinPath);
}

JNI_METHOD(jint, nativeInterface)(JNIEnv *env, jobject instance, jobject bitmap) {
    cv::Mat input;

    bool res = bitmapToMat(env, bitmap, input);
    if (res) {
        return interface(input);
    } else {
        return 0;
    }
}
}
