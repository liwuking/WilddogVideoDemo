//
//  WDGVideoErrors.h
//  WilddogVideo
//
//  Created by Zheng Li on 9/8/16.
//  Copyright © 2016 WildDog. All rights reserved.
//

#import <Foundation/Foundation.h>

extern NSString *const WDGVideoErrorDomain;

typedef NS_ENUM(NSInteger, WDGVideoErrorCode)
{
    /**
     *  未知错误
     */
    WDGVideoErrorCodeUnknown = -1,

    /**
     *  被邀请者拒绝您的邀请
     */
    WDGVideoErrorCodeConversationRejected,

    /**
     *  被邀请者繁忙，不能响应您的邀请
     */
    WDGVideoErrorCodeConversationIgnored,

    /**
     *  会话无法开启
     */
    WDGVideoErrorCodeConversationFailed,

    /**
     *  表明尚不支持特定功能
     *  @note: 详细信息见`localizedDescription`字段。
     */
    WDGVideoErrorCodeFeatureNotSupported,

};
