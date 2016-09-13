//
//  UserListTableViewController.h
//  WilddogVideoDemo
//
//  Created by IMacLi on 16/9/13.
//  Copyright © 2016年 liwuyang. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <Wilddog.h>
typedef void (^selectedUser)(NSString *user);

@interface UserListTableViewController : UITableViewController
@property(nonatomic, assign) NSString *userID;
@property(nonatomic, strong)Wilddog *wilddog;
@property(nonatomic, strong) selectedUser selectedUserBlock;

@end
