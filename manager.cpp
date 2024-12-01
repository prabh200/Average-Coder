#include "manager.h"
#include "maps.h"
#include "graph.h"
std::string man::origin() {
    return destination_prompt("\nPlease enter the origin address: ");
}

std::string man::destination() {
    return destination_prompt("\nPlease enter the destination address: ");
}

std::string man::getName() { // Gets the users name

    std::string username;
    std::cout << "\nPlease enter your name: ";
    std::getline(std::cin, username);

    return username;
}

void main_man::core() {
    // Gets users destination and starting addresses
    std::string origin = man::origin();
    std::string destination = man::destination();

    bool tolls = yes_no_prompt("\nPerform the search with tolls enabled? (Y/N): ");
    bool highways = yes_no_prompt("\nPerform the search with highways enabled? (Y/N): ");

    bool refresh_cache = yes_no_prompt("\nUse the Real-time Data?"
                                       "\n\tY/y for Up-to-date Data but Slow"
                                       "\n\tN/n for Old Data but Fast\n(Y/N): ");

    maps::curl(maps::generateAddress(origin, destination, tolls, highways));
    // std::cout << maps::readRoute();

    // check if you are driving over the seas or jungles
    if (maps::route_fail()) {
        std::cout << "\n\tRoute Error! Google API returned zero results!\n\n";
        return;
    }
    
    std::vector<float> lat = maps::getLat();
    std::vector<float> lng = maps::getLong();

    LatLngMap cache = importhash("./data/cache");
    Graph cache_graph = importgraph("./data/route");

    std::vector<float> edges = maps::edges();
    int top = edges[1];
    int bottom = edges[3];
    int left = edges[2];
    int right = edges[0];

    int width = right - left; //Width is actually height and height is actually width
      // "I can feel the sanity leaving my body" -Elliot
    int height = top - bottom; //I think this breaks in the southern hemisphere.
    if (width * height < 100 * 100){
        //Graph can't be too big.
        std::cout << std::endl;
        std::cout << "--- --- AQI Map --- ---" << std::endl;
        std::cout << "           N \n";
        std::cout << "         W ^ E\n";
        std::cout << "           S " << std::endl;
        
        int nodes[height][width];
        for (int x = 0; x < width; x++){
            for (int y = 0; y < height; y++){
                nodes[y][x] = aqi::getAQI(lat[x], lng[y], cache, refresh_cache);
                std::cout << aqi::aqiPrintChar(nodes[y][x]);
            }
            std::cout << std::endl;
        }
        std::cout << "--- --- --- --- --- ---" << std::endl;
    }

    dataE::queue *messages = maps::getMessages();
    std::cout << std::endl;
    std::cout << "Total distance: " << messages->getItem() << std::endl;
    messages->pop();

    std::cout << "Total time: " << messages->getItem() << std::endl;
    messages->pop();

    std::cout << std::setw(6) << std::right << "\nPlace";
    std::cout << std::setw(10) << std::right << "Lat";
    std::cout << std::setw(10) << std::right << "Long";
    std::cout << std::setw(20) << std::right << "AQI Level";
    std::cout << "\n---------------------------------------------\n";

    for (int i = 0; i < lat.size(); i++) {

        
      if (i % 2 == 0) {
        std::cout << std::endl;
        std::cout << "Distance: " << messages->getItem() << std::endl;
        messages->pop();

        std::cout << "Time: " << messages->getItem() << std::endl;
        messages->pop();

        std::cout << "\t" << messages->getItem() << std::endl;

        messages->pop();
    }

    std::cout << std::setw(6) << std::right << i + 1; // Place
    std::cout << std::setw(10) << std::right << std::fixed
              << std::setprecision(1) << lat[i];
    std::cout << std::setw(10) << std::right << std::fixed
              << std::setprecision(1) << lng[i];
    int aqiValue = aqi::getAQI(lat[i], lng[i], cache, refresh_cache);

    // system(aqi::aqiColor(aqiValue));
    std::cout << std::setw(20) << std::right << aqi::aqiPrint(aqiValue);

    }

    delete messages; //oops i forgor to delete the queue

    cache.exporthash();
}

void main_man::sort_cache_entries() {
    std::cout << "\n\tSorting Cache Data ...";
    
    std::ifstream infile;
    infile.open("./data/cache");

    if (infile.fail()) {
        std::cout << "No Cache data.\n";
        return;
    }

    std::vector<std::string> cache_data;

    std::string entry = "";
    while (!infile.eof()) {
        std::getline(infile, entry);
        if (entry != "") {
            cache_data.push_back(entry);
        }
    }

    infile.close();

    quicksort(cache_data);

    std::ofstream outfile;
    outfile.open("./data/cache");

    while (cache_data.size() != 0) {
        outfile << cache_data.back() << std::endl;
        cache_data.pop_back();
    }

    outfile.close();

    std::cout << " Done\n\n";
}