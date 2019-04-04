// This file is generated.
// Edit platform/darwin/scripts/generate-style-code.js, then run `make darwin-style-code`.

#import "DingiFoundation.h"
#import "DingiVectorStyleLayer.h"

NS_ASSUME_NONNULL_BEGIN

/**
 Controls the frame of reference for
 `DingiFillExtrusionStyleLayer.fillExtrusionTranslation`.

 Values of this type are used in the `DingiFillExtrusionStyleLayer.fillExtrusionTranslationAnchor`
 property.
 */
typedef NS_ENUM(NSUInteger, DingiFillExtrusionTranslationAnchor) {
    /**
     The fill extrusion is translated relative to the map.
     */
    DingiFillExtrusionTranslationAnchorMap,
    /**
     The fill extrusion is translated relative to the viewport.
     */
    DingiFillExtrusionTranslationAnchorViewport,
};

/**
 An `DingiFillExtrusionStyleLayer` is a style layer that renders one or more 3D
 extruded polygons on the map.
 
 Use a fill-extrusion style layer to configure the visual appearance of polygon
 or multipolygon features. These features can come from vector tiles loaded by
 an `DingiVectorTileSource` object, or they can be `DingiPolygon`,
 `DingiPolygonFeature`, `DingiMultiPolygon`, or `DingiMultiPolygonFeature` instances
 in an `DingiShapeSource` or `DingiComputedShapeSource` object.

 You can access an existing fill-extrusion style layer using the
 `-[MGLStyle layerWithIdentifier:]` method if you know its identifier;
 otherwise, find it using the `MGLStyle.layers` property. You can also create a
 new fill-extrusion style layer and add it to the style using a method such as
 `-[MGLStyle addLayer:]`.

 ### Example

 ```swift
 let layer = DingiFillExtrusionStyleLayer(identifier: "buildings", source: buildings)
 layer.sourceLayerIdentifier = "building"
 layer.fillExtrusionHeight = NSExpression(forKeyPath: "height")
 layer.fillExtrusionBase = NSExpression(forKeyPath: "min_height")
 layer.predicate = NSPredicate(format: "extrude == 'true'")
 mapView.style?.addLayer(layer)
 ```
 */
MGL_EXPORT
@interface DingiFillExtrusionStyleLayer : DingiVectorStyleLayer

/**
 Returns a fill-extrusion style layer initialized with an identifier and source.

 After initializing and configuring the style layer, add it to a map view’s
 style using the `-[MGLStyle addLayer:]` or
 `-[MGLStyle insertLayer:belowLayer:]` method.

 @param identifier A string that uniquely identifies the source in the style to
    which it is added.
 @param source The source from which to obtain the data to style. If the source
    has not yet been added to the current style, the behavior is undefined.
 @return An initialized foreground style layer.
 */
- (instancetype)initWithIdentifier:(NSString *)identifier source:(DingiSource *)source;

#pragma mark - Accessing the Paint Attributes

/**
 The height with which to extrude the base of this layer. Must be less than or
 equal to `fillExtrusionHeight`.
 
 This property is measured in meters.
 
 The default value of this property is an expression that evaluates to the float
 `0`. Set this property to `nil` to reset it to the default value.
 
 This property is only applied to the style if `fillExtrusionHeight` is
 non-`nil`. Otherwise, it is ignored.
 
 You can set this property to an expression containing any of the following:
 
 * Constant numeric values no less than 0
 * Predefined functions, including mathematical and string operators
 * Conditional expressions
 * Variable assignments and references to assigned variables
 * Interpolation and step functions applied to the `$zoomLevel` variable and/or
 feature attributes
 */
@property (nonatomic, null_resettable) NSExpression *fillExtrusionBase;

/**
 The transition affecting any changes to this layer’s `fillExtrusionBase` property.

 This property corresponds to the `fill-extrusion-base-transition` property in the style JSON file format.
*/
@property (nonatomic) DingiTransition fillExtrusionBaseTransition;

#if TARGET_OS_IPHONE
/**
 The base color of this layer. The extrusion's surfaces will be shaded
 differently based on this color in combination with the `light` settings. If
 this color is specified with an alpha component, the alpha component will be
 ignored; use `fillExtrusionOpacity` to set layer opacityco.
 
 The default value of this property is an expression that evaluates to
 `UIColor.blackColor`. Set this property to `nil` to reset it to the default
 value.
 
 This property is only applied to the style if `fillExtrusionPattern` is set to
 `nil`. Otherwise, it is ignored.
 
 You can set this property to an expression containing any of the following:
 
 * Constant `UIColor` values
 * Predefined functions, including mathematical and string operators
 * Conditional expressions
 * Variable assignments and references to assigned variables
 * Interpolation and step functions applied to the `$zoomLevel` variable and/or
 feature attributes
 */
@property (nonatomic, null_resettable) NSExpression *fillExtrusionColor;
#else
/**
 The base color of this layer. The extrusion's surfaces will be shaded
 differently based on this color in combination with the `light` settings. If
 this color is specified with an alpha component, the alpha component will be
 ignored; use `fillExtrusionOpacity` to set layer opacityco.
 
 The default value of this property is an expression that evaluates to
 `NSColor.blackColor`. Set this property to `nil` to reset it to the default
 value.
 
 This property is only applied to the style if `fillExtrusionPattern` is set to
 `nil`. Otherwise, it is ignored.
 
 You can set this property to an expression containing any of the following:
 
 * Constant `NSColor` values
 * Predefined functions, including mathematical and string operators
 * Conditional expressions
 * Variable assignments and references to assigned variables
 * Interpolation and step functions applied to the `$zoomLevel` variable and/or
 feature attributes
 */
@property (nonatomic, null_resettable) NSExpression *fillExtrusionColor;
#endif

/**
 The transition affecting any changes to this layer’s `fillExtrusionColor` property.

 This property corresponds to the `fill-extrusion-color-transition` property in the style JSON file format.
*/
@property (nonatomic) DingiTransition fillExtrusionColorTransition;

/**
 The height with which to extrude this layer.
 
 This property is measured in meters.
 
 The default value of this property is an expression that evaluates to the float
 `0`. Set this property to `nil` to reset it to the default value.
 
 You can set this property to an expression containing any of the following:
 
 * Constant numeric values no less than 0
 * Predefined functions, including mathematical and string operators
 * Conditional expressions
 * Variable assignments and references to assigned variables
 * Interpolation and step functions applied to the `$zoomLevel` variable and/or
 feature attributes
 */
@property (nonatomic, null_resettable) NSExpression *fillExtrusionHeight;

/**
 The transition affecting any changes to this layer’s `fillExtrusionHeight` property.

 This property corresponds to the `fill-extrusion-height-transition` property in the style JSON file format.
*/
@property (nonatomic) DingiTransition fillExtrusionHeightTransition;

/**
 The opacity of the entire fill extrusion layer. This is rendered on a
 per-layer, not per-feature, basis, and data-driven styling is not available.
 
 The default value of this property is an expression that evaluates to the float
 `1`. Set this property to `nil` to reset it to the default value.
 
 You can set this property to an expression containing any of the following:
 
 * Constant numeric values between 0 and 1 inclusive
 * Predefined functions, including mathematical and string operators
 * Conditional expressions
 * Variable assignments and references to assigned variables
 * Interpolation and step functions applied to the `$zoomLevel` variable
 
 This property does not support applying interpolation or step functions to
 feature attributes.
 */
@property (nonatomic, null_resettable) NSExpression *fillExtrusionOpacity;

/**
 The transition affecting any changes to this layer’s `fillExtrusionOpacity` property.

 This property corresponds to the `fill-extrusion-opacity-transition` property in the style JSON file format.
*/
@property (nonatomic) DingiTransition fillExtrusionOpacityTransition;

/**
 Name of image in style images to use for drawing image fill-extrusions. For
 seamless patterns, image width and height must be a factor of two (2, 4, 8,
 ..., 512).
 
 You can set this property to an expression containing any of the following:
 
 * Constant string values
 * Predefined functions, including mathematical and string operators
 * Conditional expressions
 * Variable assignments and references to assigned variables
 * Interpolation and step functions applied to the `$zoomLevel` variable and/or
 feature attributes
 */
@property (nonatomic, null_resettable) NSExpression *fillExtrusionPattern;

/**
 The transition affecting any changes to this layer’s `fillExtrusionPattern` property.

 This property corresponds to the `fill-extrusion-pattern-transition` property in the style JSON file format.
*/
@property (nonatomic) DingiTransition fillExtrusionPatternTransition;

#if TARGET_OS_IPHONE
/**
 The geometry's offset.
 
 This property is measured in points.
 
 The default value of this property is an expression that evaluates to an
 `NSValue` object containing a `CGVector` struct set to 0 points rightward and 0
 points downward. Set this property to `nil` to reset it to the default value.
 
 This attribute corresponds to the <a
 href="https://www.mapbox.com/mapbox-gl-style-spec/#paint-fill-extrusion-translate"><code>fill-extrusion-translate</code></a>
 layout property in the Mapbox Style Specification.
 
 You can set this property to an expression containing any of the following:
 
 * Constant `CGVector` values
 * Predefined functions, including mathematical and string operators
 * Conditional expressions
 * Variable assignments and references to assigned variables
 * Interpolation and step functions applied to the `$zoomLevel` variable
 
 This property does not support applying interpolation or step functions to
 feature attributes.
 */
@property (nonatomic, null_resettable) NSExpression *fillExtrusionTranslation;
#else
/**
 The geometry's offset.
 
 This property is measured in points.
 
 The default value of this property is an expression that evaluates to an
 `NSValue` object containing a `CGVector` struct set to 0 points rightward and 0
 points upward. Set this property to `nil` to reset it to the default value.
 
 This attribute corresponds to the <a
 href="https://www.mapbox.com/mapbox-gl-style-spec/#paint-fill-extrusion-translate"><code>fill-extrusion-translate</code></a>
 layout property in the Mapbox Style Specification.
 
 You can set this property to an expression containing any of the following:
 
 * Constant `CGVector` values
 * Predefined functions, including mathematical and string operators
 * Conditional expressions
 * Variable assignments and references to assigned variables
 * Interpolation and step functions applied to the `$zoomLevel` variable
 
 This property does not support applying interpolation or step functions to
 feature attributes.
 */
@property (nonatomic, null_resettable) NSExpression *fillExtrusionTranslation;
#endif

/**
 The transition affecting any changes to this layer’s `fillExtrusionTranslation` property.

 This property corresponds to the `fill-extrusion-translate-transition` property in the style JSON file format.
*/
@property (nonatomic) DingiTransition fillExtrusionTranslationTransition;

@property (nonatomic, null_resettable) NSExpression *fillExtrusionTranslate __attribute__((unavailable("Use fillExtrusionTranslation instead.")));

/**
 Controls the frame of reference for `fillExtrusionTranslation`.
 
 The default value of this property is an expression that evaluates to `map`.
 Set this property to `nil` to reset it to the default value.
 
 This property is only applied to the style if `fillExtrusionTranslation` is
 non-`nil`. Otherwise, it is ignored.
 
 This attribute corresponds to the <a
 href="https://www.mapbox.com/mapbox-gl-style-spec/#paint-fill-extrusion-translate-anchor"><code>fill-extrusion-translate-anchor</code></a>
 layout property in the Mapbox Style Specification.
 
 You can set this property to an expression containing any of the following:
 
 * Constant `DingiFillExtrusionTranslationAnchor` values
 * Any of the following constant string values:
   * `map`: The fill extrusion is translated relative to the map.
   * `viewport`: The fill extrusion is translated relative to the viewport.
 * Predefined functions, including mathematical and string operators
 * Conditional expressions
 * Variable assignments and references to assigned variables
 * Step functions applied to the `$zoomLevel` variable
 
 This property does not support applying interpolation functions to the
 `$zoomLevel` variable or applying interpolation or step functions to feature
 attributes.
 */
@property (nonatomic, null_resettable) NSExpression *fillExtrusionTranslationAnchor;

@property (nonatomic, null_resettable) NSExpression *fillExtrusionTranslateAnchor __attribute__((unavailable("Use fillExtrusionTranslationAnchor instead.")));

@end

/**
 Methods for wrapping an enumeration value for a style layer attribute in an
 `DingiFillExtrusionStyleLayer` object and unwrapping its raw value.
 */
@interface NSValue (DingiFillExtrusionStyleLayerAdditions)

#pragma mark Working with Fill extrusion Style Layer Attribute Values

/**
 Creates a new value object containing the given `DingiFillExtrusionTranslationAnchor` enumeration.

 @param fillExtrusionTranslationAnchor The value for the new object.
 @return A new value object that contains the enumeration value.
 */
+ (instancetype)valueWithDingiFillExtrusionTranslationAnchor:(DingiFillExtrusionTranslationAnchor)fillExtrusionTranslationAnchor;

/**
 The `DingiFillExtrusionTranslationAnchor` enumeration representation of the value.
 */
@property (readonly) DingiFillExtrusionTranslationAnchor DingiFillExtrusionTranslationAnchorValue;

@end

NS_ASSUME_NONNULL_END
