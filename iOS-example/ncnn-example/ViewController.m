//
//  ViewController.m
//  ncnn-example
//
//  
//

#import "ViewController.h"
#import "RecoInterface.h"

@interface ViewController ()

@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    NSString* paramPath = [[NSBundle mainBundle]URLForResource:@"demo" withExtension:@"param"].path;
    NSString* binPath = [[NSBundle mainBundle]URLForResource:@"demo" withExtension:@"bin"].path;
    NSString* imagePath = [[NSBundle mainBundle]URLForResource:@"demo" withExtension:@"jpg"].path;
    
    RecoInterface* reco = [[RecoInterface alloc]init];
    [reco init:paramPath binPath:binPath];
    
    UIImage* image = [[UIImage alloc]initWithContentsOfFile:imagePath];
    [reco interface:image];
}


@end
