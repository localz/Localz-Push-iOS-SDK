//
//  LocalzPushConfig.h
//  LocalzPushSDK
//
//  Created by Melvin Artemas on 31/03/2015.
//  Copyright (c) 2015 Localz Pty Ltd. All rights reserved.
//
#import <CoreLocation/CoreLocation.h>
#import <Foundation/Foundation.h>
#import "LocalzPushDynamicConfig.h"

typedef enum {
    LocalzPushDCRegionAU = 6000,
    LocalzPushDCRegionEU = 3000,
    LocalzPushDCRegionUS = 9000
} LocalzPushDCRegion;

FOUNDATION_EXPORT NSString * const LOCALZPUSH_SDK_VERSION;

FOUNDATION_EXPORT NSString * const LOCALZPUSH_API_AU_PROD_HOST;
FOUNDATION_EXPORT NSString * const LOCALZPUSH_API_EU_PROD_HOST;

FOUNDATION_EXPORT NSString * const LOCALZPUSH_API_DEV_HOST;

FOUNDATION_EXPORT NSString * const LOCALZPUSH_ENV_ID;
FOUNDATION_EXPORT NSString * const LOCALZPUSH_ENV_HOST;
FOUNDATION_EXPORT NSString * const LOCALZPUSH_ENV_URL;

FOUNDATION_EXPORT NSString * const LOCALZPUSH_PROJECT_ID;
FOUNDATION_EXPORT NSString * const LOCALZPUSH_PROJECT_KEY;

FOUNDATION_EXPORT NSString * const LOCALZPUSH_STARTED_KEY;
FOUNDATION_EXPORT NSString * const LOCALZPUSH_ENABLED_KEY;

//FOUNDATION_EXPORT NSString * const LocalzPush_TOKEN_REGISTERED_KEY;

FOUNDATION_EXPORT NSString * const LOCALZPUSH_APPID_AU_REGION;
FOUNDATION_EXPORT NSString * const LOCALZPUSH_APPID_EU_REGION;

@interface LocalzPushConfig : NSObject

@property (nonatomic) BOOL isDebug;
@property (nonatomic,strong) NSString *version;
@property (nonatomic,strong) NSDictionary *env;
@property (nonatomic,strong) NSString *host;
@property (nonatomic) BOOL isDevEnv;
@property (nonatomic) NSString *regionCode;
// Returns status of LocalzPush - whether or not it has been started
@property (nonatomic) BOOL isStarted;
@property (nonatomic) BOOL isPushEnabled;
@property (nonatomic) BOOL isLocationEnabled;
//@property (nonatomic) BOOL isTokenRegistered;
@property (nonatomic) int locationAuthType;
@property (nonatomic) BOOL isDynamicLocation;
//@property (nonatomic) int dynamicMinPeriod;
@property (nonatomic,strong) NSDate *lastDynamicTrackingDate;
@property (nonatomic,strong) LocalzPushDynamicConfig *dynamicConfig;
@property (nonatomic,strong) CLLocation *dynamicLastLocation;
@property (nonatomic) NSString *deviceName;
@property (nonatomic) NSString *deviceToken;

/**
 *  Retrieve SDK Version
 *
 *  @return sdk version
 */
- (NSString *) sdkVersion;

+ (LocalzPushConfig *)shared;

/**
 *  Returns projectId
 */
- (NSString *) projectId;

/**
 *  Returns projectKey
 */
- (NSString *) projectKey;

/**
 *  Retrieve device ID from user defaults
 */
- (NSString *) deviceId;

/**
 *  Retrieve device ID from user defaults
 */
- (NSString *) spotzDeviceId;

/**
 *  Set Device ID
 *
 *  @param deviceId device ID
 */
- (void) setDeviceId:(NSString *)deviceId;

/**
 *  Set application Id and client Key
 *
 *  @param pId projectID
 *  @param key projectKey
 */
- (void) setAppId:(NSString *)pId appKey:(NSString *)key;

/**
 * Additional params to configure LocalzPush
 * @param config Configuration dictionary
 */
- (void) configure:(NSDictionary *)config;
- (void) configureForEnv:(NSString *)env;
- (BOOL) pLog;
- (LocalzPushDCRegion) dcRegion;

/**
 *  Returns the value stored in the configuration file based on LocalzEnvironments.plist
 *  If there is an override value for the key given, it will return the override value
 *  If the value exists for the target build, it will return the target build value
 *  Otherwise it will return the default value set. If not found it will return null
 *
 *  @param key the key name to retrieve
 *
 *  @return returns the value for the given key
 */
- (id) getValue:(NSString *)key;

/**
 *  Override value of the SDK config
 *
 *  @param key    the key name to override
 *  @param object the object to override with
 */
- (void) overrideKey:(NSString *)key withObject:(id)object;

- (void) configureWithParams:(NSDictionary *)config;
@end
