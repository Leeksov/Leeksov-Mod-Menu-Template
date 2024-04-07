#import "Macros.h"
#import "Obfuscate.h"
void setup() {
  patchOffset(ENCRYPTOFFSET("0x1002DB3C8"), ENCRYPTHEX("0xC0035FD6"));
  patchOffset(ENCRYPTOFFSET("0x10020D2D4"), ENCRYPTHEX("0x00008052C0035FD6"));
  patchOffset(ENCRYPTOFFSET("0x10020D3A8"), ENCRYPTHEX("0x00F0271E0008201EC0035FD6"));
  patchOffset(ENCRYPTOFFSET("0x10020D3A8"), ENCRYPTHEX("00F0271E0008201EC0035FD6"));
  patchOffset(ENCRYPTOFFSET("0x10020D3A8"), ENCRYPTHEX("00 F0 27 1E 00 08 20 1E C0 03 5F D6"));
  [switches addSwitch:NSSENCRYPT("Masskill")
    description:NSSENCRYPT("Teleport all enemies to you without them knowing")
  ];
  [switches addOffsetSwitch:NSSENCRYPT("God Mode")
    description:NSSENCRYPT("You can't die")
    offsets: {
      ENCRYPTOFFSET("0x1005AB148")
    }
    bytes: {
      ENCRYPTHEX("0x00E0BF12C0035FD6")
    }
  ];
  [switches addOffsetSwitch:NSSENCRYPT("One Hit Kill")
    description:NSSENCRYPT("Enemy will die instantly")
    offsets: {
      ENCRYPTOFFSET("0x1001BB2C0"),
      ENCRYPTOFFSET("0x1002CB3B0"),
      ENCRYPTOFFSET("0x1002CB3B8")
    }
    bytes: {
      ENCRYPTHEX("0x00E0BF12C0035FD6"),
      ENCRYPTHEX("0xC0035FD6"),
      ENCRYPTHEX("0x00F0271E0008201EC0035FD6")
    }
  ];
  [switches addTextfieldSwitch:NSSENCRYPT("Custom Gold")
    description:NSSENCRYPT("Here you can enter your own gold amount")
    inputBorderColor:UIColorFromHex(0xBD0000)
  ];

  [switches addSliderSwitch:NSSENCRYPT("Custom Move Speed")
    description:NSSENCRYPT("Set your custom move speed")
    minimumValue:0
    maximumValue:10
    sliderColor:UIColorFromHex(0xBD0000)
  ];
}
void setupMenu() {
  [menu setFrameworkName:"UnityFramework"];
  menu = [[Menu alloc]  
            initWithTitle:NSSENCRYPT("@@APPNAME@@  - Mod Menu")
            titleColor:[UIColor colorWithRed: 0.33 green: 0.00 blue: 0.59 alpha: 0.80]
            titleFont:NSSENCRYPT("Copperplate-Bold")
            credits:NSSENCRYPT("This Mod Menu has been made by @@USER@@, do not share this without proper credits and my permission. \n\nEnjoy!")
            headerColor:[UIColor colorWithRed: 0.00 green: 0.55 blue: 0.01 alpha: 0.65]
            switchOffColor:[UIColor colorWithRed: 0.00 green: 0.00 blue: 0.00 alpha: 0.60]
            switchOnColor:[UIColor colorWithRed: 0.33 green: 0.00 blue: 0.59 alpha: 0.80]
            switchTitleFont:NSSENCRYPT("Copperplate-Bold")
            switchTitleColor:[UIColor colorWithRed: 0.00 green: 0.55 blue: 0.01 alpha: 0.65]
            infoButtonColor:UIColorFromHex(0xBD0000)
            maxVisibleSwitches:5 
            menuWidth:440
            menuIcon:@"bnVsbA=="
            menuButton:@"bnVsbA=="];  
     setup();
}
static void didFinishLaunching(CFNotificationCenterRef center, void *observer, CFStringRef name, const void *object, CFDictionaryRef info) {
  timer(5) {
setupMenu();
  });
}
%ctor {
  CFNotificationCenterAddObserver(CFNotificationCenterGetLocalCenter(), NULL, &didFinishLaunching, (CFStringRef)UIApplicationDidFinishLaunchingNotification, NULL, CFNotificationSuspensionBehaviorDeliverImmediately);
}