#import <Foundation/Foundation.h>

// Constants
extern NSString * const LWPrintParameterKeyCopies;
extern NSString * const LWPrintParameterKeyDensity;
extern NSString * const LWPrintParameterKeyHalfCut;
extern NSString * const LWPrintParameterKeyPrintSpeed;
extern NSString * const LWPrintParameterKeyTapeCut;
extern NSString * const LWPrintParameterKeyTapeWidth;
extern NSString * const LWPrintPrinterInfoBonjourName;

// LWPrint Class
@interface LWPrint : NSObject
@end

// LWPrintDataProvider Class
@interface LWPrintDataProvider : NSObject
@end

// LWPrintDiscoverPrinter Class
@interface LWPrintDiscoverPrinter : NSObject
@end
