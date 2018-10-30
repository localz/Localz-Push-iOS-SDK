//
//  LocalzPushNotificationExtension.h
//  LocalzPushSDK
//
//  Created by Daniel Sykes-Turner on 3/8/17.
//  Copyright © 2017 Localz Pty Ltd. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <UserNotifications/UserNotifications.h>

@interface LocalzPushNotificationExtension : NSObject

/**
 * Returns the singleton instance of LocalzPush
 */
+ (LocalzPushNotificationExtension * _Nonnull) shared;

/**
 *  Supply the notifiation extension instance with authentication keys
 *
 *  @param appId The ID of the Spotz project
 *  @param appKey The ID of the Spotz application
 */
- (void) initWithAppId:(NSString * _Nonnull)appId appKey:(NSString * _Nonnull)appKey options:(NSDictionary * _Nullable)options;

/**
 *  Handle a received notification, calling the completion handler when ready
 *
 *  @param request The notification request that can be modified before being presented to the user
 *  @param contentHandler The completion block to tell the OS when the notification is ready to display
 */
- (void) didReceiveNotificationRequest:(UNNotificationRequest * _Nonnull)request withContentHandler:(void (^ _Nullable)(UNNotificationContent * _Nonnull))contentHandler  __IOS_AVAILABLE(10.0);

/**
 *  Handle running out of time to modify the notification
 */
- (void) serviceExtensionTimeWillExpire;

/**
 *  Call the content handler completion block plus any other preperations. This is for the app to call if it performs any other operations and does not need to wait for LocalzPush to finish
 */
- (void) contentComplete;

@end
