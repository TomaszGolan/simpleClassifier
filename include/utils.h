/**
 * @brief some helpful functions
 * 
 * @author TG
 * @date 2015
 * 
*/

#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <boost/filesystem.hpp>

void createDir (boost::filesystem::path dir); //!< create a single dir

void createPath (const std::vector <std::string> &path); //!< create folder path

#endif

