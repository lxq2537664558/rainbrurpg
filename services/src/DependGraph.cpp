/* 
 * server - The RainbruRPG's services binary.
 *
 * Copyright (C) 2014-2015 Jérôme Pasquier
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include <string>
#include <deque>

#include <boost/graph/adjacency_list.hpp>
#include "boost/graph/topological_sort.hpp"
#include <boost/unordered_map.hpp>
#include <boost/foreach.hpp>
#include <boost/graph/graphviz.hpp>

using namespace std;
using namespace boost;

struct Package{
  string wikiname;
};
 
struct Edge{
  string depstring;
};

typedef boost::unordered_map<std::string, int> packages_map;
packages_map packages;
int nextNodeId=0;

int
getPackageId(const std::string& key)
{
  // Create a new node if needed
  if (packages.find(key) == packages.end())
    {
      packages[key] = nextNodeId;
      return nextNodeId++;
    }
  else
    return packages[key];
  
}

void 
print_hash(const packages_map& m)
{
  BOOST_FOREACH(packages_map::value_type i, m) 
    {
      std::cout<<i.first<<","<<i.second<<"\n";
    }
}

typedef adjacency_list<listS, vecS, directedS, Package, Edge> Graph;
typedef Graph::vertex_descriptor PackageID;
typedef Graph::edge_descriptor   EdgeID;
Graph g;
 
void 
add_dependency(const string& d1, const string& op, const string& d2)
{
  int i1 = getPackageId(d1);
  int i2 = getPackageId(d2);
  Edge e;
  e.depstring = op;
  add_edge (i1, i2, e, g);
  g[i1].wikiname = d1;
  g[i2].wikiname = d2;
  
  // g[e].depstring. = op;
}

int main()
{
  add_dependency ( "CoreNetwork", "< 1.25", "CoreCompiler");
  add_dependency ( "CoreGui", "< 1.25", "CoreCompiler");
  add_dependency ( "CoreMenu", "< 1.25", "CoreGui");
  add_dependency ( "CoreMenu", "< 1.25", "CoreCompiler");
   add_dependency ( "CoreCharacters", "< 1.25", "CoreGui");
  add_dependency ( "CoreRaces", "< 1.25", "CoreCharacters");

    //  print_hash(packages);
 
  // Perform a topological sort.
  std::deque<int> topo_order;
  boost::topological_sort(g, std::front_inserter(topo_order));
  

  // Print the results.
  boost::write_graphviz(std::cout, g,
    boost::make_label_writer(boost::get(&Package::wikiname, g)),
    boost::make_label_writer(boost::get(&Edge::depstring, g))
    );

  // Generate a png with dot
  // dot my_file.dot -Tpng -o my_fsm.png

  // see http://www.boost.org/doc/libs/1_42_0/libs/graph/doc/strong_components.html
  // To detect circular references

  return 0;
}
