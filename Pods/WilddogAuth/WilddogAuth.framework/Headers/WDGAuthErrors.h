//
//  WilddogAuth.m
//  WilddogAuth
//
//  Created by junpengwang on 16/8/5.
//  Copyright © 2016年 Wilddog. All rights reserved.
//

#import <Foundation/Foundation.h>

/** @class WDGAuthErrors
 @discussion Error Codes common to all API Methods:
 
 - WDGAuthErrorCodeNetworkError - Indicates a network error occurred during the operation.
 
 - WDGAuthErrorCodeUserNotFound - Indicates the user account was not found. This could happen
 if the user account has been deleted.
 
 - WDGAuthErrorCodeUserTokenExpired - Indicates the current user’s token has expired, for
 example, the user may have changed account password on another device. You must prompt
 the user to sign in again on this device.
 
 - WDGAuthErrorCodeTooManyRequests - Indicates that the request has been blocked after an
 abnormal number of requests have been made from the caller device to the Wilddog Auth
 servers. Retry again after some time.
 
 - WDGAuthErrorCodeInvalidAPIKey - Indicates the application has been configured with an
 invalid API key.
 
 - WDGAuthErrorCodeAppNotAuthorized - Indicates the App is not authorized to use Wilddog
 Authentication with the provided API Key. Go to the Wilddog API Console and check under
 the credentials tab that the API key you are using has your application’s bundle ID
 whitelisted.
 
 - WDGAuthErrorCodeKeychainError - Indicates an error occurred while accessing the keychain.
 The NSLocalizedFailureReasonErrorKey and NSUnderlyingErrorKey fields in the
 NSError.userInfo dictionary will contain more information about the error encountered.
 - WDGAuthErrorCodeInternalError - Indicates an internal error occurred. Please report the
 error back to us with the entire NSError object.
 
 @discussion Common error codes for WDGUser operations:
 
 - WDGAuthErrorCodeInvalidUserToken - Indicates that the signed-in user's refresh token,
 that holds session information, is invalid. You must prompt the user to sign in again
 on this device.
 
 - WDGAuthErrorCodeUserDisabled - Indicates the user's account is disabled and can no longer
 be used until enabled again from within the Users panel in the Wilddog console.
 
 */
@interface WDGAuthErrors : NSObject

/** @var WDGAuthErrorDomain
 @brief The Wilddog Auth error domain.
 */
extern NSString *const WDGAuthErrorDomain;

/** @var WDGAuthErrorNameKey
 @brief The name of the key for the "error_name" string in the NSError userinfo dictionary.
 */
extern NSString *const WDGAuthErrorNameKey;

/** @enum WDGAuthErrorCode
 @brief Error codes used by Wilddog Auth.
 */
typedef NS_ENUM(NSInteger, WDGAuthErrorCode) {
    /** Indicates a validation error with the custom token.
     */
    WDGAuthErrorCodeInvalidCustomToken = 17000,
    
    /** Indicates the service account and the API key belong to different projects.
     */
    WDGAuthErrorCodeCustomTokenMismatch = 17002,
    
    /** Indicates the IDP token or requestUri is invalid.
     */
    WDGAuthErrorCodeInvalidCredential = 17004,
    
    /** Indicates the user's account is disabled on the server.
     */
    WDGAuthErrorCodeUserDisabled = 17005,
    
    /** Indicates the administrator disabled sign in with the specified identity provider.
     */
    WDGAuthErrorCodeOperationNotAllowed = 17006,
    
    /** Indicates the email used to attempt a sign up is already in use.
     */
    WDGAuthErrorCodeEmailAlreadyInUse = 17007,
    
    /** Indicates the email is invalid.
     */
    WDGAuthErrorCodeInvalidEmail = 17008,
    
    /** Indicates the user attempted sign in with a wrong password.
     */
    WDGAuthErrorCodeWrongPassword = 17009,
    
    /** Indicates that too many requests were made to a server method.
     */
    WDGAuthErrorCodeTooManyRequests = 17010,
    
    /** Indicates the user account was not found.
     */
    WDGAuthErrorCodeUserNotFound = 17011,
    
    /** Indicates account linking is required.
     */
    WDGAuthErrorCodeAccountExistsWithDifferentCredential = 17012,
    
    /** Same enum as @c WDGAuthErrorCodeAccountExistsWithDifferentCredential ,
     but with incorrect spelling. Only exists for backwards compatiblity.
     */
    WDGAuthErrrorCodeAccountExistsWithDifferentCredential = 17012,
    
    /** Indicates the user has attemped to change email or password more than 5 minutes after
     signing in.
     */
    WDGAuthErrorCodeRequiresRecentLogin = 17014,
    
    /** Indicates an attempt to link a provider to which the account is already linked.
     */
    WDGAuthErrorCodeProviderAlreadyLinked = 17015,
    
    /** Indicates an attempt to unlink a provider that is not linked.
     */
    WDGAuthErrorCodeNoSuchProvider = 17016,
    
    /** Indicates user's saved auth credential is invalid, the user needs to sign in again.
     */
    WDGAuthErrorCodeInvalidUserToken = 17017,
    
    /** Indicates a network error occurred (such as a timeout, interrupted connection, or
     unreachable host). These types of errors are often recoverable with a retry. The @c
     NSUnderlyingError field in the @c NSError.userInfo dictionary will contain the error
     encountered.
     */
    WDGAuthErrorCodeNetworkError = 17020,
    
    /** Indicates the saved token has expired, for example, the user may have changed account
     password on another device. The user needs to sign in again on the device that made this
     request.
     */
    WDGAuthErrorCodeUserTokenExpired = 17021,
    
    /** Indicates an invalid API key was supplied in the request.
     */
    WDGAuthErrorCodeInvalidAPIKey = 17023,
    
    /** Indicates that an attempt was made to reauthenticate with a user which is not the current
     user.
     */
    WDGAuthErrorCodeUserMismatch = 17024,
    
    /** Indicates an attempt to link with a credential that has already been linked with a
     different Wilddog account
     */
    WDGAuthErrorCodeCredentialAlreadyInUse = 17025,
    
    /** Indicates an attempt to set a password that is considered too weak.
     */
    WDGAuthErrorCodeWeakPassword = 17026,
    
    /** Indicates the App is not authorized to use Wilddog Authentication with the
     provided API Key.
     */
    WDGAuthErrorCodeAppNotAuthorized = 17028,
    
    /** Indicates an error occurred while attempting to access the keychain.
     */
    WDGAuthErrorCodeKeychainError = 17995,
    
    /** Indicates an internal error occurred.
     */
    WDGAuthErrorCodeInternalError = 17999,
};

@end
