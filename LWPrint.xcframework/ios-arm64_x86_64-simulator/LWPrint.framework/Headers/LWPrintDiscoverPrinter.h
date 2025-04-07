/**
 * @file LWPrintDiscoverPrinter.h
 * @brief LWPrint SDK LWPrintDiscoverPrinter Class definition
 * @par Copyright:
 * Copyright (C) SEIKO EPSON CORPORATION 2013-2019. All rights reserved.<BR>
 */

typedef NS_OPTIONS(NSUInteger, LWPrintDiscoverConnectionType) {
    ConnectionTypeAll           = 0,
    ConnectionTypeNetwork       = 1 << 0,
    ConnectionTypeBluetooth     = 1 << 1,
};

extern NSString * const LWPrintPrinterInfoBonjourName;
extern NSString * const LWPrintPrinterInfoType;
extern NSString * const LWPrintPrinterInfoDomain;
extern NSString * const LWPrintPrinterInfoMDL;
extern NSString * const LWPrintPrinterInfoMFG;
extern NSString * const LWPrintPrinterInfoProduct;
extern NSString * const LWPrintPrinterInfoIPAddress;
extern NSString * const LWPrintPrinterInfoBonjourHostName;

@protocol LWPrintDiscoverPrinterDelegate;

/**
 * LWPrintDiscoverPrinter
 * @brief Discovery of printers
 */
@interface LWPrintDiscoverPrinter : NSObject {
@private
}

@property (nonatomic,weak)   id <LWPrintDiscoverPrinterDelegate>delegate;

/**
 * init
 * @param	models models to search
 * @return  LWPrintDiscoverPrinter object
 */
- (id)initWithModels:(NSArray *)models connectionType:(LWPrintDiscoverConnectionType)connectionType;

/**
 * start discover
 */
- (void)startDiscover;

/**
 * stop discover
 */
- (void)stopDiscover;

@end

/**
 * LWPrintDiscoverPrinterDelegate
 * @brief LWPrintDiscoverPrinter delegate
 */
@protocol LWPrintDiscoverPrinterDelegate <NSObject>
@optional

/**
 * called when a printer is discovered.
 * @param   discoverPrinter caller
 @ @param   preinters discovered printer
 */
- (void)discoverPrinter:(LWPrintDiscoverPrinter *)discoverPrinter didFindPrinter:(NSDictionary *)printerInformation;

/**
 * called when a printer is removed.
 * @param   discoverPrinter caller
 @ @param   preinters removed printer
 */
- (void)discoverPrinter:(LWPrintDiscoverPrinter *)discoverPrinter didRemovePrinter:(NSDictionary *)printerInformation;

@end


