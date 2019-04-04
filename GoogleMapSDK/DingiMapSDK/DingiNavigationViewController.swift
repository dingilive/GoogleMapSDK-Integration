//
//  NavigationViewController.swift
//  GoogleMapSDK
//
//  Created by Nafis Islam on 10/3/19.
//  Copyright © 2019 Nafis Islam. All rights reserved.
//

import UIKit
import GoogleMaps
import CoreLocation
import SwiftyJSON
import CoreLocation
import DingiMap

class MyCustomPointAnnotation: DingiPointAnnotation {
    var willUseImage: Bool = false
}

class DingiNavigationViewController: UIViewController, DingiMapViewDelegate, CLLocationManagerDelegate, SearchDelegate {
    func returnFromSearchResult(result: JSON) {
        print("after return")
        print(isnavFromSelected)
        if isnavFromSelected{
            SourceLocation = result
            SourceButton.setTitle(SourceLocation!["name"].stringValue, for: .normal)
        }
        else{
            DestLocation = result
            DestinationButton.setTitle(DestLocation!["name"].stringValue, for: .normal)
            if SourceLocation == nil{
                SourceLocation = JSON(["name":"Your Current Location", "location": [lastLocation.coordinate.latitude, lastLocation.coordinate.longitude]])
            }
        }
        
        callResultApi()
    }
    
    
    @IBAction func swapPressed(_ sender: Any) {
        
        let temp = SourceLocation
        SourceLocation = DestLocation
        DestLocation = temp
        SourceButton.setTitle(SourceLocation!["name"].stringValue, for: .normal)
        DestinationButton.setTitle(DestLocation!["name"].stringValue, for: .normal)
        callResultApi()
    }
    
    @objc func animatePolylinePath() {
//        if (self.i < self.path.count()) {
//            self.animationPath.add(self.path.coordinate(at: self.i))
//            self.animationPolyline.path = self.animationPath
//            self.animationPolyline.strokeColor = UIColor.black
//            self.animationPolyline.strokeWidth = 3
//            self.animationPolyline.map = self.mapView
//            self.i += 1
//        }
//        else {
//            self.i = 0
//            self.animationPath = GMSMutablePath()
//            self.animationPolyline.map = nil
//        }
    }
    
    func callResultApi(){
        if SourceLocation == nil || DestLocation == nil{
            return
        }
        
        let url = URL(string: "https://api.dingi.live/maps/v2/navigation/\(mode)/?steps=false&criteria=both&coordinates=\(SourceLocation!["location"][1])a\(SourceLocation!["location"][0])b\(DestLocation!["location"][1])a\(DestLocation!["location"][0])&language=en")
        var urlRequest = URLRequest(url: url!)
        urlRequest.httpMethod = "GET"
        urlRequest.setValue("ru7KPUg2Wj17lRGdT1mTn9fCbYYSI2Ojaop8iwB5", forHTTPHeaderField: "x-api-key")
        URLSession.shared.dataTask(with: urlRequest) { (data, response, err) in
            do{
                self.Result = try
                    JSONDecoder().decode(NavigationModel.self, from: data!)
                let temp = Polyline(encodedPolyline: (self.Result!.routes.first?.geometry)!, encodedLevels: nil, precision: 1e6)
                let alt_temp = Polyline(encodedPolyline: (self.Result!.routes.last?.geometry)!, encodedLevels: nil, precision: 1e6)
              
           
                if self.mapView.style?.layer(withIdentifier: "polyline_layer") != nil{
                    self.mapView.style?.removeLayer((self.mapView.style?.layer(withIdentifier: "polyline_layer"))!)
                }
                
                if self.mapView.style?.source(withIdentifier: "polyline_source") != nil{
                    self.mapView.style?.removeSource((self.mapView.style?.source(withIdentifier: "polyline_source"))!)
                }
                if self.mapView.style?.layer(withIdentifier: "alt_polyline_layer") != nil{
                    self.mapView.style?.removeLayer((self.mapView.style?.layer(withIdentifier: "alt_polyline_layer"))!)
                }
                
                if self.mapView.style?.source(withIdentifier: "alt_polyline_source") != nil{
                    self.mapView.style?.removeSource((self.mapView.style?.source(withIdentifier: "alt_polyline_source"))!)
                }
                var coordinates: [CLLocationCoordinate2D] = []
                var alt_coordinates: [CLLocationCoordinate2D] = []
                for point in temp.coordinates!
                {
                    coordinates.append(point)
                }
                for point in alt_temp.coordinates!
                {
                    alt_coordinates.append(point)
                }
                let polyline = DingiPolylineFeature(coordinates: &coordinates, count: UInt(coordinates.count))
                let source = DingiShapeSource(identifier: "polyline_source", shape: polyline, options: nil)
                self.mapView.style!.addSource(source)
                
                let alt_polyline = DingiPolylineFeature(coordinates: &alt_coordinates, count: UInt(alt_coordinates.count))
                let alt_source = DingiShapeSource(identifier: "alt_polyline_source", shape: alt_polyline, options: nil)
                self.mapView.style!.addSource(alt_source)
                
                if self.mode == "walking"{
                    DispatchQueue.main.async {
                        let layer = DingiLineStyleLayer(identifier: "polyline_layer", source: source)
                        layer.lineJoin = NSExpression(forConstantValue: "round")
                        layer.lineCap = NSExpression(forConstantValue: "round")
                        layer.lineColor = NSExpression(forConstantValue: UIColor.blue)
                        layer.lineDashPattern = NSExpression(forConstantValue:  [0.25, 1.5] )
                        
                        // The line width should gradually increase based on the zoom level.
                        layer.lineWidth = NSExpression(format: "mgl_interpolate:withCurveType:parameters:stops:($zoomLevel, 'linear', nil, %@)",
                                                       [14: 5, 18: 15])
                        self.mapView.style!.addLayer(layer)
                        self.mapView.setVisibleCoordinateBounds(polyline.overlayBounds, edgePadding: UIEdgeInsets(top: 20, left: 20, bottom: 20, right: 20), animated: true)
                    }

                }
                else{
                    DispatchQueue.main.async {
                        let layer = DingiLineStyleLayer(identifier: "polyline_layer", source: source)
                        layer.lineJoin = NSExpression(forConstantValue: "round")
                        layer.lineCap = NSExpression(forConstantValue: "round")
                        layer.lineColor = NSExpression(forConstantValue: UIColor.black)
                        
                        // The line width should gradually increase based on the zoom level.
                        layer.lineWidth = NSExpression(format: "mgl_interpolate:withCurveType:parameters:stops:($zoomLevel, 'linear', nil, %@)",
                                                       [14: 5, 18: 12])
                        self.mapView.style!.addLayer(layer)
                        
                        let alt_layer = DingiLineStyleLayer(identifier: "alt_polyline_layer", source: alt_source)
                        alt_layer.lineJoin = NSExpression(forConstantValue: "round")
                        alt_layer.lineCap = NSExpression(forConstantValue: "round")
                        alt_layer.lineColor = NSExpression(forConstantValue: UIColor(red: 0, green: 0, blue: 0, alpha: 0.5))
                        
                        // The line width should gradually increase based on the zoom level.
                        alt_layer.lineWidth = NSExpression(format: "mgl_interpolate:withCurveType:parameters:stops:($zoomLevel, 'linear', nil, %@)",
                                                           [14: 5, 18: 12])
                        self.mapView.style!.addLayer(alt_layer)
                        self.mapView.setVisibleCoordinateBounds(polyline.overlayBounds, edgePadding: UIEdgeInsets(top: 20, left: 20, bottom: 20, right: 20), animated: true)
                    }

                }
                self.ShowTime()
                
                
            } catch let jsonErr{
                print("Json parse error: ", jsonErr)
            }
            }.resume()
    }
    
    
    func ShowTime(){
        
        DispatchQueue.main.async {
            let marker = MyCustomPointAnnotation()
            marker.coordinate = CLLocationCoordinate2D(latitude: self.DestLocation!["location"][0].doubleValue, longitude: self.DestLocation!["location"][1].doubleValue)
            marker.title = self.DestLocation!["name"].stringValue
            marker.subtitle = self.secondsToHoursMinutesSeconds(seconds: Int((self.Result!.routes.first?.time)!))
            marker.willUseImage = true
            self.mapView.addAnnotation(marker)
            self.mapView.selectAnnotation(marker, animated: true)
        }
    }

    
    var lastLocation: CLLocation!
    let locationMgr = CLLocationManager()
    var isnavFromSelected = false
    var SourceLocation: JSON?
    var DestLocation:JSON?
    var Result: NavigationModel?
    @IBOutlet var SourceButton: UIButton!
    @IBOutlet var DestinationButton: UIButton!
    @IBOutlet var DriveButton: UIButton!
    @IBOutlet var WalkButton: UIButton!
    @IBOutlet var mapView: DingiMapView!
    var animationPath = GMSMutablePath()
    var polyline = GMSPolyline()
    var animationPolyline = GMSPolyline()
    var path = GMSMutablePath()
    var alt_path = GMSMutablePath()
    var alt_polyline = GMSPolyline()
    var mode = "driving"
    var i: UInt = 0
    var timer: Timer!
    
    @IBAction func SourcePressed(_ sender: Any) {
        
        print("nav from pressed")
        isnavFromSelected = true
        let viewController = UIStoryboard(name: "Main", bundle: nil).instantiateViewController(withIdentifier: "SearchTableViewController") as! UINavigationController
        if (viewController.viewControllers.count > 0) {
            let secondViewcontroller = viewController.viewControllers.first as! SearchPlaceViewController
            secondViewcontroller.delegate = self
            
        }
        self.present(viewController, animated: true, completion: nil)
        
    }
    
    @IBAction func DestinationPressed(_ sender: Any) {
        
        print("nav to pressed")
        isnavFromSelected = false
        //        if sourceStation == nil{
        //            Toast(text: Localization("selectfromfirst"), duration: Delay.short).show()
        //            return
        //        }
        let viewController = UIStoryboard(name: "Main", bundle: nil).instantiateViewController(withIdentifier: "SearchTableViewController") as! UINavigationController
        if (viewController.viewControllers.count > 0) {
            let secondViewcontroller = viewController.viewControllers.first as! SearchPlaceViewController
            secondViewcontroller.delegate = self
            
        }
        self.present(viewController, animated: true, completion: nil)
        
    }
    
    
    @IBAction func DrivePressed(_ sender: Any) {
        mode = "driving"
        DispatchQueue.main.async {
            self.WalkButton.backgroundColor = .clear
            self.WalkButton.tintColor = .white
            self.WalkButton.setTitleColor(.white, for: .normal)
            self.DriveButton.backgroundColor = .white
            self.DriveButton.tintColor = self.hexStringToUIColor(hex: "#000000")
            self.DriveButton.setTitleColor(self.hexStringToUIColor(hex: "#000000"), for: .normal)
        }
        callResultApi()
        
    }
    
    @IBAction func WalkPressed(_ sender: Any) {
        mode = "walking"
        DispatchQueue.main.async {
            self.DriveButton.backgroundColor = .clear
            self.DriveButton.tintColor = .white
            self.DriveButton.setTitleColor(.white, for: .normal)
            self.WalkButton.tintColor = self.hexStringToUIColor(hex: "#000000")
            self.WalkButton.setTitleColor(self.hexStringToUIColor(hex: "#000000"), for: .normal)
            self.WalkButton.backgroundColor = .white
        }
        callResultApi()
        
    }
    
    override func viewDidLoad() {
        super.viewDidLoad()
        
        mapView.setCenter(CLLocationCoordinate2D(latitude: 23.7925, longitude: 90.4078), zoomLevel: 12, animated: false)
        mapView.delegate = self
        mapView.showsUserLocation = true
        let driveImage = UIImage(named: "car_poi_detail")
        let tintedImage = driveImage?.withRenderingMode(.alwaysTemplate)
        DriveButton.setImage(tintedImage, for: .normal)
        self.DriveButton.tintColor = hexStringToUIColor(hex: "#000000")
        self.DriveButton.setTitleColor(hexStringToUIColor(hex: "#000000"), for: .normal)
        self.DriveButton.backgroundColor = .white
        
        let walkImage = UIImage(named: "walk_poi_detail")
        let walktintedImage = walkImage?.withRenderingMode(.alwaysTemplate)
        WalkButton.setImage(walktintedImage, for: .normal)
        WalkButton.titleLabel?.textColor = .white
        WalkButton.tintColor = .white
        
        locationMgr.delegate = self
        locationMgr.startUpdatingLocation()
        
        let status  = CLLocationManager.authorizationStatus()
        if status == .notDetermined {
            locationMgr.requestWhenInUseAuthorization()
            return
        }
    }
    
    override func viewWillDisappear(_ animated: Bool) {
        if self.timer != nil{
            self.timer.invalidate()
        }
        
    }
    
    func mapView(_ mapView: DingiMapView, imageFor annotation: DingiAnnotation) -> DingiAnnotationImage? {
        
        if let castAnnotation = annotation as? MyCustomPointAnnotation {
            if (!castAnnotation.willUseImage) {
                return nil
            }
        }
        
        // For better performance, always try to reuse existing annotations.
        var annotationImage = mapView.dequeueReusableAnnotationImage(withIdentifier: "uber")
        
        
        // If there is no reusable annotation image available, initialize a new one.
        if(annotationImage == nil) {
            annotationImage = DingiAnnotationImage(image: UIImage(named: "uber")!, reuseIdentifier: "uber")
            
        }
        
        return annotationImage
    }
    
    func mapView(_ mapView: DingiMapView, annotationCanShowCallout annotation: DingiAnnotation) -> Bool {
        // Always allow callouts to popup when annotations are tapped.
        return true
    }
    
    func locationManager(_ manager: CLLocationManager, didUpdateLocations locations: [CLLocation]) {
        let currentLocation = locations.last!
        lastLocation = locations.last!
        print("Current location: \(currentLocation)")
    }
    
    func locationManager(_ manager: CLLocationManager, didFailWithError error: Error) {
        print("Error \(error)")
    }
    
    func hexStringToUIColor (hex:String) -> UIColor {
        var cString:String = hex.trimmingCharacters(in: .whitespacesAndNewlines).uppercased()
        
        if (cString.hasPrefix("#")) {
            cString.remove(at: cString.startIndex)
        }
        
        if ((cString.count) != 6) {
            return UIColor.gray
        }
        
        var rgbValue:UInt32 = 0
        Scanner(string: cString).scanHexInt32(&rgbValue)
        return UIColor(
            red: CGFloat((rgbValue & 0xFF0000) >> 16) / 255.0,
            green: CGFloat((rgbValue & 0x00FF00) >> 8) / 255.0,
            blue: CGFloat(rgbValue & 0x0000FF) / 255.0,
            alpha: CGFloat(1.0)
        )
    }
    
    func secondsToHoursMinutesSeconds (seconds : Int) -> String {
        let hour = String(seconds/3600)
        let min  = String(((seconds % 3600) / 60) + 1)
        var ans = ""
        if (hour != "0"){
            ans += String(hour) + " " + "h" + " "
        }
        if (min != "0"){
            ans += String(min) + " " + "min" + " "
        }
        return ans
    }
    
}

