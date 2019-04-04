#import <Foundation/Foundation.h>
#import <CoreLocation/CoreLocation.h>

NS_ASSUME_NONNULL_BEGIN

@protocol DingiLocationManagerDelegate;

/**
 The `DingiLocationManager` protocol defines a set of methods that a class must
 implement in order to serve as the location manager of an `DingiMapView`. A location
 manager is responsible for notifying the map view about location-related events,
 such as a change in the user’s location. This protocol is similar to the
 Core Location framework’s `CLLocationManager` class, but your implementation
 does not need to be based on `CLLocationManager`.
 
 To receive location updates from an object that conforms to the `DingiLocationManager`
 protocol, use the optional methods available in the `DingiLocationManagerDelegate` protocol.
 */
@protocol DingiLocationManager <NSObject>

@optional

#pragma mark Configuring Location Update Precision

/**
 Specifies the minimum distance (measured in meters) a device must move horizontally
 before a location update is generated.
 
 The default value of this property is `kCLDistanceFilterNone` when `DingiMapView` uses its
 default location manager.
 
 @see `CLLocationManager.distanceFilter`
 */
@property(nonatomic, assign) CLLocationDistance distanceFilter;

/**
 Specifies the accuracy of the location data.
 
 The default value is `kCLLocationAccuracyBest` when `DingiMapView` uses its
 default location manager.
 
 @note Determining a location with greater accuracy requires more time and more power.
 
 @see `CLLocationManager.desiredAccuracy`
 */
@property (nonatomic, assign) CLLocationAccuracy desiredAccuracy;

/**
 Specifies the type of user activity associated with the location updates.
 
 The location manager uses this property as a cue to determine when location updates
 may be automatically paused.
 
 The default value is `CLActivityTypeOther` when `DingiMapView` uses its
 default location manager.
 
 @see `CLLocationManager.activityType`
 */
@property (nonatomic, assign) CLActivityType activityType;

@required

/**
 The delegate to receive location updates.
 
 Do not set the location manager’s delegate yourself. `DingiMapView` sets this property
 after the location manager becomes `DingiMapView`’s location manager.
 */
@property (nonatomic, weak) id<DingiLocationManagerDelegate> delegate;

#pragma mark Requesting Authorization for Location Services

/**
 Returns the current localization authorization status.
 
 @see `+[CLLocationManger authorizationStatus]`
 */
@property (nonatomic, readonly) CLAuthorizationStatus authorizationStatus;

/**
 Requests permission to use the location services whenever the app is running.
 */
- (void)requestAlwaysAuthorization;

/**
 Requests permission to use the location services while the app is in
 the foreground.
 */
- (void)requestWhenInUseAuthorization;

#pragma mark Initiating Location Updates

/**
 Starts the generation of location updates that reports the user's current location.
 */
- (void)startUpdatingLocation;

/**
 Stops the generation of location updates.
 */
- (void)stopUpdatingLocation;

#pragma mark Initiating Heading Updates

/**
 Specifies a physical device orientation.
 */
@property (nonatomic) CLDeviceOrientation headingOrientation;

/**
 Starts the generation of heading updates that reports the user's current hading.
 */
- (void)startUpdatingHeading;

/**
 Stops the generation of heading updates.
 */
- (void)stopUpdatingHeading;

/**
 Dissmisses immediately the heading calibration view from screen.
 */
- (void)dismissHeadingCalibrationDisplay;

@end

/**
 The `DingiLocationManagerDelegate` protocol defines a set of methods that respond
 to location updates from an `DingiLocationManager` object that is serving as the
 location manager of an `DingiMapView`.
 */
@protocol DingiLocationManagerDelegate <NSObject>

#pragma mark Responding to Location Updates

/**
 Notifies the delegate with the new location data.
 
 @param manager The location manager reporting the update.
 @param locations An array of `CLLocation` objects in chronological order,
 with the last object representing the most recent location. This array
 contains multiple `CLLocation` objects when `DingiMapView` uses  its
 default location manager.
 */
- (void)locationManager:(id<DingiLocationManager>)manager
     didUpdateLocations:(NSArray<CLLocation *> *)locations;

#pragma mark Responding to Heading Updates

/**
 Notifies the delegate with the new heading data.
 
 @param manager The location manager reporting the update.
 @param newHeading The new heading update.
 */
- (void)locationManager:(id<DingiLocationManager>)manager
       didUpdateHeading:(CLHeading *)newHeading;

/**
 Asks the delegate if the calibration alert should be displayed.
 
 @param manager The location manager reporting the calibration.
 */
- (BOOL)locationManagerShouldDisplayHeadingCalibration:(id<DingiLocationManager>)manager;

#pragma mark Responding to Location Updates Errors

/**
 Notifies the delegate that the location manager was unable to retrieve
 location updates.
 
 @param manager The location manager reporting the error.
 @param error An error object containing the error code that indicates
 why the location manager failed.
 */
- (void)locationManager:(id<DingiLocationManager>)manager
       didFailWithError:(nonnull NSError *)error;

@optional

@end

NS_ASSUME_NONNULL_END
