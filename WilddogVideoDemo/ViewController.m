//
//  ViewController.m
//  WilddogVideoDemo
//
//  Created by IMacLi on 16/9/12.
//  Copyright © 2016年 liwuyang. All rights reserved.
//

#import "ViewController.h"

#import "RoomViewController.h"
#import <WilddogAuth/WilddogAuth.h>

@interface ViewController ()
@property (weak, nonatomic) IBOutlet UITextField *textField;
@property(nonatomic,strong) WDGAuth *wilddogAuth;
@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view, typically from a nib.
}
- (IBAction)clickBtn:(id)sender {

    self.wilddogAuth = [WDGAuth authWithAppID:self.textField.text];

    [self.wilddogAuth signInAnonymouslyWithCompletion:^(WDGUser * _Nullable user, NSError * _Nullable error) {
        if (error) {
            NSLog(@"请在控制台为您的AppID开启匿名登录功能，错误信息: %@", error.localizedDescription);
            return ;
        }

         [self performSegueWithIdentifier:@"RoomViewController" sender:user];
    }];
}


#pragma mark - Navigation

- (void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender {

    RoomViewController *viewController = (RoomViewController *)[segue destinationViewController];
    viewController.wDGUser = sender;
    viewController.appid = self.textField.text;

}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

@end
