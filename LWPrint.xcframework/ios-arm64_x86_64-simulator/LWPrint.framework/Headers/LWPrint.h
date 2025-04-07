/**
 * @file    LWPrint.h
 * @brief   LWPrint SDK LWPrint Class definition
 * @par     Copyright:
 * Copyright (C) SEIKO EPSON CORPORATION 2013-2019. All rights reserved.<BR>
 */

#import <Foundation/Foundation.h>

typedef NS_ENUM(NSInteger, LWPrintTapeOperation) {
	TapeOperationFeed = 0,
	TapeOperationFeedAndCut = -1
};

typedef NS_ENUM(NSInteger, LWPrintTapeWidth) {
	TapeWidthNone = 0,
	TapeWidth4mm = 1,
	TapeWidth6mm = 2,
	TapeWidth9mm = 3,
	TapeWidth12mm = 4,
	TapeWidth18mm = 5,
	TapeWidth24mm = 6,
	TapeWidth36mm = 7,
	TapeWidth24mmCable = 8,
	TapeWidth36mmCable = 9,
	TapeWidth50mm = 10,
	TapeWidth100mm = 11,
    TapeWidthUnknown = -1
};


typedef NS_ENUM(NSInteger, LWPrintTapeKind) {
	TapeKindNormal = 0
};

typedef NS_ENUM(NSInteger, LWPrintPrintingPhase) {
	PrintingPhasePrepare = 1,
	PrintingPhaseProcessing = 2,
    PrintingPhaseWaitingForPrint = 3,
	PrintingPhaseComplete = 4
};

typedef NS_ENUM(NSInteger, LWPrintConnectionStatus) {
    ConnectionStatusNoError = 0,
    ConnectionStatusConnectionFailed = -1,     /* Connection failed */
    ConnectionStatusDisconnected = -2,         /* Disconnect */
    ConnectionStatusDeviceBusy = -3,           /* Printer busy */
    ConnectionStatusOutOfMemory = -4,          /* Out of memory */
    ConnectionStatusDeviceError = -5,          /* Device error */
    ConnectionStatusCommunicationError = -6    /* Communication error */
};

typedef NS_ENUM(NSUInteger, LWPrintStatusError) {
	StatusErrorNoError = 0x00,
	StatusErrorCutterError = 0x01,
	StatusErrorNoTapeCartridge = 0x06,
	StatusErrorHeadOverheated = 0x15,
	StatusErrorPrinterCancel = 0x20,
	StatusErrorCoverOpen = 0x21,
	StatusErrorLowVoltage = 0x22,
	StatusErrorPowerOffCancel = 0x23,
    StatusErrorTapeEjectError = 0x24,
	StatusErrorTapeFeedError = 0x30,
	StatusErrorInkRibbonSlack = 0x40,
	StatusErrorInkRibbonShort = 0x41,
	StatusErrorTapeEnd = 0x42,
	StatusErrorCutLabelError = 0x43,
	StatusErrorTemperatureError = 0x44,
	StatusErrorInsufficientParameters = 0x45,
    
    StatusErrorConnectionFailed = 0xfffffff0,
    
    StatusErrorOtherUsing = 0xfffffffa,
    StatusErrorFirmwareUpdating = 0xfffffffb,
    StatusErrorDeviceUsing = 0xfffffffc,
    
    StatusErrorUnknownError = 0xffffffff
    
};

typedef NS_ENUM(NSInteger, LWPrintTapeCut) {
    TapeCutEachLabel = 0,
    TapeCutAfterJob = 1,
    TapeCutNotCut = 2
};

extern NSString *const LWPrintParameterKeyCopies;        /* 1 ... 99 */
extern NSString *const LWPrintParameterKeyTapeCut;       /* LWPrintParameterTapeCut */
extern NSString *const LWPrintParameterKeyHalfCut;       /* YES:Half cut (BOOL) */
extern NSString *const LWPrintParameterKeyPrintSpeed;    /* YES:Low speed (BOOL) */
extern NSString *const LWPrintParameterKeyDensity;       /* -5 ... 5 */
extern NSString *const LWPrintParameterKeyTapeWidth;     /* LWPrintTapeWidth */

extern NSString *const LWPrintStatusKeyTapeKind;
extern NSString *const LWPrintStatusKeyTapeWidth;
extern NSString *const LWPrintStatusKeyDeviceError;

@protocol LWPrintDelegate;
@class LWPrintDataProvider;
@class UIImage;

/**
 * LWPrint
 * @brief   Management of a printer (print/status/tape cut/etc.)
 */
@interface LWPrint : NSObject

/**
 * LWPrint SDK version
 * @return version string
 */
+ (NSString *)version;

/**
 * set delegate
 */
@property (nonatomic, weak) id<LWPrintDelegate> delegate;

/**
 * job progress
 * @return  Progress of a print
 */
@property(nonatomic, readonly) float progressOfPrint;
/**
 * page number of printing
 * @return  page number
 */
@property(nonatomic, readonly)  NSInteger pageNumberOfPrinting;

/**
 * set printer information
 * @param	printerInfo	Printer information
 */
- (void)setPrinterInformation:(NSDictionary *)printerInformation;

/**
 * print for application
 * @param	dataProvider Data provider of Application
 * @param   printParameter print parameter
 * @li @c   LWPrintParameterKeyCopies 1 ... 99
 * @li @c   LWPrintParameterKeyTapeCut LWPrintParameterTapeCut
 * @li @c   LWPrintParameterKeyHalfCut YES:Half cut (BOOL)
 * @li @c   LWPrintParameterKeyLowSpeed YES:Low speed (BOOL)
 * @li @c   LWPrintParameterKeyDensity  -5 ... 5
 */
- (void)doPrint:(LWPrintDataProvider *)dataProvider printParameter:(NSDictionary *)printParameter;

/**
 * print for application
 * @param   printParameter print parameter
 * @li @c   LWPrintParameterKeyCopies 1 ... 99
 * @li @c   LWPrintParameterKeyTapeCut LWPrintParameterTapeCut
 * @li @c   LWPrintParameterKeyHalfCut YES:Half cut (BOOL)
 * @li @c   LWPrintParameterKeyLowSpeed YES:Low speed (BOOL)
 * @li @c   LWPrintParameterKeyDensity  -5 ... 5
 * @param   printData print data
 */
- (void)doPrint:(NSDictionary *)printParameter printData:(NSData *)printData;

/**
 * print for application
 * @param	dataProvider Data provider of Application
 * @param   printParameter print parameter
 * @li @c   LWPrintParameterKeyCopies 1 ... 99
 * @li @c   LWPrintParameterKeyTapeCut LWPrintParameterTapeCut
 * @li @c   LWPrintParameterKeyHalfCut YES:Half cut (BOOL)
 * @li @c   LWPrintParameterKeyLowSpeed YES:Low speed (BOOL)
 * @li @c   LWPrintParameterKeyDensity  -5 ... 5
 * @param   printData print data
 */
- (void)doPrint:(LWPrintDataProvider *)dataProvider printParameter:(NSDictionary *)printParameter printData:(NSData *)printData;

/**
 * print for application
 * @param	dataProvider Data provider of Application
 * @param   printParameter print parameter
 * @li @c   LWPrintParameterKeyCopies 1 ... 99
 * @li @c   LWPrintParameterKeyTapeCut LWPrintParameterTapeCut
 * @li @c   LWPrintParameterKeyHalfCut YES:Half cut (BOOL)
 * @li @c   LWPrintParameterKeyLowSpeed YES:Low speed (BOOL)
 * @li @c   LWPrintParameterKeyDensity  -5 ... 5
 * @param   printData print data
 * @param   margin print margin
 */
- (void)doPrint:(LWPrintDataProvider *)dataProvider printParameter:(NSDictionary *)printParameter printData:(NSData *)printData margin:(NSUInteger)margin;

/**
 * get label image
 * @param	dataProvider Data provider of Application
 * @param   printParameter print parameter
 * @li @c   LWPrintParameterKeyCopies 1 ... 99
 * @li @c   LWPrintParameterKeyTapeCut LWPrintParameterTapeCut
 * @li @c   LWPrintParameterKeyHalfCut YES:Half cut (BOOL)
 * @li @c   LWPrintParameterKeyLowSpeed YES:Low speed (BOOL)
 * @li @c   LWPrintParameterKeyDensity  -5 ... 5
 */
- (UIImage *)labelImage:(LWPrintDataProvider *)dataProvider printParameter:(NSDictionary *)printParameter;

/**
 * get label images
 * @param	dataProvider Data provider of Application
 * @param   printParameter print parameter
 * @li @c   LWPrintParameterKeyCopies 1 ... 99
 * @li @c   LWPrintParameterKeyTapeCut LWPrintParameterTapeCut
 * @li @c   LWPrintParameterKeyHalfCut YES:Half cut (BOOL)
 * @li @c   LWPrintParameterKeyLowSpeed YES:Low speed (BOOL)
 * @li @c   LWPrintParameterKeyDensity  -5 ... 5
 */
- (NSArray *)labelImages:(LWPrintDataProvider *)dataProvider printParameter:(NSDictionary *)printParameter;

/**
 * tape feed and tape send
 * @param	mode feed or send
 * @li @c   TapeOperationFeed
 * @li @c   TapeOperationFeedAndCut
 */
- (void)doTapeFeed:(LWPrintTapeOperation)mode;

/**
 * resume job
 */
- (void)resumeOfPrint;

/**
 * cancel job
 */
- (void)cancelPrint;

/**
 * get printers tatus
 * @return  NSDictionary status dictionary
 */
- (NSDictionary *)fetchPrinterStatus;

/**
 * get tape width from status dictionary
 * @param   status status dictionary
 * @return  LWPrintTapeWidth
 */
- (LWPrintTapeWidth)tapeWidthFromStatus:(NSDictionary *)status;

/**
 * get tape kind from status dictionary
 * @param   status status dictionary
 * @return  LWPrintTapeKind
 */
- (LWPrintTapeKind)tapeKindFromStatus:(NSDictionary *)status;

/**
 * get device error from status dictionary
 * @param   status status dictionary
 * @return  LWPrintDeviceStatus
 */
- (LWPrintStatusError)deviceErrorFromStatus:(NSDictionary *)status;

/**
 * tape width which can be used
 * @return  LWPrintDeviceStatus
 */
- (NSArray *)kindOfTape;

/**
 * model name
 * @return  model name
 */
- (NSString *)modelName;

/**
 * printer resolution
 * @return  resolution (180/270/300/360)
 */
- (NSInteger)resolution;

/**
 * printer equipped with the half cut
 * @return YES:equipment
 */
- (BOOL)isSupportHalfCut;

/**
 * low-speed printing supported
 * @return YES:supported
 */
- (BOOL)isPrintSpeedSupport;

@end

/**
 * LWPrintDelegate
 * @brief   LWPrint delegate
 */
@protocol LWPrintDelegate <NSObject>

@optional

/**
 * called when print phase changes
 * @param   lwPrint caller
 * @param   jobPhase job phase LWPrintJobPhase
 */
- (void)lwPrint:(LWPrint *)lwPrint didChangePrintOperationPhase:(LWPrintPrintingPhase)jobPhase;

/**
 * called when a print job is suspended
 * @param   lwPrint caller
 * @param   errorStatus error status LWPrintErrorStatus
 * @param   deviceStatus device status LWPrintDeviceStatus
 */
- (void)lwPrint:(LWPrint *)lwPrint didSuspendPrintOperation:(LWPrintConnectionStatus)errorStatus deviceStatus:(LWPrintStatusError)deviceStatus;

/**
 * called when a print job is aborted
 * @param   lwPrint caller
 * @param   errorStatus error status LWPrintErrorStatus
 * @param   deviceStatus device status LWPrintDeviceStatus
 */
- (void)lwPrint:(LWPrint *)lwPrint didAbortPrintOperation:(LWPrintConnectionStatus)errorStatus deviceStatus:(LWPrintStatusError)deviceStatus;

/**
 * called when tape feed phase changes
 * @param   lwPrint caller
 * @param   jobPhase job phase LWPrintJobPhase
 */
- (void)lwPrint:(LWPrint *)lwPrint didChangeTapeFeedOperationPhase:(LWPrintPrintingPhase)jobPhase;
/**
 * called when a tape feed is aborted
 * @param   lwPrint caller
 * @param   errorStatus error status LWPrintErrorStatus
 * @param   deviceStatus device status LWPrintDeviceStatus
 */
- (void)lwPrint:(LWPrint *)lwPrint didAbortTapeFeedOperation:(LWPrintConnectionStatus)errorStatus deviceStatus:(LWPrintStatusError)deviceStatus;

@end
