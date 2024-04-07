#if defined(__has_feature) && __has_feature(modules)
@import UIKit;
#else
#import <UIKit/UIKit.h>
#endif
#import "SCLButton.h"
@interface SCLTimerDisplay : UIView {
    CGFloat currentAngle;
    CGFloat currentTime;
    CGFloat timerLimit;
    CGFloat radius;
    CGFloat lineWidth;
    NSTimer *timer;
    SCLActionBlock completedBlock;
}
@property CGFloat currentAngle;
@property NSInteger buttonIndex;
@property (strong, nonatomic) UIColor *color;
@property (assign, nonatomic) BOOL reverse;
- (instancetype)initWithOrigin:(CGPoint)origin radius:(CGFloat)r;
- (instancetype)initWithOrigin:(CGPoint)origin radius:(CGFloat)r lineWidth:(CGFloat)width;
- (void)updateFrame:(CGSize)size;
- (void)cancelTimer;
- (void)stopTimer;
- (void)startTimerWithTimeLimit:(int)tl completed:(SCLActionBlock)completed;
@end
