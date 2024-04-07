#if defined(__has_feature) && __has_feature(modules)
@import UIKit;
#else
#import <UIKit/UIKit.h>
#endif
@interface SCLSwitchView : UIView
@property (strong, nonatomic) UIColor *tintColor UI_APPEARANCE_SELECTOR;
@property (strong, nonatomic) UIColor *labelColor UI_APPEARANCE_SELECTOR;
@property (strong, nonatomic) UIFont *labelFont UI_APPEARANCE_SELECTOR;
@property (strong, nonatomic) NSString *labelText UI_APPEARANCE_SELECTOR;
@property (nonatomic, getter=isSelected) BOOL selected;
@end
