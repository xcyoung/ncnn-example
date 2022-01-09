//
//  Reco.m
//  ncnn-example
//
//  Created by 肖楚🐑 on 2022/1/9.
//

#import "Reco.h"
#import "RecoInterface.h"
#import <opencv2/core.hpp>
#import <opencv2/imgproc.hpp>
#import <opencv2/highgui/highgui.hpp>

@implementation RecoInterface

- (void)init:(NSString *)paramPath binPath:(NSString *)binPath {
    init([paramPath UTF8String], [binPath UTF8String]);
}

- (int)interface:(UIImage *)image {
    cv::Mat input = [self image2Mat:image];
    return interface(input);
}

//- (int)interface2:(NSString *)path {
//    cv::Mat a = cv::imread([path UTF8String]);
//    return interface(a);
//}

- (cv::Mat)image2Mat:(UIImage *)image {
    CGColorSpaceRef colorSpace = CGImageGetColorSpace(image.CGImage);
    CGFloat cols = image.size.width;
    CGFloat rows = image.size.height;
    
    cv::Mat cvMat(rows, cols, CV_8UC4);
    CGContextRef contextRef = CGBitmapContextCreate(cvMat.data,
                                                cols,
                                                rows,
                                                8,
                                                cvMat.step[0],
                                                colorSpace,
                                                kCGImageAlphaNoneSkipLast |
                                                kCGBitmapByteOrderDefault);
    CGContextDrawImage(contextRef, CGRectMake(0, 0, cols, rows), image.CGImage);
    CGContextRelease(contextRef);
    cv::cvtColor(cvMat, cvMat, CV_RGBA2BGR);
    return cvMat;
}

@end
