/*
 * config_parser.h
 *
 *  Created on: Oct 4, 2024
 *      Author: gizbo89
 */

#ifndef INPUT_CONFIG_PARSER_H_
#define INPUT_CONFIG_PARSER_H_
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/property_tree/detail/file_parser_error.hpp>
#include <iostream>

int parse_config(){
    // Create an empty property tree object
    pt :: ptree tv_tree;

    try {
        read_xml("tv.xml", tv_tree);
    } catch (pt :: xml_parser_error &e) {
        std :: cout << "Failed to parse the xml string." << e.what();
    } catch (...) {
        std :: cout << "Failed !!!";
    }

    // get_child is used to find the node in xml for iterating over its children.
    // Note : get_child throws if the path cannot be resolved.
    for (auto& p : tv_tree.get_child("tv")) {
        std :: cout << "[" << p.first << "]" << std :: endl;
        for (auto& c : p.second) {
            std :: cout << "Tag : [" << c.first.data() << "], ";
            std :: cout << "Value : [" << c.second.data() << "]" << std :: endl;
        }
    }
}



#endif /* INPUT_CONFIG_PARSER_H_ */
