//
//  WDGClient.h
//  WilddogVideo
//
//  Created by Zheng Li on 8/16/16.
//  Copyright © 2016 WildDog. All rights reserved.
//

#import <Foundation/Foundation.h>

@class WDGSyncReference;
@class WDGVideoLocalStream;
@class WDGVideoRemoteStream;
@class WDGVideoOutgoingInvite;
@class WDGVideoParticipant;
@protocol WDGVideoConversationDelegate;

typedef NS_ENUM(NSUInteger, WDGVideoConversationMode) {
    WDGVideoConversationModeBasic,
    WDGVideoConversationModeAdvanced
};

NS_ASSUME_NONNULL_BEGIN

@interface WDGVideoConversation : NSObject

@property (nonatomic, assign, readonly) WDGVideoConversationMode mode;
@property (nonatomic, strong, readonly) NSString *conversationID;
@property (nonatomic, strong, readonly) NSString *userID;
@property (nonatomic, strong, readonly) WDGVideoLocalStream *localStream;
@property (nonatomic, strong, readonly) NSArray<WDGVideoParticipant *> *participants;

@property (nonatomic, weak) id<WDGVideoConversationDelegate> delegate;

- (WDGVideoOutgoingInvite *)inviteUser:(NSString *)userID error:(NSError * _Nullable * _Nullable)error;

- (void)disconnect;

- (WDGVideoParticipant * _Nullable)getParticipant:(NSString *)participantUserID;

@end

@protocol WDGVideoConversationDelegate <NSObject>
@optional

- (void)conversation:(WDGVideoConversation *)conversation didConnectParticipant:(WDGVideoParticipant *)participant;
- (void)conversation:(WDGVideoConversation *)conversation didFailToConnectParticipant:(WDGVideoParticipant *)participant error:(NSError *)error;
- (void)conversation:(WDGVideoConversation *)conversation didDisconnectParticipant:(WDGVideoParticipant *)participant;

@end

NS_ASSUME_NONNULL_END
