//
//  WDGVideoLocalStream.h
//  WilddogVideo
//
//  Created by Zheng Li on 8/23/16.
//  Copyright © 2016 WildDog. All rights reserved.
//

#import "WDGVideoStream.h"

@class WDGVideoConfiguration;

typedef NS_ENUM(NSUInteger, WDGVideoConstraints) {
    WDGVideoConstraintsOff = 0,
    WDGVideoConstraintsLow,
    WDGVideoConstraintsStandard,
    WDGVideoConstraintsStandard16x9,
    WDGVideoConstraintsHigh16x9,
};

NS_ASSUME_NONNULL_BEGIN

@interface WDGVideoLocalStreamConfiguration : NSObject

@property (nonatomic, assign) BOOL audioOn;
@property (nonatomic, assign) WDGVideoConstraints videoOption;

- (instancetype)init;
- (instancetype)initWithVideoOption:(WDGVideoConstraints)videoOption audioOn:(BOOL)audioOn;

@end

@interface WDGVideoLocalStream : WDGVideoStream

- (void)flipCamera;

@end

NS_ASSUME_NONNULL_END
