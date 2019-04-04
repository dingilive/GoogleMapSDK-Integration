#import <Foundation/Foundation.h>

#import "DingiFoundation.h"
#import "DingiStyleLayer.h"

#import "DingiTypes.h"

@class DingiSource;
@class DingiLight;

NS_ASSUME_NONNULL_BEGIN

/**
 A version number identifying the default version of the Mapbox Streets style
 obtained through the `-streetsStyleURL` method. This version number may also be
 passed into the `-streetsStyleURLWithVersion:` method.

 The value of this constant generally corresponds to the latest released version
 as of the date on which this SDK was published. You can use this constant to
 ascertain the style used by `DingiMapView` and `DingiTilePyramidOfflineRegion` when
 no style URL is specified. Consult the
 <a href="https://www.mapbox.com/api-documentation/#styles">Mapbox Styles API documentation</a>
 for the most up-to-date style versioning information.

 @warning The value of this constant may change in a future release of the SDK.
    If you use any feature that depends on a specific aspect of a default style
    – for instance, the minimum zoom level that includes roads – you may use the
    current value of this constant or the underlying style URL, but do not use
    the constant itself. Such details may change significantly from version to
    version.
 */
static MGL_EXPORT const NSInteger DingiStyleDefaultVersion = 10;

FOUNDATION_EXTERN MGL_EXPORT MGLExceptionName const MGLInvalidStyleURLException;
FOUNDATION_EXTERN MGL_EXPORT MGLExceptionName const MGLRedundantLayerException;
FOUNDATION_EXTERN MGL_EXPORT MGLExceptionName const MGLRedundantLayerIdentifierException;
FOUNDATION_EXTERN MGL_EXPORT MGLExceptionName const MGLRedundantSourceException;
FOUNDATION_EXTERN MGL_EXPORT MGLExceptionName const MGLRedundantSourceIdentifierException;

/**
 The proxy object for the current map style.

 DingiStyle provides a set of convenience methods for changing Mapbox
 default styles using `-[DingiMapView styleURL]`.
 <a href="https://www.mapbox.com/maps/">Learn more about Mapbox default styles</a>.

 It is also possible to directly manipulate the current map style
 via `-[DingiMapView style]` by updating the style's data sources or layers.

 @note Wait until the map style has finished loading before modifying a map's
    style via any of the `DingiStyle` instance methods below. You can use the
    `-[DingiMapViewDelegate mapView:didFinishLoadingStyle:]` or
    `-[DingiMapViewDelegate mapViewDidFinishLoadingMap:]` methods as indicators
    that it's safe to modify the map's style.
 */
MGL_EXPORT
@interface DingiStyle : NSObject

#pragma mark Accessing Default Styles

/**
 Returns the URL to the current version of the
 <a href="https://www.mapbox.com/maps/streets/">Mapbox Streets</a> style as of
 publication.

 Streets is a general-purpose style with detailed road and transit networks.

 `DingiMapView` and `DingiTilePyramidOfflineRegion` use Mapbox Streets when no style
 is specified explicitly.

 @warning The return value may change in a future release of the SDK. If you use
    any feature that depends on a specific aspect of a default style – for
    instance, the minimum zoom level that includes roads – use the
    `-streetsStyleURLWithVersion:` method instead. Such details may change
    significantly from version to version.
 */
@property (class, nonatomic, readonly) NSURL *englishStyleURL;

/**
 Returns the URL to the given version of the
 <a href="https://www.mapbox.com/maps/streets/">Mapbox Streets</a> style.

 Streets is a general-purpose style with detailed road and transit networks.

 `DingiMapView` and `DingiTilePyramidOfflineRegion` use Mapbox Streets when no style
 is specified explicitly.

 @param version A specific version of the style.
 */
+ (NSURL *)englishStyleURLWithVersion:(NSInteger)version;

+ (NSURL *)emeraldStyleURL __attribute__((unavailable("Create an NSURL object with the string “mapbox://styles/mapbox/emerald-v8”.")));

/**
 Returns the URL to the current version of the
 <a href="https://www.mapbox.com/maps/outdoors/">Mapbox Outdoors</a> style as of
 publication.

 Outdoors is a general-purpose style tailored to outdoor activities.

 @warning The return value may change in a future release of the SDK. If you use
    any feature that depends on a specific aspect of a default style – for
    instance, the minimum zoom level that includes roads – use the
    `-outdoorsStyleURLWithVersion:` method instead. Such details may change
    significantly from version to version.
 */
@property (class, nonatomic, readonly) NSURL *banglaStyleURL;

/**
 Returns the URL to the given version of the
 <a href="https://www.mapbox.com/maps/outdoors/">Mapbox Outdoors</a> style.

 Outdoors is a general-purpose style tailored to outdoor activities.

 @param version A specific version of the style.
 */
+ (NSURL *)banglaStyleURLWithVersion:(NSInteger)version;

/**
 Returns the URL to the current version of the
 <a href="https://www.mapbox.com/maps/light-dark/">Mapbox Light</a> style.

 Light is a subtle, light-colored backdrop for data visualizations.

 @warning The return value may change in a future release of the SDK. If you use
    any feature that depends on a specific aspect of a default style – for
    instance, the minimum zoom level that includes roads – use the
    `-lightStyleURLWithVersion:` method instead. Such details may change
    significantly from version to version.
 */
//@property (class, nonatomic, readonly) NSURL *lightStyleURL;

/**
 Returns the URL to the given version of the
 <a href="https://www.mapbox.com/maps/light-dark/">Mapbox Light</a> style as of
 publication.

 Light is a subtle, light-colored backdrop for data visualizations.

 @param version A specific version of the style.
 */
//+ (NSURL *)lightStyleURLWithVersion:(NSInteger)version;

/**
 Returns the URL to the current version of the
 <a href="https://www.mapbox.com/maps/light-dark/">Mapbox Dark</a> style.

 Dark is a subtle, dark-colored backdrop for data visualizations.

 @warning The return value may change in a future release of the SDK. If you use
    any feature that depends on a specific aspect of a default style – for
    instance, the minimum zoom level that includes roads – use the
    `-darkStyleURLWithVersion:` method instead. Such details may change
    significantly from version to version.
 */
//@property (class, nonatomic, readonly) NSURL *darkStyleURL;

/**
 Returns the URL to the given version of the
 <a href="https://www.mapbox.com/maps/light-dark/">Mapbox Dark</a> style as of
 publication.

 Dark is a subtle, dark-colored backdrop for data visualizations.

 @param version A specific version of the style.
 */
//+ (NSURL *)darkStyleURLWithVersion:(NSInteger)version;

/**
 Returns the URL to the current version of the
 <a href="https://www.mapbox.com/maps/satellite/">Mapbox Satellite</a> style.

 Satellite is high-resolution satellite and aerial imagery.

 @warning The return value may change in a future release of the SDK. If you use
    any feature that depends on a specific aspect of a default style – for
    instance, the raster tile sets included in the style – use the
    `-satelliteStyleURLWithVersion:` method instead. Such details may change
    significantly from version to version.
 */
//@property (class, nonatomic, readonly) NSURL *satelliteStyleURL;

/**
 Returns the URL to the given version of the
 <a href="https://www.mapbox.com/maps/satellite/">Mapbox Satellite</a> style as
 of publication.

 Satellite is high-resolution satellite and aerial imagery.

 @param version A specific version of the style.
 */
//+ (NSURL *)satelliteStyleURLWithVersion:(NSInteger)version;


//+ (NSURL *)hybridStyleURL __attribute__((unavailable("Use -satelliteStreetsStyleURL.")));

/**
 Returns the URL to the current version of the
 <a href="https://www.mapbox.com/maps/satellite/">Mapbox Satellite Streets</a>
 style as of publication.

 Satellite Streets combines the high-resolution satellite and aerial imagery of
 Mapbox Satellite with unobtrusive labels and translucent roads from Mapbox
 Streets.

 @warning The return value may change in a future release of the SDK. If you use
    any feature that depends on a specific aspect of a default style – for
    instance, the minimum zoom level that includes roads – use the
    `-satelliteStreetsStyleURLWithVersion:` method instead. Such details may
    change significantly from version to version.
 */
//@property (class, nonatomic, readonly) NSURL *satelliteStreetsStyleURL;

/**
 Returns the URL to the given version of the
 <a href="https://www.mapbox.com/maps/satellite/">Mapbox Satellite Streets</a>
 style.

 Satellite Streets combines the high-resolution satellite and aerial imagery of
 Mapbox Satellite with unobtrusive labels and translucent roads from Mapbox
 Streets.

 @param version A specific version of the style.
 */
//+ (NSURL *)satelliteStreetsStyleURLWithVersion:(NSInteger)version;


+ (NSURL *)trafficDayStyleURL __attribute__((unavailable("Create an NSURL object with the string “mapbox://styles/mapbox/traffic-day-v2”.")));

+ (NSURL *)trafficDayStyleURLWithVersion:(NSInteger)version __attribute__((unavailable("Create an NSURL object with the string “mapbox://styles/mapbox/traffic-day-v2”.")));;

+ (NSURL *)trafficNightStyleURL __attribute__((unavailable("Create an NSURL object with the string “mapbox://styles/mapbox/traffic-night-v2”.")));

+ (NSURL *)trafficNightStyleURLWithVersion:(NSInteger)version __attribute__((unavailable("Create an NSURL object with the string “mapbox://styles/mapbox/traffic-night-v2”.")));

#pragma mark Accessing Metadata About the Style

/**
 The name of the style.

 You can customize the style’s name in Mapbox Studio.
 */
@property (readonly, copy, nullable) NSString *name;

#pragma mark Managing Sources

/**
 A set containing the style’s sources.
 */
@property (nonatomic, strong) NSSet<__kindof DingiSource *> *sources;

/**
 Values describing animated transitions to changes on a style's individual
 paint properties.
 */
@property (nonatomic) DingiTransition transition;

/**
 Returns a source with the given identifier in the current style.

 @note Source identifiers are not guaranteed to exist across styles or different
    versions of the same style. Applications that use this API must first set the
    style URL to an explicitly versioned style using a convenience method like
    `+[DingiStyle outdoorsStyleURLWithVersion:]`, `DingiMapView`’s “Style URL”
    inspectable in Interface Builder, or a manually constructed `NSURL`. This
    approach also avoids source identifer name changes that will occur in the default
    style’s sources over time.

 @return An instance of a concrete subclass of `DingiSource` associated with the
    given identifier, or `nil` if the current style contains no such source.
 */
- (nullable DingiSource *)sourceWithIdentifier:(NSString *)identifier;

/**
 Adds a new source to the current style.

 @note Adding the same source instance more than once will result in a
    `MGLRedundantSourceException`. Reusing the same source identifier, even with
    different source instances, will result in a
    `MGLRedundantSourceIdentifierException`.

 @note Sources should be added in
    `-[DingiMapViewDelegate mapView:didFinishLoadingStyle:]` or
    `-[DingiMapViewDelegate mapViewDidFinishLoadingMap:]` to ensure that the map
    has loaded the style and is ready to accept a new source.

 @param source The source to add to the current style.
 */
- (void)addSource:(DingiSource *)source;

/**
 Removes a source from the current style.

 @note Source identifiers are not guaranteed to exist across styles or different
    versions of the same style. Applications that use this API must first set the
    style URL to an explicitly versioned style using a convenience method like
    `+[DingiStyle outdoorsStyleURLWithVersion:]`, `DingiMapView`’s “Style URL”
    inspectable in Interface Builder, or a manually constructed `NSURL`. This
    approach also avoids source identifer name changes that will occur in the default
    style’s sources over time.

 @param source The source to remove from the current style.
 */
- (void)removeSource:(DingiSource *)source;

#pragma mark Managing Style Layers

/**
 The layers included in the style, arranged according to their back-to-front
 ordering on the screen.
 */
@property (nonatomic, strong) NSArray<__kindof DingiStyleLayer *> *layers;

/**
 Returns a style layer with the given identifier in the current style.

 @note Layer identifiers are not guaranteed to exist across styles or different
    versions of the same style. Applications that use this API must first set
    the style URL to an explicitly versioned style using a convenience method like
    `+[DingiStyle outdoorsStyleURLWithVersion:]`, `DingiMapView`’s “Style URL”
    inspectable in Interface Builder, or a manually constructed `NSURL`. This
    approach also avoids layer identifer name changes that will occur in the default
    style’s layers over time.

 @return An instance of a concrete subclass of `DingiStyleLayer` associated with
    the given identifier, or `nil` if the current style contains no such style
    layer.
 */
- (nullable DingiStyleLayer *)layerWithIdentifier:(NSString *)identifier;

/**
 Adds a new layer on top of existing layers.

 @note Adding the same layer instance more than once will result in a
    `MGLRedundantLayerException`. Reusing the same layer identifer, even with
    different layer instances, will also result in an exception.

 @note Layers should be added in
    `-[DingiMapViewDelegate mapView:didFinishLoadingStyle:]` or
    `-[DingiMapViewDelegate mapViewDidFinishLoadingMap:]` to ensure that the map
    has loaded the style and is ready to accept a new layer.

 @param layer The layer object to add to the map view. This object must be an
    instance of a concrete subclass of `DingiStyleLayer`.
 */
- (void)addLayer:(DingiStyleLayer *)layer;

/**
 Inserts a new layer into the style at the given index.

 @note Adding the same layer instance more than once will result in a
    `MGLRedundantLayerException`. Reusing the same layer identifer, even with
    different layer instances, will also result in an exception.

 @note Layers should be added in
    `-[DingiMapViewDelegate mapView:didFinishLoadingStyle:]` or
    `-[DingiMapViewDelegate mapViewDidFinishLoadingMap:]` to ensure that the map
    has loaded the style and is ready to accept a new layer.

 @param layer The layer to insert.
 @param index The index at which to insert the layer. An index of 0 would send
    the layer to the back; an index equal to the number of objects in the
    `layers` property would bring the layer to the front.
 */
- (void)insertLayer:(DingiStyleLayer *)layer atIndex:(NSUInteger)index;

/**
 Inserts a new layer below another layer.

 @note Layer identifiers are not guaranteed to exist across styles or different
    versions of the same style. Applications that use this API must first set
    the style URL to an explicitly versioned style using a convenience method like
    `+[DingiStyle outdoorsStyleURLWithVersion:]`, `DingiMapView`’s “Style URL”
    inspectable in Interface Builder, or a manually constructed `NSURL`. This
    approach also avoids layer identifer name changes that will occur in the default
    style’s layers over time.

    Inserting the same layer instance more than once will result in a
    `MGLRedundantLayerException`. Reusing the same layer identifer, even with
    different layer instances, will also result in an exception.

 @param layer The layer to insert.
 @param sibling An existing layer in the style.
 */
- (void)insertLayer:(DingiStyleLayer *)layer belowLayer:(DingiStyleLayer *)sibling;

/**
 Inserts a new layer above another layer.

 @note Layer identifiers are not guaranteed to exist across styles or different
    versions of the same style. Applications that use this API must first set
    the style URL to an explicitly versioned style using a convenience method like
    `+[DingiStyle outdoorsStyleURLWithVersion:]`, `DingiMapView`’s “Style URL”
    inspectable in Interface Builder, or a manually constructed `NSURL`. This
    approach also avoids layer identifer name changes that will occur in the default
    style’s layers over time.

    Inserting the same layer instance more than once will result in a
    `MGLRedundantLayerException`. Reusing the same layer identifer, even with
    different layer instances, will also result in an exception.

 @param layer The layer to insert.
 @param sibling An existing layer in the style.
 */
- (void)insertLayer:(DingiStyleLayer *)layer aboveLayer:(DingiStyleLayer *)sibling;

/**
 Removes a layer from the map view.

 @note Layer identifiers are not guaranteed to exist across styles or different
    versions of the same style. Applications that use this API must first set
    the style URL to an explicitly versioned style using a convenience method like
    `+[DingiStyle outdoorsStyleURLWithVersion:]`, `DingiMapView`’s “Style URL”
    inspectable in Interface Builder, or a manually constructed `NSURL`. This
    approach also avoids layer identifer name changes that will occur in the default
    style’s layers over time.

 @param layer The layer object to remove from the map view. This object
 must conform to the `DingiStyleLayer` protocol.
 */
- (void)removeLayer:(DingiStyleLayer *)layer;

#pragma mark Managing Style Classes


@property (nonatomic) NSArray<NSString *> *styleClasses __attribute__((unavailable("Support for style classes has been removed.")));

- (BOOL)hasStyleClass:(NSString *)styleClass __attribute__((unavailable("Support for style classes has been removed.")));

- (void)addStyleClass:(NSString *)styleClass __attribute__((unavailable("Support for style classes has been removed.")));

- (void)removeStyleClass:(NSString *)styleClass __attribute__((unavailable("Support for style classes has been removed.")));

#pragma mark Managing a Style’s Images

/**
 Returns the image associated with the given name in the style.

 @note Names and their associated images are not guaranteed to exist across
    styles or different versions of the same style. Applications that use this
    API must first set the style URL to an explicitly versioned style using a
    convenience method like `+[DingiStyle outdoorsStyleURLWithVersion:]`,
    `DingiMapView`’s “Style URL” inspectable in Interface Builder, or a manually
    constructed `NSURL`. This approach also avoids image name changes that will
    occur in the default style over time.

 @param name The name associated with the image you want to obtain.
 @return The image associated with the given name, or `nil` if no image is
    associated with that name.
 */
- (nullable MGLImage *)imageForName:(NSString *)name;

/**
 Adds or overrides an image used by the style’s layers.

 To use an image in a style layer, give it a unique name using this method, then
 set the `iconImageName` property of an `DingiSymbolStyleLayer` object to that
 name.

 @param image The image for the name.
 @param name The name of the image to set to the style.
 */
- (void)setImage:(MGLImage *)image forName:(NSString *)name;

/**
 Removes a name and its associated image from the style.

 @note Names and their associated images are not guaranteed to exist across
    styles or different versions of the same style. Applications that use this
    API must first set the style URL to an explicitly versioned style using a
    convenience method like `+[DingiStyle outdoorsStyleURLWithVersion:]`,
    `DingiMapView`’s “Style URL” inspectable in Interface Builder, or a manually
    constructed `NSURL`. This approach also avoids image name changes that will
    occur in the default style over time.

 @param name The name of the image to remove.
 */
- (void)removeImageForName:(NSString *)name;


#pragma mark Managing the Style's Light

/**
 Provides global light source for the style.
 */
@property (nonatomic, strong) DingiLight *light;

#pragma mark Localizing Map Content

/**
 Attempts to localize labels in the style into the given locale.
 
 This method automatically modifies the text property of any symbol style layer
 in the style whose source is the
 <a href="https://www.mapbox.com/vector-tiles/mapbox-streets-v7/#overview">Mapbox Streets source</a>.
 On iOS, the user can set the system’s preferred language in Settings, General
 Settings, Language & Region. On macOS, the user can set the system’s preferred
 language in the Language & Region pane of System Preferences.
 
 @param locale The locale into which labels should be localized. To use the
    system’s preferred language, if supported, specify `nil`. To use the local
    language, specify a locale with the identifier `mul`.
 */
- (void)localizeLabelsIntoLocale:(nullable NSLocale *)locale;

@property (nonatomic) BOOL localizesLabels __attribute__((unavailable("Use -localizeLabelsIntoLocale: instead.")));

@end

NS_ASSUME_NONNULL_END
