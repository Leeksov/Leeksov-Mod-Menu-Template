#if defined(__has_feature) && __has_feature(modules)
@import Foundation;
#else
#import <Foundation/Foundation.h>
#endif
#import "SCLAlertView.h"
@interface SCLAlertViewResponder : NSObject
- (instancetype)init:(SCLAlertView *)alertview;
- (void)close;
@end
