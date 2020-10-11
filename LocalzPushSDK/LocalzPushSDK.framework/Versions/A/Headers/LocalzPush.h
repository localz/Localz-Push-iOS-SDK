//
//  LocalzPushSDK.h
//  LocalzPushSDK
//
//  Created by Melvin Artemas on 29/03/2015.
//  Copyright (c) 2015 Localz Pty Ltd. All rights reserved.
//
#import <UIKit/UIKit.h>
#import <CoreLocation/CoreLocation.h>
#import <Foundation/Foundation.h>
#import <UserNotifications/UserNotifications.h>

@class LocalzPush;

@protocol LocalzPushDelegate <NSObject>
@optional
- (void) LocalzPush:(LocalzPush * _Nonnull)LocalzPush failedToRegisterDevice:(NSError * _Nonnull)error;
- (void) LocalzPush:(LocalzPush * _Nonnull)LocalzPush failedToUpdateDevice:(NSError * _Nonnull)error;
- (void) LocalzPush:(LocalzPush * _Nonnull)LocalzPush didReceiveRemoteNotification:(NSDictionary * _Nullable)userInfo fetchCompletionHandler:(void(^ _Nullable)(UIBackgroundFetchResult result))completionHandler;
- (void) LocalzPushDidFinishRegistering:(LocalzPush * _Nonnull)LocalzPush;
@end

@interface LocalzPush : NSObject

@property (nullable,nonatomic,assign) id<LocalzPushDelegate, UNUserNotificationCenterDelegate> delegate;


/**
 * Returns the singleton instance of LocalzPush
 */
+ (LocalzPush * _Nonnull) shared;

/**
 *  Initialise service and register device with the given API Key and client Key. Call this method inside the AppDelegate's didFinishLaunching.
 *  This will setup push with default UIUserNotificationTypes and no categories. Use this init method if you want to have the flexibility to place the iOS Push notification permission popup in your app by calling [[LocalzPush shared] startLocalzPush].
 *
 *  @param appId appId provided by Localz
 *  @param appKey appKey provided by Localz
 *  @param config config for advance settings/debugging
 */
+ (void) initWithProjectId:(NSString * _Nonnull)appId projectKey:(NSString * _Nonnull)appKey config:(NSDictionary * _Nullable)config;

/**
 *  Initialise service and register device with the given API Key and client Key. Call this method inside the AppDelegate's didFinishLaunching.
 *  This will setup push with default UIUserNotificationTypes and no categories. 
 *
 *  @param appId appId provided by Localz
 *  @param appKey appKey provided by Localz
 *  @param start automatically starts Localz Push if it is not yet started previously. This may popup the iOS push notification permission dialog.
 *  @param config config for advance settings/debugging
 */
+ (void) initWithAppId:(NSString * _Nonnull)appId appKey:(NSString * _Nonnull)appKey start:(BOOL)start config:(NSDictionary * _Nullable)config;

/**
 *  Initialise service and register device with the given API Key and client Key. Call this method inside the AppDelegate's didFinishLaunching.
 *  This will setup push with default UIUserNotificationTypes and no categories.
 *  For versions greater than iOS 10 ONLY
 *
 *  @param appId appId provided by Localz
 *  @param appKey appKey provided by Localz
 *  @param start automatically starts Localz Push if it is not yet started previously. This may popup the iOS push notification permission dialog.
 *  @param options The notification types that your app supports. For a list of possible values, see the constants for the UNAuthorizationOptions type.
 *  @param categories A set of UNNotificationCategory objects that define the groups of actions a notification may include.
 *  @param config config for advance settings/debugging
 */
+ (void) initWithAppId:(NSString * _Nonnull)appId appKey:(NSString * _Nonnull)appKey start:(BOOL)start authorizationOptions:(UNAuthorizationOptions)options categories:(NSSet * _Nullable)categories config:(NSDictionary * _Nonnull)config;


/**
 *  Enables push notification with default alerts with default settings.
 *  Call this method when the time is right to prompt user to accept notifications.
 */
- (void) startLocalzPush;

/**
 *  Returns LocalzPush started status.
 *  @return true if Localz push is started, false if not.
 */
- (BOOL) isLocalzPushStarted;

/**
 *  Enables location services. If user has not yet enabled location services, this will prompt the permission dialog.
 *  This is required to be called prior to locating user via push notification. 
 *  Call this method when the time is right to prompt user to accept location services.
 */
- (void) enableLocationServices;

/**
 *  Register push notification device token for Push Notifications
 *
 *  @param deviceToken deviceToken from Apple
 */
- (void) appRegisteredForRemoteNotificationsWithDeviceToken:(NSData * _Nonnull)deviceToken;

/**
 *  Register push notification device token for Push Notifications and device name
 *
 *  @param deviceToken deviceToken from Apple
 *  @param deviceName the device name to identify this device on the console, e.g customerId
 */
- (void) appRegisteredForRemoteNotificationsWithDeviceToken:(NSData * _Nonnull)deviceToken deviceName:(NSString * _Nonnull)deviceName;

/**
 *  Handles the errors when registering for push notification.
 *
 *  @param error error returned from didFailToRegisterForRemoteNotificationsWithError
 */
- (void) appFailedToRegisterForRemoteNotificationsWithError:(NSError * _Nullable)error;

/**
 *  Handles the remote notification for LocalzPush purposes
 *
 *  @param userInfo dictionary of the push notification
 *  @param state state of the application. Default is to pass [UIApplication sharedApplication].applicationState.
 *  @param completionHandler block after fetch result
 */
- (void) appReceivedRemoteNotification:(NSDictionary * _Nonnull)userInfo applicationState:(UIApplicationState)state fetchCompletionHandler:(void (^ _Nullable)(UIBackgroundFetchResult))completionHandler;

- (void) appPerformFetchWithCompletionHandler:(void (^ _Nullable)(UIBackgroundFetchResult))completionHandler;

#pragma mark Push helpers

/**
 * Retrieve current device ID
 */
- (NSString * _Nullable) getDeviceId;

/**
 *  Returns true if push notification is enabled and UIUserNotificationType is not set to none
 */
+ (BOOL) isPushNotificationEnabled;

/**
 *  Returns true of location services is enabled
 *  on the device. Does not tell whether location has been authorized or not.
 */
+ (BOOL) isLocationServicesEnabledOnDevice;

/**
 *  Returns location services authorization status.
 *  Will return true if authorized for always or inuse only.
 */
+ (BOOL) isLocationServicesAuthorized;

/**
 *  Check if the background refresh is enabled
 *  @return true if enabled, false if not
 */
+ (BOOL) isBackgroundRefreshEnabled;

/**
 *  Set device name to be able to identify the device easily in the push console
 */
+ (void) deviceName:(NSString * _Nonnull)deviceName;

@end
