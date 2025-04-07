/**
 * @file LWPrintDataProvider.h
 * @brief LWPrint SDK LWPrintDataProvider Class definition
 * @par Copyright:
 * Copyright (C) SEIKO EPSON CORPORATION 2013-2019. All rights reserved.<BR>
 */

#import <Foundation/Foundation.h>

/**
 * LWPrintDataProvider
 * @brief Provider of contents data
 */
@interface LWPrintDataProvider : NSObject

/**
 * beginJob of Application is processed.
 */
- (void)startOfPrint;

/**
 * endJob of Application is processed.
 */
- (void)endOfPrint;

/**
 * beginPage of Application is processed.
 */
- (void)startPage;

/**
 * endPage of Application is processed.
 */
- (void)endPage;

/**
 * number of pages to print is returned.
 * @return  number of pages
 */
- (NSInteger)numberOfPages;

/**
 * Form data is returned.
 * @param pageIndex Page number to print
 * @return form data
 */
- (NSDictionary *)formDataForPage:(NSInteger)pageIndex;

/**
 * Content data is returned.
 * @param contentName content name
 * @param pageIndex Page number to print
 * @return form data
 */
- (id)contentData:(NSString *)contentName forPage:(NSInteger)pageIndex;

@end
