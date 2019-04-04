//
//  ViewController.swift
//  GoogleMapSDK
//
//  Created by Nafis Islam on 10/3/19.
//  Copyright © 2019 Nafis Islam. All rights reserved.
//

import UIKit
import GoogleMaps

class ViewController: UIViewController {

    override func viewDidLoad() {
        super.viewDidLoad()
        // Do any additional setup after loading the view, typically from a nib.
        let camera = GMSCameraPosition.camera(withLatitude: 23.7925, longitude: 90.4078, zoom: 14.0)
        let mapView = GMSMapView.map(withFrame: CGRect.zero, camera: camera)
        self.view = mapView
    }


}

