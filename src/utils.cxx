#include "utils.h"

using namespace std;

//! check if dir exists, if not - try to create and stop the program in the case of failure
void createDir (boost::filesystem::path dir)
{
  if (not boost::filesystem::exists (dir)) // dir does not exists
    if (not boost::filesystem::create_directory (dir)) // try to create folder
    {
      // stop program if folder could not be created
      cout << "\n\nERROR: could not create " << dir << "\n\n";
      exit (1); 
    }  
}

//! the following convention is assumed: dirs[0] / dirs[1] / dirs[2] / ...
void createPath (const vector <string> &path)
{
  vector <boost::filesystem::path> folders; // list of folders to create

  for (unsigned int i = 0; i < path.size(); i++) // loop over folders in the path
  {
    // fill the string with "dir[0]/dir[1]..."
    string dir;
    for (unsigned int j = 0; j <= i; j++) dir += path[j] + "/";
  
    folders.push_back (dir); // save current path
  }
  
  for (auto &dir : folders) createDir (dir); // loop over folders and create them (starting from base)
}
