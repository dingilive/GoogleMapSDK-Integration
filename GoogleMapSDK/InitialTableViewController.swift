//
//  InitialTableViewController.swift
//  GoogleMapSDK
//
//  Created by Nafis Islam on 3/4/19.
//  Copyright © 2019 Nafis Islam. All rights reserved.
//

import UIKit

class InitialTableViewController: UITableViewController{
 

    @IBOutlet var tableview: UITableView!
    var selectedSDK = 0
    let headerTitle = ["Map Types", "Search", "Navigation"]
    let cellTitle = [
        ["GoogleMap SDK", "DingiMap SDK"],
        ["Reverse Geocoding", "Reverse LandMark", "AutoComplete Search", "Address Search"],
        ["Navigation Driving/Walking"]
    ]
    let nameViewController = [
        [],
        ["ReverseGeocodingViewController", "ReverseLandMarkViewController", "AutoCompleteSearchViewController", "AddressSearchViewController"],
        ["NavigationViewController"]
    ]
//    let cellTitle = ["Reverse Geocoding", "Reverse LandMark", "AutoComplete Search", "A]
    let rowNumber = [2, 4, 1]
    var initialLoad = true
    
    
    override func viewDidLoad() {
        super.viewDidLoad()
        // Uncomment the following line to preserve selection between presentations
        // self.clearsSelectionOnViewWillAppear = false

        // Uncomment the following line to display an Edit button in the navigation bar for this view controller.
        
    }
    

    // MARK: - Table view data source

    override func numberOfSections(in tableView: UITableView) -> Int {
        // #warning Incomplete implementation, return the number of sections
        
        return 3
    }

    override func tableView(_ tableView: UITableView, numberOfRowsInSection section: Int) -> Int {
        // #warning Incomplete implementation, return the number of rows
        return rowNumber[section]
    }

    
    override func tableView(_ tableView: UITableView, cellForRowAt indexPath: IndexPath) -> UITableViewCell {
        let cell = tableView.dequeueReusableCell(withIdentifier: "reuseIdentifier", for: indexPath)
        
        cell.textLabel?.text = cellTitle[indexPath.section][indexPath.row]
        if indexPath.section == 0 && indexPath.row == 0{
            if initialLoad == true{
                cell.accessoryType = .checkmark
                initialLoad = false
            }
        }
        if indexPath.section > 0{
            cell.accessoryType = .disclosureIndicator
        }
        return cell
    }
    
    override func tableView(_ tableView: UITableView, heightForHeaderInSection section: Int) -> CGFloat {
        return 50
    }
    
    override func tableView(_ tableView: UITableView, titleForHeaderInSection section: Int) -> String? {
        return headerTitle[section]
    }
    
    override func tableView(_ tableView: UITableView, didSelectRowAt indexPath: IndexPath) {
        tableview.deselectRow(at: indexPath, animated: true)
        print(indexPath.section)
        print(indexPath.row)
        if indexPath.section == 0{ 
            selectedSDK = indexPath.row
            tableView.cellForRow(at: indexPath)?.accessoryType = .checkmark
            for a in tableView.indexPathsForVisibleRows!{
                if a != indexPath{
                    tableView.cellForRow(at: a)?.accessoryType = .none
                }
            }
        }
        else{
            var viewControllerName = nameViewController[indexPath.section][indexPath.row]
            if selectedSDK == 1{
                viewControllerName = "Dingi\(viewControllerName)"
            }
            let viewcontroller = UIStoryboard(name: "Main", bundle: nil).instantiateViewController(withIdentifier: viewControllerName)
            self.navigationController?.pushViewController(viewcontroller, animated: true)
        }
        
    }
 

    /*
    // Override to support conditional editing of the table view.
    override func tableView(_ tableView: UITableView, canEditRowAt indexPath: IndexPath) -> Bool {
        // Return false if you do not want the specified item to be editable.
        return true
    }
    */

    /*
    // Override to support editing the table view.
    override func tableView(_ tableView: UITableView, commit editingStyle: UITableViewCell.EditingStyle, forRowAt indexPath: IndexPath) {
        if editingStyle == .delete {
            // Delete the row from the data source
            tableView.deleteRows(at: [indexPath], with: .fade)
        } else if editingStyle == .insert {
            // Create a new instance of the appropriate class, insert it into the array, and add a new row to the table view
        }    
    }
    */

    /*
    // Override to support rearranging the table view.
    override func tableView(_ tableView: UITableView, moveRowAt fromIndexPath: IndexPath, to: IndexPath) {

    }
    */

    /*
    // Override to support conditional rearranging of the table view.
    override func tableView(_ tableView: UITableView, canMoveRowAt indexPath: IndexPath) -> Bool {
        // Return false if you do not want the item to be re-orderable.
        return true
    }
    */

    /*
    // MARK: - Navigation

    // In a storyboard-based application, you will often want to do a little preparation before navigation
    override func prepare(for segue: UIStoryboardSegue, sender: Any?) {
        // Get the new view controller using segue.destination.
        // Pass the selected object to the new view controller.
    }
    */

}
