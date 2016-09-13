//
//  WDGVideo.h
//  WilddogVideo
//
//  Created by Zheng Li on 8/19/16.
//  Copyright © 2016 WildDog. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "WDGVideoInvite.h"
#import "WDGVideoConversation.h"

@class Wilddog;
@class WDGUser;
@class WDGVideoConversation;
@class WDGVideoIncomingInvite;
@class WDGVideoOutgoingInvite;
@class WDGVideoLocalStream;
@class WDGVideoLocalStreamConfiguration;
@protocol WDGVideoClientDelegate;

NS_ASSUME_NONNULL_BEGIN

@interface WDGVideoClient : NSObject

@property(nonatomic, strong) id<WDGVideoClientDelegate> delegate;

- (instancetype)init NS_UNAVAILABLE;

- (nullable instancetype)initWithWilddog:(Wilddog *)wilddog user:(WDGUser *)user NS_DESIGNATED_INITIALIZER;

- (WDGVideoOutgoingInvite *)inviteUser:(NSString *)userID
                      conversationMode:(WDGVideoConversationMode)conversationMode
                            completion:(WDGVideoInviteAcceptanceBlock)completionHandler;

- (WDGVideoOutgoingInvite *)inviteUser:(NSString *)userID
                           localStream:(WDGVideoLocalStream *)localStream
                      conversationMode:(WDGVideoConversationMode)conversationMode
                            completion:(WDGVideoInviteAcceptanceBlock)completionHandler;

- (WDGVideoLocalStream *)localStreamWithConfiguration:(WDGVideoLocalStreamConfiguration *)configuration;

@end

@protocol WDGVideoClientDelegate <NSObject>
@optional

- (void)wilddogVideoClient:(WDGVideoClient *)videoClient didReceiveInvite:(WDGVideoIncomingInvite *)invite;
- (void)wilddogVideoClient:(WDGVideoClient *)videoClient inviteDidCancel:(WDGVideoIncomingInvite *)invite;

@end

NS_ASSUME_NONNULL_END
