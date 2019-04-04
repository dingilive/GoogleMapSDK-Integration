//
//  ReverseGeocodingViewController.swift
//  GoogleMapSDK
//
//  Created by Nafis Islam on 10/3/19.
//  Copyright © 2019 Nafis Islam. All rights reserved.
//

import UIKit
import GoogleMaps
import SwiftyJSON
import AudioToolbox

class ReverseGeocodingViewController: UIViewController, GMSMapViewDelegate, UITextFieldDelegate {
    
    var mapView: GMSMapView?
    var sampleTextField: UITextField!
    var mapType = 0
    var json: JSON!

    override func viewDidLoad() {
        super.viewDidLoad()

        let camera = GMSCameraPosition.camera(withLatitude: 23.7925, longitude: 90.4078, zoom: 14.0)
        mapView = GMSMapView.map(withFrame: CGRect.zero, camera: camera)
        mapView!.delegate = self
        self.view = mapView
        
        sampleTextField =  UITextField(frame: CGRect(x: 20, y: 80, width: UIScreen.main.bounds.width - 32.0, height: 50))
        sampleTextField.font = UIFont.systemFont(ofSize: 15)
        sampleTextField.borderStyle = UITextField.BorderStyle.roundedRect
        sampleTextField.autocorrectionType = UITextAutocorrectionType.no
        sampleTextField.keyboardType = UIKeyboardType.default
        sampleTextField.returnKeyType = UIReturnKeyType.done
        sampleTextField.clearButtonMode = UITextField.ViewMode.whileEditing
        sampleTextField.contentVerticalAlignment = UIControl.ContentVerticalAlignment.center
        sampleTextField.delegate = self
        self.view.addSubview(sampleTextField)
        
        let imageView = UIImageView(image: UIImage(named: "pin.png"))
        imageView.frame = CGRect(x: UIScreen.main.bounds.width/2 - 32, y: UIScreen.main.bounds.height/2 - 64, width: 64, height: 64)
        self.view.addSubview(imageView)
    
    
    }
    

    func mapView(_ mapView: GMSMapView, didTapAt coordinate: CLLocationCoordinate2D) {
        print("You tapped at \(coordinate.latitude), \(coordinate.longitude)")
        callReverseGeocoding(coord: coordinate)
    }
    
    func mapView(_ mapView: GMSMapView, idleAt position: GMSCameraPosition) {
        print("scroll ended")
       
        callReverseGeocoding(coord: mapView.projection.coordinate(for: mapView.center))
    }
    
    func callReverseGeocoding(coord: CLLocationCoordinate2D){

        let url = URL(string: "https://api.dingi.live/maps/v2/reverse/demo?lat=\(coord.latitude)&lng=\(coord.longitude)&address_level=UPTO_THANA")
        var urlRequest = URLRequest(url: url!)
        urlRequest.httpMethod = "GET"
        urlRequest.setValue("ru7KPUg2Wj17lRGdT1mTn9fCbYYSI2Ojaop8iwB5", forHTTPHeaderField: "x-api-key")
        URLSession.shared.dataTask(with: urlRequest) { (data, response, err) in
            do{
                self.json = try JSON(data: data!)
                print(self.json)
                
               /* Sample Response
                 {
                 "addr_comp_en": [
                 "Dhaka",
                 "Dhaka",
                 "Gulshan",
                 "",
                 "Dhaka City",
                 "",
                 ""
                 ],
                 "name_en": "HSIA Bay 12",
                 "addr_en": "HSIA Bay 12, Dhaka City, Gulshan Thana",
                 "addr_bn": "এইচএসআইএ বে ১২, ঢাকা সিটি, গুলশান থানা",
                 "name_bn": "এইচএসআইএ বে ১২",
                 "addr_comp_bn": [
                 "ঢাকা বিভাগ",
                 "ঢাকা জেলা",
                 "গুলশান থানা",
                 "",
                 "ঢাকা সিটি",
                 "",
                 ""
                 ],
                 "location": {
                 "lon": 90.406414,
                 "lat": 23.845147
                 }
                 }
               */
                DispatchQueue.main.async {[weak self] in
                    self!.sampleTextField.text = self?.json["addr_en"].stringValue
                }
   
            } catch let jsonErr{
                print("Json parse error: ", jsonErr)
            }
            }.resume()
    }

}
