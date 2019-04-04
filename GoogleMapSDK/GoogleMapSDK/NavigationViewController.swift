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

class NavigationViewController: UIViewController, GMSMapViewDelegate, CLLocationManagerDelegate, SearchDelegate {
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
        if (self.i < self.path.count()) {
            self.animationPath.add(self.path.coordinate(at: self.i))
            self.animationPolyline.path = self.animationPath
            self.animationPolyline.strokeColor = UIColor.black
            self.animationPolyline.strokeWidth = 3
            self.animationPolyline.map = self.mapView
            self.i += 1
        }
        else {
            self.i = 0
            self.animationPath = GMSMutablePath()
            self.animationPolyline.map = nil
        }
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

                self.path.removeAllCoordinates()
                self.alt_path.removeAllCoordinates()
                self.animationPath.removeAllCoordinates()
                for point in temp.coordinates!
                {
                    self.path.add(point)
                }
                for point in alt_temp.coordinates!
                {
                    self.alt_path.add(point)
                }
                if self.timer != nil{
                    self.timer.invalidate()
                }
                self.i = 0
                
                if self.mode == "walking"{
                    DispatchQueue.main.async {
                        self.polyline = GMSPolyline(path: self.path)
                        self.drawWalking()
                        let bounds = GMSCoordinateBounds(path: self.path)
                        let cameraUpdate = GMSCameraUpdate.fit(bounds)
                        self.mapView.moveCamera(cameraUpdate)
                    }
                }
                else{
                    DispatchQueue.main.async {
                        self.mapView.clear()
                        self.polyline = GMSPolyline(path: self.path)
                        self.polyline.strokeColor = UIColor(red: 0, green: 0, blue: 0, alpha: 0.5)
                        self.polyline.strokeWidth = 3
                        self.polyline.map = self.mapView
                        
                        self.alt_polyline = GMSPolyline(path: self.alt_path)
                        self.alt_polyline.strokeWidth = 3
                        let styles = [GMSStrokeStyle.solidColor(UIColor(red: CGFloat(0), green: CGFloat(0), blue: CGFloat(0), alpha: CGFloat(0.5))), GMSStrokeStyle.solidColor(UIColor.clear)]
                        let lengths = [10,10]
                        self.alt_polyline.spans = GMSStyleSpans(self.alt_polyline.path!, styles, lengths as [NSNumber], .rhumb);
                        self.alt_polyline.map = self.mapView
                        let bounds = GMSCoordinateBounds(path: self.path)
                        let cameraUpdate = GMSCameraUpdate.fit(bounds)
                        self.mapView.moveCamera(cameraUpdate)
                        self.timer = Timer.scheduledTimer(timeInterval: 0.0009, target: self, selector: #selector(self.animatePolylinePath), userInfo: nil, repeats: true)
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
            let marker = GMSMarker(position: CLLocationCoordinate2D(latitude: self.DestLocation!["location"][0].doubleValue, longitude: self.DestLocation!["location"][1].doubleValue))
            marker.snippet = self.DestLocation!["name"].stringValue
            marker.map = self.mapView
            marker.icon = UIImage(named: "uber")
            self.mapView.selectedMarker = marker
        }
    }
    func drawWalking(){
        guard let path = polyline.path else {
            return
        }
        self.mapView.clear()
        let intervalDistanceIncrement: CGFloat = 10
        let circleRadiusScale = 1 / mapView.projection.points(forMeters: 1, at: mapView.camera.target)
        var previousCircle: GMSCircle?
        for coordinateIndex in 0 ..< path.count() - 1 {
            let startCoordinate = path.coordinate(at: coordinateIndex)
            let endCoordinate = path.coordinate(at: coordinateIndex + 1)
            let startLocation = CLLocation(latitude: startCoordinate.latitude, longitude: startCoordinate.longitude)
            let endLocation = CLLocation(latitude: endCoordinate.latitude, longitude: endCoordinate.longitude)
            let pathDistance = endLocation.distance(from: startLocation)
            let intervalLatIncrement = (endLocation.coordinate.latitude - startLocation.coordinate.latitude) / pathDistance
            let intervalLngIncrement = (endLocation.coordinate.longitude - startLocation.coordinate.longitude) / pathDistance
            for intervalDistance in 0 ..< Int(pathDistance) {
                let intervalLat = startLocation.coordinate.latitude + (intervalLatIncrement * Double(intervalDistance))
                let intervalLng = startLocation.coordinate.longitude + (intervalLngIncrement * Double(intervalDistance))
                let circleCoordinate = CLLocationCoordinate2D(latitude: intervalLat, longitude: intervalLng)
                if let previousCircle = previousCircle {
                    let circleLocation = CLLocation(latitude: circleCoordinate.latitude,
                                                    longitude: circleCoordinate.longitude)
                    let previousCircleLocation = CLLocation(latitude: previousCircle.position.latitude,
                                                            longitude: previousCircle.position.longitude)
                    if mapView.projection.points(forMeters: circleLocation.distance(from: previousCircleLocation),
                                                 at: mapView.camera.target) < intervalDistanceIncrement {
                        continue
                    }
                }
                let circleRadius = 2 * CLLocationDistance(circleRadiusScale)
                let circle = GMSCircle(position: circleCoordinate, radius: circleRadius)
                circle.fillColor = self.hexStringToUIColor(hex: "#4b8fff")
                circle.strokeColor = .blue
                circle.strokeWidth = 2
                circle.map = mapView
                previousCircle = circle
            }
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
    @IBOutlet var mapView: GMSMapView!
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
        let camera = GMSCameraPosition.camera(withLatitude: 23.7925, longitude: 90.4078, zoom: 14)
        mapView.camera = camera
        mapView.delegate = self
        mapView.isMyLocationEnabled = true
        
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
    
    func mapView(_ mapView: GMSMapView, markerInfoWindow marker: GMSMarker) -> UIView? {
        let view = UIView(frame: CGRect.init(x: 0, y: 0, width: 250, height: 40))
        view.backgroundColor = UIColor.white
        
        let view1 = UIView(frame: CGRect.init(x: 0, y: 0, width: 100, height: 40))
        view1.backgroundColor = .black
        let lbl1 = UILabel(frame: CGRect.init(x: 0, y: 0, width: 100, height: 40))
        lbl1.text = secondsToHoursMinutesSeconds(seconds: Int((self.Result!.routes.first?.time)!))
        lbl1.textColor = .white
        lbl1.textAlignment = .center
        view1.addSubview(lbl1)
        
        let lbl2 = UILabel(frame: CGRect.init(x: 100, y: 0, width: 150, height: 40))
        lbl2.text = DestLocation!["name"].stringValue
        lbl2.textColor = .black
        lbl2.textAlignment = .center
        view1.addSubview(lbl1)
        
        view.addSubview(view1)
        view.addSubview(lbl2)
        
        return view
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

