// This file is generated.
// Edit platform/darwin/scripts/generate-style-code.js, then run `make darwin-style-code`.

#import "DingiFoundation.h"
#import "DingiVectorStyleLayer.h"

NS_ASSUME_NONNULL_BEGIN

/**
 The display of line endings.

 Values of this type are used in the `DingiLineStyleLayer.lineCap`
 property.
 */
typedef NS_ENUM(NSUInteger, DingiLineCap) {
    /**
     A cap with a squared-off end which is drawn to the exact endpoint of the
     line.
     */
    DingiLineCapButt,
    /**
     A cap with a rounded end which is drawn beyond the endpoint of the line at
     a radius of one-half of the line's width and centered on the endpoint of
     the line.
     */
    DingiLineCapRound,
    /**
     A cap with a squared-off end which is drawn beyond the endpoint of the line
     at a distance of one-half of the line's width.
     */
    DingiLineCapSquare,
};

/**
 The display of lines when joining.

 Values of this type are used in the `DingiLineStyleLayer.lineJoin`
 property.
 */
typedef NS_ENUM(NSUInteger, DingiLineJoin) {
    /**
     A join with a squared-off end which is drawn beyond the endpoint of the
     line at a distance of one-half of the line's width.
     */
    DingiLineJoinBevel,
    /**
     A join with a rounded end which is drawn beyond the endpoint of the line at
     a radius of one-half of the line's width and centered on the endpoint of
     the line.
     */
    DingiLineJoinRound,
    /**
     A join with a sharp, angled corner which is drawn with the outer sides
     beyond the endpoint of the path until they meet.
     */
    DingiLineJoinMiter,
};

/**
 Controls the frame of reference for `DingiLineStyleLayer.lineTranslation`.

 Values of this type are used in the `DingiLineStyleLayer.lineTranslationAnchor`
 property.
 */
typedef NS_ENUM(NSUInteger, DingiLineTranslationAnchor) {
    /**
     The line is translated relative to the map.
     */
    DingiLineTranslationAnchorMap,
    /**
     The line is translated relative to the viewport.
     */
    DingiLineTranslationAnchorViewport,
};

/**
 An `DingiLineStyleLayer` is a style layer that renders one or more stroked
 polylines on the map.
 
 Use a line style layer to configure the visual appearance of polyline or
 multipolyline features. These features can come from vector tiles loaded by an
 `DingiVectorTileSource` object, or they can be `DingiPolyline`,
 `DingiPolylineFeature`, `DingiMultiPolyline`, or `DingiMultiPolylineFeature`
 instances in an `DingiShapeSource` or `DingiComputedShapeSource` object.

 You can access an existing line style layer using the
 `-[MGLStyle layerWithIdentifier:]` method if you know its identifier;
 otherwise, find it using the `MGLStyle.layers` property. You can also create a
 new line style layer and add it to the style using a method such as
 `-[MGLStyle addLayer:]`.

 ### Example

 ```swift
 let layer = DingiLineStyleLayer(identifier: "trails-path", source: trails)
 layer.sourceLayerIdentifier = "trails"
 layer.lineWidth = NSExpression(format: "mgl_interpolate:withCurveType:parameters:stops:($zoomLevel, 'exponential', 1.5, %@)",
                                [14: 2,
                                 18: 20])
 layer.lineColor = NSExpression(forConstantValue: UIColor.brown)
 layer.lineCap = NSExpression(forConstantValue: "round")
 layer.predicate = NSPredicate(format: "%K == %@", "trail-type", "mountain-biking")
 mapView.style?.addLayer(layer)
 ```
 */
MGL_EXPORT
@interface DingiLineStyleLayer : DingiVectorStyleLayer

/**
 Returns a line style layer initialized with an identifier and source.

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

#pragma mark - Accessing the Layout Attributes

/**
 The display of line endings.
 
 The default value of this property is an expression that evaluates to `butt`.
 Set this property to `nil` to reset it to the default value.
 
 You can set this property to an expression containing any of the following:
 
 * Constant `DingiLineCap` values
 * Any of the following constant string values:
   * `butt`: A cap with a squared-off end which is drawn to the exact endpoint
 of the line.
   * `round`: A cap with a rounded end which is drawn beyond the endpoint of the
 line at a radius of one-half of the line's width and centered on the endpoint
 of the line.
   * `square`: A cap with a squared-off end which is drawn beyond the endpoint
 of the line at a distance of one-half of the line's width.
 * Predefined functions, including mathematical and string operators
 * Conditional expressions
 * Variable assignments and references to assigned variables
 * Step functions applied to the `$zoomLevel` variable
 
 This property does not support applying interpolation functions to the
 `$zoomLevel` variable or applying interpolation or step functions to feature
 attributes.
 */
@property (nonatomic, null_resettable) NSExpression *lineCap;

/**
 The display of lines when joining.
 
 The default value of this property is an expression that evaluates to `miter`.
 Set this property to `nil` to reset it to the default value.
 
 You can set this property to an expression containing any of the following:
 
 * Constant `DingiLineJoin` values
 * Any of the following constant string values:
   * `bevel`: A join with a squared-off end which is drawn beyond the endpoint
 of the line at a distance of one-half of the line's width.
   * `round`: A join with a rounded end which is drawn beyond the endpoint of
 the line at a radius of one-half of the line's width and centered on the
 endpoint of the line.
   * `miter`: A join with a sharp, angled corner which is drawn with the outer
 sides beyond the endpoint of the path until they meet.
 * Predefined functions, including mathematical and string operators
 * Conditional expressions
 * Variable assignments and references to assigned variables
 * Interpolation and step functions applied to the `$zoomLevel` variable and/or
 feature attributes
 */
@property (nonatomic, null_resettable) NSExpression *lineJoin;

/**
 Used to automatically convert miter joins to bevel joins for sharp angles.
 
 The default value of this property is an expression that evaluates to the float
 `2`. Set this property to `nil` to reset it to the default value.
 
 This property is only applied to the style if `lineJoin` is set to an
 expression that evaluates to `miter`. Otherwise, it is ignored.
 
 You can set this property to an expression containing any of the following:
 
 * Constant numeric values
 * Predefined functions, including mathematical and string operators
 * Conditional expressions
 * Variable assignments and references to assigned variables
 * Interpolation and step functions applied to the `$zoomLevel` variable
 
 This property does not support applying interpolation or step functions to
 feature attributes.
 */
@property (nonatomic, null_resettable) NSExpression *lineMiterLimit;

/**
 Used to automatically convert round joins to miter joins for shallow angles.
 
 The default value of this property is an expression that evaluates to the float
 `1.05`. Set this property to `nil` to reset it to the default value.
 
 This property is only applied to the style if `lineJoin` is set to an
 expression that evaluates to `round`. Otherwise, it is ignored.
 
 You can set this property to an expression containing any of the following:
 
 * Constant numeric values
 * Predefined functions, including mathematical and string operators
 * Conditional expressions
 * Variable assignments and references to assigned variables
 * Interpolation and step functions applied to the `$zoomLevel` variable
 
 This property does not support applying interpolation or step functions to
 feature attributes.
 */
@property (nonatomic, null_resettable) NSExpression *lineRoundLimit;

#pragma mark - Accessing the Paint Attributes

/**
 Blur applied to the line, in points.
 
 This property is measured in points.
 
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
@property (nonatomic, null_resettable) NSExpression *lineBlur;

/**
 The transition affecting any changes to this layer’s `lineBlur` property.

 This property corresponds to the `line-blur-transition` property in the style JSON file format.
*/
@property (nonatomic) DingiTransition lineBlurTransition;

#if TARGET_OS_IPHONE
/**
 The color with which the line will be drawn.
 
 The default value of this property is an expression that evaluates to
 `UIColor.blackColor`. Set this property to `nil` to reset it to the default
 value.
 
 This property is only applied to the style if `linePattern` is set to `nil`.
 Otherwise, it is ignored.
 
 You can set this property to an expression containing any of the following:
 
 * Constant `UIColor` values
 * Predefined functions, including mathematical and string operators
 * Conditional expressions
 * Variable assignments and references to assigned variables
 * Interpolation and step functions applied to the `$zoomLevel` variable and/or
 feature attributes
 */
@property (nonatomic, null_resettable) NSExpression *lineColor;
#else
/**
 The color with which the line will be drawn.
 
 The default value of this property is an expression that evaluates to
 `NSColor.blackColor`. Set this property to `nil` to reset it to the default
 value.
 
 This property is only applied to the style if `linePattern` is set to `nil`.
 Otherwise, it is ignored.
 
 You can set this property to an expression containing any of the following:
 
 * Constant `NSColor` values
 * Predefined functions, including mathematical and string operators
 * Conditional expressions
 * Variable assignments and references to assigned variables
 * Interpolation and step functions applied to the `$zoomLevel` variable and/or
 feature attributes
 */
@property (nonatomic, null_resettable) NSExpression *lineColor;
#endif

/**
 The transition affecting any changes to this layer’s `lineColor` property.

 This property corresponds to the `line-color-transition` property in the style JSON file format.
*/
@property (nonatomic) DingiTransition lineColorTransition;

/**
 Specifies the lengths of the alternating dashes and gaps that form the dash
 pattern. The lengths are later scaled by the line width. To convert a dash
 length to points, multiply the length by the current line width. Note that
 GeoJSON sources with `lineMetrics: true` specified won't render dashed lines to
 the expected scale. Also note that zoom-dependent expressions will be evaluated
 only at integer zoom levels.
 
 This property is measured in line widths.
 
 This property is only applied to the style if `linePattern` is set to `nil`.
 Otherwise, it is ignored.
 
 This attribute corresponds to the <a
 href="https://www.mapbox.com/mapbox-gl-style-spec/#paint-line-dasharray"><code>line-dasharray</code></a>
 layout property in the Mapbox Style Specification.
 
 You can set this property to an expression containing any of the following:
 
 * Constant array values no less than 0
 * Predefined functions, including mathematical and string operators
 * Conditional expressions
 * Variable assignments and references to assigned variables
 * Step functions applied to the `$zoomLevel` variable
 
 This property does not support applying interpolation functions to the
 `$zoomLevel` variable or applying interpolation or step functions to feature
 attributes.
 */
@property (nonatomic, null_resettable) NSExpression *lineDashPattern;

/**
 The transition affecting any changes to this layer’s `lineDashPattern` property.

 This property corresponds to the `line-dasharray-transition` property in the style JSON file format.
*/
@property (nonatomic) DingiTransition lineDashPatternTransition;

@property (nonatomic, null_resettable) NSExpression *lineDasharray __attribute__((unavailable("Use lineDashPattern instead.")));

/**
 Draws a line casing outside of a line's actual path. Value indicates the width
 of the inner gap.
 
 This property is measured in points.
 
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
@property (nonatomic, null_resettable) NSExpression *lineGapWidth;

/**
 The transition affecting any changes to this layer’s `lineGapWidth` property.

 This property corresponds to the `line-gap-width-transition` property in the style JSON file format.
*/
@property (nonatomic) DingiTransition lineGapWidthTransition;

#if TARGET_OS_IPHONE
/**
 The color gradient with which the line will be drawn. This property only has an
 effect on lines defined by an `DingiShapeSource` whose
 `DingiShapeSourceOptionLineDistanceMetrics` option is set to `YES`.
 
 This property is only applied to the style if `lineDasharray` is set to `nil`,
 and `linePattern` is set to `nil`, and the data source requirements are met.
 Otherwise, it is ignored.
 
 You can set this property to an expression containing any of the following:
 
 * Constant `UIColor` values
 * Predefined functions, including mathematical and string operators
 * Conditional expressions
 * Variable assignments and references to assigned variables
 * Interpolation and step functions applied to the `$lineProgress` variable
 
 This property does not support applying interpolation or step functions to
 feature attributes.
 */
@property (nonatomic, null_resettable) NSExpression *lineGradient;
#else
/**
 The color gradient with which the line will be drawn. This property only has an
 effect on lines defined by an `DingiShapeSource` whose
 `DingiShapeSourceOptionLineDistanceMetrics` option is set to `YES`.
 
 This property is only applied to the style if `lineDasharray` is set to `nil`,
 and `linePattern` is set to `nil`, and the data source requirements are met.
 Otherwise, it is ignored.
 
 You can set this property to an expression containing any of the following:
 
 * Constant `NSColor` values
 * Predefined functions, including mathematical and string operators
 * Conditional expressions
 * Variable assignments and references to assigned variables
 * Interpolation and step functions applied to the `$lineProgress` variable
 
 This property does not support applying interpolation or step functions to
 feature attributes.
 */
@property (nonatomic, null_resettable) NSExpression *lineGradient;
#endif

/**
 The line's offset. For linear features, a positive value offsets the line to
 the right, relative to the direction of the line, and a negative value to the
 left. For polygon features, a positive value results in an inset, and a
 negative value results in an outset.
 
 This property is measured in points.
 
 The default value of this property is an expression that evaluates to the float
 `0`. Set this property to `nil` to reset it to the default value.
 
 You can set this property to an expression containing any of the following:
 
 * Constant numeric values
 * Predefined functions, including mathematical and string operators
 * Conditional expressions
 * Variable assignments and references to assigned variables
 * Interpolation and step functions applied to the `$zoomLevel` variable and/or
 feature attributes
 */
@property (nonatomic, null_resettable) NSExpression *lineOffset;

/**
 The transition affecting any changes to this layer’s `lineOffset` property.

 This property corresponds to the `line-offset-transition` property in the style JSON file format.
*/
@property (nonatomic) DingiTransition lineOffsetTransition;

/**
 The opacity at which the line will be drawn.
 
 The default value of this property is an expression that evaluates to the float
 `1`. Set this property to `nil` to reset it to the default value.
 
 You can set this property to an expression containing any of the following:
 
 * Constant numeric values between 0 and 1 inclusive
 * Predefined functions, including mathematical and string operators
 * Conditional expressions
 * Variable assignments and references to assigned variables
 * Interpolation and step functions applied to the `$zoomLevel` variable and/or
 feature attributes
 */
@property (nonatomic, null_resettable) NSExpression *lineOpacity;

/**
 The transition affecting any changes to this layer’s `lineOpacity` property.

 This property corresponds to the `line-opacity-transition` property in the style JSON file format.
*/
@property (nonatomic) DingiTransition lineOpacityTransition;

/**
 Name of image in style images to use for drawing image lines. For seamless
 patterns, image width must be a factor of two (2, 4, 8, ..., 512).
 
 You can set this property to an expression containing any of the following:
 
 * Constant string values
 * Predefined functions, including mathematical and string operators
 * Conditional expressions
 * Variable assignments and references to assigned variables
 * Interpolation and step functions applied to the `$zoomLevel` variable and/or
 feature attributes
 */
@property (nonatomic, null_resettable) NSExpression *linePattern;

/**
 The transition affecting any changes to this layer’s `linePattern` property.

 This property corresponds to the `line-pattern-transition` property in the style JSON file format.
*/
@property (nonatomic) DingiTransition linePatternTransition;

#if TARGET_OS_IPHONE
/**
 The geometry's offset.
 
 This property is measured in points.
 
 The default value of this property is an expression that evaluates to an
 `NSValue` object containing a `CGVector` struct set to 0 points rightward and 0
 points downward. Set this property to `nil` to reset it to the default value.
 
 This attribute corresponds to the <a
 href="https://www.mapbox.com/mapbox-gl-style-spec/#paint-line-translate"><code>line-translate</code></a>
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
@property (nonatomic, null_resettable) NSExpression *lineTranslation;
#else
/**
 The geometry's offset.
 
 This property is measured in points.
 
 The default value of this property is an expression that evaluates to an
 `NSValue` object containing a `CGVector` struct set to 0 points rightward and 0
 points upward. Set this property to `nil` to reset it to the default value.
 
 This attribute corresponds to the <a
 href="https://www.mapbox.com/mapbox-gl-style-spec/#paint-line-translate"><code>line-translate</code></a>
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
@property (nonatomic, null_resettable) NSExpression *lineTranslation;
#endif

/**
 The transition affecting any changes to this layer’s `lineTranslation` property.

 This property corresponds to the `line-translate-transition` property in the style JSON file format.
*/
@property (nonatomic) DingiTransition lineTranslationTransition;

@property (nonatomic, null_resettable) NSExpression *lineTranslate __attribute__((unavailable("Use lineTranslation instead.")));

/**
 Controls the frame of reference for `lineTranslation`.
 
 The default value of this property is an expression that evaluates to `map`.
 Set this property to `nil` to reset it to the default value.
 
 This property is only applied to the style if `lineTranslation` is non-`nil`.
 Otherwise, it is ignored.
 
 This attribute corresponds to the <a
 href="https://www.mapbox.com/mapbox-gl-style-spec/#paint-line-translate-anchor"><code>line-translate-anchor</code></a>
 layout property in the Mapbox Style Specification.
 
 You can set this property to an expression containing any of the following:
 
 * Constant `DingiLineTranslationAnchor` values
 * Any of the following constant string values:
   * `map`: The line is translated relative to the map.
   * `viewport`: The line is translated relative to the viewport.
 * Predefined functions, including mathematical and string operators
 * Conditional expressions
 * Variable assignments and references to assigned variables
 * Step functions applied to the `$zoomLevel` variable
 
 This property does not support applying interpolation functions to the
 `$zoomLevel` variable or applying interpolation or step functions to feature
 attributes.
 */
@property (nonatomic, null_resettable) NSExpression *lineTranslationAnchor;

@property (nonatomic, null_resettable) NSExpression *lineTranslateAnchor __attribute__((unavailable("Use lineTranslationAnchor instead.")));

/**
 Stroke thickness.
 
 This property is measured in points.
 
 The default value of this property is an expression that evaluates to the float
 `1`. Set this property to `nil` to reset it to the default value.
 
 You can set this property to an expression containing any of the following:
 
 * Constant numeric values no less than 0
 * Predefined functions, including mathematical and string operators
 * Conditional expressions
 * Variable assignments and references to assigned variables
 * Interpolation and step functions applied to the `$zoomLevel` variable and/or
 feature attributes
 */
@property (nonatomic, null_resettable) NSExpression *lineWidth;

/**
 The transition affecting any changes to this layer’s `lineWidth` property.

 This property corresponds to the `line-width-transition` property in the style JSON file format.
*/
@property (nonatomic) DingiTransition lineWidthTransition;

@end

/**
 Methods for wrapping an enumeration value for a style layer attribute in an
 `DingiLineStyleLayer` object and unwrapping its raw value.
 */
@interface NSValue (DingiLineStyleLayerAdditions)

#pragma mark Working with Line Style Layer Attribute Values

/**
 Creates a new value object containing the given `DingiLineCap` enumeration.

 @param lineCap The value for the new object.
 @return A new value object that contains the enumeration value.
 */
+ (instancetype)valueWithDingiLineCap:(DingiLineCap)lineCap;

/**
 The `DingiLineCap` enumeration representation of the value.
 */
@property (readonly) DingiLineCap DingiLineCapValue;

/**
 Creates a new value object containing the given `DingiLineJoin` enumeration.

 @param lineJoin The value for the new object.
 @return A new value object that contains the enumeration value.
 */
+ (instancetype)valueWithDingiLineJoin:(DingiLineJoin)lineJoin;

/**
 The `DingiLineJoin` enumeration representation of the value.
 */
@property (readonly) DingiLineJoin DingiLineJoinValue;

/**
 Creates a new value object containing the given `DingiLineTranslationAnchor` enumeration.

 @param lineTranslationAnchor The value for the new object.
 @return A new value object that contains the enumeration value.
 */
+ (instancetype)valueWithDingiLineTranslationAnchor:(DingiLineTranslationAnchor)lineTranslationAnchor;

/**
 The `DingiLineTranslationAnchor` enumeration representation of the value.
 */
@property (readonly) DingiLineTranslationAnchor DingiLineTranslationAnchorValue;

@end

NS_ASSUME_NONNULL_END
