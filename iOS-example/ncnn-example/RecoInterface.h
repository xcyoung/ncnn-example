//
//  Reco.h
//  ncnn-example
//
//  Created by 肖楚🐑 on 2022/1/9.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

@interface RecoInterface : NSObject

- (void)init:(NSString *)paramPath binPath:(NSString *)binPath;

- (int)interface:(UIImage *)image;

//- (int)interface2:(NSString *)path;

@end

NS_ASSUME_NONNULL_END
