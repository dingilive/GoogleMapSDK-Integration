//
//  DingiReverseGeocodingViewController.swift
//  GoogleMapSDK
//
//  Created by Nafis Islam on 3/4/19.
//  Copyright © 2019 Nafis Islam. All rights reserved.
//

import UIKit
import DingiMap
import SwiftyJSON

class DingiReverseGeocodingViewController: UIViewController, UITextFieldDelegate, DingiMapViewDelegate, UIGestureRecognizerDelegate {
    
    var mapView: DingiMapView!
    var json: JSON!
    var sampleTextField: UITextField!

    override func viewDidLoad() {
        super.viewDidLoad()
        
        mapView = DingiMapView(frame: view.bounds)
        mapView.autoresizingMask = [.flexibleWidth, .flexibleHeight]
        mapView.setCenter(CLLocationCoordinate2D(latitude: 23.7925, longitude: 90.4078), zoomLevel: 12, animated: false)
        mapView.delegate = self
        view.addSubview(mapView)
        
        
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
        imageView.frame = CGRect(x: UIScreen.main.bounds.width/2 - 32, y: UIScreen.main.bounds.height/2 - 32, width: 64, height: 64)
        self.view.addSubview(imageView)
        
        let singleTap = UIPanGestureRecognizer(target: self, action: #selector(handlePan(_:)))
        singleTap.delegate = self
        mapView.addGestureRecognizer(singleTap)
        
        // Do any additional setup after loading the view.
    }
    
    func gestureRecognizer(_ gestureRecognizer: UIGestureRecognizer, shouldRecognizeSimultaneouslyWith otherGestureRecognizer: UIGestureRecognizer) -> Bool {
        return true
    }
    
    @objc func handlePan(_ sender: UIPanGestureRecognizer) -> Bool {
        if sender.state == .ended{
            print("scroll ended")
            callReverseGeocoding(coord: mapView.centerCoordinate)
            
        }
        return true
    }
    
    func mapView(_ mapView: DingiMapView, didFinishLoading style: DingiStyle) {
        print("loaded")
        callReverseGeocoding(coord: mapView.centerCoordinate)
    }
    

    
    func callReverseGeocoding(coord: CLLocationCoordinate2D){
        let url = URL(string: "https://api.dingi.live/maps/v2/reverse/demo?lat=\(coord.latitude)&lng=\(coord.longitude)&address_level=UPTO_THANA")
        var urlRequest = URLRequest(url: url!)
        urlRequest.httpMethod = "GET"
        urlRequest.setValue("ru7KPUg2Wj17lRGdT1mTn9fCbYYSI2Ojaop8iwB5", forHTTPHeaderField: "x-api-key")
        URLSession.shared.dataTask(with: urlRequest) { (data, response, err) in
            do{
                self.json = try JSON(data: data!)
                DispatchQueue.main.async {[weak self] in
                    if self!.mapView.annotations != nil{
                        for annotation in (self?.mapView.annotations!)!{
                            self!.mapView.removeAnnotation(annotation)
                        }
                    }
                    self!.sampleTextField.text = self?.json["addr_en"].stringValue
                }
                
                
                
            } catch let jsonErr{
                print("Json parse error: ", jsonErr)
            }
            }.resume()
    }
    

}
