//
//  WDGVideoParticipant.h
//  WilddogVideo
//
//  Created by Zheng Li on 9/8/16.
//  Copyright © 2016 WildDog. All rights reserved.
//

#import <Foundation/Foundation.h>

@class WDGVideoRemoteStream;

NS_ASSUME_NONNULL_BEGIN

@interface WDGVideoParticipant : NSObject

@property (nonatomic, strong, readonly) NSString *userID;
@property (nonatomic, strong, readonly, nullable) WDGVideoRemoteStream *stream;

@end

NS_ASSUME_NONNULL_END
