//
//  NotificationService.m
//  SampleNotificationServiceExtension
//
//  Created by Daniel Sykes-Turner on 10/5/17.
//  Copyright © 2017 Localz Pty Ltd. All rights reserved.
//

#import "NotificationService.h"

@interface NotificationService ()

@property (nonatomic, strong) void (^contentHandler)(UNNotificationContent *contentToDeliver);
@property (nonatomic, strong) UNMutableNotificationContent *bestAttemptContent;

@end

@implementation NotificationService

- (void)didReceiveNotificationRequest:(UNNotificationRequest *)request withContentHandler:(void (^)(UNNotificationContent * _Nonnull))contentHandler {
    
    self.contentHandler = contentHandler;
    self.bestAttemptContent = [request.content mutableCopy];
        
    // Check for the attachment
    NSDictionary *userInfo = request.content.userInfo;
    self.bestAttemptContent.body = userInfo.description;
    [self checkNotificationForRemoval:userInfo];
    
    NSString *attachmentURL = userInfo[@"attachment"];
    if (attachmentURL == nil) {
        [self contentComplete];
        return;
    }
    
    // Detect the attachment type to load
    NSArray *urlComponents = [attachmentURL componentsSeparatedByString:@"."];
    NSString *type = [@"." stringByAppendingString:[urlComponents lastObject]];
    
    // Load the attachment
    [self loadAttachmentForUrlString:attachmentURL withType:type completionHandler:^(UNNotificationAttachment *attachment) {
        // Add the attachment to our best attempt content
        if (attachment) {
            self.bestAttemptContent.attachments = [NSArray arrayWithObject:attachment];
        }
        [self contentComplete];
    }];
}

- (void)serviceExtensionTimeWillExpire {
    // Called just before the extension will be terminated by the system.
    // This will be used to deliver a "best attempt" at the modified content (otherwise the original push payload will be used)
    [self contentComplete];
}

- (void)contentComplete {
    // Confirm the content to be delivered to the user
    self.contentHandler(self.bestAttemptContent);
}

- (void)loadAttachmentForUrlString:(NSString *)urlString withType:(NSString *)type completionHandler:(void(^)(UNNotificationAttachment *))completionHandler  {
    
    __block UNNotificationAttachment *attachment = nil;
    NSURL *attachmentURL = [NSURL URLWithString:urlString];
    
    // Download the attachment
    NSURLSession *session = [NSURLSession sessionWithConfiguration:[NSURLSessionConfiguration defaultSessionConfiguration]];
    [[session downloadTaskWithURL:attachmentURL completionHandler:^(NSURL *temporaryFileLocation, NSURLResponse *response, NSError *error) {
        
        if (error != nil) NSLog(@"%@", error.localizedDescription);
        else {
            // Store the attachment in a temporary location
            NSFileManager *fileManager = [NSFileManager defaultManager];
            NSURL *localURL = [NSURL fileURLWithPath:[temporaryFileLocation.path stringByAppendingString:type]];
            [fileManager moveItemAtURL:temporaryFileLocation toURL:localURL error:&error];
            
            // Link the attachment to our UNNotificationAttachment
            NSError *attachmentError = nil;
            attachment = [UNNotificationAttachment attachmentWithIdentifier:@"" URL:localURL options:nil error:&attachmentError];
            if (attachmentError) NSLog(@"%@", attachmentError.localizedDescription);
        }
        completionHandler(attachment);
    }] resume];
}
    
- (void)checkNotificationForRemoval:(NSDictionary *)userInfo {
    
    // Remove any notifications with the same ID if the reset flag is set
    // NOTE: This is a custom flag you need to add in the notification's payload
    BOOL reset = [[userInfo objectForKey:@"reset"] boolValue];
    if (userInfo[@"id"] && reset) {
        NSString *notificationId = userInfo[@"id"];
        
        [[UNUserNotificationCenter currentNotificationCenter] getDeliveredNotificationsWithCompletionHandler:^(NSArray<UNNotification *> * _Nonnull notifications) {
            
            for (UNNotification *n in notifications) {
                NSDictionary *uInfo = n.request.content.userInfo;
                NSString *uId = uInfo[@"id"];
                
                if (uId && [uId isEqualToString:notificationId]) {
                    NSLog(@"Removing notification with id %@ and %@", uId, n.request.identifier);
                    [[UNUserNotificationCenter currentNotificationCenter] removeDeliveredNotificationsWithIdentifiers:@[n.request.identifier]];
                }
            }
        }];
    }
}
    
@end

