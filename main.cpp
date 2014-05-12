// $Id: main.cpp,v 1.4 2014-04-24 18:14:51-07 - - $

#include <cstdlib>
#include <exception>
#include <iostream>
#include <string>
#include <unistd.h>
#include <fstream>

//TODO delete this later
//#include <stdio.h>

using namespace std;

#include "listmap.h"
#include "xpair.h"
#include "util.h"

typedef xpair<string,string> str_str_pair;
typedef listmap<string,string> str_str_map;


void scan_options (int argc, char** argv) {

   opterr = 0;
   for (;;) {
      int option = getopt (argc, argv, "@:");
      if (option == -1) break;
      switch (option) {
         case '@':
            traceflags::setflags (optarg);
            break;
         default:
            complain() << "-" << (char) optopt << ": invalid option"
                       << endl;
            break;
      }
   }
}


void trim(string *line)
{
    //Trim White Space:
    //found_white_space holds position of first instance of whitespace
    size_t found_white_space = line->find_first_of(" ");

    //goes through the line and erases all whitespace
    while(found_white_space!=std::string::npos)
    {
        line->erase(found_white_space, 1);
        found_white_space = line->find_first_of(" ");
    }
}

int main (int argc, char** argv) {
   sys_info::set_execname (argv[0]);
   scan_options (argc, argv);

   str_str_map *the_map = new str_str_map();
   for (int argi = 0; argi < argc; ++argi) {

      //line will be the current line from the file.
      string line;
      ifstream myfile (argv[argi]);
      if (myfile.is_open())
      {
            //reads in from the file line by line
            while ( getline (myfile,line) )
            {
                //if the first char is a # it's a comment and is ignored
                if(line[0]=='#')
                    continue;

                trim(&line);

                //found holds position of the first equals sign
                size_t found = line.find_first_of("=");

                if(found == std::string::npos)
                {
                    auto itor=the_map->find(line);
                    if(line == itor->first)
                        cout << "<" << itor->first << "," << itor->second << ">" << endl;
                    else
                        cout << line << ": key not found" << endl;

                    continue;
                }

                //split up line around the '=' to make two strings, key and value
                string key = line.substr(0,found-1);

                if(found=line.size()-1)
                {
                    the_map->erase(key);
                }

                string value = line.substr(found+1);

                //construct a new pair using key and value and insert it into the map
                str_str_pair *insert_pair = new str_str_pair(key, value);
                the_map->insert (*insert_pair);
            }

            myfile.close();
      }

  else cout << "Unable to open file";


   }

   for (str_str_map::iterator itor = the_map->begin();
        itor != the_map->end(); ++itor) {
      cout << "During iteration: " << *itor << endl;
   }

   str_str_map::iterator itor = the_map->begin();
   itor.erase();

   cout << "EXIT_SUCCESS" << endl;
   return EXIT_SUCCESS;
}

