//
//  WDGVideoInvite.h
//  WilddogVideo
//
//  Created by Zheng Li on 9/6/16.
//  Copyright © 2016 WildDog. All rights reserved.
//

#import <Foundation/Foundation.h>

@class WDGVideoConversation;

typedef NS_ENUM(NSUInteger, WDGVideoInviteStatus)
{
    /**
     *  邀请刚刚被发送或接收
     */
    WDGVideoInviteStatusPending = 0,

    /**
     *  被邀请方接受邀请
     */
    WDGVideoInviteStatusAccepting,

    /**
     *  邀请方确认邀请被接收，双方建立会话
     */
    WDGVideoInviteStatusAccepted,

    /**
     *  邀请被本地客户端拒绝
     */
    WDGVideoInviteStatusRejected,

    /**
     *  邀请被邀请方撤销
     */
    WDGVideoInviteStatusCancelled,

    /**
     *  邀请被接受但无法建立会话
     */
    WDGVideoInviteStatusFailed
};

typedef void (^WDGVideoInviteAcceptanceBlock)(WDGVideoConversation * _Nullable conversation, NSError * _Nullable error);
