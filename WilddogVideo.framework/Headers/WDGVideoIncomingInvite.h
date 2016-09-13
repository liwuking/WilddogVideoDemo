//
//  WDGVideoIncomingInvite.h
//  WilddogVideo
//
//  Created by Zheng Li on 8/24/16.
//  Copyright © 2016 WildDog. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "WDGVideoInvite.h"

@class WDGVideoConversation;

NS_ASSUME_NONNULL_BEGIN

@interface WDGVideoIncomingInvite : NSObject

@property (nonatomic, strong, readonly) NSString *fromUserID;
@property (nonatomic, strong, readonly) NSString *conversationID;

@property (nonatomic, assign, readonly) WDGVideoInviteStatus status;

- (void)acceptWithCompletionHandler:(WDGVideoInviteAcceptanceBlock)completionHandler;
- (void)reject;

@end

NS_ASSUME_NONNULL_END
