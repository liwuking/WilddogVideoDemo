//
//  WDGVideoOutgoingInvite.h
//  WilddogVideo
//
//  Created by Zheng Li on 8/24/16.
//  Copyright © 2016 WildDog. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "WDGVideoInvite.h"

@class Wilddog;

NS_ASSUME_NONNULL_BEGIN

@interface WDGVideoOutgoingInvite : NSObject

@property (nonatomic, strong, readonly) NSString *toUserID;
@property (nonatomic, strong, readonly) NSString *conversationID;

@property (nonatomic, assign, readonly) WDGVideoInviteStatus status;

- (void)cancel;

@end

NS_ASSUME_NONNULL_END
