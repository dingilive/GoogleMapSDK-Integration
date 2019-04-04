#import <Foundation/Foundation.h>

#import "DingiFoundation.h"

NS_ASSUME_NONNULL_BEGIN

/**
 The `DingiAccountManager` object provides a global way to set a DingiMap API access
 token.
 */
MGL_EXPORT
@interface DingiAccountManager : NSObject

#pragma mark Authorizing Access

/**
 The DingiMap access token used by all instances of `DingiMapView` in the current application.
 
 DingiMap-hosted vector tiles and styles require an API access token, which you
 can obtain from the DingiMap account page.
 Access tokens associate requests to DingiMap’s vector tile and style APIs with
 your DingiMap account. They also deter other developers from using your styles
 without your permission.

 Setting this property to a value of `nil` has no effect.

 @note You must set the access token before attempting to load any DingiMap-hosted
    style. Therefore, you should generally set it before creating an instance of
    `DingiMapView`. The recommended way to set an access token is to add an entry
    to your application’s Info.plist file with the key `DingiMapAccessToken`
    and the type `String`. Alternatively, you may call this method from your
    application delegate’s `-applicationDidFinishLaunching:` method.
 */
@property (class, nullable) NSString *accessToken;

+ (BOOL)mapboxMetricsEnabledSettingShownInApp __attribute__((unavailable("Telemetry settings are now always shown in the ℹ️ menu.")));

@end

NS_ASSUME_NONNULL_END
