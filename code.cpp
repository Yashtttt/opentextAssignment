#include <iostream>
#include <fstream>
#include "tinyxml2.h"

using namespace tinyxml2;

int main() {
    XMLDocument xmlDoc;
    
    // Load the XML file
    if (xmlDoc.LoadFile("cd_catalog.xml") != XML_SUCCESS) {
        std::cerr << "Error loading XML file." << std::endl;
        return 1;
    }

    // Create an HTML file
    std::ofstream htmlFile("cd_catalog.html");
    if (!htmlFile.is_open()) {
        std::cerr << "Error creating HTML file." << std::endl;
        return 1;
    }

    // Write the HTML header
    htmlFile << "<!DOCTYPE html>\n";
    htmlFile << "<html>\n<head>\n<title>CD Catalog</title>\n</head>\n<body>\n";
    htmlFile << "<h1>CD Catalog</h1>\n";

    // Get the root element
    XMLElement* rootElement = xmlDoc.RootElement();
    if (rootElement) {
        // Iterate through CD elements
        XMLElement* cdElement = rootElement->FirstChildElement("CD");
        while (cdElement) {
            // Extract CD information
            const char* title = cdElement->FirstChildElement("TITLE")->GetText();
            const char* artist = cdElement->FirstChildElement("ARTIST")->GetText();
            const char* company = cdElement->FirstChildElement("COMPANY")->GetText();
            const char* country = cdElement->FirstChildElement("COUNTRY")->GetText();
            const char* price = cdElement->FirstChildElement("PRICE")->GetText();
            const char* year = cdElement->FirstChildElement("YEAR")->GetText();

            // Write CD information to HTML
            htmlFile << "<p><strong>Title:</strong> " << title << "<br>";
            htmlFile << "<strong>Artist:</strong> " << artist << "<br>";
            htmlFile << "<strong>Company:</strong> " << company << "<br>";
            htmlFile << "<strong>Country:</strong> " << country << "<br>";
            htmlFile << "<strong>Price:</strong> " << price << "<br>";
            htmlFile << "<strong>Year:</strong> " << year << "</p>\n";

            // Move to the next CD element
            cdElement = cdElement->NextSiblingElement("CD");
        }
    }

    // Write the HTML footer
    htmlFile << "</body>\n</html>\n";

    // Close the HTML file
    htmlFile.close();

    std::cout << "Conversion completed. HTML file created: cd_catalog.html" << std::endl;

    return 0;
}
