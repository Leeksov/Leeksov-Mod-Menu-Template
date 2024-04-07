#import "SCLAlertViewResponder.h"
@interface SCLAlertViewResponder ()
@property SCLAlertView *alertview;
@end
@implementation SCLAlertViewResponder
- (instancetype)init:(SCLAlertView *)alertview
{
    self.alertview = alertview;
    return self;
}
- (void)setTitletitle:(NSString *)title
{
    self.alertview.labelTitle.text = title;
}
- (void)setSubTitle:(NSString *)subTitle
{
    self.alertview.viewText.text = subTitle;
}
- (void)close
{
    [self.alertview hideView];
}
@end
