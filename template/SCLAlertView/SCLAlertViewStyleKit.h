#if defined(__has_feature) && __has_feature(modules)
@import Foundation;
@import UIKit;
#else
#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#endif
#import "SCLButton.h"
@interface SCLAlertViewStyleKit : NSObject
+ (UIImage *)imageOfCheckmark;
+ (UIImage *)imageOfCross;
+ (UIImage *)imageOfNotice;
+ (UIImage *)imageOfWarning;
+ (UIImage *)imageOfInfo;
+ (UIImage *)imageOfEdit;
+ (UIImage *)imageOfQuestion;
+ (void)drawCheckmark;
+ (void)drawCross;
+ (void)drawNotice;
+ (void)drawWarning;
+ (void)drawInfo;
+ (void)drawEdit;
+ (void)drawQuestion;
@end
