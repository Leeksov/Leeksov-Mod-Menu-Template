#if defined(__has_feature) && __has_feature(modules)
@import UIKit;
#else
#import <UIKit/UIKit.h>
#endif
#import "SCLButton.h"
#import "SCLTextView.h"
#import "SCLSwitchView.h"
typedef NSAttributedString* (^SCLAttributedFormatBlock)(NSString *value);
typedef void (^SCLDismissBlock)(void);
typedef void (^SCLDismissAnimationCompletionBlock)(void);
typedef void (^SCLShowAnimationCompletionBlock)(void);
typedef void (^SCLForceHideBlock)(void);
@interface SCLAlertView : UIViewController 
typedef NS_ENUM(NSInteger, SCLAlertViewStyle)
{
    SCLAlertViewStyleSuccess,
    SCLAlertViewStyleError,
    SCLAlertViewStyleNotice,
    SCLAlertViewStyleWarning,
    SCLAlertViewStyleInfo,
    SCLAlertViewStyleEdit,
    SCLAlertViewStyleWaiting,
    SCLAlertViewStyleQuestion,
    SCLAlertViewStyleCustom
};
typedef NS_ENUM(NSInteger, SCLAlertViewHideAnimation)
{
    SCLAlertViewHideAnimationFadeOut,
    SCLAlertViewHideAnimationSlideOutToBottom,
    SCLAlertViewHideAnimationSlideOutToTop,
    SCLAlertViewHideAnimationSlideOutToLeft,
    SCLAlertViewHideAnimationSlideOutToRight,
    SCLAlertViewHideAnimationSlideOutToCenter,
    SCLAlertViewHideAnimationSlideOutFromCenter,
    SCLAlertViewHideAnimationSimplyDisappear
};
typedef NS_ENUM(NSInteger, SCLAlertViewShowAnimation)
{
    SCLAlertViewShowAnimationFadeIn,
    SCLAlertViewShowAnimationSlideInFromBottom,
    SCLAlertViewShowAnimationSlideInFromTop,
    SCLAlertViewShowAnimationSlideInFromLeft,
    SCLAlertViewShowAnimationSlideInFromRight,
    SCLAlertViewShowAnimationSlideInFromCenter,
    SCLAlertViewShowAnimationSlideInToCenter,
    SCLAlertViewShowAnimationSimplyAppear
};
typedef NS_ENUM(NSInteger, SCLAlertViewBackground)
{
    SCLAlertViewBackgroundShadow,
    SCLAlertViewBackgroundBlur,
    SCLAlertViewBackgroundTransparent
};
@property CGFloat cornerRadius;
@property (assign, nonatomic) BOOL tintTopCircle;
@property (assign, nonatomic) BOOL useLargerIcon;
@property (strong, nonatomic) UILabel *labelTitle;
@property (strong, nonatomic) UITextView *viewText;
@property (strong, nonatomic) UIActivityIndicatorView *activityIndicatorView;
@property (assign, nonatomic) BOOL shouldDismissOnTapOutside;
@property (strong, nonatomic) NSURL *soundURL;
@property (copy, nonatomic) SCLAttributedFormatBlock attributedFormatBlock;
@property (copy, nonatomic) CompleteButtonFormatBlock completeButtonFormatBlock;
@property (copy, nonatomic) ButtonFormatBlock buttonFormatBlock;
@property (copy, nonatomic) SCLForceHideBlock forceHideBlock;
@property (nonatomic) SCLAlertViewHideAnimation hideAnimationType;
@property (nonatomic) SCLAlertViewShowAnimation showAnimationType;
@property (nonatomic) SCLAlertViewBackground backgroundType;
@property (strong, nonatomic) UIColor *customViewColor;
@property (strong, nonatomic) UIColor *backgroundViewColor;
@property (strong, nonatomic) UIColor *iconTintColor;
@property (nonatomic) CGFloat circleIconHeight;
@property (nonatomic) CGRect extensionBounds;
@property (nonatomic) BOOL statusBarHidden;
@property (nonatomic) UIStatusBarStyle statusBarStyle;
@property (nonatomic) BOOL horizontalButtons;
- (instancetype)initWithNewWindow;
- (instancetype)initWithNewWindowWidth:(CGFloat)windowWidth;
- (void)alertIsDismissed:(SCLDismissBlock)dismissBlock;
- (void)alertDismissAnimationIsCompleted:(SCLDismissAnimationCompletionBlock)dismissAnimationCompletionBlock;
- (void)alertShowAnimationIsCompleted:(SCLShowAnimationCompletionBlock)showAnimationCompletionBlock;
- (void)hideView;
- (BOOL)isVisible;
- (void)removeTopCircle;
- (UIView *)addCustomView:(UIView *)customView;
- (SCLTextView *)addTextField:(NSString *)title;
- (void)addCustomTextField:(UITextField *)textField;
- (SCLSwitchView *)addSwitchViewWithLabel:(NSString *)label;
- (void)addTimerToButtonIndex:(NSInteger)buttonIndex reverse:(BOOL)reverse;
- (void)setTitleFontFamily:(NSString *)titleFontFamily withSize:(CGFloat)size;
- (void)setBodyTextFontFamily:(NSString *)bodyTextFontFamily withSize:(CGFloat)size;
- (void)setButtonsTextFontFamily:(NSString *)buttonsFontFamily withSize:(CGFloat)size;
- (SCLButton *)addButton:(NSString *)title actionBlock:(SCLActionBlock)action;
- (SCLButton *)addButton:(NSString *)title validationBlock:(SCLValidationBlock)validationBlock actionBlock:(SCLActionBlock)action;
- (SCLButton *)addButton:(NSString *)title target:(id)target selector:(SEL)selector;
- (void)showSuccess:(UIViewController *)vc title:(NSString *)title subTitle:(NSString *)subTitle closeButtonTitle:(NSString *)closeButtonTitle duration:(NSTimeInterval)duration;
- (void)showSuccess:(NSString *)title subTitle:(NSString *)subTitle closeButtonTitle:(NSString *)closeButtonTitle duration:(NSTimeInterval)duration;
- (void)showError:(UIViewController *)vc title:(NSString *)title subTitle:(NSString *)subTitle closeButtonTitle:(NSString *)closeButtonTitle duration:(NSTimeInterval)duration;
- (void)showError:(NSString *)title subTitle:(NSString *)subTitle closeButtonTitle:(NSString *)closeButtonTitle duration:(NSTimeInterval)duration;
- (void)showNotice:(UIViewController *)vc title:(NSString *)title subTitle:(NSString *)subTitle closeButtonTitle:(NSString *)closeButtonTitle duration:(NSTimeInterval)duration;
- (void)showNotice:(NSString *)title subTitle:(NSString *)subTitle closeButtonTitle:(NSString *)closeButtonTitle duration:(NSTimeInterval)duration;
- (void)showWarning:(UIViewController *)vc title:(NSString *)title subTitle:(NSString *)subTitle closeButtonTitle:(NSString *)closeButtonTitle duration:(NSTimeInterval)duration;
- (void)showWarning:(NSString *)title subTitle:(NSString *)subTitle closeButtonTitle:(NSString *)closeButtonTitle duration:(NSTimeInterval)duration;
- (void)showInfo:(UIViewController *)vc title:(NSString *)title subTitle:(NSString *)subTitle closeButtonTitle:(NSString *)closeButtonTitle duration:(NSTimeInterval)duration;
- (void)showInfo:(NSString *)title subTitle:(NSString *)subTitle closeButtonTitle:(NSString *)closeButtonTitle duration:(NSTimeInterval)duration;
- (void)showEdit:(UIViewController *)vc title:(NSString *)title subTitle:(NSString *)subTitle closeButtonTitle:(NSString *)closeButtonTitle duration:(NSTimeInterval)duration;
- (void)showEdit:(NSString *)title subTitle:(NSString *)subTitle closeButtonTitle:(NSString *)closeButtonTitle duration:(NSTimeInterval)duration;
- (void)showTitle:(UIViewController *)vc title:(NSString *)title subTitle:(NSString *)subTitle style:(SCLAlertViewStyle)style closeButtonTitle:(NSString *)closeButtonTitle duration:(NSTimeInterval)duration;
- (void)showTitle:(NSString *)title subTitle:(NSString *)subTitle style:(SCLAlertViewStyle)style closeButtonTitle:(NSString *)closeButtonTitle duration:(NSTimeInterval)duration;
- (void)showCustom:(UIViewController *)vc image:(UIImage *)image color:(UIColor *)color title:(NSString *)title subTitle:(NSString *)subTitle closeButtonTitle:(NSString *)closeButtonTitle duration:(NSTimeInterval)duration;
- (void)showCustom:(UIImage *)image color:(UIColor *)color title:(NSString *)title subTitle:(NSString *)subTitle closeButtonTitle:(NSString *)closeButtonTitle duration:(NSTimeInterval)duration;
- (void)showWaiting:(UIViewController *)vc title:(NSString *)title subTitle:(NSString *)subTitle closeButtonTitle:(NSString *)closeButtonTitle duration:(NSTimeInterval)duration;
- (void)showWaiting:(NSString *)title subTitle:(NSString *)subTitle closeButtonTitle:(NSString *)closeButtonTitle duration:(NSTimeInterval)duration;
- (void)showQuestion:(UIViewController *)vc title:(NSString *)title subTitle:(NSString *)subTitle closeButtonTitle:(NSString *)closeButtonTitle duration:(NSTimeInterval)duration;
- (void)showQuestion:(NSString *)title subTitle:(NSString *)subTitle closeButtonTitle:(NSString *)closeButtonTitle duration:(NSTimeInterval)duration;
@end
@protocol SCLItemsBuilder__Protocol__Fluent <NSObject>
- (void)setupFluent;
@end
@interface SCLAlertViewBuilder__WithFluent: NSObject <SCLItemsBuilder__Protocol__Fluent> @end
@interface SCLAlertViewShowBuilder : SCLAlertViewBuilder__WithFluent
@property(weak, nonatomic, readonly) UIViewController *parameterViewController;
@property(copy, nonatomic, readonly) UIImage *parameterImage;
@property(copy, nonatomic, readonly) UIColor *parameterColor;
@property(copy, nonatomic, readonly) NSString *parameterTitle;
@property(copy, nonatomic, readonly) NSString *parameterSubTitle;
@property(copy, nonatomic, readonly) NSString *parameterCompleteText;
@property(copy, nonatomic, readonly) NSString *parameterCloseButtonTitle;
@property(assign, nonatomic, readonly) SCLAlertViewStyle parameterStyle;
@property(assign, nonatomic, readonly) NSTimeInterval parameterDuration;
#pragma mark - Setters
@property(copy, nonatomic, readonly) SCLAlertViewShowBuilder *(^viewController)(UIViewController *viewController);
@property(copy, nonatomic, readonly) SCLAlertViewShowBuilder *(^image)(UIImage *image);
@property(copy, nonatomic, readonly) SCLAlertViewShowBuilder *(^color)(UIColor *color);
@property(copy, nonatomic, readonly) SCLAlertViewShowBuilder *(^title)(NSString *title);
@property(copy, nonatomic, readonly) SCLAlertViewShowBuilder *(^subTitle)(NSString *subTitle);
@property(copy, nonatomic, readonly) SCLAlertViewShowBuilder *(^completeText)(NSString *completeText);
@property(copy, nonatomic, readonly) SCLAlertViewShowBuilder *(^style)(SCLAlertViewStyle style);
@property(copy, nonatomic, readonly) SCLAlertViewShowBuilder *(^closeButtonTitle)(NSString *closeButtonTitle);
@property(copy, nonatomic, readonly) SCLAlertViewShowBuilder *(^duration)(NSTimeInterval duration);
- (void)showAlertView:(SCLAlertView *)alertView;
- (void)showAlertView:(SCLAlertView *)alertView onViewController:(UIViewController *)controller;
@property(copy, nonatomic, readonly) void (^show)(SCLAlertView *view, UIViewController *controller);
@end
@interface SCLALertViewTextFieldBuilder : SCLAlertViewBuilder__WithFluent
#pragma mark - Available later after adding
@property(weak, nonatomic, readonly) SCLTextView *textField;
#pragma mark - Setters
@property(copy, nonatomic, readonly) SCLALertViewTextFieldBuilder *(^title) (NSString *title);
@end
@interface SCLALertViewButtonBuilder : SCLAlertViewBuilder__WithFluent
#pragma mark - Available later after adding
@property(weak, nonatomic, readonly) SCLButton *button;
#pragma mark - Setters
@property(copy, nonatomic, readonly) SCLALertViewButtonBuilder *(^title) (NSString *title);
@property(copy, nonatomic, readonly) SCLALertViewButtonBuilder *(^target) (id target);
@property(copy, nonatomic, readonly) SCLALertViewButtonBuilder *(^selector) (SEL selector);
@property(copy, nonatomic, readonly) SCLALertViewButtonBuilder *(^actionBlock) (void(^actionBlock)(void));
@property(copy, nonatomic, readonly) SCLALertViewButtonBuilder *(^validationBlock) (BOOL(^validationBlock)(void));
@end
@interface SCLAlertViewBuilder : SCLAlertViewBuilder__WithFluent
#pragma mark - Parameters
@property (strong, nonatomic, readonly) SCLAlertView *alertView;
#pragma mark - Init
- (instancetype)init;
- (instancetype)initWithNewWindow;
- (instancetype)initWithNewWindowWidth:(CGFloat)width;
#pragma mark - Properties
@property(copy, nonatomic) SCLAlertViewBuilder *(^cornerRadius) (CGFloat cornerRadius);
@property(copy, nonatomic) SCLAlertViewBuilder *(^tintTopCircle) (BOOL tintTopCircle);
@property(copy, nonatomic) SCLAlertViewBuilder *(^useLargerIcon) (BOOL useLargerIcon);
@property(copy, nonatomic) SCLAlertViewBuilder *(^labelTitle) (UILabel *labelTitle);
@property(copy, nonatomic) SCLAlertViewBuilder *(^viewText) (UITextView *viewText);
@property(copy, nonatomic) SCLAlertViewBuilder *(^activityIndicatorView) (UIActivityIndicatorView *activityIndicatorView);
@property(copy, nonatomic) SCLAlertViewBuilder *(^shouldDismissOnTapOutside) (BOOL shouldDismissOnTapOutside);
@property(copy, nonatomic) SCLAlertViewBuilder *(^soundURL) (NSURL *soundURL);
@property(copy, nonatomic) SCLAlertViewBuilder *(^attributedFormatBlock) (SCLAttributedFormatBlock attributedFormatBlock);
@property(copy, nonatomic) SCLAlertViewBuilder *(^completeButtonFormatBlock) (CompleteButtonFormatBlock completeButtonFormatBlock);
@property(copy, nonatomic) SCLAlertViewBuilder *(^buttonFormatBlock) (ButtonFormatBlock buttonFormatBlock);
@property(copy, nonatomic) SCLAlertViewBuilder *(^forceHideBlock) (SCLForceHideBlock forceHideBlock);
@property(copy, nonatomic) SCLAlertViewBuilder *(^hideAnimationType) (SCLAlertViewHideAnimation hideAnimationType);
@property(copy, nonatomic) SCLAlertViewBuilder *(^showAnimationType) (SCLAlertViewShowAnimation showAnimationType);
@property(copy, nonatomic) SCLAlertViewBuilder *(^backgroundType) (SCLAlertViewBackground backgroundType);
@property(copy, nonatomic) SCLAlertViewBuilder *(^customViewColor) (UIColor *customViewColor);
@property(copy, nonatomic) SCLAlertViewBuilder *(^backgroundViewColor) (UIColor *backgroundViewColor);
@property(copy, nonatomic) SCLAlertViewBuilder *(^iconTintColor) (UIColor *iconTintColor);
@property(copy, nonatomic) SCLAlertViewBuilder *(^circleIconHeight) (CGFloat circleIconHeight);
@property(copy, nonatomic) SCLAlertViewBuilder *(^extensionBounds) (CGRect extensionBounds);
@property(copy, nonatomic) SCLAlertViewBuilder *(^statusBarHidden) (BOOL statusBarHidden);
@property(copy, nonatomic) SCLAlertViewBuilder *(^statusBarStyle) (UIStatusBarStyle statusBarStyle);
#pragma mark - Custom Setters
@property(copy, nonatomic) SCLAlertViewBuilder *(^alertIsDismissed) (SCLDismissBlock dismissBlock);
@property(copy, nonatomic) SCLAlertViewBuilder *(^alertDismissAnimationIsCompleted) (SCLDismissAnimationCompletionBlock dismissAnimationCompletionBlock);
@property(copy, nonatomic) SCLAlertViewBuilder *(^alertShowAnimationIsCompleted) (SCLShowAnimationCompletionBlock showAnimationCompletionBlock);
@property(copy, nonatomic) SCLAlertViewBuilder *(^removeTopCircle)(void);
@property(copy, nonatomic) SCLAlertViewBuilder *(^addCustomView)(UIView *view);
@property(copy, nonatomic) SCLAlertViewBuilder *(^addTextField)(NSString *title);
@property(copy, nonatomic) SCLAlertViewBuilder *(^addCustomTextField)(UITextField *textField);
@property(copy, nonatomic) SCLAlertViewBuilder *(^addSwitchViewWithLabelTitle)(NSString *title);
@property(copy, nonatomic) SCLAlertViewBuilder *(^addTimerToButtonIndex)(NSInteger buttonIndex, BOOL reverse);
@property(copy, nonatomic) SCLAlertViewBuilder *(^setTitleFontFamily)(NSString *titleFontFamily, CGFloat size);
@property(copy, nonatomic) SCLAlertViewBuilder *(^setBodyTextFontFamily)(NSString *bodyTextFontFamily, CGFloat size);
@property(copy, nonatomic) SCLAlertViewBuilder *(^setButtonsTextFontFamily)(NSString *buttonsFontFamily, CGFloat size);
@property(copy, nonatomic) SCLAlertViewBuilder *(^addButtonWithActionBlock)(NSString *title, SCLActionBlock action);
@property(copy, nonatomic) SCLAlertViewBuilder *(^addButtonWithValidationBlock)(NSString *title, SCLValidationBlock validationBlock, SCLActionBlock action);
@property(copy, nonatomic) SCLAlertViewBuilder *(^addButtonWithTarget)(NSString *title, id target, SEL selector);
#pragma mark - Builders
@property(copy, nonatomic) SCLAlertViewBuilder *(^addButtonWithBuilder)(SCLALertViewButtonBuilder *builder);
@property(copy, nonatomic) SCLAlertViewBuilder *(^addTextFieldWithBuilder)(SCLALertViewTextFieldBuilder *builder);
@end
