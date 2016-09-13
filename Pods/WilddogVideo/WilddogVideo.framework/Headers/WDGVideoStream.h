//
//  WDGVideoStream.h
//  WilddogVideo
//
//  Created by Zheng Li on 8/16/16.
//  Copyright © 2016 WildDog. All rights reserved.
//

#import <UIKit/UIKit.h>

@class WDGVideoView;

NS_ASSUME_NONNULL_BEGIN

@interface WDGVideoStream : NSObject

- (void)close;

- (void)attach:(WDGVideoView *)view;
- (void)detach:(WDGVideoView *)view;

- (void)enableAudio;
- (void)disableAudio;

- (void)enableVideo;
- (void)disableVideo;

@end

NS_ASSUME_NONNULL_END
